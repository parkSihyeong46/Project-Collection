#pragma once
#include "CommonData.h"
#include "PlayerInfo.h"
#include "GameManager.h"
#include "SoundManager.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <list>
#include <string>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <iomanip>

using namespace std;

//공통으로 사용할것들만 입력
class UI
{
protected:
	CommonData *commonData = CommonData::GetInstance();
	GameManager gameManager;
	SoundManager soundManager;
	string choice = "☞";
	int currentChoice;			//현재 커서 위치
	bool selected;				//선택완료여부
	int LowestScore;
	wstring cleckExit;

	//랭킹관련
	wifstream wfcin;
	wofstream wfcout;
	list<PlayerInfo*> playerList;		//이름과 점수를 입력받아서 저장할 클래스의 리스트(구조체로할까 생각중)
	PlayerInfo* player;
	int rank;					//등수를 출력할때 사용할 변수
	
public:
	UI();			//시작시 실행할것들 (지금은 랭킹불러와서 scoreList에 저장)
	void ReadFile(const char* filename, wstring* wstr);
	void RankRead();					//랭킹 기록 불러오기
	virtual void Show() = 0;			//메뉴창 화면에 출력
	virtual void RankShow() = 0;		//랭킹 화면에 출력
	~UI();
};

