#pragma once
#include <Windows.h>
#include <random>
#include "CommonData.h"
#include "DelayManager.h"
#include "Pos.h"

class Bullet{
private:
	CommonData *commonData = CommonData::GetInstance();
	DelayManager moveDelay;
	Pos pos;

	int dir;								//총알방향
	bool isSurv = true;					//총알생존여부
	int isCrash;						//충돌한놈을 반환

public:
	Bullet(const int &x, const int &y,const bool& isPlayer);	//x,y좌표설정 및 3번째 매개변수 값으로 dir 결정
	Pos& GetPos();
	void SetSurv(const bool& surv);
	const bool& GetSurv();
	const int Move(); //벽 접촉 시 0리턴 아니면 1리턴
	const int IsHit();
};
