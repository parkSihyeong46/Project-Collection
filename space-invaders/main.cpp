#include <iostream>
#include "UI.h"
#include "MenuUI.h"
#include "GameUI.h"
#include "GameOverUI.h"
#include "CommonData.h"
#include "GameManager.h"
#include "Enemy.h"
#include "Player.h"
#include "UfoEnemy.h"
#include "EffectManager.h"
#include "SoundManager.h"

using namespace std;

int main(void)
{
	//커서 사라지게만듦
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	//사용할 변수들 선언
	CommonData *commonData = CommonData::GetInstance();
	GameManager gameManager;
	gameManager.InitBoard();
	EffectManager *effectManager = EffectManager::GetEffectInstance();
	MenuUI menuUI;
	GameUI gameUI;
	GameOverUI gameoverUI;
	Enemy enemy;
	UfoEnemy ufo;
	Player player;
	SoundManager soundManager;

	int* enemyCrashInfo = NULL;
	bool isGameover = false;
	bool restartGame = false;


	menuUI.Select();
	soundManager.PlayGameBGM();

	system("cls");
	while (true) 
	{
		gameUI.show();
		gameManager.Show();
		
		player.Move();
		enemy.Move();
		enemy.ShotBulletMove();
		ufo.Move();

		player.Shoot();
		enemy.Shot();

		ufo.Spawn();

		if (enemy.IsPlayertHit()) 
			isGameover = player.Respwan();

		ufo.Spawn();

		enemyCrashInfo = player.Hit();	//적과플레이어 충돌시 충돌관련정보값전송
		if (NULL == enemyCrashInfo)		//충돌해서 적의값을 받으면 실행
			continue;

		//플레이어의 총알이 적을 맞췄을 때
		if (1 == enemyCrashInfo[0]) 
		{
			switch (enemyCrashInfo[3]) 
			{
			case OCTOPUS:
			case CRAB:
			case SQUID:
				enemy.Hit(enemyCrashInfo[1], enemyCrashInfo[2]);
				enemyCrashInfo[0] = false;
				break;
			case UFO:
				ufo.Hit();
				enemyCrashInfo[0] = false;
				break;
			case SHIELD:
				commonData->SetBoard(enemyCrashInfo[1], enemyCrashInfo[2], BLANK);
				enemyCrashInfo[0] = false;
				break;
			default:
				break;
			}
		}

		//life모두잃었을때
		if (isGameover) 
		{
			soundManager.StopBGM();

			restartGame = gameoverUI.Select();

			if (true == restartGame) 
			{
				commonData->SetCurrentScore(0);
				gameManager.InitBoard();
				enemy.Init();
				player.Init();
				restartGame = false;
				isGameover = false;
				system("cls");
			}
			else
				break;
		}

		if (gameManager.CheckGameOver()) 
		{
			restartGame = gameoverUI.Select();
			enemy.ClearDynamicAlloc();	//동적할당 해제

			if (restartGame == true) 
			{
				commonData->SetCurrentScore(0);
				gameManager.InitBoard();
				effectManager->Init();
				enemy.Init();
				player.Init();
				ufo.Init();
				restartGame = false;
				isGameover = false;
				system("cls");
			}
			else
				break;
		}

		//적을모두 죽였을 때
		if (0 == enemy.CkEnemyCount()) 
		{
			commonData->SetCurrentScore(commonData->GetCurrentScore() + 1000);
			gameManager.InitBoard();
			player.Init();
			ufo.Init();
			commonData->SetLife(commonData->GetLife() + 1);
			enemy.NextStage();
			restartGame = false;
			isGameover = false;
			system("cls");
		}
		

		effectManager->DeleteHitEffect();
	}
	commonData->ReleaseInstance();
	effectManager->ReleaseEffectInstance();

	return 0;
}
