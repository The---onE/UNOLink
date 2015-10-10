#pragma once

#include "Global.h"

//��Ϣ��

class InformationLayer : public Layer
{
protected:
	Label* timeLabel; //ʱ���ǩ
	Label* scoreLabel; //������ǩ

public:
	CREATE_FUNC(InformationLayer);
	bool init();

	void createLabel(Label* &label, char* text, Color4B color, Point pos, float size, Point anchor = Point(0.5, 0.5)); //���һ����ǩ

	void initTimeLabel(); //��ʼ��ʱ���ǩ
	void showTime(float t); //��ʾʱ��

	void initScoreLabel(); //��ʼ���÷ֱ�ǩ
	void showScore(int s); //��ʾ�÷�

	void scoreUp(int delta, int time); //��ʾ�÷�����
};
