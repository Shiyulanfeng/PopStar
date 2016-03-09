#include "MenuLayer.h"
#include "GameScene.h"
#include "GameData.h"
USING_NS_CC;

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size size = Director::getInstance()->getVisibleSize();

	Sprite* bg = Sprite::create("bg_menuscene.jpg");
	bg->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(bg,-1);
		
	MenuItemImage* menu_start = MenuItemImage::create("menu_start.png","menu_start1.png",CC_CALLBACK_0(MenuLayer::startGame,this));
	MenuItemImage* menu_continue = MenuItemImage::create("menu_continue.png","menu_continue1.png",CC_CALLBACK_0(MenuLayer::continueGame,this));
	MenuItemImage* menu_shop = MenuItemImage::create("menu_shop.png","menu_shop1.png",CC_CALLBACK_0(MenuLayer::gameShop,this));

	Menu* menu = Menu::create(menu_start,menu_continue,menu_shop,NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(size.width/2,size.height/2));
	this->addChild(menu);

	return true;
}

void MenuLayer::startGame()
{
	//TransitionCrossFade* fade = TransitionCrossFade::create(0.5f,GameScene::create());
	Director::getInstance()->replaceScene(GameScene::create());
}

void MenuLayer::continueGame()
{

}

void MenuLayer::gameShop()
{

}

