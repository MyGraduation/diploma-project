#include "stdafx.h"
#include "TCP_net.h"

TCP_net::TCP_net(void)
{
	ifcon = FALSE;

}

TCP_net::~TCP_net(void)
{
	WSACleanup();  //卸载库
}

int TCP_net::connect_server(const char* ip,int host)
{
	WORD wVersionRequested;  //加载库
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);  //改变字节位操作

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        //printf("WSAStartup failed with error: %d\n", err);
        return 0;
    }


    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {  //检验库的版本是不是2.0
       // printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
        return 0;
    }
    else
       // printf("The Winsock 2.2 dll was found okay\n");


	client = socket(AF_INET,SOCK_STREAM,0);

	if(client == INVALID_SOCKET)
	{
		return 0;
	}

	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(host);
	sin.sin_addr.S_un.S_addr = inet_addr(ip);
	if(connect(client,(sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR)
	{
		closesocket(client);
		return 0;
	}

	ifcon = TRUE;

	return client;

}

int TCP_net::Send_message(cli_date_t date)
{
	int len = 0;
	int radlen = 0;

	if(ifcon)
	{
		while(radlen < sizeof(date))
		{
			len = send(client,(char*)&date,sizeof(date)-radlen,0);
			radlen = radlen+len;
		}

		return 1;
	}
	return 0;
}

int TCP_net::Recv_message(cli_date_t* date,int n)
{

	int len = 0;
	int radlen = 0;
	int wlen = 0;
	int wrlen = 0;
	unsigned char bufdate[300];
	char videname[100];
	strcpy_s(videname,sizeof(videname), dirstr);
	strcat_s(videname, sizeof(videname),"video.mp4");
	memset(bufdate,'\0',sizeof(bufdate));



	FILE* fd = nullptr;
	if(ifcon)
	{
		switch (n)
		{
		case 1:
			fopen_s(&fd, filenameTT,"ab");
			break;
		case 2:
			fopen_s(&fd, filenameTXT,"ab");
			break;
		case 3:
			fopen_s(&fd, filenameJPG,"ab");
			break;
		case 4:
			fopen_s(&fd, filenameVIDEO,"ab");
			break;
		case 5:
			fopen_s(&fd, videname,"wb");
			break;
		default:
			break;
		}
		
		len = 0;

		if(fd == nullptr)
			return 0;
		
		while(len < sizeof(*date))
		{
			len = recv(client,(char*)date,sizeof(*date),0);
		}

		if(date->number == 0 || len < 0)
		{
			fclose(fd);
			return 0;
		}

		

		if(len > 0)
		{
			len = 0;

			while(radlen < date->buflen)
			{
				len = recv(client,(char*)bufdate,sizeof(bufdate),0);
				radlen = radlen + len;
				while(len > 0)
				{
					wlen = fwrite(bufdate+wrlen,1,len-wrlen,fd);
					wrlen = wrlen + wlen;
					len -= wlen;
				}

				wrlen = 0;
				wlen = 0;
				memset(bufdate,0,sizeof(bufdate));
				
			}

			fclose(fd);
			fd = nullptr;
			if(n == 2 || n == 3 || n == 4 )
			Send_message(*date);
			return 1;
		}

		return 0;

	}

	return 0;

}

int TCP_net::Recv_video(cli_date_t* date)
{
	int len = 0;
	int radlen = 0;
	int wlen = 0;
	int wrlen = 0;
	unsigned char bufdate[4096];
	memset(bufdate,0,sizeof(bufdate));

	FILE* fd = nullptr;
	if(ifcon)
	{
		
		fopen_s(&fd,date->buf,"wb");

		len = recv(client,(char*)date,sizeof(*date),0);

		if(date->number == 0)
		{
			fclose(fd);
			return 0;
		}

		if(len > 0)
		{
			len = 0;

			while(radlen < date->buflen)
			{
	
				len = recv(client,(char*)bufdate,sizeof(bufdate),0);
				radlen = radlen + len;
				while(len > 0)
				{
					wlen = fwrite(bufdate+wrlen,1,len-wrlen,fd);
					wrlen = wrlen + wlen;
					len -= wlen;
				}

				wrlen = 0;
				wlen = 0;
				memset(bufdate,0,sizeof(bufdate));
				
			}

			fclose(fd);
			fd = nullptr;
			return 1;
		}

		return 0;
	}
	return 0;
}

int TCP_net::Recv_jpg(cli_date_t date,char* jpgname)
{

	cli_date_t newdate;
	int len = 0;
	int radlen = 0;
	int wlen = 0;
	int wrlen = 0;
	unsigned char bufdate[4096];
	char filename[100];
	memset(filename,'\0',sizeof(filename));
	strcpy_s(filename,sizeof(filename), dirstr);
	strcat_s(filename, sizeof(filename), "\\");
	strcat_s(filename,sizeof(filename),jpgname);
	memset(bufdate,0,sizeof(bufdate));

	FILE* fd = nullptr;
	if(ifcon)
	{
		
		fopen_s(&fd,filename,"wb");

		if(fd == NULL)
			return 0;

		len = recv(client,(char*)&newdate,sizeof(newdate),0);

		while(newdate.buflen == 0)
		{
			Send_message(date);
			len = recv(client,(char*)&newdate,sizeof(newdate),0);
		}

		if(newdate.number == 0 || newdate.number != 6 )
		{
			fclose(fd);
			fd = nullptr;
			remove(filename);
			return 0;
		}

		if(len > 0)
		{
			len = 0;

			while(radlen < newdate.buflen)
			{
	
				len = recv(client,(char*)bufdate,sizeof(bufdate),0);
				radlen = radlen + len;
				while(len > 0)
				{
					wlen = fwrite(bufdate+wrlen,1,len-wrlen,fd);
					wrlen = wrlen + wlen;
					len -= wlen;
				}

				wrlen = 0;
				wlen = 0;
				memset(bufdate,0,sizeof(bufdate));
				
			}

			fclose(fd);
			fd = nullptr;
			return 1;
		}

		return 0;
	}

	return 0;
}


