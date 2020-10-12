#include "Player.h"

Player::Player()
{
	position.SetX((commonData->GetMapSizeX() / 2) - 1);
	position.SetY(commonData->GetMapSizeY() - 2);

	respwanPosition.SetX((commonData->GetMapSizeX() / 2) - 1);
	respwanPosition.SetY(commonData->GetMapSizeY() - 2);

	Init();
}

void Player::Move() 
{
	if (_kbhit())						//키보드누르면
	{
		key = _getch();
		if (224 == key)					//방향키입력받기위해사용
		{
			key = _getch();
			switch (key)				//키입력받고
			{
			case 75:		//좌측이동
				if (position.GetX() <= 1)		//좌측벽에 부딪힐때
					return;
				
				commonData->SetBoard(position.GetX(), position.GetY(), BLANK);
				position.SetX(position.GetX()-1);
				commonData->SetBoard(position.GetX(), position.GetY(), PLAYER);
				break;
			case 77:		//우측 이동
				if (position.GetX() >= commonData->GetMapSizeX() - 2)			//우측벽에 부딪힐때
					return;

				commonData->SetBoard(position.GetX(), position.GetY(), BLANK);
				position.SetX(position.GetX() + 1);
				commonData->SetBoard(position.GetX(), position.GetY(), PLAYER);
				break;
			}
		}
		else if (32 == key)		//스페이스바 : 총알발사
		{
			if (!shootable)		//발사중이아니면
				return;

			bullet = new Bullet(position.GetX(), position.GetY(), true);		//총알생성
			isShoot = true;					//총알발사여부판단
			shootable = false;				//총알발사가능여부
		}
	}
}

void Player::Shoot()
{
	if (!isShoot)									//총알이발사중이면
		return;

	isCrash = bullet->Move();			//총알움직이기

	switch (isCrash)						//충돌한놈의 정보 기록
	{
		case WALL:
			RemoveBullet();
			break;

		case BLANK:
		case HIT:
			break;

		default:
			hitInfo[0] = true;
			hitInfo[1] = bullet->GetPos().GetX();
			hitInfo[2] = bullet->GetPos().GetY();
			hitInfo[3] = isCrash;
			RemoveBullet();
	}
	isCrash = -1;
}

//총알발사중이면 총알삭제
void Player::RemoveBullet()
{
	if (!isShoot)
		return;

	if (-1 == commonData->GetBoard(bullet->GetPos().GetX(), bullet->GetPos().GetY()))		//총알위치값이 제대로 전송됬는지 검사
		return;

	if(commonData->GetBoard(bullet->GetPos().GetX(), bullet->GetPos().GetY()) != WALL)
		commonData->SetBoard(bullet->GetPos().GetX(), bullet->GetPos().GetY(), BLANK);

	isShoot = false;
	shootable = true;
	delete bullet;
	bullet = NULL;

}

//총알맞을경우 실행하기.. true반환하면 게임오버
bool Player::Respwan()
{
	if (life > 1)		//라이프있으면 실행
	{
		gameManager.GotoXY(position.GetX(), position.GetY() + 5);
		cout << "※";
		gameManager.GotoXY(position.GetX() - 1, position.GetY() + 5);
		cout << "  ";
		gameManager.GotoXY(position.GetX() + 1, position.GetY() + 5);
		cout << "  ";
		Sleep(1000);

		//캐릭터위치 리스폰
		commonData->SetBoard(position.GetX(), position.GetY(), BLANK);
		position.SetX(respwanPosition.GetX());
		position.SetY(respwanPosition.GetY());
		commonData->SetBoard(position.GetX(), position.GetY(), PLAYER);

		//총알삭제
		RemoveBullet();
		commonData->SetLife(--life);
		return false;
	}
	else
		return true;

}

//총알 맞췃을때 실행...  맞췄다는 정보와 맞춘놈의 좌표를 저장
int* Player::Hit() 
{
	return hitInfo;
}

void Player::Init()
{
	life = 3;

	commonData->SetLife(life);
	commonData->SetBoard(position.GetX(), position.GetY(), BLANK);
	position.SetX(respwanPosition.GetX());
	position.SetY(respwanPosition.GetY());
	commonData->SetBoard(position.GetX(), position.GetY(), PLAYER);

	RemoveBullet();
}