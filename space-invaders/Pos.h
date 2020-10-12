#pragma once
class Pos
{
private:
	int x;
	int y;
public:
	const int& GetX();
	void SetX(const int &x);

	const int& GetY();
	void SetY(const int &y);
};

