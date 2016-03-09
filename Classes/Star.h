#ifndef _STAR_H_
#define _STAR_H_
#include "cocos2d.h"
USING_NS_CC;
class Star : public Sprite
{
public:
	enum colorId
	{
		GREEN,
		RED,
		YELLOW,
		PURPLE,
		BLUE
	};
	static const int COLOR_MAX_NUM = 5;
	static const int STAR_WIDTH = 48;
	static const int STAR_HEIGHT = 48;
	static const int MOVE_SPEED = 6;

	static Star* create(int color);
	inline void setDesPosition(const Vec2& p){m_pDesPosition = p;}
	inline Vec2 getDesPosition(){return m_pDesPosition;}	
	inline void setStarIndex(int i,int j){m_nIndex_i = i;m_nIndex_j = j;}
	inline int getStarIndex_i(){return m_nIndex_i;}
	inline int getStarIndex_j(){return m_nIndex_j;}
	inline int getColor(){return m_nColor;}
	inline void setStarSelected(bool b){m_bSelected = b;}
	inline bool isStarSelected(){return m_bSelected;}
	void updatePosition();
private:
	char* getImage(int color);
	int m_nColor;
	Vec2 m_pDesPosition;
	bool m_bSelected;
	int m_nIndex_i;
	int m_nIndex_j;
};

#endif