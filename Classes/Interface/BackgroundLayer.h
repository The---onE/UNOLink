#pragma once

#include "Global.h"

//������

class BackgroundLayer : public Layer
{
protected:
	Sprite* bG; //����ͼƬ

public:
	CREATE_FUNC(BackgroundLayer);
	bool init();
};