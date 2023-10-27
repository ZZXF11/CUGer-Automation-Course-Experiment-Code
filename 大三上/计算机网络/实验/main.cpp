#include<iostream>
#include<WinSock2.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable : 4996)
using namespace std;

int main() {

	//套接字信息结构
	WSADATA wsadata;
	//设置版本号
	WORD sockVersion = MAKEWORD(2, 2);
	//建立一个客户端套接字；
	SOCKET sClient;
	//启动构建，将“为ws2_32.lib”加载到内存中，做一些初始化工作
	if (WSAStartup(sockVersion, &wsadata) != 0) {
		//判断是否构建成功，若失败，则客户端打印一句提示话。
		printf("错误：");
		return 0;
	}

	//创建客户端udp套接字
	sClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SOCKET_ERROR == sClient) {
		printf("连接错误：");
		return 0;
	}

	//创建服务器端地址
	sockaddr_in serverAddr;
	//创建服务器端地址
	sockaddr_in clientAddr;
	//设置服务器端地址，端口号，协议族
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8889);
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//获取服务器地址和客户端地址构造体的长度
	int slen = sizeof(serverAddr);
	int clen = sizeof(clientAddr);
	//设置接受数据缓冲区大小
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	//用于记录发送函数和接受函数的返回值
	int iSend = 0;
	int iRcv = 0;
    //ring str;
	cout << "建立通信：" << endl;

	while (true) {

		//从控制台获取数据
		cout << "传输： ";
		//getline(cin, str) ;
		cin >> buffer;
		//将string型数据处理成char数组型
		//const int len = sizeof(str);
		// ar senddata[len];
		// rcpy_s(senddata, str.c_str());

		//发送信息给客户端
		iSend = sendto(sClient, buffer, strlen(buffer), 0, (SOCKADDR*)&serverAddr, slen);
		if (iSend == SOCKET_ERROR) {
			cout << "sendto failed " << endl;
			closesocket(sClient);
			WSACleanup();
			cout << "5s后关闭控制台。" << endl;
			Sleep(5000);
			return 0;
		}
		//若数据为byebye，断开连接
		if (!(strcmp(buffer, "byebye"))) {
			cout << "close connection " << endl;
			closesocket(sClient);
			WSACleanup();
			cout << "5s后关闭控制它。" << endl;
			Sleep(5000);
			return 0;
		}
		memset(buffer, 0, sizeof(buffer));

		//接受服务器端数据
		iRcv = recvfrom(sClient, buffer, sizeof(buffer), 0, (SOCKADDR*)&clientAddr, &clen);
		if (iRcv == SOCKET_ERROR) {
			cout << "recvFrom failed " << endl;
			closesocket(sClient);
			WSACleanup();
			cout << "5s后关闭控制台。" << endl;
			Sleep(5000);
			return 0;
		}
		//判断服务器是否关闭
		if (iRcv <= 0) {
			cout << "server disconnected··· " << endl;
			closesocket(sClient);
			WSACleanup();
			cout << "5s后关闭控制台。" << endl;
			Sleep(5000);
			return 0;
		}
		else {
			cout << " 反馈： " << buffer << endl;
		}
		memset(buffer, 0, sizeof(buffer));

	}
	closesocket(sClient);
	WSACleanup();
	return 0;
}
