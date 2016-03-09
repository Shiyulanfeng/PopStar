#include "Star.h"

Star* Star::create( int color )
{
	Star* pRet = new Star();
	if (pRet && pRet->initWithFile(pRet->getImage(color)))
	{
		pRet->m_nColor = color;
		pRet->m_bSelected = false;
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}

void Star::updatePosition()
{
	if (this->getPositionX() != m_pDesPosition.x)
	{
		this->setPositionX(this->getPositionX() - MOVE_SPEED);
		if (this->getPositionX() < m_pDesPosition.x)
		{
			this->setPositionX(m_pDesPosition.x);
		}
	}

	if (this->getPositionY() != m_pDesPosition.y)
	{
		this->setPositionY(this->getPositionY() - MOVE_SPEED);
		if (this->getPositionY() < m_pDesPosition.y)
		{
			this->setPositionY(m_pDesPosition.y);
		}
	}
}

char* Star::getImage( int color )
{
	switch (color)
	{
	case colorId::GREEN:
		return "green.png";
		break;
	case colorId::RED:
		return "red.png";
		break;
	case colorId::PURPLE:
		return "purple.png";
		break;
	case colorId::BLUE:
		return "blue.png";
		break;
	case colorId::YELLOW:
		return "yellow.png";
		break;
	}
}
