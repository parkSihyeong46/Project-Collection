#pragma once
#include <random>
#include <list>
#include "GameManager.h"
#include "EffectManager.h"
#include "EnemyInfo.h"
#include "CommonData.h"
#include "Bullet.h"
#include "DelayManager.h"

class Enemy
{
private:
	static constexpr int ENEMY_SIZE = 55;
	static constexpr int ENEMY_SPAWNSPOT = 9;
	const int ENEMIES_IN_LINE = 11;
	CommonData *commonData = CommonData::GetInstance();
	EffectManager *effectManager = EffectManager::GetEffectInstance();
	GameManager gameManager;
	DelayManager shotDelay;
	DelayManager moveDelay;

	list<Bullet*> bullet;

	int randomShotAbleIndex;	//랜덤 총알발사 인덱스 설정
	list<int> shotAbleEnemy;	//사격 가능한 적

	EnemyInfo enemy[ENEMY_SIZE];
	int dir;
	int roundCount = 0;

	bool isWall = false;
	bool isPlayer = false;
	bool bulletHit = false;
public:
	Enemy();
	void Init();
	void Move();
	void ShotBulletMove();
	const bool CkWall();
	void Shot();			//총알발사
	void RemoveBullet();	//쏜 총알 삭제
	void Hit(const int &x, const int &y);	//플레이어 총알에 맞았을 경우 죽는처리
	const bool IsPlayertHit();		//총알 접촉 유무 확인

	const int CkEnemyCount();		//현재 생존한 적 수 리턴
	void SetShotAbleEnemies();	//샤격 가능한 적 위치 수정

	void SetSpawnPos();	//시작 위치 설정
	void SetShotAbleEnemy();	//사격 가능 적들 설정

	void NextStage();
	void ClearDynamicAlloc();	//동적할당 해제
};	

 