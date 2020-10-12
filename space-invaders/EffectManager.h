#pragma once
#include "CommonData.h"
#include "SoundManager.h"
#include "Pos.h"
#include "DelayManager.h"
#include <list>
#include <ctime>

class EffectManager
{
private:
	list<DelayManager *> delayManager;
	list<Pos> hitPosList;

	CommonData *commonData = CommonData::GetInstance();
	SoundManager soundManager;

	int deleteIndex = 0;
	int deleteCount = 0;

	bool isDelete = false;

	static EffectManager* effectManagerInstance;
	EffectManager() {};
public:
	static EffectManager* GetEffectInstance();
	static void ReleaseEffectInstance();

	void Init();

	void PrintHitEffect(Pos& pos);

	void DeleteHitEffect();
};

