#pragma once

#include "Global.h"

//±³¾°²ã

class BackgroundLayer : public Layer
{
protected:
	Sprite* bG; //±³¾°Í¼Æ¬

public:
	CREATE_FUNC(BackgroundLayer);
	bool init();
};