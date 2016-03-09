#ifndef _STARMATRIX_H_
#define _STARMATRIX_H_
#include "cocos2d.h"
#include "Star.h"
#include <deque>
USING_NS_CC;
using namespace std;
class GameLayer;
class StarMatrix : public Node
{
public:
	static const int ROW_NUM = 10;
	static const int COL_NUM = 10;

	static StarMatrix* create(GameLayer* layer);
	virtual bool init(GameLayer* layer);
	void initMatrix();
	void updateStar(float dt);
	void onTouchStar(const Vec2& p);
	inline void setStarNeedClear(bool b){m_bNeedClear = b;}

private:
	Vec2 getPositionByIndex(int i,int j);
	Star* getStarByTouch(const Vec2& p);
	void starSelectedList(Star* s);
	void deleteStarSelectedList();
	void adjustMatrix();
	bool isStarEnded();
	void clearStarOneByOne();
	void refreshScore();
	int getSurplusStarReward();

	Star* stars[ROW_NUM][COL_NUM];
	deque<Star*> selectedList;
	GameLayer* m_pGameLayer;
	bool m_bNeedClear;
	float m_fStarClearSumTime;
};

#endif