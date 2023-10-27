
#include <iostream>
#include <WinSock2.h>
#include<WS2tcpip.h>
#include<string>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main() {
	//���ð汾��
	WORD sockVersion = MAKEWORD(2, 2);
	//����һ��WSADATA���͵Ľṹ�壬�洢��WSAStartup�������ú󷵻ص�Windows Sockets����
	WSADATA wsadata;
	//��ʼ���׽��֣���������������ws2_32.lib�����ص��ڴ���
	if (WSAStartup(sockVersion, &wsadata)) {
		printf("WSAStartup failed \n");
		return 0;
	}
	//����һ���׽��֣�������һ���ں˶���
	SOCKET hServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (hServer == INVALID_SOCKET) {
		printf("socket failed \n");
		return 0;
	}
	//�����������˵�ַ���󶨶˿ںŵ�IP��ַ
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(8889);
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;

	// ��ʼ���ں˶��󣬴��θ��ں˶��󣬴�ʱ���ݿ��ܶ�����δ��������
	int nRet = bind(hServer, (sockaddr*)&addrServer, sizeof(addrServer));
	if (nRet == SOCKET_ERROR) {
		printf("socket bind failed\n");
		closesocket(hServer);
		WSACleanup();
		return 0;
	}
	//����һ���ͷ��˵�ַ
	sockaddr_in  addrClient;
	int nlen = sizeof(addrClient);
	//����һ���м���������ڴ���û��������Ϣ
	// ring str;

	//���ڽ������ݵĻ�������
	char buffer[1024];
	//��ʼ��������
	memset(buffer, 0, sizeof(buffer));
	int irecv;
	int isend;

	//����ѭ����������
	while (true) {
		//�������ݣ�
			   //���ܿͻ��˵���Ϣ
		irecv = recvfrom(hServer, buffer, sizeof(buffer), 0, (SOCKADDR*)&addrClient, &nlen);
		//�����������ݣ���ʼ��ȡ����
		if (irecv > 0) {
			//�ж������Ƿ�Ϊ������־��������رշ�����
			if (!(strcmp(buffer, "byebye"))) {
				//�رշ������׽���
				cout << "���ܣ� " << buffer << endl;
				cout << "close connection������ " << endl;
				closesocket(hServer);
				WSACleanup();
				cout << "5s��رտ�������" << endl;
				Sleep(5000);
				return 0;
			}
			else {
				cout << " ���ܣ�" << buffer << endl;
			}
		}
		//��������ʧ��
		else {
			cout << "recvFrom failed " << endl;
			closesocket(hServer);
			WSACleanup();
			cout << "5s��رտ���̨��" << endl;
			Sleep(5000);
			return 0;
		}
		//��ʼ����������������һ�����ݵĽ���
		memset(buffer, 0, sizeof(buffer));

		//�������ݣ�
		cout << "������";
		//�Ӽ��̻�ȡ����
		cin >> buffer;
		//getline(cin, str);
		//�����������ݻ�����
		//const int len = sizeof(str);
		// ar senddata[len];
		// rcpy_s(senddata, str.c_str());

		//��������
		isend = sendto(hServer, buffer, strlen(buffer), 0, (SOCKADDR*)&addrClient, nlen);
		if (isend == SOCKET_ERROR) {
			cout << "sendto failed " << endl;
			closesocket(hServer);
			WSACleanup();
			cout << "5s��رտ���̨��" << endl;
			Sleep(5000);
			return 0;
		}
		// r = "";
		//��ʼ����������������һ�����ݵĽ���
		memset(buffer, 0, sizeof(buffer));
	}

	//�رշ������׽���
	closesocket(hServer);
	WSACleanup();
	return 0;
}

