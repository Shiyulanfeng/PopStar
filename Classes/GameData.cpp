#include "GameData.h"
#include "cocos2d.h"
USING_NS_CC;
GameData* GameData::m_pInstance = nullptr;
GameData* GameData::getInstance()
{
	if(m_pInstance == nullptr)
	{
		m_pInstance = new GameData();
	}
	return m_pInstance;
}

GameData::GameData()
{
	setCurLevel(0);
	setCurScore(0);
	setHighestScore(UserDefault::getInstance()->getIntegerForKey("highestScore",0));

}

void GameData::setCurLevel(int level)
{
	if(level < 0)
	{
		return;
	}
	m_nCurLevel = level;
	m_nNextLevel = level + 1;
	m_nTargetScore = getTargetScoreByLevel(m_nNextLevel);
}

int GameData::getTargetScoreByLevel(int level)
{
	int score = 0;

	if (level == 1)
	{
		score = 1000;
	}
	else if (level == 2)
	{
		score = 3000;
	}
	else if ((level >=3) && (level <= 10))
	{
		score = 3000 + 3000 * (level - 2);
	}
	else
	{
		score = 27000 + 4000 * (level - 10);
	}
	return score;
}

int GameData::getReward(int size)
{
	static const int reward[10][2] =
	{
		{0, 2000},
		{1, 1980},//20
		{2, 1920},//60
		{3, 1820},//100
		{4, 1680},//140
		{5, 1500},//180
		{6, 1280},//220
		{7, 1020},//260
		{8, 720},//300
		{9, 380} //340
	};

	if(size>9 || size<0){
		return 0;
	}

	return reward[size][1];
}

void GameData::saveHighestScore()
{
	UserDefault::getInstance()->setIntegerForKey("highestScore",getHighestScore());
}


