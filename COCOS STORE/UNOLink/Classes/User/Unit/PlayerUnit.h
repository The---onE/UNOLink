#pragma once

#include "Global.h"
#include "Data/PlayerData.h"

class PlayerUnit : public Node
{
protected:
	int id; //��ұ��

	int score; //��ҷ���

public:
	CREATE_FUNC(PlayerUnit);
	bool init();

	void setId(int i); //������ұ��

	void setScore(int s = 0); //������ҷ���
	int getScore(); //������ҷ���
	int scoreUp(int delta); //��ҷ�����ߣ�������ߺ�ķ���
};