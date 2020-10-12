#include "EnemyInfo.h"

const int& EnemyInfo::GetEnemyScore()
{
	return enemyScore;
}

void EnemyInfo::SetEnemyScore(const int& score)
{
	enemyScore = score;
}

Pos& EnemyInfo::GetPos()
{
	return pos;
}

const bool& EnemyInfo::GetIsSurv()
{
	return isSurv;
}

void EnemyInfo::SetIsSurv(const bool& surv)
{
	isSurv = surv;
}
