#include "MenuUI.h"
#include <locale>
#include <codecvt>
//시작할때 기록된 정보 읽어옴
MenuUI::MenuUI() : UI(), gameStart(17), infoShow(19), rankShow(21)
{
	//게임타이틀불러오기
	ReadFile("gameinfo\\gameTitle.txt", gameTitle);
	wfcin.close();

	//적정보불러오기
	ReadFile("gameinfo\\enemyInfo.txt", enemy);
	wfcin.close();

	//메뉴선택창문구 불러오기
	ReadFile("gameinfo\\menu_select.txt", menuSelect);
	wfcin.close();

	//게임설명불러오기
	ReadFile("gameinfo\\game_info.txt", gameInfo);
	wfcin.close();

}

//선택메뉴출력
void MenuUI::Show()
{
	if (-1 == _setmode(_fileno(stdout), _O_U8TEXT))
		exit(0);

	for (int i = 0; i < 5; i++)
	{
		gameManager.GotoXY(3, 5 + i);
		wcout << gameTitle[i];
	}
	
	gameManager.GotoXY(15, 4);
	for (int i = 0; i < 4; i++)
	{
		gameManager.GotoXY(25, 12+i);
		wcout << enemy[i];
	}

	gameManager.GotoXY(25, 17);
	wcout << menuSelect[0];
	gameManager.GotoXY(25, 19);
	wcout << menuSelect[1];
	gameManager.GotoXY(25, 21);
	wcout << menuSelect[2];

	if (-1 == _setmode(_fileno(stdout), _O_TEXT))
		exit(0);
}

//게임설명창
void MenuUI::Infomation()
{
	if (-1 == _setmode(_fileno(stdout), _O_U8TEXT))
		exit(0);

	system("cls");
	for (int i = 0; i < 11; i++)
	{
		gameManager.GotoXY(4, 4 + i);
		wcout << gameInfo[i];
	}

	gameManager.GotoXY(4, 18);
	wcout << cleckExit << endl;
	cin.get();
	Select();

	if (-1 == _setmode(_fileno(stdout), _O_TEXT))
		exit(0);
}

//선택메뉴
void MenuUI::Select()
{
	system("cls");
	Show();

	soundManager.PlayMenuBGM();

	gameManager.GotoXY(22, currentChoice);		// 최초 커서 표시
	cout << choice;

	while (true)
	{
		if (_kbhit())					//키보드누르면
		{
			if (224 == _getch())		//방향키입력받기위해사용
			{					
				switch (_getch())			//키입력받고
				{
				case 72:			//위로이동
					if (currentChoice <= 17)
						break;

					soundManager.PlaySelectSound();
					gameManager.GotoXY(22, currentChoice);
					cout << "  ";
					currentChoice -= 2;
					gameManager.GotoXY(22, currentChoice);
					cout << choice;
					break;

				case 80:							//아래로 이동
					if (currentChoice >= 21)
						break;

					soundManager.PlaySelectSound();
					gameManager.GotoXY(22, currentChoice);
					cout << "  ";
					currentChoice += 2;
					gameManager.GotoXY(22, currentChoice);
					cout << choice;
					break;
				}
			}
			else
				break;
		}
	}

	if (currentChoice == gameStart)
	{
		soundManager.StopBGM();
		return;
	}
	else if (currentChoice == infoShow)
		Infomation();
	else if (currentChoice == rankShow)
	{
		RankShow();
		Select();
	}

	
}

//랭킹출력.. 뭔가 디자인 별로 수정필요
void MenuUI::RankShow()
{
	system("cls");
	cout.setf(ios::left);
	for (auto player : playerList)
	{
		gameManager.GotoXY(22, rank + 3);
		string str = to_string(rank) + "등";

		cout.width(5);
		cout << str;
		wcout.width(10);

		if (-1 == _setmode(_fileno(stdout), _O_U8TEXT))
			exit(0);
		
		wcout.setf(ios::left);
		wcout << player->name;
		wcout << player->score;

		if (-1 == _setmode(_fileno(stdout), _O_TEXT))
			exit(0);
		cout << "점";
		rank++;
	}

	if (-1 == _setmode(_fileno(stdout), _O_U8TEXT))
		exit(0);
	rank = 1;
	wcout << endl << endl << cleckExit << endl;
	cin.get();

	if (-1 == _setmode(_fileno(stdout), _O_TEXT))
		exit(0);
}