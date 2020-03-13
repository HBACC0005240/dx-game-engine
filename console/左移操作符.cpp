#include <iostream>
#include <Windows.h>
using namespace std;
int _3main() {


	BYTE sh1 = 0b00110011;
	BYTE sh2 = 0b00000011;
	//×óÒÆ
	//			 00000011 00000000
	//			 00000011 00110011
	USHORT sh = (sh2 << 8) | sh1;

	cout << sh << endl;
	return 0;
}