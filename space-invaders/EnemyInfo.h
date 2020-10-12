#pragma once
#include "Pos.h"
class EnemyInfo{
private:
	int enemyScore;			//점수
	bool isSurv;		//생존유무
	Pos pos;
public:
	const int& GetEnemyScore();
	void SetEnemyScore(const int& score);

	Pos& GetPos();

	const bool& GetIsSurv();
	void SetIsSurv(const bool& surv);
};

