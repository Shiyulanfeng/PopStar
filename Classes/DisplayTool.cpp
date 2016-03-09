#include "DisplayTool.h"
#include "Star.h"

string getUTF8Char(const string key)
{
	auto sharedFileUtils = FileUtils::getInstance();

	std::string fullPathForFilename = sharedFileUtils->fullPathForFilename("utf8_char.plist");

	bool isExist = false;
	isExist = sharedFileUtils->isFileExist(fullPathForFilename);
	if (!isExist) {
		return "";
	}

	ValueMap map = sharedFileUtils->getValueMapFromFile(fullPathForFilename);
	Value value =  map[key];

	if (value.isNull()) {
		return "";
	}
	return value.asString();

}

void showAdmireEffect( int size,Node* node )
{
	if (size < 5)
	{
		return;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* admireSprite;
	if (size >= 10)
	{
		admireSprite = Sprite::create("admire_3.png");
	} 
	else if(size >= 7)
	{
		admireSprite = Sprite::create("admire_2.png");
	}
	else
	{
		admireSprite = Sprite::create("admire_1.png");
	}
	admireSprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
	node->addChild(admireSprite);

	Blink* blink = Blink::create(1.f,5);
	CallFunc* remove = CallFunc::create([=](){
		admireSprite->removeFromParentAndCleanup(true);
	});
	Sequence* sequence = Sequence::create(blink,remove,nullptr);
	admireSprite->runAction(sequence);
}

void showStarParticleEffect( int color,Vec2 position,Node* node )
{
	ParticleExplosion* explosion = ParticleExplosion::create();
	explosion->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
	
	explosion->setGravity(Vec2(0,-300));
	explosion->setTotalParticles(500);

	explosion->setStartSize(20);
	explosion->setStartSizeVar(0);

	explosion->setStartColor(getColor4F(color));
	explosion->setStartColorVar(Color4F(0,0,0,1));

	explosion->setEndColor(getColor4F(color));
	explosion->setEndColorVar(Color4F(0,0,0,1));

	explosion->setSpeed(200);
	explosion->setSpeedVar(30);

	explosion->setLife(1.0f);
	explosion->setLifeVar(0);

	explosion->setPosition(position);
	node->addChild(explosion);
}

cocos2d::Color4F getColor4F( int color )
{
	switch(color)
	{
	case Star::GREEN:
		return Color4F(130/255.0f,220/255.0f,110/255.0f,1.0f);
	case Star::RED:
		return Color4F(250/255.0f,80/255.0f,120/255.0f,1.0f);
	case Star::YELLOW:
		return Color4F(250/255.0f,230/255.0f,80/255.0f,1.0f);
	case Star::PURPLE:
		return Color4F(200/255.0f,80/255.0f,250/255.0f,1.0f);
	case Star::BLUE:
		return Color4F(80/255.0f,200/255.0f,250/255.0f,1.0f);
	}
	return Color4F(1,1,1,0);
}



