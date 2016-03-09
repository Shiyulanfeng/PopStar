#ifndef _FLOATWORD_H_
#define _FLOATWORD_H_
#include "cocos2d.h"
USING_NS_CC;
class FloatWord : public Node
{
public:
	static FloatWord* create(const std::string& fonts,const int fontSize,Vec2 begin);
	bool init(const std::string& fonts,const int fontSize,Vec2 begin);
	void floatIn(const float delay,std::function<void()> callBack);
	void floatOut(const float delay,std::function<void()> callBack);
	void floatScaleRotate(const float delay,std::function<void()> callBack);
	void floatBlink(const float delay,std::function<void()> callBack);
private:
	Label* m_pLabel;
	int m_nFontSize;
	Vec2 m_pBegin;
};

#endif