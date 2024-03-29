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

//设置玩家编号
void PlayerUnit::setId(int i)
{
	id = i;
}

//设置玩家分数
void PlayerUnit::setScore(int s /* = 0 */)
{
	score = s;
}

//返回玩家分数
int PlayerUnit::getScore()
{
	return score;
}

//玩家分数提高，返回提高后的分数
int PlayerUnit::scoreUp(int delta)
{
	score += delta;
	return score;
}