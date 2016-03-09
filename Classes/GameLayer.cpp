#include "GameLayer.h"
#include "DisplayTool.h"
#include "GameData.h"
#include "Audio.h"
#include "MenuScene.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_pMatrix = nullptr;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* bg = Sprite::create("bg_mainscene.jpg");
	bg->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	this->addChild(bg,-1);

	m_pTopMenu = TopMenu::create();//顶部信息
	this->addChild(m_pTopMenu);
	
	//连消提示信息
	m_pLinkStar = Label::create(" ","Arial",30);
	m_pLinkStar->setPosition(Vec2(visibleSize.width/2,visibleSize.height-220));
	m_pLinkStar->setVisible(false);
	this->addChild(m_pLinkStar,1);

	this->floatLevelWord();
	this->scheduleUpdate();
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}

void GameLayer::floatLevelWord()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_pLevelMsg = FloatWord::create( getUTF8Char("guanqia") + __String::createWithFormat(":%d",GameData::getInstance()->getNextLevel())->_string,30,Vec2(visibleSize.width+200,visibleSize.height/3*2+50));
	this->addChild(m_pLevelMsg,1);
	m_pLevelMsg->floatIn(0.5f,CC_CALLBACK_0(GameLayer::floatTargetScoreWord,this));
	Audio::getInstance()->playReadyGoAudio();
}

void GameLayer::floatTargetScoreWord()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_pTagertScore = FloatWord::create(getUTF8Char("mubiao") + __String::createWithFormat(":%d",GameData::getInstance()->getTargetScore())->_string + getUTF8Char("fen") ,30,Vec2(visibleSize.width+200,visibleSize.height/3*2));
	this->addChild(m_pTagertScore,1);
	m_pTagertScore->floatIn(0.5f,CC_CALLBACK_0(GameLayer::removefloatWord,this));
}

void GameLayer::removefloatWord()
{
	m_pLevelMsg->floatOut(0.5f,nullptr);
	m_pTagertScore->floatOut(0.5f,CC_CALLBACK_0(GameLayer::showStarMatrix,this));
}

void GameLayer::showStarMatrix()
{
	m_pMatrix = StarMatrix::create(this);
	this->addChild(m_pMatrix);
}

bool GameLayer::onTouchBegan( Touch *touch, Event *event )
{
	Vec2 p = Director::getInstance()->convertToGL(touch->getLocationInView());
	if (m_pMatrix)
	{
		m_pMatrix->onTouchStar(p);
	}
	return true;
}

void GameLayer::update( float dt )
{
	if (m_pMatrix!=nullptr)
	{
		m_pMatrix->updateStar(dt);
	}
}

void GameLayer::refreshMenu()
{
	m_pTopMenu->refreshTopWord();
}

void GameLayer::showLinkStarWord( int size )
{
	string s = __String::createWithFormat("%d",size)->_string + getUTF8Char("lianxiao") + __String::createWithFormat("%d",size*size*5)->_string + getUTF8Char("fen");
	m_pLinkStar->setString(s);
	m_pLinkStar->setVisible(true);
}

void GameLayer::hideLinkStarWord()
{
	m_pLinkStar->setVisible(false);

}

void GameLayer::floatStarRewardWord( int starNum )
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	FloatWord* surplusStarWord = FloatWord::create(getUTF8Char("shengyu") + __String::createWithFormat("%d",starNum)->_string + getUTF8Char("ge") + getUTF8Char("star"),30,Vec2(visibleSize.width/2,visibleSize.height/2-150));
	this->addChild(surplusStarWord);

	int rewardScore = GameData::getInstance()->getReward(starNum);

	FloatWord* starReward = FloatWord::create( getUTF8Char("jiangli") + __String::createWithFormat("%d",rewardScore)->_string + getUTF8Char("fen"),30,Vec2(visibleSize.width/2,visibleSize.height/2 - 100));
	this->addChild(starReward);

	surplusStarWord->floatBlink(1.0f,[=](){
			hideLinkStarWord();
			m_pMatrix->setStarNeedClear(true);
			GameData* data = GameData::getInstance();
			data->setCurScore(data->getCurScore() + rewardScore);
			if(data->getCurScore() > data->getHighestScore())
			{
				data->setHighestScore(data->getCurScore());
			}
			refreshMenu();
	});
	starReward->floatBlink(1.0f,nullptr);
}

void GameLayer::gotoNextLevel()
{
	refreshMenu();
	floatLevelWord();
}

void GameLayer::gameOver()
{
	GameData* data = GameData::getInstance();
	data->saveHighestScore();
	Audio::getInstance()->playGameOverAudio();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* gameover = FloatWord::create(getUTF8Char("gameover"),40,Vec2(visibleSize.width*5,visibleSize.height*5));
	gameover->setScale(0.1f);
	this->addChild(gameover);
	data->setCurLevel(0);
	data->setCurScore(0);
	gameover->floatScaleRotate(1.0f,[](){Director::getInstance()->replaceScene(MenuScene::create());});
}

