#include "UfoEnemy.h"

UfoEnemy::UfoEnemy()
{
	Init();
}

void UfoEnemy::Init()
{
	srand((unsigned)time(NULL));

	ufo.SetIsSurv(false);
	SetRandomScore();
	moveDelay.SetDelayTime(300);
	spawnDelay.SetDelayTime(rand() % ((6000 - 5000) + 1) + 5000);

	pos.SetX(1);
	pos.SetY(1);
}

void UfoEnemy::Spawn()
{
	if (ufo.GetIsSurv())
		return;
	
	if (spawnDelay.CkEndDelay()) 
	{
		ufo.SetIsSurv(true);
		commonData->SetBoard(pos.GetX(), pos.GetY(), UFO);
	}
	
}

void UfoEnemy::SetRandomScore()
{
	ufo.SetEnemyScore((rand() % ((35 - 5) + 1) + 5) * 10);		//50~350 난수 생성
}

void UfoEnemy::Move()
{
	if (!(ufo.GetIsSurv() && moveDelay.CkEndDelay()))
		return;

	commonData->SetBoard(pos.GetX(), pos.GetY(), BLANK);

	switch (commonData->GetBoard(pos.GetX() + 1, pos.GetY()))
	{
	case WALL:
		DisapearUFO();
		break;
	default:
		pos.SetX(pos.GetX() + 1);
		commonData->SetBoard(pos.GetX(), pos.GetY(), UFO);
		break;
	}

}

void UfoEnemy::DisapearUFO()
{
	Init();
	SetRandomScore();
	spawnDelay.SetStartTime();
}

void UfoEnemy::Hit()
{
	effectManager->PrintHitEffect(pos);
	
	commonData->SetCurrentScore(commonData->GetCurrentScore() + ufo.GetEnemyScore());
	DisapearUFO();
}
