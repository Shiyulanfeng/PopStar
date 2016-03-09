#include "TopMenu.h"
#include "GameData.h"
#include "DisplayTool.h"
//#include "MyUtility.h"

bool TopMenu::init()
{
	if (!Node::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_pHighestScore = Label::create(getUTF8Char("highestScore") + __String::createWithFormat(": %d",GameData::getInstance()->getHighestScore())->_string,"Arial",30);
	m_pHighestScore->setPosition(visibleSize.width/2,visibleSize.height - 50);
	m_pHighestScore->setColor(Color3B(200,200,255));
	this->addChild(m_pHighestScore);

	m_pLevel = Label::create(getUTF8Char("guanqia") + __String::createWithFormat(": %d",GameData::getInstance()->getNextLevel())->_string,"Arial",30);
	m_pLevel->setPosition(Vec2(120,visibleSize.height - 100));
	this->addChild(m_pLevel);

	m_pTargetScore = Label::create(getUTF8Char("mubiao") + __String::createWithFormat(": %d",GameData::getInstance()->getTargetScore())->_string + getUTF8Char("fen"),"Arial",30);
	m_pTargetScore->setPosition(visibleSize.width-120,visibleSize.height - 100);
	this->addChild(m_pTargetScore);

	m_pCurScore = Label::create(__String::createWithFormat("%d",GameData::getInstance()->getCurScore())->_string,"Arial",40);
	m_pCurScore->setPosition(visibleSize.width/2,visibleSize.height - 150);
	m_pCurScore->setColor(Color3B(255,255,150));
	this->addChild(m_pCurScore);

	return true;
}

void TopMenu::refreshTopWord()
{
	char buf[64];
	sprintf(buf,"%d",GameData::getInstance()->getCurScore());
	m_pCurScore->setString(buf);

	std::string history = getUTF8Char("highestScore") + __String::createWithFormat(": %d",GameData::getInstance()->getHighestScore())->_string;
	m_pHighestScore->setString(history);

	std::string levels = getUTF8Char("guanqia") +  __String::createWithFormat(": %d",GameData::getInstance()->getNextLevel())->_string;
	m_pLevel->setString(levels);

	std::string target = getUTF8Char("mubiao") + __String::createWithFormat(": %d",GameData::getInstance()->getTargetScore())->_string  + getUTF8Char("fen");
	m_pTargetScore->setString(target);
}
