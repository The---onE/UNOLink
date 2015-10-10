#include "InformationLayer.h" //��Ϣ��

#include "Data/InformationData.h"
#include "Data/RoundData.h"

bool InformationLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		initTimeLabel(); //��ʼ��ʱ���ǩ
		initScoreLabel(); //��ʼ��������ǩ

		bRet = true;
	} while (0);
	return bRet;
}

//���һ����ǩ
void InformationLayer::createLabel(Label* &label, char* text, Color4B color, Point pos, float size, Point anchor /* = Point(0.5, 0.5) */)
{
	label = Label::createWithTTF(text, INFORMATION_FONT, INFORMATION_FONTSIZE); //������ǩ
	label->setTextColor(color); //���ñ�ǩ��ɫ
	label->enableShadow(Color4B::BLACK, INFORMATION_SHADOW_OFFSET); //���������Ӱ
	label->setPosition(pos); //���ñ�ǩλ��
	label->setAnchorPoint(anchor); //���ñ�ǩê��
	setSize(label, size); //���ñ�ǩ�ߴ�
	addChild(label);
}

//��ʼ��ʱ���ǩ
void InformationLayer::initTimeLabel()
{
	char text[32];
	sprintf(text, "TIME:0.0s");
	createLabel(timeLabel, text, TIME_NORMAL_COLOR, TIME_POSITION, TIME_SIZE, TIME_ANCHOR); //���ʱ���ǩ��֮��ͨ��showTime�����޸�ʱ��
}

//��ʾʱ��
void InformationLayer::showTime(float t)
{
	if (t > LITTLE_TIME_FLAG)
	{
		timeLabel->setTextColor(TIME_NORMAL_COLOR); //ʱ���ԣʱ������ɫΪһ����ɫ
	}
	else if (t <= 0)
	{
		t = 0; //ʱ���þ�����ʾʱ��Ϊ0
	}
	else
	{
		timeLabel->setTextColor(TIME_LITTLE_COLOR); //ʱ�����ʱ������ɫΪ������ɫ
	}

	char text[32];
	sprintf(text, "TIME:%.1fs", t);

	timeLabel->setString(text); //�޸�ʱ���ǩ���ı�Ϊ��Ӧʱ��
}

//��ʼ���÷ֱ�ǩ
void InformationLayer::initScoreLabel()
{
	char text[32];
	sprintf(text, "SCORE:0");
	createLabel(scoreLabel, text, SCORE_COLOR, SCORE_POSITION, SCORE_SIZE, SCORE_ANCHOR); //��ӷ�����ǩ��֮��ͨ��showScore�����޸ķ���
}

//��ʾ�÷�
void InformationLayer::showScore(int s)
{
	char text[32];
	sprintf(text, "SCORE:%d", s);

	scoreLabel->setString(text); //�޸ķ�����ǩ���ı�Ϊ��Ӧ����
}

//��ʾ�÷�����
void InformationLayer::scoreUp(int delta, int time)
{
	char text[32];
	sprintf(text, "+%d", delta);
	Label* l;
	createLabel(l, text, SCORE_UP_COLOR, SCORE_UP_POSITION, SCORE_UP_SIZE, SCORE_UP_ANCHOR); //��ӷ������ӱ�ǩ

	Action* a = Sequence::create(FadeOut::create(time), RemoveSelf::create(), NULL); //���ö�������ǩ��һ��ʱ���ڵ�����Ȼ����ʧ
	l->runAction(a);
}