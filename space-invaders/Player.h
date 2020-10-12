#pragma once
#include <iostream>
#include <conio.h>
#include "CommonData.h"
#include "GameManager.h"
#include "Bullet.h"
#include "Pos.h"

using namespace std;

class Player
{
	CommonData *commonData = CommonData::GetInstance();
	GameManager gameManager;
	Pos respwanPosition;
	Pos position;
	Bullet* bullet;
	bool isShoot = false;		//발사여부
	bool shootable = true;		//발사가능여부
	int isCrash = -1;				//맞춘놈의 정보를 가지고있음
	int hitInfo[4] = { 0 };			//충돌여부, x값, y값, 누구와충돌했는지
	int life;
	int key;

public:
	Player();
	void Move();			//캐릭터움직이기 및 총알발사
	void Shoot();			//총알움직이기
	bool Respwan();		//충돌시 새위치에서 다시시작
	void RemoveBullet();	//총알삭제
	int* Hit();						//적과 총알충돌시 보내줄 데이터를 보내는 메소드
	void Init();
};
