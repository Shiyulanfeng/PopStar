#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GameData
{
public:
	static GameData* getInstance();
	//��ǰ�ؿ�
	void setCurLevel(int level);
	inline int getCurLevel(){return m_nCurLevel;}
	//��һ�ؿ�
	inline int getNextLevel(){return m_nNextLevel;}
	//��߷�
	inline void setHighestScore(int score){m_nHighestScore = score;}
	inline int getHighestScore(){return m_nHighestScore;}
	//��ǰ����
	inline void setCurScore(int score){m_nCurScore = score;}
	inline int getCurScore(){return m_nCurScore;}
	//Ŀ�����
	inline int getTargetScore(){return m_nTargetScore;}
	int getTargetScoreByLevel(int level);
	//����
	int getReward(int size);
	void saveHighestScore();

private:
	GameData();
	static GameData* m_pInstance;

	int m_nCurLevel;
	int m_nNextLevel;
	int m_nHighestScore;
	int m_nCurScore;
	int m_nTargetScore;
	friend class MenuLayer;
};

#endif