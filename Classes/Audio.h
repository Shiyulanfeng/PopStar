#ifndef _AUDIO_H_
#define _AUDIO_H_
class Audio
{
public:
	static Audio* getInstance();
	void prepareAudio();
	void playBGMAudio();
	void playReadyGoAudio();
	void playAdmireAudio(int size);
	void playPopAudio();
	void stopBGMAudio();
	void playGameOverAudio();
	void playNextLevelAudio();
private:
	static Audio* m_pAudio;
};

#endif