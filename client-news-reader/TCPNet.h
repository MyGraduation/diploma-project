#pragma once
#include<winsock2.h>
#include"TCP_Message.h"
#pragma comment(lib, "ws2_32.lib")

extern char dirstr[50];
extern char filenameTXT[150];
extern char filenameJPG[150];
extern char filenameVIDEO[150];
extern char filenameTT[150];

class TCP_net
{
public:
	TCP_net(void);
	~TCP_net(void);

public:
	bool ifcon;  //是否连接成功
	SOCKET client;

public:
	int connect_server(const char* ip,int host);
	int Send_message(cli_date_t date);
	int Recv_message(cli_date_t* date,int n);
	int Recv_video(cli_date_t* date);
	int Recv_jpg(cli_date_t date,char* jpgurl); 

};



