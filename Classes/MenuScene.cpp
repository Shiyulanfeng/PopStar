#include "MenuScene.h"
#include "MenuLayer.h"
#include "Audio.h"

bool MenuScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	addChild(MenuLayer::create());
	Audio::getInstance()->playBGMAudio();

	return true;
}

