#include "Audio.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

Audio* Audio::m_pAudio = nullptr;
Audio* Audio::getInstance()
{
	if (m_pAudio == nullptr)
	{
		m_pAudio = new Audio();
	}
	return m_pAudio;
}

void Audio::prepareAudio()
{
#if  CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/music.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/readygo.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/pop.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_1.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_2.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_3.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/gameover.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/nextlevel.mp3");
#else
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/music.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/readygo.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/pop.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_1.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_2.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/combo_3.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/gameover.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/nextlevel.ogg");
#endif
	
}

void Audio::playBGMAudio()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.mp3",true);
#else
	SimpleAudioEngine::getInstance()->playBackgroundMusic("Music/music.ogg",true);
#endif	
}

void Audio::playReadyGoAudio()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	SimpleAudioEngine::getInstance()->playEffect("Music/readygo.mp3",false);
#else
	SimpleAudioEngine::getInstance()->playEffect("Music/readygo.ogg",false);
#endif
}

void Audio::playAdmireAudio(int size)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	if(size < 5)
		return;
	if(size >= 10){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_3.mp3",false);
	}else if(size >= 7){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_2.mp3",false);
	}else {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_1.mp3",false);
	}
#else
	if(size < 5)
		return;
	if(size >= 10){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_3.ogg",false);
	}else if(size >= 7){
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_2.ogg",false);
	}else {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Music/combo_1.ogg",false);
	}
#endif

}

void Audio::playPopAudio()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	SimpleAudioEngine::getInstance()->playEffect("Music/pop.mp3",false);
#else
	SimpleAudioEngine::getInstance()->playEffect("Music/pop.ogg",false);
#endif
}

void Audio::stopBGMAudio()
{
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
}

void Audio::playGameOverAudio()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	SimpleAudioEngine::getInstance()->playEffect("Music/gameover.mp3",false);
#else
	SimpleAudioEngine::getInstance()->playEffect("Music/gameover.ogg",false);
#endif
}

void Audio::playNextLevelAudio()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	SimpleAudioEngine::getInstance()->playEffect("Music/nextlevel.mp3",false);
#else
	SimpleAudioEngine::getInstance()->playEffect("Music/nextlevel.ogg",false);
#endif
}
