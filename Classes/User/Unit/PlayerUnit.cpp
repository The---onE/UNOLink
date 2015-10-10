#include "PlayerUnit.h"

bool PlayerUnit::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		id = -1;
		score = 0;

		bRet = true;
	} while (0);
	return bRet;
}

//������ұ��
void PlayerUnit::setId(int i)
{
	id = i;
}

//������ҷ���
void PlayerUnit::setScore(int s /* = 0 */)
{
	score = s;
}

//������ҷ���
int PlayerUnit::getScore()
{
	return score;
}

//��ҷ�����ߣ�������ߺ�ķ���
int PlayerUnit::scoreUp(int delta)
{
	score += delta;
	return score;
}