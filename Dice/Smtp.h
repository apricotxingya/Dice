#include <iostream>  
#include <string>  
#include <vector>
#include <fstream>  

#include <WinSock2.h>  //����ƽ̨ Windows

#pragma  comment(lib, "ws2_32.lib") /*����ws2_32.lib��̬���ӿ�*/ 
// POP3���������˿ڣ�110�� Csmtp���������˿ڣ�25�� 
using namespace std;
class Csmtp
{
	int port_init = 25;
	string domain_init = "smtp.qq.com";
	string user_init = "2659648392@qq.com";
	string pass_init = "brfovvusofhkdjcf";

	int port;
	string domain;
	string user;
	string pass;
	string target;
	string title;  //�ʼ�����
	string content;  //�ʼ�����


	HOSTENT* pHostent;
	SOCKET sockClient;  //�ͻ��˵��׽���
	vector <string> filename;  //�洢������������

public:

	Csmtp(
		int _port, //�˿�25
		string _domain,     //����
		string _user,       //�����ߵ�����
		string _pass,       //����
		string _target)     //Ŀ������
		:port(_port), domain(_domain), user(_user), pass(_pass), target(_target) {};//����
	Csmtp(
		string _target)     //Ŀ������
		:port(port_init), domain(domain_init), user(user_init), pass(pass_init), target(_target) {};//����
	bool CReateSocket();
	void setTitle(string tem) { title = tem; }
	void setContent(string tem) { content = tem; }

	int SendAttachment(SOCKET &sockClient);
	int SendMail();
	void addfile(string str) { filename.push_back(str); }

};
