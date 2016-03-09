#ifndef _DISPLAYTOOL_H_
#define _DISPLAYTOOL_H_
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

	string getUTF8Char(const string key);
	void showAdmireEffect(int size,Node* node);
	void showStarParticleEffect(int color,Vec2 position,Node* node);
	Color4F getColor4F(int color);

#endif