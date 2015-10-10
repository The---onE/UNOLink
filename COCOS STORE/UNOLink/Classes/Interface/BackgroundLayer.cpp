#include "BackgroundLayer.h" //±³¾°²ã

#include "Data/BackgroundData.h"

bool BackgroundLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		addSprite(bG, BACKGROUND_IMG, BACKGROUND_POSITION, BACKGROUND_SIZE, this); //½«±³¾°Í¼Æ¬Ìí¼Óµ½ÆÁÄ»

		bRet = true;
	} while (0);
	return bRet;
}