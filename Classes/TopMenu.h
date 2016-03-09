#ifndef _TOPMENU_H_
#define _TOPMENU_H_
#include "cocos2d.h"
USING_NS_CC;

class TopMenu : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(TopMenu);
	void refreshTopWord();
private:
	Label* m_pHighestScore;
	Label* m_pLevel;
	Label* m_pTargetScore;
	Label* m_pCurScore;
};

#endif