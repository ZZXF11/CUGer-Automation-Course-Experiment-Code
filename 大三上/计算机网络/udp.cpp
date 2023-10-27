
#include <iostream>
#include <WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main() {
	//设置版本号
	WORD sockVersion = MAKEWORD(2, 2);
	//定义一个WSADATA类型的结构体，存储被WSAStartup函数调用后返回的Windows Sockets数据
	WSADATA wsadata;
	//初始化套接字，启动构建，将“ws2_32.lib”加载到内存中
	if (WSAStartup(sockVersion, &wsadata)) {
		printf("WSAStartup failed \n");
		return 0;
	}
	//创建一个套接字，即创建一个内核对象
	SOCKET hServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (hServer == INVALID_SOCKET) {
		printf("socket failed \n");
		return 0;
	}
	//创建服务器端地址并绑定端口号的IP地址
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(8889);
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;

	// 初始化内核对象，传参给内核对象，此时数据可能都处于未就绪链表
	int nRet = bind(hServer, (sockaddr*)&addrServer, sizeof(addrServer));
	if (nRet == SOCKET_ERROR) {
		printf("socket bind failed\n");
		closesocket(hServer);
		WSACleanup();
		return 0;
	}
	//创建一个客服端地址
	sockaddr_in  addrClient;
	int nlen = sizeof(addrClient);
	//创建一个中间变量，用于存放用户输入的信息
	// ring str;

	//用于接受数据的缓冲区。
	char buffer[1024];
	//初始化缓冲区
	memset(buffer, 0, sizeof(buffer));
	int irecv;
	int isend;

	//可以循环接受数据
	while (true) {
		//接收数据：
			   //接受客户端的消息
		irecv = recvfrom(hServer, buffer, sizeof(buffer), 0, (SOCKADDR*)&addrClient, &nlen);
		//缓冲区有数据，开始读取数据
		if (irecv > 0) {
			//判断数据是否为结束标志，若是则关闭服务器
			if (!(strcmp(buffer, "byebye"))) {
				//关闭服务器套接字
				cout << "接受： " << buffer << endl;
				cout << "close connection··· " << endl;
				closesocket(hServer);
				WSACleanup();
				cout << "5s后关闭控制它。" << endl;
				Sleep(5000);
				return 0;
			}
			else {
				cout << " 接受：" << buffer << endl;
			}
		}
		//接受数据失败
		else {
			cout << "recvFrom failed " << endl;
			closesocket(hServer);
			WSACleanup();
			cout << "5s后关闭控制台。" << endl;
			Sleep(5000);
			return 0;
		}
		//初始化缓冲区，用于下一次数据的接收
		memset(buffer, 0, sizeof(buffer));

		//发送数据：
		cout << "反馈：";
		//从键盘获取数据
		cin >> buffer;
		//getline(cin, str);
		//建立发送数据缓冲区
		//const int len = sizeof(str);
		// ar senddata[len];
		// rcpy_s(senddata, str.c_str());

		//发送数据
		isend = sendto(hServer, buffer, strlen(buffer), 0, (SOCKADDR*)&addrClient, nlen);
		if (isend == SOCKET_ERROR) {
			cout << "sendto failed " << endl;
			closesocket(hServer);
			WSACleanup();
			cout << "5s后关闭控制台。" << endl;
			Sleep(5000);
			return 0;
		}
		// r = "";
		//初始化缓冲区，用于下一次数据的接收
		memset(buffer, 0, sizeof(buffer));
	}

	//关闭服务器套接字
	closesocket(hServer);
	WSACleanup();
	return 0;
}

