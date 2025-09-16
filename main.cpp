#include <iostream>
#include <windows.h>
#include <conio.h>
#include <random>
#include <vector>

#define UP 0x48
#define LEFT 0x4B
#define RIGHT 0x4D
#define DOWN 0x50
#define SPACE 0x20

using namespace std;

//pair<int, int> KeyProcess();

// 1. 난수 엔진을 위한 시드 생성기
random_device rd;

// 2. 시드를 이용해 메르센 트위스터 엔진 초기화
//    mt19937은 32비트 메르센 트위스터 엔진입니다.
mt19937 gen(rd());

// 3. 원하는 범위의 정수 값을 균등하게 생성하는 분포 정의
//    uniform_int_distribution<int>(최소값, 최대값)
uniform_int_distribution<int> dist(-1, 1);

class Character
{

public:
	int HP = 1;
	bool isAlive = true;
	char CharacterShape = '1';
	pair<int, int> CharacterPosition = { 0,0 };

	// 기본 생성자
	Character() : CharacterShape('1') {}

	// 모양을 받아 초기화하는 생성자
	Character(char shape, pair<int,int> pos) : CharacterShape(shape), CharacterPosition(pos) {}

};

class Enemy : public Character
{
public:
	int Level;

	Enemy(int Level, pair<int,int>pos) : Level(Level), Character(Level+'0', pos)
	{

	}

	bool Hit(int PlayerLevel)
	{
		if (PlayerLevel >= this->Level)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Move()
	{
		if (!isAlive) return;

		CharacterPosition.first += (dist(gen));
		CharacterPosition.second += (dist(gen));
	}
};

class Player : public Character
{

public:
	int Level;

	Player(int Level, char PlayerShape, pair<int, int>pos) : Level(Level), Character(PlayerShape, pos)
	{

	}

	void LevelUp()
	{
		Level += 1;
		this->CharacterShape += 1;
	}

	pair<int, int> KeyProcess() {
		int KeyInput = 0;
		int MoveDirectionX = 0;
		int MoveDirectionY = 0;
		if (KeyInput = _getch()) // 키입력을 체크
		{
			switch (KeyInput) {
			case UP: MoveDirectionY--; break;
			case DOWN: MoveDirectionY++; break;
			case LEFT: MoveDirectionX--; break;
			case RIGHT: MoveDirectionX++; break;
			case SPACE: break;
			}


			return { MoveDirectionX, MoveDirectionY };
		}

		return { 0,0 };
	}
};

int main() 
{

	Player Player(1, 'A', {0,0});

	const int EnemyNum = 10;
	vector<Enemy> Enemies;

	uniform_int_distribution<int> distX(5, 30);
	uniform_int_distribution<int> distY(5, 30);

	for (int i=0; i < EnemyNum; i++)
	{
		int RandomX = distX(gen);
		int RandomY = distY(gen);
		int Level = i;

		Enemies.emplace_back(Level, make_pair( RandomX, RandomY ));
	}


	int EXP = 0;
	int GetEXP = 4;
	int NeedEXP = 10;
	int Level = 1;

	while (Player.isAlive)
	{
		//Input();
		//_getch();
		pair<int, int> Direction = Player.KeyProcess();
		system("cls");
		Player.CharacterPosition.first += Direction.first;
		Player.CharacterPosition.second += Direction.second;

		//엔진
		//Render();
		COORD Cur;
		Cur.X = Player.CharacterPosition.first;
		Cur.Y = Player.CharacterPosition.second;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

		cout << Player.CharacterShape << endl;

		for (int i = 0; i < EnemyNum; i++)
		{
			Enemies[i].Move();

			Cur.X = Enemies[i].CharacterPosition.first;
			Cur.Y = Enemies[i].CharacterPosition.second;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);

			cout << Enemies[i].CharacterShape << endl;

			if (Player.CharacterPosition == Enemies[i].CharacterPosition and Enemies[i].isAlive)
			{
				if (Enemies[i].Hit(Player.Level))
				{
					Enemies[i].isAlive = false;
					Enemies[i].CharacterShape = ' ';

					Player.LevelUp();
				}
				else
				{
					Player.HP -= 1;
				}
			}
		}

		if (Player.HP <= 0)
		{
			Player.isAlive = false;
		}

		//EXP += GetEXP;
		//cout << "GetEXP + ";
		//cout << GetEXP << endl;

		//if (EXP > NeedEXP)
		//{
		//	EXP = 0;
		//	NeedEXP *= 2;
		//	Level += 1;
		//	cout << "level up" << endl;
		//	cout << "level : "; cout << Level << endl;
		//}

	}

	return 0;
}

//pair<int, int> KeyProcess() {
//	int KeyInput = 0;
//	int MoveDirectionX = 0;
//	int MoveDirectionY = 0;
//	if (KeyInput = _getch()) // 키입력을 체크
//	{
//		switch (KeyInput) {
//		case UP: MoveDirectionY--; break;
//		case DOWN: MoveDirectionY++; break;
//		case LEFT: MoveDirectionX--; break;
//		case RIGHT: MoveDirectionX++; break;
//		case SPACE: break;
//		}
//
//		
//		return { MoveDirectionX, MoveDirectionY };
//	}
//
//	return { 0,0 };
//}
//
//void PlayerMove(int X, int Y)
//{
//	
//}