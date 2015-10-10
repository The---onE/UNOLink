#include "StartScene.h" //��Ϸ��ʼ���泡��

#include "GameScene.h"

bool StartScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		createBackGround(BACKGROUND_IMG); //��������
		createMenu(); //�����˵�

		bRet = true;
	} while (0);
	return bRet;
}

//�����˵�ѡ��޻ص�����
MenuItemLabel* StartScene::createItem(string text)
{
	Label* label;
	label = Label::createWithTTF(text, MENUITEM_FONT, MENUITEM_FONTSIZE);
	label->setTextColor(MENUITEM_COLOR);
	label->enableShadow(Color4B::BLACK, MENUITEM_SHADOW_OFFSET);
	return MenuItemLabel::create(label);
}

//�����˵�ѡ��лص�����
#define ITEM_CALLBACK(__selector__,__target__, ...) std::bind(__selector__,__target__, ##__VA_ARGS__)
//#define CC_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)��Ϊ�����лص������꣬ͨ���Զ���꣬��ʵ�ֶԺ���ָ��İ�
MenuItemLabel* StartScene::createItem(string text, void(StartScene::*func)())
{
	Label* label;
	label = Label::createWithTTF(text, MENUITEM_FONT, MENUITEM_FONTSIZE);
	label->setTextColor(MENUITEM_COLOR);
	label->enableShadow(Color4B::BLACK, MENUITEM_SHADOW_OFFSET);
	return MenuItemLabel::create(label, ITEM_CALLBACK(func, this));
}
#undef ITEM_CALLBACK

//��������
void StartScene::createBackGround(string filename)
{
	Sprite* bG = Sprite::create(filename);
	bG->setPosition(BACKGROUND_POSITION);
	setSize(bG, BACKGROUND_SIZE);
	addChild(bG);
}

//�����˵�
void StartScene::createMenu()
{
	MenuItemLabel* startGame = createItem("Start Game", &StartScene::StartGame); //������ʼ��Ϸ�˵���

	//�������ر������ֲ˵���
	//////////////////////////////////////////////////////////////////////////
	bool bgmFlag = UserDefault::getInstance()->getBoolForKey(BGM_UD, BGM_DEFAULT_FLAG);

	MenuItemLabel* playBGM = createItem("BGM:ON");
	MenuItemLabel* stopBGM = createItem("BGM:OFF");

	MenuItemToggle* bgm;
	SimpleAudioEngine::getInstance()->playBackgroundMusic(BGM, true);
	if (bgmFlag) //���ݱ��������ȷ����ǰ״̬
	{
		bgm = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::PlayStopBGM, this), playBGM, stopBGM, NULL); //���һ���л�һ���ı��������ûص�����
	}
	else
	{
		bgm = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::PlayStopBGM, this), stopBGM, playBGM, NULL); //���һ���л�һ���ı��������ûص�����
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	bool effectFlag = UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG);

	MenuItemLabel* openEffect = createItem("EFFECT:ON");
	MenuItemLabel* closeEffect = createItem("EFFECT:OFF");

	MenuItemToggle* effect;
	if (effectFlag) //���ݱ��������ȷ����ǰ״̬
	{
		effect = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseEffect, this), openEffect, closeEffect, NULL); //���һ���л�һ���ı��������ûص�����
	}
	else
	{
		effect = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseEffect, this), closeEffect, openEffect, NULL); //���һ���л�һ���ı��������ûص�����
	}
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	bool vibrateFlag = UserDefault::getInstance()->getBoolForKey(VIBRATE_UD, VIBRATE_DEFAULT_FLAG);

	MenuItemLabel* openVibrate = createItem("VIBRATE:ON");
	MenuItemLabel* closeVibrate = createItem("VIBRATE:OFF");

	MenuItemToggle* vibrate;
	if (vibrateFlag) //���ݱ��������ȷ����ǰ״̬
	{
		vibrate = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseVibrate, this), openVibrate, closeVibrate, NULL); //���һ���л�һ���ı��������ûص�����
	}
	else
	{
		vibrate = MenuItemToggle::createWithCallback(CC_CALLBACK_0(StartScene::OpenCloseVibrate, this), closeVibrate, openVibrate, NULL); //���һ���л�һ���ı��������ûص�����
	}
	//////////////////////////////////////////////////////////////////////////

	MenuItemLabel* quitGame = createItem("Quit Game", &StartScene::QuitGame); //�����˳���Ϸ�˵���


	Menu* mainMenu = Menu::create(startGame, bgm, effect, vibrate, quitGame, NULL);
	mainMenu->alignItemsVerticallyWithPadding(20);
	addChild(mainMenu);
}

//��ʼ��Ϸ
void StartScene::StartGame()
{
	GameScene* game = GameScene::create();
	Director::getInstance()->pushScene(game); //����GameScene
}

//���Ż�ֹͣ��������
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

//�򿪻�ر���Ч
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

//�򿪻�ر���
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

//�˳���Ϸ
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