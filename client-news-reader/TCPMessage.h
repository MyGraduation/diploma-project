//供客户端和服务器使用的消息头文件
#pragma once
//通信结构体

struct cli_date_t
{
	char buf[300];
	char url[300];
	int buflen;
	int number;
	int clifd;

};


//map容器结构体
struct map_date
{
	char url[300];
	char title[300];
	char jpg_url[300];
	char jpg_name[100];

};

/*
	数字 2 表示更新所有数据标题
	数字 3 表示获取某一条数据详细内容
	数字 4 表示获取查询信息
	数字 5 表示获取视频数据
	数字 6 表示获取图片数据
*/

