#include "GameManager.h"

void GameManager::GotoXY(const int& x, const int& y) 
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void GameManager::InitBoard() 
{
	//보드읽기
	wfcin.open("gameinfo\\board.txt");

	int temp = 0;
	int w = 0;
	int h = 0;

	while (!wfcin.eof()) 
	{
		if (w == 31) 
		{
			h++;
			w = 0;
		}
		temp = wfcin.get();
		if (temp != '\n' && temp != -1) 
		{
			switch (temp - 48) 
			{
			case 6:
				commonData->SetBoard(w, h, OCTOPUS);
				break;
			case 7:
				commonData->SetBoard(w, h, CRAB);
				break;
			case 8:
				commonData->SetBoard(w, h, SQUID);
				break;
			default:
				commonData->SetBoard(w, h, temp - 48);
				break;
			}

			w++;
		}
	}

	wfcin.close();
}

void GameManager::Show() 
{
	GotoXY(0, 5);
	for (int y = 0; y < commonData->GetMapSizeY(); y++) 
	{
		for (int x = 0; x < commonData->GetMapSizeX(); x++) 
		{
			switch (commonData->GetBoard(x, y)) 
			{
			case BLANK:
				cout << "  ";
				break;
			case WALL:
				cout << "■";
				break;
			case PLAYER:
				cout << "凸";
				break;
			case SHIELD:
				cout << "□";
				break;
			case UFO:
				cout << "◐";
				break;
			case OCTOPUS:
				cout << "♣";
				break;
			case CRAB:
				cout << "☎";
				break;
			case SQUID:
				cout << "♨";
				break;
			case BULLET:
				cout << "⊙";
				break;
			case HIT:
				cout << "※";
				break;
			}
		}
		cout << endl;
	}
}

const bool GameManager::CheckGameOver()	//바닥 부분 점검해서 게임오버인지 확인
{
	for (int boardX = 0; boardX < commonData->GetMapSizeX(); boardX++)
	{
		switch (commonData->GetBoard(boardX, commonData->GetMapSizeY() - 2)) 
		{
		case OCTOPUS:
		case CRAB:
		case SQUID:
			return true;
		}
	}

	return false;
}
