#include "Bullet.h"

Bullet::Bullet(const int &x, const int &y, const bool& isPlayer)
{
	srand((unsigned)time(NULL));

	if (isPlayer) 
	{
		dir = -1;
		moveDelay.SetDelayTime(40);
	}
	else 
	{
		dir = 1;

		int temp = rand() % 3;

		if (temp == 1) 
			moveDelay.SetDelayTime(130);
		else
			moveDelay.SetDelayTime(80);
	}
		
	pos.SetX(x);
	pos.SetY(y + dir);

	isCrash = -1;

	commonData->SetBoard(pos.GetX(),pos.GetY(), BULLET);
}

Pos& Bullet::GetPos()
{
	return pos;
}

void Bullet::SetSurv(const bool& surv)
{
	isSurv = surv;
}

const bool& Bullet::GetSurv()
{
	return isSurv;
}

const int Bullet::Move()
{
	isCrash = IsHit();
	if (isCrash != BLANK && isCrash != BULLET)		//공백이나 자기자신아니면 충돌한놈 반환
		return isCrash;

	if (!isSurv)
		return BLANK;

	if (moveDelay.CkEndDelay()) 
	{
		commonData->SetBoard(pos.GetX(), pos.GetY(), BLANK);
		pos.SetY(pos.GetY() + dir);

		//총알이 움직이고나서 적이나 캐릭터 충돌여부 반환
		isCrash = IsHit();
		if (isCrash != BLANK && isCrash != BULLET)
			return isCrash;

		commonData->SetBoard(pos.GetX(), pos.GetY(), BULLET);
	}
	
	//아무것도 충돌안했으면 BLANK반환
	return BLANK;
}	


const int Bullet::IsHit()
{
	if (commonData->GetBoard(pos.GetX(), pos.GetY()) == HIT)
		return BLANK;
	else
		return commonData->GetBoard(pos.GetX(), pos.GetY());
}
