#pragma once

class CommonData {
private:
	static constexpr int mapSizeX = 31;
	static constexpr int mapSizeY = 21;
	int currentScore = 0;
	int board[mapSizeY][mapSizeX] = { 0 };
	int life; 

	static CommonData* commonDataInstance;
	CommonData() {};
public:
	static CommonData* GetInstance();
	static void ReleaseInstance();

	const int& GetMapSizeX();
	const int& GetMapSizeY();

	const int& GetCurrentScore();
	void SetCurrentScore(const int& score);

	void SetBoard(const int& x, const int& y,const int& character);
	const int GetBoard(const int& x, const int& y);

	const int& GetLife();
	void SetLife(const int& life);
};	

enum BoardInfo //55마리
{	
	BLANK,
	WALL,
	PLAYER,
	BULLET,
	SHIELD,
	HIT,
	OCTOPUS = 10,
	CRAB = 20,
	SQUID = 30,
	UFO
};