#include "Smtp.h"
//#include <afx.h>//�쳣��
static const char base64Char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char* base64Encode(char const* origSigned, unsigned origLength)
{
	unsigned char const* orig = (unsigned char const*)origSigned; // in case any input bytes have the MSB set  
	if (orig == NULL) return NULL;

	unsigned const numOrig24BitValues = origLength / 3;
	bool havePadding = origLength > numOrig24BitValues * 3;
	bool havePadding2 = origLength == numOrig24BitValues * 3 + 2;
	unsigned const numResultBytes = 4 * (numOrig24BitValues + havePadding);
	char* result = new char[numResultBytes + 3]; // allow for trailing '/0'  

	// Map each full group of 3 input bytes into 4 output base-64 characters:  
	unsigned i;
	for (i = 0; i < numOrig24BitValues; ++i)
	{
		result[4 * i + 0] = base64Char[(orig[3 * i] >> 2) & 0x3F];
		result[4 * i + 1] = base64Char[(((orig[3 * i] & 0x3) << 4) | (orig[3 * i + 1] >> 4)) & 0x3F];
		result[4 * i + 2] = base64Char[((orig[3 * i + 1] << 2) | (orig[3 * i + 2] >> 6)) & 0x3F];
		result[4 * i + 3] = base64Char[orig[3 * i + 2] & 0x3F];
	}

	// Now, take padding into account.  (Note: i == numOrig24BitValues)  
	if (havePadding)
	{
		result[4 * i + 0] = base64Char[(orig[3 * i] >> 2) & 0x3F];
		if (havePadding2)
		{
			result[4 * i + 1] = base64Char[(((orig[3 * i] & 0x3) << 4) | (orig[3 * i + 1] >> 4)) & 0x3F];
			result[4 * i + 2] = base64Char[(orig[3 * i + 1] << 2) & 0x3F];
		}
		else
		{
			result[4 * i + 1] = base64Char[((orig[3 * i] & 0x3) << 4) & 0x3F];
			result[4 * i + 2] = '=';
		}
		result[4 * i + 3] = '=';
	}

	result[numResultBytes] = '\0';
	return result;
}


int Csmtp::SendAttachment(SOCKET &sockClient) /*���͸���*/
{
	for (std::vector<string>::iterator iter = filename.begin(); iter != filename.end(); iter++)
	{
		//cout << "Attachment is sending������ " << endl;

		string path = *iter;
		ifstream ifs(path, ios::in | ios::binary); //'������2�����ԣ������롢�����ƴ�'
		if (false == ifs.is_open())
		{
			//cout << "�޷����ļ���" << endl;
			return 1;
		}
		char pathName[256];
		const char *p = path.c_str();
		strcpy_s(pathName, p + path.find_last_of("\\") + 1);
		string strPathName = pathName;

		string sendstring;
		sendstring = "--@boundary@\r\nContent-Type: application/octet-stream; name=\"" + strPathName + "\"\r\n";
		sendstring += "Content-Disposition: attachment; filename=\"" + strPathName + "\"\r\n";
		sendstring += "Content-Transfer-Encoding: base64\r\n\r\n";
		send(sockClient, sendstring.c_str(), sendstring.length(), 0);

		//infile.read((char*)buffer,sizeof(��������));

		// get length of file:
		ifs.seekg(0, ifs.end);
		int length = ifs.tellg();
		ifs.seekg(0, ifs.beg);
		//cout << "length:" << length << endl;
		// allocate memory:
		char * buffer = new char[length];
		// read data as a block:
		ifs.read(buffer, length);
		ifs.close();
		char *pbase;
		pbase = base64Encode(buffer, length);
		delete[]buffer;
		string str(pbase);
		delete[]pbase;
		str += "\r\n";
		int err = send(sockClient, str.c_str(), strlen(str.c_str()), 0);

		if (err != strlen(str.c_str()))
		{
			//cout << "�������ͳ���!" << endl;
			return 1;
		}
	}
	return 0;
}


bool Csmtp::CReateSocket()
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 1);
	//WSAStarup����WSA(Windows SocKNDs Asynchronous��Windows�׽����첽)����������
	int err = WSAStartup(wVersionRequested, &wsaData);
	//cout << "WSAStartup(0:successful):" << err << endl;

	char namebuf[128];    //��ñ��ؼ������
	string ip_list;
	if (0 == gethostname(namebuf, 128))
	{
		struct hostent* pHost;  //��ñ���IP��ַ
		pHost = gethostbyname(namebuf);  //pHost���ص���ָ���������б�
		for (int i = 0; pHost != NULL && pHost->h_addr_list[i] != NULL; i++)
		{
			string tem = inet_ntoa(*(struct in_addr *)pHost->h_addr_list[i]);
			ip_list += tem;
			ip_list += "\n";
		}
	}
	else
	{
		//cout << "��ȡ������Ϣʧ��..." << endl;
	}
	//////////////////////////////////////////////////////////////////////////
	title = namebuf;// �ʼ�����
	content = ip_list; //����ip

	sockClient = socket(AF_INET, SOCK_STREAM, 0); //����socket����  

	pHostent = gethostbyname(domain.c_str()); //�õ��й�����������Ϣ

	if (pHostent == NULL)
	{
		//printf("��������ʧ�ܣ�Ҳ��û������\n");
		return false;
	}

	return true;
}


int Csmtp::SendMail()
{
	char *ecode;

	char buff[500];  //recv�������صĽ��
	int err = 0;
	string message; //

	SOCKADDR_IN addrServer;  //����˵�ַ
	addrServer.sin_addr.S_un.S_addr = *((DWORD *)pHostent->h_addr_list[0]); //�õ�smtp�������������ֽ����ip��ַ     



	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port); //���Ӷ˿�25 
	//int connect (SOCKET s , const struct sockaddr FAR *name , int namelen );
	err = connect(sockClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR));   //���������������  
	//cout << "connect:" << err << endl;
	//telnet smtp.126.com 25 ���ӷ���������
	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "connect:" << buff << endl;

	message = "ehlo 126.com\r\n";
	send(sockClient, message.c_str(), message.length(), 0);

	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "helo:" << buff << endl;

	message = "auth login \r\n";
	send(sockClient, message.c_str(), message.length(), 0);
	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "auth login:" << buff << endl;
	//�ϴ�������
	message = user;
	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
	message = ecode;
	message += "\r\n";
	delete[]ecode;
	send(sockClient, message.c_str(), message.length(), 0);
	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "usrname:" << buff << endl;
	//�ϴ���������
	message = pass;
	ecode = base64Encode(message.c_str(), strlen(message.c_str()));
	message = ecode;
	delete[]ecode;
	message += "\r\n";
	send(sockClient, message.c_str(), message.length(), 0);
	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "password:" << buff << endl;

	message = "mail from:<" + user + ">\r\nrcpt to:<" + target + ">\r\n";
	send(sockClient, message.c_str(), message.length(), 0);
	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "mail from: " << buff << endl;
	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "rcpt to: " << buff << endl;

	message = "data\r\n";//dataҪ��������һ��
	send(sockClient, message.c_str(), message.length(), 0);
	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "data: " << buff << endl;
	///-----------------------------------------DATA-------------------------------------
	//Ҫʹ��Csmtp ���͸���, ��Ҫ��Csmtp ͷ��Ϣ����˵��, �ı�Content-type ��Ϊÿһ���������BOUNDARY ��,
	//cout << "-------------------DATA------------------------" << endl;
	//  ͷ
	message = "from:" + user + "\r\nto:" + target + "\r\nsubject:" + title + "\r\n";
	message += "MIME-Version: 1.0\r\n";
	message += "Content-Type: multipart/mixed;boundary=@boundary@\r\n\r\n";
	send(sockClient, message.c_str(), message.length(), 0);

	//  ����
	message = "--@boundary@\r\nContent-Type: text/plain;charset=\"gb2312\"\r\n\r\n" + content + "\r\n\r\n";
	send(sockClient, message.c_str(), message.length(), 0);

	//------------------------------------------------------------------------------------------------
	//  ���͸���

	SendAttachment(sockClient);

	/*���ͽ�β��Ϣ*/
	message = "--@boundary@--\r\n.\r\n";
	send(sockClient, message.c_str(), message.length(), 0);
	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "end_qwertyuiop:" << buff << endl;

	message = "QUIT\r\n";
	send(sockClient, message.c_str(), message.length(), 0);
	buff[recv(sockClient, buff, 500, 0)] = '\0';
	//cout << "Send mail is finish:" << buff << endl;
	return 0;
}
