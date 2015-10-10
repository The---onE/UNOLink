#include "BackgroundLayer.h" //������

#include "Data/BackgroundData.h"

bool BackgroundLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		addSprite(bG, BACKGROUND_IMG, BACKGROUND_POSITION, BACKGROUND_SIZE, this); //������ͼƬ��ӵ���Ļ

		bRet = true;
	} while (0);
	return bRet;
}