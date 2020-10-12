#include "Enemy.h"

Enemy::Enemy()
{
	Init();
}

void Enemy::Init()
{
	NextStage();

	moveDelay.SetDelayTime(1000);
	roundCount = 0;
}

void Enemy::Move()
{
	if (!moveDelay.CkEndDelay())
		return;

	if (isWall == false) 
	{
		if (CkWall())
			isWall = true;
	}
	else
		isWall = false;

	if (dir > 0 && isWall == false) 
	{
		for (int enemyIndex = ENEMY_SIZE - 1; enemyIndex >= 0; enemyIndex--)
		{
			if (enemy[enemyIndex].GetIsSurv())
			{
				commonData->SetBoard(enemy[enemyIndex].GetPos().GetX(), enemy[enemyIndex].GetPos().GetY(), BLANK);
				enemy[enemyIndex].GetPos().SetX(enemy[enemyIndex].GetPos().GetX()+ dir);
				commonData->SetBoard(enemy[enemyIndex].GetPos().GetX(), enemy[enemyIndex].GetPos().GetY(), enemy[enemyIndex].GetEnemyScore());
			}
		}
	}
	else if (dir < 0 && isWall == false) 
	{
		for (int enemyIndex = 0; enemyIndex < ENEMY_SIZE; enemyIndex++) 
		{
			if (enemy[enemyIndex].GetIsSurv()) 
			{
				commonData->SetBoard(enemy[enemyIndex].GetPos().GetX(), enemy[enemyIndex].GetPos().GetY(), BLANK);
				enemy[enemyIndex].GetPos().SetX(enemy[enemyIndex].GetPos().GetX() + dir);
				commonData->SetBoard(enemy[enemyIndex].GetPos().GetX(), enemy[enemyIndex].GetPos().GetY(), enemy[enemyIndex].GetEnemyScore());
			}
		}
	}
	else 
	{
		for (int enemyIndex = ENEMY_SIZE - 1; enemyIndex >= 0; enemyIndex--) 
		{
			if (enemy[enemyIndex].GetIsSurv()) 
			{
				commonData->SetBoard(enemy[enemyIndex].GetPos().GetX(), enemy[enemyIndex].GetPos().GetY(), BLANK);
				enemy[enemyIndex].GetPos().SetY(enemy[enemyIndex].GetPos().GetY() + 1);
				commonData->SetBoard(enemy[enemyIndex].GetPos().GetX(), enemy[enemyIndex].GetPos().GetY(), enemy[enemyIndex].GetEnemyScore());
			}
		}
		moveDelay.SetDelayTime(moveDelay.GetDelayTime() - 20);
		dir *= -1;
	}
	
}

void Enemy::ShotBulletMove()
{
	if (bullet.size() <= 0)
		return;

	int temp;
	for (auto bullets : bullet)
	{
		temp = bullets->Move();

		switch (temp)
		{
		case WALL:		bullets->SetSurv(false);
			break;
		case PLAYER:	bullets->SetSurv(false);
			isPlayer = true;
			break;
		case SHIELD:	bullets->SetSurv(false);
			commonData->SetBoard(bullets->GetPos().GetX(), bullets->GetPos().GetY(), BLANK);
			break;
		}
	}
	
	RemoveBullet();
}

const bool Enemy::CkWall()
{
	for (auto enemies : enemy)
	{
		if (enemies.GetIsSurv())
		{
			if ((enemies.GetPos().GetX() + 1) == (commonData->GetMapSizeX() - 1))
				return true;	//벽 옆이면 1리턴
			if ((enemies.GetPos().GetX() - 1) == 0)
				return true;
		}
	}

	return false; //벽 X 0리턴
}

void Enemy::Shot()
{
	int count = 0;
	randomShotAbleIndex = rand() % 11; // 랜덤 인덱스 설정
	shotDelay.SetDelayTime((rand() % ((5000 - 1000) + 1) + 1000));

	if (!(shotDelay.CkEndDelay()))
		return;
	
	for (auto shotAbleIndex : shotAbleEnemy)
	{
		if (count == randomShotAbleIndex)
		{
			enemy[shotAbleIndex].GetPos().GetX();
			bullet.emplace_back(new Bullet(enemy[shotAbleIndex].GetPos().GetX(), enemy[shotAbleIndex].GetPos().GetY(), false));
			break;
		}
		count++;
	}
}

void Enemy::RemoveBullet()
{
	for (auto bullets = bullet.begin(); bullets != bullet.end();) 
	{
		if (!(*bullets)->GetSurv()) 
		{
			delete(*bullets);
			bullet.erase(bullets++);
			bulletHit = false;
			break;
		}
		else
			bullets++;
	}
}

void Enemy::Hit(const int &x, const int& y)
{
	int index = 0;

	for (auto enemies : enemy)
	{
		if (enemies.GetPos().GetX() == x && enemies.GetPos().GetY() == y)
			break;
		index++;
	}

	enemy[index].SetIsSurv(false);
	commonData->SetCurrentScore(commonData->GetCurrentScore() + enemy[index].GetEnemyScore());

	Pos pos;

	pos.SetX(enemy[index].GetPos().GetX());
	pos.SetY(enemy[index].GetPos().GetY());
	effectManager->PrintHitEffect(pos);

	moveDelay.SetDelayTime(moveDelay.GetDelayTime() - ((ENEMY_SIZE - CkEnemyCount()) / 2));
	SetShotAbleEnemies();
}

const bool Enemy::IsPlayertHit() 
{
	if (isPlayer == true) 
	{
		isPlayer = false;
		return true;
	}

	return false;
}

const int Enemy::CkEnemyCount()
{
	int count = 0;
	for (int enemyIndex = 0; enemyIndex < ENEMY_SIZE; enemyIndex++)
	{
		if (enemy[enemyIndex].GetIsSurv())
			count++;
	}
	return count;
}

void Enemy::SetShotAbleEnemies()
{
	bool loop = true;				//샤격불가 = -1 / 그 이외엔 다음샤격가능 적 설정
	for (auto shotAbleIndex = shotAbleEnemy.begin(); shotAbleIndex != shotAbleEnemy.end(); shotAbleIndex++) 
	{
		if (!enemy[*shotAbleIndex].GetIsSurv()) 
		{
			while (loop) 
			{
				if ((0 <= (*shotAbleIndex - ENEMIES_IN_LINE))) 
				{
					if (enemy[*shotAbleIndex - ENEMIES_IN_LINE].GetIsSurv()) 
					{
						*shotAbleIndex = *shotAbleIndex - ENEMIES_IN_LINE;
						loop = false;
					}
					else
						*shotAbleIndex = *shotAbleIndex - ENEMIES_IN_LINE;
				}
				else 
				{
					*shotAbleIndex = -1;
					loop = false;
				}
			}
		}
	}

	//만약 -1로 설정되었다면 그 값 삭제
	for (auto shotAbleEnemies = shotAbleEnemy.begin(); shotAbleEnemies != shotAbleEnemy.end();) 
	{
		if (*shotAbleEnemies == -1)
			shotAbleEnemy.erase(shotAbleEnemies++);
		else
			shotAbleEnemies++;
	}
}

void Enemy::SetSpawnPos()
{
	int tempIndex = 0;

	//보드판 정보로 스폰위치 설정
	for (int y = 0; y < (commonData->GetMapSizeY() - 1); y++) 
	{
		for (int x = 0; x < (commonData->GetMapSizeX() - 1); x++) 
		{
			switch (commonData->GetBoard(x, y)) 
			{
			case SQUID:
			case CRAB:
			case OCTOPUS:
				enemy[tempIndex].SetIsSurv(TRUE);
				enemy[tempIndex].GetPos().SetX(x);
				enemy[tempIndex].GetPos().SetY(y);
				enemy[tempIndex].SetEnemyScore(commonData->GetBoard(x, y));
				tempIndex++;
				break;
			default:
				break;
			}
		}
	}
}

void Enemy::SetShotAbleEnemy()
{
	shotAbleEnemy.clear();
	for (int shotEnemyIndex = (ENEMY_SIZE - 1); shotEnemyIndex > ((ENEMY_SIZE - 1) - ENEMIES_IN_LINE); shotEnemyIndex--)	//사격가능 적위치 설정
		shotAbleEnemy.emplace_back(shotEnemyIndex);		//발사 가능 적들 설정
}

void Enemy::NextStage()
{
	srand((unsigned)time(NULL));

	isWall = false;

	SetShotAbleEnemy();

	roundCount++;
	moveDelay.SetDelayTime(1000-(roundCount*30));
	dir = 1;

	SetSpawnPos();
}

void Enemy::ClearDynamicAlloc()
{
	for (auto bulletIndex = bullet.begin(); bulletIndex != bullet.end(); bulletIndex++)
		delete(*bulletIndex);

	bullet.clear();
}
