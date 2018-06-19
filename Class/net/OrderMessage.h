#ifndef OrderMessage_H
#define OrderMessage_H

#include <cstdio>
#include <cstdlib>
#include <cstring>


 /*此为信息传输编码格式*/
/*一条数据分为三部分：\n
* 1、字符串头的4个字节表示数据部分的长度，最大为9999，不足补0
* 2、字符串第五个字符表示命令类型
* 3、字符串后面为命令内容*/

class Order_Msg
{
public:
	enum { header_length = 4 };
	enum { max_body_length = 512 };

	Order_Msg()
		:body_length_(0){}

	const char* data() const
	{
		return data_;
	}

	char* data()
	{
		return data_;
	}

	size_t length() const
	{
		return header_length + body_length_;
	}

	size_t body_length() const
	{
		return body_length_;
	}

	const char* body() const
	{
		return data_ + header_length;
	}

	char* body()
	{
		return data_ + header_length;
	}

	void body_length(size_t new_length)
	{
		body_length_ = new_length;
		if (body_length_ > max_body_length)
			body_length_ = max_body_length;
	}
	/*将表示命令长度的字符串变成整形，并与最大长度比较*/
	bool decode_header()
	{
		using namespace std;
		char header[header_length + 1] = "";
		strncat(header, data_, header_length);
		body_length_ = atoi(header);
		if (body_length_ > max_body_length)
		{
			body_length_ = 0;
			return false;
		}
		return true;
	}

	/*操作函数，将字符串编入命令头中*/
	void encode_header()
	{
		using namespace std;
		char header[header_length + 1] = "";
		sprintf(header, "%4d", body_length_);
		memcpy(data_, header, header_length);
	}


private:
	char data_[header_length + max_body_length];
	size_t body_length_;

};




#endif /*OrderMessage_H*/