#include <iostream>
#include <Windows.h>
using namespace std;

struct LEVEL
{
	int level;
	int exp;
};

int main() {

	//定义等级
	const int max = 10;
	LEVEL level[max];

	//字符串
	wchar_t buf[256] = {0};
	for (int i = 0; i < max; i++)
	{
		//设置当前等级信息
		level[i] = { i + 1,i * 1000 + (i % 10) * 500};

		swprintf_s(buf, TEXT("{\"level\":%d,\"exp\":%d}\n"), level[i].level, level[i].exp);
		OutputDebugString(buf);
	}

	//当前等级
	int n_level = 1;
	//当前经验
	int n_exp = level[n_level - 1].exp;

	for (; n_exp < level[max-1].exp; n_exp+=100)
	{
		Sleep(500);

		//当前初始经验
		int ini_exp = level[n_level - 1].exp;
		//下一级经验
		int next_exp = level[n_level].exp;

		if (n_exp >= next_exp)
		{
			//升级
			n_level++;
			cout << "恭喜您升级了!!! 等级：" << n_level << endl << endl;
		}

		cout << "当前等级:" << n_level << endl;
		cout << "当前经验:" << n_exp << "\t 进度:" << static_cast<float>((n_exp - ini_exp)) / static_cast<float>((next_exp - ini_exp)) * 100 << "%" << endl;
		cout << "下一级等级:" << level[n_level].level << endl;
		cout << "下一级经验:" << next_exp << endl;
		cout << "-------------------------------------" << endl;
	}
}