#include "GameScene.h"
#include "GameLayer.h"
#include "Audio.h"

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	addChild(GameLayer::create());
	Audio::getInstance()->stopBGMAudio();
	return true;
}

