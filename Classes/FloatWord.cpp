#include "FloatWord.h"

FloatWord* FloatWord::create( const std::string& fonts,const int fontSize,Vec2 begin )
{
	FloatWord* pRet = new FloatWord();
	if (pRet && pRet->init(fonts,fontSize,begin))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

bool FloatWord::init( const std::string& fonts,const int fontSize,Vec2 begin )
{
	if (!Node::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_pBegin = begin;

	m_pLabel = Label::createWithSystemFont(fonts,"Arial",fontSize);
	m_pLabel->setPosition(begin);
	this->addChild(m_pLabel);

	return true;
}

void FloatWord::floatIn( const float delay,std::function<void()> callBack )
{
	Size visibaleSize = Director::getInstance()->getVisibleSize();
	MoveTo* moveTo = MoveTo::create(delay,Vec2(visibaleSize.width/2,m_pBegin.y));
	CallFunc* call = CallFunc::create(callBack);
	Sequence* sequence = Sequence::create(EaseIn::create(moveTo,4),DelayTime::create(0.5f),call,NULL);
	m_pLabel->runAction(sequence);
}

void FloatWord::floatOut( const float delay,std::function<void()> callBack )
{
	Size visibaleSize = Director::getInstance()->getVisibleSize();
	MoveTo* moveTo = MoveTo::create(delay,Vec2(-200,m_pBegin.y));
	CallFunc* call = CallFunc::create(callBack);
	CallFunc* remove = CallFunc::create([this](){
		this->removeAllChildrenWithCleanup(true);
	});
	Sequence* sequence = Sequence::create(EaseIn::create(moveTo,4),DelayTime::create(0.5f),call,remove,NULL);
	m_pLabel->runAction(sequence);
}

void FloatWord::floatScaleRotate( const float duration,std::function<void()> callBack )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	ScaleTo* scaleTo = ScaleTo::create(duration,10);
	RotateBy* rotataBy = RotateBy::create(duration,360);
	CallFunc* call = CallFunc::create(callBack);
	Spawn* spawn = Spawn::create(scaleTo,rotataBy,NULL);
	Sequence* sequence = Sequence::create(spawn,DelayTime::create(0.5f),call,NULL);
	m_pLabel->runAction(sequence);
}

void FloatWord::floatBlink( const float delay,std::function<void()> callBack )
{
	Size visibaleSize = Director::getInstance()->getVisibleSize();
	Blink* blink = Blink::create(delay,5);
	CallFunc* remove = CallFunc::create([this](){
		this->removeAllChildrenWithCleanup(true);
	});
	Sequence* sequence = Sequence::create(blink,DelayTime::create(0.5f),remove,CallFunc::create(callBack),NULL);
	m_pLabel->runAction(sequence);
}



