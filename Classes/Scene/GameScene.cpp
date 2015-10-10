#include "GameScene.h" //游戏主场景

#include "State/StateList.h"

bool GameScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		//auto rootNode = CSLoader::createNode("MainScene.csb");
		//addChild(rootNode);

		createQuitButton("images/QuitNormal.png", "images/QuitSelected.png"); //添加退出游戏按钮
		stateMachine = StateMachine::createWithGameScene(this); //创建状态机
		stateMachine->changeState(StartState::create(this)); //进入准备开始游戏状态
		this->scheduleUpdate();

		bRet = true;
	} while (0);
	return bRet;
}

//初始化一局游戏
void GameScene::initGame()
{
	time = ROUND_TIME;
	showTime(time); //显示剩余时间
}

//初始化背景层
void GameScene::initBackground()
{
	background = BackgroundLayer::create();
	addChild(background);
}

//初始化矩阵层
void GameScene::initMatrix()
{
	matrix = MatrixTLayer::create();
	addChild(matrix);
}

//初始化矩阵层
void GameScene::initInformation()
{
	information = InformationLayer::create();
	addChild(information);
}

//初始化玩家
void GameScene::initPlayers()
{
	players = Players::create();
	addChild(players);
}

//初始化主控玩家
void GameScene::initMaster()
{
	players->createAlly(MASTER_ID);
	players->setMaster(MASTER_ID); //设置主控玩家
}

//时间流逝
float GameScene::timeLapse(float dt)
{
	time -= dt;

	return time;
}

//显示游戏剩余时间
void GameScene::showTime(float t)
{
	information->showTime(t);
}

//时间流逝并显示
float GameScene::timeLapseShow(float dt)
{
	float t = timeLapse(dt);
	showTime(t);

	return t;
}

//一次消除后分数提高并显示，返回提高后的分数
int GameScene::showScoreUp()
{
	return showScoreUp(getScoreByLinkCount(matrix->getRemoveCount())); //通过消除元素个数计算获得的分数并显示
}

//分数提高并显示，返回提高后的分数
int GameScene::showScoreUp(int delta)
{
	int s = players->scoreUp(delta);
	information->showScore(s);
	if (delta > 0) //提高分数为0则不显示
	{
		information->scoreUp(delta, SCORE_UP_TIME);
	}
	
	return s;
}

//矩阵元素下落，返回是否下落结束无空位
bool GameScene::elementsFall()
{
	return matrix->elementsFall();
}

//允许开始连接，使矩阵层响应触控
void GameScene::allowLink()
{
	matrix->allowResponse();
}

//禁止开始连接，使矩阵层不响应触控
void GameScene::forbiddenLink()
{
	matrix->forbiddenResponse();
}

//是否有有效的连接结束
bool GameScene::isLinkFinish()
{
	return matrix->isLinkFinish();
}

//准备下一次连接
void GameScene::prepareLink()
{
	matrix->prepareLink();
}

//符合条件则消除被连接的元素，否则连接失效
void GameScene::removeLink()
{
	matrix->removeLink();
}

void GameScene::gameOver()
{
	int score = players->getScore(); //获得最终分数
	int high = UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE_UD, 0); //获取纪录分数
	Label* label;
	char text[128];
	if (score > high) //若刷新纪录
	{
		sprintf(text, "New Record!\nScore:%d\nHigh Score:%d\nPress To Start A New Game.", score, score);

		UserDefault::getInstance()->setIntegerForKey(HIGH_SCORE_UD, score); //刷新纪录

		//若开启音效，则播放游戏结束音效
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG))
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->playEffect(NEW_RECORD_EFFECT);
		}
	}
	else
	{
		sprintf(text, "Score:%d\nHigh Score:%d\nPress To Start A New Game.", score, high);

		//若开启音效，则播放新纪录音效
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG))
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->playEffect(GAME_OVER_EFFECT);
		}
	}

	label = Label::createWithTTF(text, INFORMATION_FONT, GAME_OVER_SIZE, Size::ZERO, TextHAlignment::CENTER); //创建Label
	label->setTextColor(GAME_OVER_COLOR);
	label->enableShadow(Color4B::BLACK, Size(5, -5)); //添加阴影

	MenuItemLabel* re = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::restart, this)); //创建菜单项，按下时调用开始新游戏函数
	Menu* menu = Menu::create(re, NULL);
	addChild(menu, 1000);
}


//开始新游戏
void GameScene::restart(Ref* pSender)
{
	Scene* s = GameScene::create();
	Director::getInstance()->replaceScene(s); //用新的Game场景替换原场景，开始新游戏
}

//创建退出游戏按钮
void GameScene::createQuitButton(string normal, string selected)
{
	auto closeItem = MenuItemImage::create(normal, selected, CC_CALLBACK_1(GameScene::quitGame, this));
	closeItem->setPosition(Point(WIDTH / 2, 0));
	closeItem->setAnchorPoint(Point(0.5f, 0));
	setSize(closeItem, 0.08f);
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);
}
//退出游戏
void GameScene::quitGame(Ref* pSender)
{
	Director::getInstance()->popScene(); //返回上一场景
}

//返回状态机指针
StateMachine* GameScene::getStateMachine()
{
	return stateMachine;
}
//游戏主循环
void GameScene::update(float dt)
{
	stateMachine->update(dt); //游戏主循环由状态机调度
}