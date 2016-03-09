#include "StarMatrix.h"
#include "DisplayTool.h"
#include "Audio.h"
#include "GameData.h"
#include "GameLayer.h"

StarMatrix* StarMatrix::create( GameLayer* layer )
{
	StarMatrix* pRet = new StarMatrix();
	if (pRet && pRet->init(layer))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

bool StarMatrix::init( GameLayer* layer )
{
	if (!Node::init())
	{
		return false;
	}

	m_pGameLayer = layer;
	m_bNeedClear = false;
	m_fStarClearSumTime = 0;

	memset(stars,0,sizeof(Star*)*ROW_NUM*COL_NUM);
	this->initMatrix();

	return true;
}

void StarMatrix::initMatrix()
{
	srand(time(0));
	for (int i = 0;i < ROW_NUM;i++){
		for (int j = 0;j < COL_NUM;j++){
			int color = abs(rand()%Star::COLOR_MAX_NUM);
			Star* star = Star::create(color);
			stars[i][j] = star;
			star->setPosition(getPositionByIndex(i,j) + Vec2(0,200));
			star->setDesPosition(getPositionByIndex(i,j));
			star->setStarIndex(i,j);
			//log("star%d,%d DesPosition = %f,%f",star->getStarIndex_i(),star->getStarIndex_j(),star->getDesPosition().x,star->getDesPosition().y);
			this->addChild(star);
		}
	}
}

Vec2 StarMatrix::getPositionByIndex( int i,int j )
{
	float x = j * Star::STAR_WIDTH + Star::STAR_WIDTH/2;
	float y = (StarMatrix::ROW_NUM - i) * Star::STAR_HEIGHT - Star::STAR_HEIGHT/2;
	return Vec2(x,y);
}

void StarMatrix::updateStar( float dt )//逐帧事件
{
	for (int i = 0;i < ROW_NUM;i++){
		for (int j = 0;j < COL_NUM;j++){
			if (stars[i][j] != nullptr){
				stars[i][j]->updatePosition();//更新位置
			}
		}
	}

	if (m_bNeedClear)
	{
		m_fStarClearSumTime += dt;
		if (m_fStarClearSumTime > 0.05)
		{
			clearStarOneByOne();
			m_fStarClearSumTime = 0;
		}
	}

}

void StarMatrix::onTouchStar( const Vec2& p )
{
	Star* star = getStarByTouch(p);
	if (star)
	{
		starSelectedList(star);
		//log("star_selected = %d",selectedList.size());
		deleteStarSelectedList();
	}
}

Star* StarMatrix::getStarByTouch( const Vec2& p )
{
	int k = p.y/Star::STAR_HEIGHT;
	int i = ROW_NUM - k -1;
	int j = p.x/Star::STAR_WIDTH;
	if (i >= 0 &&  i < ROW_NUM && j >= 0 && j < COL_NUM && stars[i][j] != nullptr){
		//log("i = %d,j = %d",i,j);
		return stars[i][j];
	}else
		return nullptr;
}

void StarMatrix::starSelectedList( Star* s )
{
	selectedList.clear();
	deque<Star*> travelList;
	travelList.push_back(s);
	deque<Star*>::iterator it;
	for (it = travelList.begin();it != travelList.end();)
	{
		Star* star = *it;
		Star* linkStar = nullptr;
		int starIndex_i = star->getStarIndex_i();
		int starIndex_j = star->getStarIndex_j();
		//上
		if (starIndex_i-1 >= 0 && (linkStar = stars[starIndex_i-1][starIndex_j])){
			if (!linkStar->isStarSelected() && star->getColor() == linkStar->getColor()){
				travelList.push_back(stars[starIndex_i-1][starIndex_j]);
			}
		}
		//下
		if (starIndex_i+1 < ROW_NUM && (linkStar = stars[starIndex_i+1][starIndex_j])){
			if (!linkStar->isStarSelected() && star->getColor() == linkStar->getColor()){
				travelList.push_back(stars[starIndex_i+1][starIndex_j]);
			}
		}
		//左
		if (starIndex_j-1 >= 0 && (linkStar = stars[starIndex_i][starIndex_j-1])){
			if (!linkStar->isStarSelected() && star->getColor() == linkStar->getColor()){
				travelList.push_back(stars[starIndex_i][starIndex_j-1]);
			}
		}
		//右
		if (starIndex_j+1 < COL_NUM && (linkStar = stars[starIndex_i][starIndex_j+1])){
			if (!linkStar->isStarSelected() && star->getColor() == linkStar->getColor()){
				travelList.push_back(stars[starIndex_i][starIndex_j+1]);
			}
		}
		if (!star->isStarSelected())
		{
			star->setStarSelected(true);
			selectedList.push_back(star);
		}
		travelList.pop_front();
		it =travelList.begin();
	}
}

void StarMatrix::deleteStarSelectedList()
{
	if (selectedList.size() <= 1)
	{
		selectedList.at(0)->setStarSelected(false);	
		m_pGameLayer->hideLinkStarWord();
		return;
	}

	for (auto it = selectedList.begin();it != selectedList.end();it++)
	{
		Star* star = *it;
		//消除星星的粒子特效
		showStarParticleEffect(star->getColor(),star->getPosition(),this);
		stars[star->getStarIndex_i()][star->getStarIndex_j()] = nullptr;
		star->removeFromParentAndCleanup(true);
		Audio::getInstance()->playPopAudio();
	}
	
	//显示赞叹效果
	showAdmireEffect(selectedList.size(),this);
	Audio::getInstance()->playAdmireAudio(selectedList.size());

	refreshScore(); //刷新分数和顶部信息
	m_pGameLayer->showLinkStarWord(selectedList.size());//显示连消的信息

	adjustMatrix();
	
	if (isStarEnded())
	{
		m_pGameLayer->floatStarRewardWord(getSurplusStarReward());//通知layer弹出剩余星星奖励的信息
		//log("star...........ended");
	}
}

void StarMatrix::adjustMatrix()
{
	//垂直方向调整
	for (int i = ROW_NUM -1;i >= 0 ;i--){
		for (int j = COL_NUM - 1;j >= 0 ;j--){
			if (stars[i][j] == nullptr)
			{
				//log("star[%d][%d] == nullptr",i,j);
				int upStarIndex = i;
				int blankCount = 0;
				while(stars[upStarIndex][j] == nullptr)
				{
					blankCount++;
					upStarIndex--;
					if (upStarIndex<0){
						break;
					}	
				}

				for (int moveStar_i = i - blankCount;moveStar_i >= 0;moveStar_i--)
				{
					if (stars[upStarIndex][j] == nullptr){
						continue;
					}
					Star* s = stars[upStarIndex+blankCount][j] = stars[moveStar_i][j];
					s->setStarIndex(moveStar_i+blankCount,j);
					s->setDesPosition(getPositionByIndex(moveStar_i+blankCount,j));
					stars[moveStar_i][j] = nullptr;
				}
			}
			else
			{
				continue;
			}
		}
	}
	//水平方向调整
	for (int j = 0;j < COL_NUM;j++)
	{
		if (stars[ROW_NUM-1][j] == nullptr)
		{
			int rightStarIndex = j;
			int blantCount = 0;
			while(stars[ROW_NUM-1][rightStarIndex] == nullptr)
			{
				rightStarIndex++;
				blantCount++;
			}

			for (int moveStar_i = 0;moveStar_i < ROW_NUM;moveStar_i++){
				for (int moveStar_j = j + blantCount;moveStar_j < COL_NUM;moveStar_j++){
					if (stars[moveStar_i][moveStar_j] == nullptr)
					{
						continue;
					}

					Star* s = stars[moveStar_i][moveStar_j-blantCount] = stars[moveStar_i][moveStar_j];
					s->setStarIndex(moveStar_i,moveStar_j-blantCount);
					s->setDesPosition(getPositionByIndex(moveStar_i,moveStar_j-blantCount));
					stars[moveStar_i][moveStar_j] = nullptr;
				}
			}	
		}
	}

}

bool StarMatrix::isStarEnded()
{
	bool bRet = true;
	for (int i = 0;i < ROW_NUM;i++){
		for (int j = 0;j < COL_NUM;j++){
			if (stars[i][j] == nullptr)
			{
				continue;
			}
			int currColor = stars[i][j]->getColor();
			//上
			if (i-1 >= 0 && stars[i-1][j] != nullptr && stars[i-1][j]->getColor() == currColor)
			{
				return false;
			}
			//左
			if (j-1 >= 0 && stars[i][j-1] != nullptr && stars[i][j-1]->getColor() == currColor)
			{
				return false;
			}
		}
	}
	return bRet;
}

void StarMatrix::clearStarOneByOne() //逐帧事件 清除剩余星星
{
	for (int i = 0;i < ROW_NUM;i++){
		for (int j = 0;j < COL_NUM;j++){
			if (stars[i][j] == nullptr)
				continue;
			showStarParticleEffect(stars[i][j]->getColor(),stars[i][j]->getPosition(),this);
			stars[i][j]->removeFromParentAndCleanup(true);
			stars[i][j] = nullptr;
			return;
		}
	}

	m_bNeedClear = false;
	//转到下一关或者弹出游戏结束的窗口
	if(GameData::getInstance()->getCurScore() >= GameData::getInstance()->getTargetScore())
	{
		GameData::getInstance()->setCurLevel(GameData::getInstance()->getCurLevel() + 1);
		m_pGameLayer->gotoNextLevel();
	}
	else
	{
		m_pGameLayer->gameOver();
	}

}

void StarMatrix::refreshScore()
{
	GameData* data = GameData::getInstance();
	data->setCurScore(data->getCurScore() + selectedList.size()*selectedList.size()*5);
	if(data->getCurScore() > data->getHighestScore())
	{
		data->setHighestScore(data->getCurScore());
	}
	m_pGameLayer->refreshMenu();
}

int StarMatrix::getSurplusStarReward()
{
	int star = 0;
	for(int i=0;i<ROW_NUM;i++){
		for(int j=0;j<COL_NUM;j++){
			if(stars[i][j] == nullptr)
				continue;
			star++;
		}
	}
	return star;
}
