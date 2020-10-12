#pragma once
#include "UI.h"

class MenuUI : public UI
{
	wstring gameTitle[5];
	wstring enemy[4];
	wstring menuSelect[3];
	wstring gameInfo[11];
	string choice = "☞";
	const int gameStart;
	const int infoShow;
	const int rankShow;

public:
	MenuUI();
	void Show();				//메뉴창 화면에 출력
	void Infomation();	//게임정보창 화면에 출력
	void Select();			//메뉴창에서 선택을 입력받음
	void RankShow();		//랭킹 화면에 출력
};

//currentchoice => 17 : 게임시작
//currentchoice => 19 : 설명서
//currentchoice => 21 : 랭킹보기


/*
■■■  ■■■    ■      ■■■■  ■■■■    ■■■■■  ■     ■   ■      ■     ■     ■■    ■■■■  ■■
■      ■  ■   ■■     ■        ■              ■      ■■   ■    ■    ■     ■■    ■  ■  ■        ■ ■
■■■  ■■■  ■  ■    ■        ■■■■        ■      ■ ■  ■     ■  ■     ■  ■   ■   ■ ■■■■  ■■ 
    ■  ■     ■ ■ ■   ■        ■              ■      ■  ■ ■      ■■     ■■■■  ■  ■  ■        ■ ■
■■■  ■    ■      ■  ■■■■  ■■■■    ■■■■■  ■   ■■       ■     ■      ■ ■■    ■■■■  ■  ■
*/

