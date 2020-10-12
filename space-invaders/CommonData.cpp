#include "CommonData.h"

CommonData* CommonData::commonDataInstance = nullptr;

CommonData* CommonData::GetInstance()
{
	if(commonDataInstance == nullptr)
		commonDataInstance = new CommonData;

	return commonDataInstance;
}

void CommonData::ReleaseInstance()
{
	if (commonDataInstance)
	{
		delete commonDataInstance;
		commonDataInstance = nullptr;
	}
}

const int& CommonData::GetMapSizeX()
{
	return mapSizeX;
}

const int& CommonData::GetMapSizeY()
{
	return mapSizeY;
}

const int& CommonData::GetCurrentScore() 
{
	return currentScore;
}

void CommonData::SetCurrentScore(const int& score) 
{
	currentScore = score;
}

void CommonData::SetBoard(const int& x, const  int& y ,const int& character) 
{
	if (!(x >= 0 && x <= (mapSizeX - 1)))
		return;		//x범위 초과

	if (!(y >= 0 && y <= (mapSizeY - 1)))
		return;		//y범위 초과

	board[y][x] = character;
}

const int CommonData::GetBoard(const int& x,const int& y)
{
	if (!(x >= 0 && x <= (mapSizeX - 1)))
		return -1;		//x범위 초과
	
	if (!(y >= 0 && y <= (mapSizeY - 1)))
		return -2;		//y범위 초과

	return board[y][x];
}

const int& CommonData::GetLife()
{
	return life;
}

void CommonData::SetLife(const int& life) 
{
	this->life = life;
}

