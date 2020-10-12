#include "EffectManager.h"

EffectManager* EffectManager::effectManagerInstance = nullptr;

EffectManager* EffectManager::GetEffectInstance()
{
	if (effectManagerInstance == nullptr)
		effectManagerInstance = new EffectManager;
	return effectManagerInstance;
}

void EffectManager::ReleaseEffectInstance()
{
	if (effectManagerInstance)
	{
		delete effectManagerInstance;
		effectManagerInstance = nullptr;
	}
}

void EffectManager::Init()
{
	delayManager.clear();
	hitPosList.clear();

	deleteIndex = 0;
	deleteCount = 0;
	isDelete = false;
}

void EffectManager::PrintHitEffect(Pos& pos)
{
	soundManager.PlayEffectSound();
	delayManager.emplace_back(new DelayManager());

	hitPosList.emplace_back(pos); 

	commonData->SetBoard(pos.GetX(), pos.GetY(), HIT);
}

void EffectManager::DeleteHitEffect()
{
	deleteIndex = 0;
	deleteCount = 0;
	isDelete = false;

	for (auto effectDelay = delayManager.begin(); effectDelay != delayManager.end(); effectDelay++)
	{
		if ( (*effectDelay)->CkEndDelay() )
		{
			delete(*effectDelay);
			delayManager.erase(effectDelay);
			isDelete = true;
			break;
		}
		else
			deleteIndex++;
	}

	if (isDelete == false)
		return;

	for (auto effectPos = hitPosList.begin(); effectPos != hitPosList.end(); effectPos++)
	{
		if (deleteCount == deleteIndex) 
		{
			if (commonData->GetBoard((*effectPos).GetX(), (*effectPos).GetY()) == HIT)
			{
				commonData->SetBoard((*effectPos).GetX(), (*effectPos).GetY(), BLANK);
				hitPosList.erase(effectPos);
				break;
			}
			else
			{
				hitPosList.erase(effectPos);
				break;
			}
		}
		else
			deleteCount++;	
	}
}
