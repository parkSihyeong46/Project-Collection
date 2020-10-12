#include "GameOverUI.h"

//시작할때 기록된 정보 읽어옴
GameOverUI::GameOverUI() : UI(), replayGame(17), rankingShow(19), gameExit(21), rankingUpdate(5), rankExit(7)
{
	//gameover타이틀 불러오기
	ReadFile("gameinfo\\gameoverTitle.txt", gameoverTitle);
	wfcin.close();

	//게임종료선택창불러오기
	ReadFile("gameinfo\\gameover_select.txt", gameoverSelect);
	wfcin.close();

	reGame = false;
	rankChoice = 5;
	chance = 1;

	score = commonData->GetCurrentScore();		//현재 점수값 저장

	//왜 경고표시뜨는지 모르겠음 초기화했는데 초기화안됬다고...
	LowestScore = playerList.back()->score;		//최하점수값 받아옴
}

//선택메뉴출력
void GameOverUI::Show()
{
	_setmode(_fileno(stdout), _O_U8TEXT);

	system("cls");
	
	for (int i = 0; i < 5; i++)
	{
		gameManager.GotoXY(3, 5 + i);
		wcout << gameoverTitle[i] << endl;
	}

	gameManager.GotoXY(25, 17);
	wcout << gameoverSelect[0];
	gameManager.GotoXY(25, 19);
	wcout << gameoverSelect[1];
	gameManager.GotoXY(25, 21);
	wcout << gameoverSelect[2];

	_setmode(_fileno(stdout), _O_TEXT);
}

//선택메뉴
const bool& GameOverUI::Select()
{
	reGame = false;
	system("cls");
	Show();

	gameManager.GotoXY(22, currentChoice);		// 최초 커서 표시
	cout << choice;

	soundManager.StopBGM();
	soundManager.PlayMenuBGM();

	while (true)
	{
		if (_kbhit())					//키보드누르면
		{
			if (224 == _getch())		//방향키입력받기위해사용
			{
				switch (_getch())				//키입력받고
				{
				case 72:							//위로이동
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

	if (currentChoice == replayGame)		//게임다시시작하기
	{
		reGame = true;
		chance = 1;
		soundManager.StopBGM();
		soundManager.PlayGameBGM();
	}
	else if (currentChoice == rankingShow)
		RankShow();
	else if (currentChoice == gameExit)		//게임종료
		soundManager.StopBGM();

	return reGame;
}

//랭킹출력.. 뭔가 디자인 별로 수정필요
void GameOverUI::RankShow()
{
	score = commonData->GetCurrentScore();		//현재 점수값 저장
	LowestScore = playerList.back()->score;		//최하점수값 받아옴
	rankChoice = 5;

	system("cls");
	//랭킹출력(1등~10등)
	for (auto player : playerList)
	{
		gameManager.GotoXY(22, rank + 3);
		string str = to_string(rank) + "등";

		cout.setf(ios::left);
		cout.width(5);
		cout << str;
		wcout.setf(ios::left);
		wcout.width(10);
		_setmode(_fileno(stdout), _O_U8TEXT);
		wcout << player->name;
		wcout.setf(ios::left);
		wcout << player->score;
		_setmode(_fileno(stdout), _O_TEXT);
		cout << "점";
		rank++;
	}

	rank = 1;

	gameManager.GotoXY(40, rankChoice);		// 최초 커서 표시
	cout << choice;
	gameManager.GotoXY(42, rankChoice);
	cout << "기록 입력하기";
	gameManager.GotoXY(42, rankChoice + 2);
	cout << "나가기";

	while (true)
	{
		if (_kbhit())					//키보드누르면
		{
			if (224 == _getch())		//방향키입력받기위해사용
			{
				switch (_getch())		//키입력받고
				{
				case 72:			//위로이동
					if (rankChoice != rankExit)
						break;

					gameManager.GotoXY(40, rankChoice);
					cout << "    " << endl;
					rankChoice -= 2;
					gameManager.GotoXY(40, rankChoice);
					cout << choice;
					break;
				case 80:			//아래로 이동
					if (rankChoice != rankingUpdate)
						break;
					
					gameManager.GotoXY(40, rankChoice);
					cout << "   " << endl;
					rankChoice += 2;
					gameManager.GotoXY(40, rankChoice);
					cout << choice;
					break;
				}
			}
			else
				break;
		}
	}

	//랭킹업데이트선택 + 최하점수이상 + 업데이트기회있으면 실행
	if (rankChoice == rankingUpdate && score >= LowestScore && 1 == chance)
	{
		chance--;
		gameManager.GotoXY(22, 20);
		
		////stdin에 *넣고 이전에 입력받은것들 모두 지워버리는문장
		//freopen("sentinel.txt", "r", stdin);
		//fclose(stdin);
		//cin.ignore(100, '*');		//센티널값으로 *사용

		cout << "이름을 입력하세요 : ";				wcin >> name;
		RankRecord(name, score);
		Select();
	}
	else if (rankChoice == rankExit)
		Select();
	else
	{
		gameManager.GotoXY(22, 20);
		cout << "점수가 10위내에 들지 못하거나, 이미 기록을 입력하셨습니다..!";
		cin.get();
		Select();
	}
}

//이름과 점수를 매개변수로 주면 점수에 따라 갱신됨
void GameOverUI::RankRecord(const wstring inputName, const int inputScore)
{
	//입력받은 이름과 점수 추가
	player = new PlayerInfo();
	player->name = inputName;
	player->score = inputScore;
	playerList.emplace_back(player);

	//입력받은이름점수 추가후 정렬하기
	//auto와 범위for문 안쓰고 iterator정의해서 사용한 이유
	//1. iterator를 for범위밖에서도 사용해야함
	//2. 범위for문은 중간부터 연산이 불가능함(무조건 처음부터 끝까지),, 가능해도 더 복잡해지는걸로 알고있음
	rankIt = playerList.begin();
	for (int i = 0; i < 11; i++)
	{
		for (rankIt; rankIt != playerList.end(); rankIt++)
		{
			if ((*rankIt)->score < minValue)
			{
				minValue = (*rankIt)->score;
				tempIt = rankIt;
			}
		}

		playerList.insert(playerList.begin(), *tempIt);			//맨앞에 젤 작은놈 추가
		playerList.erase(tempIt);								//추가한놈 삭제
		minValue = 100000000;

		for (int k = -1; k < i; k++)			//앞에놔둔거는 비교안하기
		{
			if (k == -1)
				rankIt = playerList.begin();
			rankIt++;
		}
	}
	playerList.pop_back();		//크기순으로 정렬후 맨뒤에 있는놈은 삭제 (10위까지만 기록)

	wfcout.open("gameinfo\\score.txt");

	for (auto player : playerList) {
		if(player == (*(--playerList.end())))
			wfcout << player->name << L" " << player->score;
		else
			wfcout << player->name << L" " << player->score << endl;
	}

	wfcout.close();
}