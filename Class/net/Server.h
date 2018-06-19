#ifndef _Server_h_
#define _Server_h_

#include "cocos2d.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <set>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <stdio.h>
#include<ostream>
#include"OrderMessage.h"

using namespace boost::asio;
using boost::asio::ip::tcp;
typedef std::deque<Order_Msg> message_queue;
//-----------------------------基类----------------------------------
/*会话类的抽象基类，需要每个子类重载deliver函数
每个客户端跟服务端间形成会话*/
class chat_base
{
public:
	virtual ~chat_base() {}
	virtual void deliver(const Order_Msg &msg);
};

typedef boost:: shared_ptr<chat_base> chat_base_ptr;

//-----------------------------会话房间类----------------------------------

/*会话服务的基类*/
class chat_room
{
public:

	/*向房间内所有会话发送数据*/
	void deliver(const Order_Msg& msg)
	{
		temp_msg_.push_back(msg);
		while (temp_msg_.size() > max_temp_msg)
		{
			temp_msg_.pop_front();
		}
		std::for_each(pars_.begin(), pars_.end(),
			boost::bind(&chat_base::deliver, _1, boost::ref(msg)));
	}

	/*将新加入的会话加入房间并以广播方式发送数据*/
	void join(chat_base_ptr par)
	{
		pars_.insert(par);
		std::for_each(temp_msg_.begin(), temp_msg_.end(),
			boost::bind(&chat_base::deliver, par, _1));
	}

	/*退出的会话将退出房间，不再向其传递数据*/
	void leave(chat_base_ptr par)
	{
		pars_.erase(par);
	}


private:
	std::set<chat_base_ptr>  pars_; //保存房间内所有参与的会话
	message_queue temp_msg_; //保存房间内需要发送的信息

	enum {max_temp_msg=0}; //当前允许存在的最大未发送会话量
};
//------------------------------会话类---------------------------------

/*继承自chat_base*/

class session :public chat_base,public boost::enable_shared_from_this<session>
{
public:

	/*构造会话，此时并未连接和加入房间*/
	session(boost::asio::io_service& service,chat_room room)
		:socket_(service),room_(room)
	{}

	/*返回套接字*/
	tcp::socket& socket()
	{
		return socket_;
	}

	/*启动会话，加入房间*/
	void start()
	{
		room_.join(shared_from_this());
		boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), Order_Msg::header_length),
			boost::bind(
				&session::handle_read_header, shared_from_this(),
				boost::asio::placeholders::error));
	}

	/*将某个客户端收到的消息发送给此会话对应的客户端*/
	void deliver(const Order_Msg& msg)
	{
		bool write_in_progress = !write_msg_.empty();
		write_msg_.push_back(msg);
		if (!write_in_progress)
		{
			boost::asio::async_write(socket_, boost::asio::buffer(write_msg_.front().data(), write_msg_.front().length()),
				boost::bind(&session::handle_write, shared_from_this(), boost::asio::placeholders::error));
		}
	}

	/*接收客户端消息后处理字符串长度*/
	void handle_read_header(const boost::system::error_code& error)
	{
		if (!error&&read_msg_.decode_header())
		{
			boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&session::handle_read_body, shared_from_this(), boost::asio::placeholders::error));

		}
		else {
			room_.leave(shared_from_this());
		}
	}

	/*调用完处理字符串长度的函数后，调用本函数，处理主要数据*/
	void handle_read_body(const boost::system::error_code& error)
	{
		if (!error)
		{
			room_.deliver(read_msg_);
			boost::asio::async_read(socket_, boost::asio::buffer(read_msg_.data(), Order_Msg::header_length),
				boost::bind(&session::handle_read_header, shared_from_this(), boost::asio::placeholders::error));
		}
		else {
			room_.leave(shared_from_this());
		}
	}

	/*发送数据，如有消息未发完递归调用该发送函数*/
	void handle_write(const boost::system::error_code& error)
	{
		if (!error)
		{
			write_msg_.pop_front();
			if (!write_msg_.empty())
			{
				boost::asio::async_write(socket_, boost::asio::buffer(write_msg_.front().data(), write_msg_.front().length()),
					boost::bind(&session::handle_write, shared_from_this(), boost::asio::placeholders::error));
			}
		}
		else {
			room_.leave(shared_from_this());
		}
	}


private:
	tcp::socket socket_; //该会话套接字
	chat_room& room_; //所在房间
	Order_Msg read_msg_; //所读取的信息
	message_queue  write_msg_; //需要发送的数据队列
};

	typedef boost::shared_ptr<session> session_ptr;

//------------------------------server类---------------------------------
	
class server
{
public:

	/*构造服务器，将监听器与端点信息绑定，开始监听客户端的链接，并调用函数处理请求*/
	server(boost::asio::io_service& service, const tcp::endpoint& ep)
		:service_(service), acceptor_(service, ep)
	{
		start_accept();
	}

	/*启动异步操作，接受连接，创建会话*/
	void start_accept()
	{
		session_ptr new_(new session(service_, room_));
		acceptor_.async_accept(new_->socket(),
			boost::bind(&server::handle_accept, this, new_, boost::asio::placeholders::error));
	}

	/*处理接受，将新的会话加入room，开始读取来自异步客户端的信息*/
	void handle_accept(session_ptr session, const boost::system::error_code& error)
	{
		if (!error)
		{
			session->start();
		}
		start_accept();
	}

private:
	boost::asio::io_service& service_; //执行异步操作的对象（全局只产生一个）
	tcp::acceptor  acceptor_;  //用来监听收到链接的监听器
	chat_room  room_;  //房间，每当接收到新的链接请求并当不存在链接错误时将新的会话加入房间

};

typedef boost::shared_ptr<server> server_ptr;
typedef std::list<server_ptr> server_list;

//==================================LocalServer===============================

/*真正的本地服务器，用Cocos内存管理系统管理*/

class LocalServer : public cocos2d::Node
{
public:

	/*构造本地服务器，并启动server*/
	static LocalServer* create()
	{
		LocalServer *ls = new LocalServer();
		if (ls)
		{
			ls->autorelease();
			ls->runserver();

			return ls;

		}
		return nullptr;
	}

	/*新建一个线程，运行server*/
	void runserver()
	{
		std::thread new_t(&LocalServer::newserver, this);
		new_t.detach();
	}

	/*在独立线程中运行server*/
	int newserver()
	{
		try 
		{
			boost::asio::io_service service;
			server_list servers;
			using namespace std;
			tcp::endpoint ep(tcp::v4(), 8001);
			server_ptr  new_server(new server(service, ep));
			servers.push_back(new_server);

			service.run();

		}
		catch (std::exception& e)
		{
			std:: cerr << "Exception:" << e.what() << "\n";
		}
		return 0;
	}
};



#endif /*_Server_h_*/
