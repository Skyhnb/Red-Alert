#ifndef Client_h
#define Client_h


#include "cocos2d.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <fstream>
#include "OrderMessage.h"
#include <vector>
#include <string>

/*异步客户端，进行数据接收和发送*/

using boost::asio::ip::tcp;
typedef std::deque<Order_Msg> message_queue;

/*进行数据的接收/发送/操作*/
class deal_order
{
public:
	/*构造可以连接的客户端
	  service   用于创建socket
	  endpoint  连接位置的端口号
	*/
	deal_order(boost::asio::io_service& service, tcp::resolver::iterator endpoint)
		:service_(service), socket_(service)
	{
		boost::asio::async_connect(socket_, endpoint,
			boost::bind(&deal_order::handle_connect, this, boost::asio::placeholders::error));
	}

	/*发送指令给server*/
	void write(const Order_Msg& msg)
	{
		service_.post(boost::bind(&deal_order::do_write, this, msg));
	}

	/*终止操作*/
	void close()
	{
		service_.post(boost::bind(&deal_order::do_close, this));
	}

private:

	/*成功链接时调用该函数处理*/
	void handle_connect(const boost::system::error_code& error);

	/*递归发送等待发送的数据，在没有数据发送时停止递归*/
	void handle_write(const boost::system::error_code& error);

	/*do_write()方法会先把信息拷贝到缓冲区,等待发送*/
	void do_write(Order_Msg msg);

	/*关闭时调用*/
	void do_close()
	{
		socket_.close();
	}

	/*在接受到消息后处理数据字符串*/
	void handle_read_header(const boost::system::error_code& error);

	/*当接受完数据并处理完字符串长度后调用该函数，处理命令本体*/
	void handle_read_body(const boost::system::error_code& error);

private:

	boost::asio::io_service&    service_;       // 用于创建socket
	tcp::socket                 socket_;        //tcp类套接字
	Order_Msg                read_msg_;      //每次循环所读取的数据对象
	message_queue          write_msgs_;    //等待被发送的数据对象
};

//----------------------------------------------------------------------

/*搜索并连接服务器，真正的客户端*/
class Client :public cocos2d::Node
{
public:
	bool _is_searched;   //是否完成搜索并且建立了连接
	bool _filter_mode;  //是否开启了过滤模式
	bool _with_server;  //是否同时启动了服务端
	deal_order* _DOInstance; //处理数据接收与发送
	std::mutex  t_lock; //线程锁
	std::string order_type; //识别指令类型
	std::deque<std::string> _orderlist; //读取的指令的容器

	/*创建客户端*/
	static Client* create(int mode)
	{
		Client* sprite = new Client();
		if (sprite)
		{
			sprite->autorelease();
			sprite->runclient(mode);

			return sprite;
		}
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	/*运行client，
	1.同时与server启动
	2.只启动client*/
	void runclient(int mode);

	/*取出读取的指令，返回读取到的并经过过滤的指令*/
	std::string pullorder();

	/*发送操作
	code 指令编码
	msg  指令内容*/
	void send_message(const std::string& code, const std::string &msg);

	/*启动并搜索/连接服务端*/
	int client();


};

#endif/*Client_h*/
