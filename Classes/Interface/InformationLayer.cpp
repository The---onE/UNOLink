#include "InformationLayer.h" //信息层

#include "Data/InformationData.h"
#include "Data/RoundData.h"

bool InformationLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		initTimeLabel(); //初始化时间标签
		initScoreLabel(); //初始化分数标签

		bRet = true;
	} while (0);
	return bRet;
}

//添加一个标签
void InformationLayer::createLabel(Label* &label, char* text, Color4B color, Point pos, float size, Point anchor /* = Point(0.5, 0.5) */)
{
	label = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE); //创建标签
	label->setTextColor(color); //设置标签颜色
	label->enableShadow(Color4B::BLACK, INFORMATION_SHADOW_OFFSET); //添加字体阴影
	label->setPosition(pos); //设置标签位置
	label->setAnchorPoint(anchor); //设置标签锚点
	setSize(label, size); //设置标签尺寸
	addChild(label);
}

//初始化时间标签
void InformationLayer::initTimeLabel()
{
	char text[32];
	sprintf(text, "TIME:0.0s");
	createLabel(timeLabel, text, TIME_NORMAL_COLOR, TIME_POSITION, TIME_SIZE, TIME_ANCHOR); //添加时间标签，之后通过showTime函数修改时间
}

//显示时间
void InformationLayer::showTime(float t)
{
	if (t > LITTLE_TIME_FLAG)
	{
		timeLabel->setTextColor(TIME_NORMAL_COLOR); //时间充裕时设置颜色为一般颜色
	}
	else if (t <= 0)
	{
		t = 0; //时间用尽后显示时间为0
	}
	else
	{
		timeLabel->setTextColor(TIME_LITTLE_COLOR); //时间紧迫时设置颜色为特殊颜色
	}

	char text[32];
	sprintf(text, "TIME:%.1fs", t);

	timeLabel->setString(text); //修改时间标签的文本为对应时间
}

//初始化得分标签
void InformationLayer::initScoreLabel()
{
	char text[32];
	sprintf(text, "SCORE:0");
	createLabel(scoreLabel, text, SCORE_COLOR, SCORE_POSITION, SCORE_SIZE, SCORE_ANCHOR); //添加分数标签，之后通过showScore函数修改分数
}

//显示得分
void InformationLayer::showScore(int s)
{
	char text[32];
	sprintf(text, "SCORE:%d", s);

	scoreLabel->setString(text); //修改分数标签的文本为对应分数
}

//显示得分增加
void InformationLayer::scoreUp(int delta, int time)
{
	char text[32];
	sprintf(text, "+%d", delta);
	Label* l;
	createLabel(l, text, SCORE_UP_COLOR, SCORE_UP_POSITION, SCORE_UP_SIZE, SCORE_UP_ANCHOR); //添加分数增加标签

	Action* a = Sequence::create(FadeOut::create(time), RemoveSelf::create(), NULL); //设置动画，标签在一定时间内淡出，然后消失
	l->runAction(a);
}