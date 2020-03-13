#include <iostream>
#include <Windows.h>
using namespace std;

struct LEVEL
{
	int level;
	int exp;
};

int main() {

	//����ȼ�
	const int max = 10;
	LEVEL level[max];

	//�ַ���
	wchar_t buf[256] = {0};
	for (int i = 0; i < max; i++)
	{
		//���õ�ǰ�ȼ���Ϣ
		level[i] = { i + 1,i * 1000 + (i % 10) * 500};

		swprintf_s(buf, TEXT("{\"level\":%d,\"exp\":%d}\n"), level[i].level, level[i].exp);
		OutputDebugString(buf);
	}

	//��ǰ�ȼ�
	int n_level = 1;
	//��ǰ����
	int n_exp = level[n_level - 1].exp;

	for (; n_exp < level[max-1].exp; n_exp+=100)
	{
		Sleep(500);

		//��ǰ��ʼ����
		int ini_exp = level[n_level - 1].exp;
		//��һ������
		int next_exp = level[n_level].exp;

		if (n_exp >= next_exp)
		{
			//����
			n_level++;
			cout << "��ϲ��������!!! �ȼ���" << n_level << endl << endl;
		}

		cout << "��ǰ�ȼ�:" << n_level << endl;
		cout << "��ǰ����:" << n_exp << "\t ����:" << static_cast<float>((n_exp - ini_exp)) / static_cast<float>((next_exp - ini_exp)) * 100 << "%" << endl;
		cout << "��һ���ȼ�:" << level[n_level].level << endl;
		cout << "��һ������:" << next_exp << endl;
		cout << "-------------------------------------" << endl;
	}
}