#include"main.h"
HANDLE hcom;
void c_comi()
{
	//�򿪴���
	hcom = CreateFile(TEXT("COM3"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hcom == (HANDLE)-1)
	{
		cout << "�򿪴���ʧ��" << endl;
		return;
	}
	//���ô���
	//�������뻺�����������������С����1024
	SetupComm(hcom, 1024, 1024);
	//���ó�ʱ��дʱ�䣬0Ϊ�޳�ʱ������Ϊʱ��
	COMMTIMEOUTS TimeOuts;
	memset(&TimeOuts, 0, sizeof(TimeOuts));
	TimeOuts.ReadIntervalTimeout = MAXDWORD;
	TimeOuts.ReadTotalTimeoutConstant = 0;	//ԭ��д����1000������ʵ����֤��0��ʱ��ſ���������ȡ����
	TimeOuts.ReadTotalTimeoutMultiplier = 0;
	TimeOuts.WriteTotalTimeoutConstant = MAXDWORD;
	TimeOuts.WriteTotalTimeoutMultiplier = MAXDWORD;
	SetCommTimeouts(hcom, &TimeOuts);
	//���ô���
	DCB dcb;
	GetCommState(hcom, &dcb);
	dcb.BaudRate = 9600;
	dcb.ByteSize = 8;
	dcb.Parity = 0;
	dcb.StopBits = 1;
	SetCommState(hcom, &dcb);
}
char c_comr()
{
	char temp;
	char Rchar[100] = { '0' }, Schar[9] = { "99999999" };
	DWORD dwWantRead = 100;
	DWORD dwRealRead = 0;

	if (!ReadFile(hcom, Rchar, dwWantRead, &dwRealRead, NULL))
	{
		cout << "��ȡ��������ʧ��" << endl;
		return 0;
	}
	else
	{
		for (int i = 0; i < 9; i++)
		{
			Schar[i] = Rchar[i];
		}
		Schar[8] = '\0';
		temp = Schar[0];
		cout << Schar << endl;
		//��ջ���
		PurgeComm(hcom, PURGE_RXCLEAR | PURGE_RXABORT | PURGE_TXABORT | PURGE_TXCLEAR);
	}
	return temp;
}
void c_coms()
{
	char data[] = { 0x01 };
	DWORD dwWrittenlen = 0;
	if (!WriteFile(hcom, data, 8, &dwWrittenlen, NULL))
	{
		return;
	}
}
void c_comn()
{
	char data[] = { 0x00 };
	DWORD dwWrittenlen = 0;
	if (!WriteFile(hcom, data, 8, &dwWrittenlen, NULL))
	{
		return;
	}
}