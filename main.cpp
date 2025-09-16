#include <iostream>

using namespace std;

int main() 
{
	int EXP = 0;
	int GetEXP = 4;
	int NeedEXP = 10;
	while (EXP >= NeedEXP)
	{
		EXP += GetEXP;
	}
	NeedEXP *= 2;
	cout << "level up" << endl;
	return 0;
}