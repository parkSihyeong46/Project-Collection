#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "UI.h"

class GameOverUI : public UI
{
	wstring gameoverTitle[5];
	wstring gameoverSelect[3];
	const int replayGame;
	const int rankingShow;
	const int gameExit;
	const int rankingUpdate;
	const int rankExit;
	int score;
	int Lowestscore;
	bool reGame;
	int chance;		//기록을 입력할 수 있는 기회
	

	//순위변동에 사용할 변수들
	list<PlayerInfo*>::iterator tempIt;		//랭킹 순위변동에 사용할 반복자
	list<PlayerInfo*>::iterator rankIt;
	int minValue = 10000000;				//순위변동에 사용할 변수
	wstring name;
	int rankChoice;

public:
	GameOverUI();				//시작시 실행할것들 (지금은 랭킹불러와서 scoreList에 저장)
	void Show();				//메뉴창 화면에 출력
	const bool& Select();				//메뉴창에서 선택을 입력받음
	void RankShow();
	void RankRecord(const wstring inputName, const int inputScore);		//랭킹 기록하기( 나중에 게임끝나고 점수와 이름입력받으면 10위안에 드는지 확인후 랭킹기록)
};
