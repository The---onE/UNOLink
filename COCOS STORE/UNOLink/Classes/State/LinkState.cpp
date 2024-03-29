#include "StateList.h"

//等待连线状态

bool LinkState::checkStateChange() //状态改变返回true，状态未改变返回false，
{
	if (gameOverFlag)
	{
		CHANGE_TO_STATE(GameOverState); //若时间用尽，则进入游戏结束状态
	}
	else if (scene->isLinkFinish())
	{
		CHANGE_TO_STATE(RemoveState); //若完成一次连线，则进入消除状态
	}
	return false;
}

bool LinkState::entryState()
{
	scene->allowLink(); //允许触摸
	scene->prepareLink(); //为连线准备

	gameOverFlag = false;
 
 	return true;
}

void LinkState::onUpdate(float dt)
{
	time += dt;
	if (scene->timeLapseShow(dt) <= 0)
	{
		gameOverFlag = true; //若时间用尽，则游戏结束
	}
}

bool LinkState::exitState()
{
 	scene->forbiddenLink(); //不允许触摸
 	return true;
}