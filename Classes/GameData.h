#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

class GameData
{
public:
	static GameData* getInstance();
	//当前关卡
	void setCurLevel(int level);
	inline int getCurLevel(){return m_nCurLevel;}
	//下一关卡
	inline int getNextLevel(){return m_nNextLevel;}
	//最高分
	inline void setHighestScore(int score){m_nHighestScore = score;}
	inline int getHighestScore(){return m_nHighestScore;}
	//当前分数
	inline void setCurScore(int score){m_nCurScore = score;}
	inline int getCurScore(){return m_nCurScore;}
	//目标分数
	inline int getTargetScore(){return m_nTargetScore;}
	int getTargetScoreByLevel(int level);
	//奖励
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