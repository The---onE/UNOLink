#pragma once

#include "Global.h"
#include "State/StateMachine.h"
#include "Data/Data.h"
#include "Interface/Interface.h"
#include "User/User.h"

//游戏主场景

class GameScene : public Scene
{
protected:
	BackgroundLayer* background; //背景层
	MatrixTLayer* matrix; //矩阵层
	InformationLayer* information; //信息层

	Players* players; //玩家信息

	float time; //一局游戏已进行的时间
	float timeLapse(float dt); //时间流逝
	void showTime(float t); //显示游戏剩余时间

	void restart(Ref* pSender); //开始新游戏

	void createQuitButton(string normal, string selected); //创建退出游戏按钮
	void quitGame(Ref* pSender); //退出游戏

public:
	CREATE_FUNC(GameScene);
	bool init();

	void initGame(); //初始化一局游戏

	void initBackground(); //初始化背景层
	void initMatrix(); //初始化矩阵层
	void initInformation(); //初始化信息层

	void initPlayers(); //初始化玩家
	void initMaster(); //初始化主控玩家

	float timeLapseShow(float dt); //时间流逝并显示

	int showScoreUp(); //一次消除后分数提高并显示，返回提高后的分数
	int showScoreUp(int delta); //分数提高并显示，返回提高后的分数

	bool elementsFall(); //矩阵元素下落，返回是否下落结束无空位
	
	void allowLink(); //允许开始连接，使矩阵层响应触控
	void forbiddenLink(); //禁止开始连接，使矩阵层不响应触控
	bool isLinkFinish(); //是否有有效的连接结束
	void prepareLink(); //准备下一次连接

	void removeLink(); //符合条件则消除被连接的元素，否则连接失效

	void gameOver(); //游戏结束，显示分数，提示开始新游戏

public:
	StateMachine* stateMachine; //状态机
	StateMachine* getStateMachine(); //返回状态机指针
	void update(float dt);
};

