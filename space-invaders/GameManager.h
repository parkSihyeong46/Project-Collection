#pragma once
#include "CommonData.h"
#include <iostream>
#include <Windows.h>
#include <fstream>

using namespace std;

class GameManager
{
private:
	CommonData *commonData = CommonData::GetInstance();
	wifstream wfcin;

	bool nextStage = false;
public:
	void GotoXY(const int& x, const int& y);			
	void InitBoard();						
	void Show();
	const bool CheckGameOver();
};

