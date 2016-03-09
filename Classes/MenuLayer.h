#ifndef _MENULAYER_H_
#define _MENULAYER_H_
#include "cocos2d.h"
USING_NS_CC;
class MenuLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	void startGame();
	void continueGame();
	void gameShop();
};

#endif