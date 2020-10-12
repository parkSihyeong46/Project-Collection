#include "GameUI.h"

GameUI::GameUI()
{
	index = 0;

	wfcin.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	wfcin.open("gameinfo\\decoration.txt");
	while (!wfcin.eof())
		getline(wfcin, decoration[index++]);

	wfcin.close();
}

void GameUI::show()
{
	gameManager.GotoXY(0, 0);
	setlocale(LC_ALL, "ko_KR.UTF8");
	for (int i = 0; i < 5; i++)
		wcout << decoration[i] << endl;
	setlocale(LC_ALL, "Korean");

	for (int i = 0; i < 3; i++) 
	{
		gameManager.GotoXY(commonData->GetMapSizeX() - 1, i + 1);
		cout << "★";
	}

	//score, life출력부
	gameManager.GotoXY(7, 2);
	cout << "score : " << commonData->GetCurrentScore();

	gameManager.GotoXY(20, 2);
	cout << "LIFE : " << commonData->GetLife();
}