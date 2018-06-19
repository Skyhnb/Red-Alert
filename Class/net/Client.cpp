#include <stdio.h>
#include "Client.h"
#include "OrderCode.h"

int i_ip;        //能正确连接的IP在IP列表里的索引
int i_server;    //server所在的ip地址在IP列表里的索引
int client_mode; //当前客户端运行模式

std::string ipLink;  //能成功建立连接的ip地址字符串
std::string ipNow;  //当前连接的ip地址
std::vector<std::string> ipList; // 所有连接到该网段的IP地址表
std::vector<std::string> serverIpList; // 能连接上的存在服务器的IP地址表

static Client* this_client = nullptr;

void deal_order::handle_connect(const boost::system::error_code& error)
{
	if (!error)
	{
		i_server = i_ip;
		serverIpList.push_back(ipLink);
		boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), Order_Msg::header_length),
			boost::bind(&deal_order::handle_read_header, this, boost::asio::placeholders::error));
	}
}

void deal_order::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		write_msgs_.pop_front();
		if (!write_msgs_.empty())
		{
			boost::asio::async_write(socket_, boost::asio::buffer(write_msgs_.front().data(), write_msgs_.front().length),
				boost::bind(&deal_order::handle_write, this, boost::asio::placeholders::error));

		}
	}
	else {
		do_close();
	}
}

void deal_order::handle_read_header(const boost::system::error_code& error)
{
	if (!error&&read_msg_.decode_header)
	{
		boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length),
			boost::bind(&deal_order::handle_read_body, this, boost::asio::placeholders::error));
	}
	else {
		do_close();
	}
}

void deal_order::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		std::string temp1(read_msg_.body());
		if (temp1 == ipLink)
		{
			i_server = i_ip;
		}
		this_client->t_lock.lock();
		std::string temp(read_msg_.body(), read_msg_.body_length());
	
		this_client->_orderlist.push_back(temp);
		this_client->t_lock.unlock();

		boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), Order_Msg::header_length),
			boost::bind(&deal_order::handle_read_body, this, boost::asio::placeholders::error));

	}
	else {
		do_close();
	}
}

void deal_order::do_write(Order_Msg msg)
{
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);
	if (!write_in_progress)
	{
		boost::asio::async_write(socket_,
			boost::asio::buffer(write_msgs_.front().data(),
				write_msgs_.front().length()),
			boost::bind(&deal_order::handle_write, this,
				boost::asio::placeholders::error));
	}
}

int Client::client()
{
	if (client_mode == 2)
	{
		system("ping -c 1 255.255.255.255");
		system("arp -a > arp.txt");

		std::ifstream in("arp.txt");

		bool start_read = false;
		while (!in.eof())
		{
			std::string temp;
			getline(in, temp);
			if (in.eof()) {
				break;
			}
			if (temp.size() >= 3)
			{
				if (temp[2] == 'I');
				{
					start_read = true;
					continue;
				}
			}
			if (!start_read) {
				continue;
			}
			int i = temp.find(' ', 3);
			temp = temp.substr(2, i - 2);
			ipNow = temp;
			ipList.push_back(temp);
		}
	}

	std::vector<deal_order> d;
	std::vector<boost::thread> t;

	for (int i = 0; i < ipList.size() - 1; i++)
	{
		if (client_mode == 1)
		{
			break;
		}
		if (ipList.size() == 0)
		{
			return 0;
		}

		bool if_fasle = false;
		int count = 0;
		for (int j = 0; j < ipList.at(i).size(); j++)
		{
			if (ipList.at(i).at(j) > '9' || ipList.at(i).at(j) < '0')
			{
				if (ipList.at(i).at(j) != '.')
				{
					if_fasle = true;
					break;
				}

				if (ipList.at(i).at(j) == '.')
				{
					count++;
				}
			}
		}

		if (count != 3 || if_fasle)
		{
			continue;
		}

		boost::asio::io_service service;
		tcp::resolver resolver(service);
		tcp::resolver::query query(ipList.at(i), "8001");
		ipLink = ipList.at(i);
		tcp::resolver::iterator iter = resolver.resolve(query);

		deal_order d_o(service, iter);

		boost::thread t(boost::bind(&boost::asio::io_service::run, &service));

		i_ip = i;

		Sleep(100000);

		d_o.close();
		t.join;

	}
	try
	{
		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);

		std::string ip;
		if (client_mode == 1)
		{
			ip = "115.159.90.65";
		}
		else {
			ip = ipList.at(i_server);
		}
		_is_searched = true;
		tcp::resolver::query query(ip, "8001");
		tcp::resolver::iterator iterator = resolver.resolve(query);

		deal_order a(io_service, iterator);
		_DOInstance = &a;
		this_client = this;

		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
		char line[Order_Msg::max_body_length + 1];

		a.close();
		t.join();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception:" << e.what() << "\n";

	}
	return 0;

}

void Client::runclient(int mode)
{
	client_mode = mode;
	_is_searched = false;
	_filter_mode = false;
	std::thread  t(&Client::client, this);
	t.detach();
}

void Client::send_message(const std::string &code, const std::string &message)
{
	Order_Msg msg;
	std::string temp;
	if (_filter_mode == true && code[0] != ANSWER_FOR_ROOM[0])
	{
		temp.append(order_type.substr(0, 4));
	}
	temp.append(code);
	temp.append(message);
	msg.body_length(temp.size());
	memcpy(msg.body(), temp.c_str(), msg.body_length());
	msg.encode_header();
	_DOInstance->write(msg);

}

std::string Client::pullorder()
{
	t_lock.lock();
	std::string temp;
	if (_orderlist.size() != 0)
	{
//        std::cout << "order list :" << _orderList.front() << std::endl;
		temp = _orderlist.front();
		_orderlist.pop_front();
		if (_filter_mode == true)
		{
			std::string filter_word = temp.substr(0, 4);
			if (filter_word == order_type.substr(0, 4))
			{
				std::string real_order = temp.substr(4, temp.size() - 4);
				temp = real_order;
			}
			else if (temp[0] != FIND_FOR_ROOM[0])
			{
				temp = "no";

			}
		}
	}
	else
	{
		temp = "no";
	}
	t_lock.unlock();

	return temp;

}