#include "UI.h"

//시작할때 기록된 정보 읽어옴
UI::UI()
{
	currentChoice = 17;		//현재 커서 위치
	selected = false;		//선택완료여부
	RankRead();
	rank = 1;

	//cleckExit읽기
	wifstream wif("gameinfo\\exit.txt");
	wif.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
	getline(wif, cleckExit);
	wif.close();
}

//파일읽기
void UI::ReadFile(const char* filename, wstring* wstr)
{
	int index = 0;
	wifstream wif(filename);

	wif.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));

	while (!wif.eof())
	{
		getline(wif, wstr[index]);
		index++;
	}
}		//사용후에 파일닫기 사용한곳에서

//시작할때 한번만 실행.. 이름 점수 기록을 가져옴
void UI::RankRead()
{
	//랭크읽어오기
	wfcin.open("gameinfo\\score.txt");

	while (!wfcin.eof())
	{
		player = new PlayerInfo();
		wfcin >> player->name;
		wfcin >> player->score;
		playerList.emplace_back(player);
	}

	wfcin.close();
}

UI::~UI() 
{
	for (auto player : playerList)	//playerList들 반환
		delete player;
}