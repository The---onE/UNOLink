#pragma once

#include "Global.h"
#include "Data/SettingData.h"

//游戏开始界面场景

class StartScene : public Scene
{
protected:
	MenuItemLabel* createItem(string text); //创建菜单选项，无回调函数
	MenuItemLabel* createItem(string text, void(StartScene::*func)()); //创建菜单选项，有回调函数

	void createBackGround(string filename); //创建背景
	void createMenu(); //创建菜单

	void StartGame(); //开始游戏
	void PlayStopBGM(); //播放或停止背景音乐
	void OpenCloseEffect(); //打开或关闭音效
	void OpenCloseVibrate(); //打开或关闭震动
	void QuitGame(); //退出游戏

public:
	CREATE_FUNC(StartScene);
	bool init();
};
