#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_
#include "cocos2d.h"
#include "FloatWord.h"
#include "StarMatrix.h"
#include "TopMenu.h"
USING_NS_CC;
class GameLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	void floatLevelWord();
	void floatTargetScoreWord();
	void removefloatWord();
	void showStarMatrix();

	virtual bool onTouchBegan(Touch *touch, Event *event);
	void update(float dt);

	void refreshMenu();
	void showLinkStarWord(int size);
	void hideLinkStarWord();
	void floatStarRewardWord(int starNum);
	void gotoNextLevel();
	void gameOver();

private:
	FloatWord * m_pLevelMsg;
	FloatWord * m_pTagertScore;
	StarMatrix * m_pMatrix;
	Label* m_pLinkStar;
	TopMenu* m_pTopMenu;
};

#endif