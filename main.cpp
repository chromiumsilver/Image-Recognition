#include"main.h"
int main()
{
	char c;
	c_comi();
	while (true)
	{
		/*cout << "ѡ��һ������" << endl;
		cout << "����r ��ɫʶ���ɫ" << endl;
		cout << "����y ��ɫʶ���ɫ" << endl;
		cout << "����b ��ɫʶ����ɫ" << endl;
		cout << "����f ͼ��ƥ��Ҵ�" << endl;
		cout << "����k ͼ��ƥ�����" << endl;
		cout << "����x ͼ��ƥ��ѩ��" << endl;
		cout << "����e �˳�" << endl;*/
		c = c_comr();

		if (c == 'r'||c == 'y'||c == 'b')
		{
			cout << "��ɫʶ��" << endl;
			check_color(c);
			cout << "success" << endl;
		}
		else if (c == 'f'||c == 'k'||c == 'x'||c == '1')
		{
			cout << "ͼ��ƥ��" << endl;
			check_shape('f');
			cout << "suceess" << endl;
		}
		else if (c == 'e')
		{
			cout << "�˳�" << endl;
			return 0;
		}
		else
			cout << "ʧ��" << endl;
	}
}