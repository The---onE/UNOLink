#pragma once

#include "Global.h"

//信息层

class InformationLayer : public Layer
{
protected:
	Label* timeLabel; //时间标签
	Label* scoreLabel; //分数标签

public:
	CREATE_FUNC(InformationLayer);
	bool init();

	void createLabel(Label* &label, char* text, Color4B color, Point pos, float size, Point anchor = Point(0.5, 0.5)); //添加一个标签

	void initTimeLabel(); //初始化时间标签
	void showTime(float t); //显示时间

	void initScoreLabel(); //初始化得分标签
	void showScore(int s); //显示得分

	void scoreUp(int delta, int time); //显示得分增加
};
