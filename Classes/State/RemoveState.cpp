#include "StateList.h"

//消除状态

bool RemoveState::checkStateChange() //状态改变返回true，状态未改变返回false，
{
	if (gameOverFlag)
	{
		CHANGE_TO_STATE(GameOverState); //若时间用尽，则进入游戏结束状态
	}
	if (matrixFinishFlag)
		CHANGE_TO_STATE(LinkState); //若元素已下落完成，则进入等待连线状态
	return false;
}

bool RemoveState::entryState()
{
	scene->showScoreUp(); //显示分数增加
	matrixFinishFlag = false;
	matrixTime = FALL_TIME;

	gameOverFlag = false;

	return true;
}

void RemoveState::onUpdate(float dt)
{
	time += dt;
	if (scene->timeLapseShow(dt) <= 0)
	{
		gameOverFlag = true; //若时间用尽，则游戏结束
	}
	matrixTime += dt;
	if (matrixTime > FALL_TIME)
	{
		matrixTime = 0;
		matrixFinishFlag = !scene->elementsFall(); //不断填充空位，直至矩阵填充满
	}
}

bool RemoveState::exitState()
{
	return true;
}