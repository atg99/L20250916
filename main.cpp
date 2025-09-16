#include <iostream>

using namespace std;

int main() 
{
	int EXP = 0;
	int GetEXP = 4;
	int NeedEXP = 10;
	int Level = 1;
	while (Level < 10)
	{
		while (EXP <= NeedEXP)
		{
			EXP += GetEXP;
			cout << "GetEXP + ";
			cout << GetEXP << endl;
		}
		EXP = 0;
		NeedEXP *= 2;
		Level += 1;
		cout << "level up" << endl;
		cout << "level : "; cout << Level << endl;
	}

	return 0;
}