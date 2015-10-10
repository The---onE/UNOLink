#include "StartScene.h" //游戏开始界面场景

#include "GameScene.h"

bool StartScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		createBackGround(BACKGROUND_IMG); //创建背景
		createMenu(); //创建菜单

		bRet = true;
	} while (0);
	return bRet;
}

//创建菜单选项，无回调函数
MenuItemLabel* StartScene::createItem(string text)
{
	Label* label;
	label = Label::createWithTTF(text, MENUITEM_FONT, MENUITEM_FONTSIZE);
	label->setTextColor(MENUITEM_COLOR);
	label->enableShadow(Color4B::BLACK, MENUITEM_SHADOW_OFFSET);
	return MenuItemLabel::create(label);
}

//创建菜单选项，有回调函数
#define ITEM_CALLBACK(__selector__,__target__, ...) std::bind(__selector__,__target__, ##__VA_ARGS__)
//#define CC_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)此为引擎中回调函数宏，通过自定义宏，可实现对函数指针的绑定
MenuItemLabel* StartScene::createItem(string text, void(StartScene::*func)())
{
	Label* label;
	label = Label::createWithTTF(text, MENUITEM_FONT, MENUITEM_FONTSIZE);
	label->setTextColor(MENUITEM_COLOR);
	label->enableShadow(Color4B::BLACK, MENUITEM_SHADOW_OFFSET);
	return MenuItemLabel::create(label, ITEM_CALLBACK(func, this));
}
#undef ITEM_CALLBACK

//创建背景
void StartScene::createBackGround(string filename)
{
	Sprite* bG = Sprite::create(filename);
	bG->setPosition(BACKGROUND_POSITION);
	setSize(bG, BACKGROUND_SIZE);
	addChild(bG);
}

//创建菜单
void StartScene::createMenu()
{
	MenuItemLabel* startGame = createItem("Start Game", &StartScene::StartGame); //创建开始游戏菜单项

	//创建开关背景音乐菜单项
	//////////////////////////////////////////////////////////////////////////
	bool bgmFlag = UserDefault::getInstance()->getBoolForKey(BGM_UD, BGM_DEFAULT_FLAG);

	MenuItemLabel* playBGM = createItem("BGM:ON");
	MenuItemLabel* stopBGM = createItem("BGM:OFF");

	MenuItemToggle* bgm;
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM, true);
	if (bgmFlag) //根据保存的设置确定当前状态
	{
		bgm = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::PlayStopBGM, this), playBGM, stopBGM, NULL); //点击一次切换一次文本，并调用回调函数
	}
	else
	{
		bgm = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::PlayStopBGM, this), stopBGM, playBGM, NULL); //点击一次切换一次文本，并调用回调函数
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	bool effectFlag = UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG);

	MenuItemLabel* openEffect = createItem("EFFECT:ON");
	MenuItemLabel* closeEffect = createItem("EFFECT:OFF");

	MenuItemToggle* effect;
	if (effectFlag) //根据保存的设置确定当前状态
	{
		effect = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseEffect, this), openEffect, closeEffect, NULL); //点击一次切换一次文本，并调用回调函数
	}
	else
	{
		effect = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseEffect, this), closeEffect, openEffect, NULL); //点击一次切换一次文本，并调用回调函数
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	bool vibrateFlag = UserDefault::getInstance()->getBoolForKey(VIBRATE_UD, VIBRATE_DEFAULT_FLAG);

	MenuItemLabel* openVibrate = createItem("VIBRATE:ON");
	MenuItemLabel* closeVibrate = createItem("VIBRATE:OFF");

	MenuItemToggle* vibrate;
	if (vibrateFlag) //根据保存的设置确定当前状态
	{
		vibrate = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseVibrate, this), openVibrate, closeVibrate, NULL); //点击一次切换一次文本，并调用回调函数
	}
	else
	{
		vibrate = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseVibrate, this), closeVibrate, openVibrate, NULL); //点击一次切换一次文本，并调用回调函数
	}
	//////////////////////////////////////////////////////////////////////////

	MenuItemLabel* quitGame = createItem("Quit Game", &StartScene::QuitGame); //创建退出游戏菜单项


	Menu* mainMenu = Menu::create(startGame, bgm, effect, vibrate, quitGame, NULL);
	mainMenu->alignItemsVerticallyWithPadding(20);
	addChild(mainMenu);
}

//开始游戏
void StartScene::StartGame()
{
	GameScene* game = GameScene::create();
	Director::getInstance()->pushScene(game); //进入GameScene
}

//播放或停止背景音乐
void StartScene::PlayStopBGM()
{
	bool flag = UserDefault::getInstance()->getBoolForKey(BGM_UD, BGM_DEFAULT_FLAG);
	if (flag)
	{
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		UserDefault::getInstance()->setBoolForKey(BGM_UD, false);
	}
	else
	{
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		UserDefault::getInstance()->setBoolForKey(BGM_UD, true);
	}
}

//打开或关闭音效
void StartScene::OpenCloseEffect()
{
	bool flag = UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG);
	if (flag)
	{
		UserDefault::getInstance()->setBoolForKey(EFFECT_UD, false);
	}
	else
	{
		UserDefault::getInstance()->setBoolForKey(EFFECT_UD, true);
	}
}

//打开或关闭震动
void StartScene::OpenCloseVibrate()
{
	bool flag = UserDefault::getInstance()->getBoolForKey(VIBRATE_UD, VIBRATE_DEFAULT_FLAG);
	if (flag)
	{
		UserDefault::getInstance()->setBoolForKey(VIBRATE_UD, false);
	}
	else
	{
		UserDefault::getInstance()->setBoolForKey(VIBRATE_UD, true);
	}
}

//退出游戏
void StartScene::QuitGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}