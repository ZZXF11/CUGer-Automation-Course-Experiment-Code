#include<iostream>
#include<WinSock2.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable : 4996)
using namespace std;

int main() {

	//�׽�����Ϣ�ṹ
	WSADATA wsadata;
	//���ð汾��
	WORD sockVersion = MAKEWORD(2, 2);
	//����һ���ͻ����׽��֣�
	SOCKET sClient;
	//��������������Ϊws2_32.lib�����ص��ڴ��У���һЩ��ʼ������
	if (WSAStartup(sockVersion, &wsadata) != 0) {
		//�ж��Ƿ񹹽��ɹ�����ʧ�ܣ���ͻ��˴�ӡһ����ʾ����
		printf("����");
		return 0;
	}

	//�����ͻ���udp�׽���
	sClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (SOCKET_ERROR == sClient) {
		printf("���Ӵ���");
		return 0;
	}

	//�����������˵�ַ
	sockaddr_in serverAddr;
	//�����������˵�ַ
	sockaddr_in clientAddr;
	//���÷������˵�ַ���˿ںţ�Э����
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8889);
	serverAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	//��ȡ��������ַ�Ϳͻ��˵�ַ������ĳ���
	int slen = sizeof(serverAddr);
	int clen = sizeof(clientAddr);
	//���ý������ݻ�������С
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	//���ڼ�¼���ͺ����ͽ��ܺ����ķ���ֵ
	int iSend = 0;
	int iRcv = 0;
    //ring str;
	cout << "����ͨ�ţ�" << endl;

	while (true) {

		//�ӿ���̨��ȡ����
		cout << "���䣺 ";
		//getline(cin, str) ;
		cin >> buffer;
		//��string�����ݴ����char������
		//const int len = sizeof(str);
		// ar senddata[len];
		// rcpy_s(senddata, str.c_str());

		//������Ϣ���ͻ���
		iSend = sendto(sClient, buffer, strlen(buffer), 0, (SOCKADDR*)&serverAddr, slen);
		if (iSend == SOCKET_ERROR) {
			cout << "sendto failed " << endl;
			closesocket(sClient);
			WSACleanup();
			cout << "5s��رտ���̨��" << endl;
			Sleep(5000);
			return 0;
		}
		//������Ϊbyebye���Ͽ�����
		if (!(strcmp(buffer, "byebye"))) {
			cout << "close connection " << endl;
			closesocket(sClient);
			WSACleanup();
			cout << "5s��رտ�������" << endl;
			Sleep(5000);
			return 0;
		}
		memset(buffer, 0, sizeof(buffer));

		//���ܷ�����������
		iRcv = recvfrom(sClient, buffer, sizeof(buffer), 0, (SOCKADDR*)&clientAddr, &clen);
		if (iRcv == SOCKET_ERROR) {
			cout << "recvFrom failed " << endl;
			closesocket(sClient);
			WSACleanup();
			cout << "5s��رտ���̨��" << endl;
			Sleep(5000);
			return 0;
		}
		//�жϷ������Ƿ�ر�
		if (iRcv <= 0) {
			cout << "server disconnected������ " << endl;
			closesocket(sClient);
			WSACleanup();
			cout << "5s��رտ���̨��" << endl;
			Sleep(5000);
			return 0;
		}
		else {
			cout << " ������ " << buffer << endl;
		}
		memset(buffer, 0, sizeof(buffer));

	}
	closesocket(sClient);
	WSACleanup();
	return 0;
}
