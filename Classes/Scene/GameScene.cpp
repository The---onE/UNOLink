#include "GameScene.h" //��Ϸ������

#include "State/StateList.h"

bool GameScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Scene::init());

		//auto rootNode = CSLoader::createNode("MainScene.csb");
		//addChild(rootNode);

		createQuitButton("images/QuitNormal.png", "images/QuitSelected.png"); //����˳���Ϸ��ť
		stateMachine = StateMachine::createWithGameScene(this); //����״̬��
		stateMachine->changeState(StartState::create(this)); //����׼����ʼ��Ϸ״̬
		this->scheduleUpdate();

		bRet = true;
	} while (0);
	return bRet;
}

//��ʼ��һ����Ϸ
void GameScene::initGame()
{
	time = ROUND_TIME;
	showTime(time); //��ʾʣ��ʱ��
}

//��ʼ��������
void GameScene::initBackground()
{
	background = BackgroundLayer::create();
	addChild(background);
}

//��ʼ�������
void GameScene::initMatrix()
{
	matrix = MatrixTLayer::create();
	addChild(matrix);
}

//��ʼ�������
void GameScene::initInformation()
{
	information = InformationLayer::create();
	addChild(information);
}

//��ʼ�����
void GameScene::initPlayers()
{
	players = Players::create();
	addChild(players);
}

//��ʼ���������
void GameScene::initMaster()
{
	players->createAlly(MASTER_ID);
	players->setMaster(MASTER_ID); //�����������
}

//ʱ������
float GameScene::timeLapse(float dt)
{
	time -= dt;

	return time;
}

//��ʾ��Ϸʣ��ʱ��
void GameScene::showTime(float t)
{
	information->showTime(t);
}

//ʱ�����Ų���ʾ
float GameScene::timeLapseShow(float dt)
{
	float t = timeLapse(dt);
	showTime(t);

	return t;
}

//һ�������������߲���ʾ��������ߺ�ķ���
int GameScene::showScoreUp()
{
	return showScoreUp(getScoreByLinkCount(matrix->getRemoveCount())); //ͨ������Ԫ�ظ��������õķ�������ʾ
}

//������߲���ʾ��������ߺ�ķ���
int GameScene::showScoreUp(int delta)
{
	int s = players->scoreUp(delta);
	information->showScore(s);
	if (delta > 0) //��߷���Ϊ0����ʾ
	{
		information->scoreUp(delta, SCORE_UP_TIME);
	}
	
	return s;
}

//����Ԫ�����䣬�����Ƿ���������޿�λ
bool GameScene::elementsFall()
{
	return matrix->elementsFall();
}

//����ʼ���ӣ�ʹ�������Ӧ����
void GameScene::allowLink()
{
	matrix->allowResponse();
}

//��ֹ��ʼ���ӣ�ʹ����㲻��Ӧ����
void GameScene::forbiddenLink()
{
	matrix->forbiddenResponse();
}

//�Ƿ�����Ч�����ӽ���
bool GameScene::isLinkFinish()
{
	return matrix->isLinkFinish();
}

//׼����һ������
void GameScene::prepareLink()
{
	matrix->prepareLink();
}

//�������������������ӵ�Ԫ�أ���������ʧЧ
void GameScene::removeLink()
{
	matrix->removeLink();
}

void GameScene::gameOver()
{
	int score = players->getScore(); //������շ���
	int high = UserDefault::getInstance()->getIntegerForKey(HIGH_SCORE_UD, 0); //��ȡ��¼����
	Label* label;
	char text[128];
	if (score > high) //��ˢ�¼�¼
	{
		sprintf(text, "New Record!\nScore:%d\nHigh Score:%d\nPress To Start A New Game.", score, score);

		UserDefault::getInstance()->setIntegerForKey(HIGH_SCORE_UD, score); //ˢ�¼�¼

		//��������Ч���򲥷���Ϸ������Ч
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG))
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->playEffect(NEW_RECORD_EFFECT);
		}
	}
	else
	{
		sprintf(text, "Score:%d\nHigh Score:%d\nPress To Start A New Game.", score, high);

		//��������Ч���򲥷��¼�¼��Ч
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG))
		{
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->playEffect(GAME_OVER_EFFECT);
		}
	}

	label = Label::createWithTTF(text, INFORMATION_FONT, GAME_OVER_SIZE, Size::ZERO, TextHAlignment::CENTER); //����Label
	label->setTextColor(GAME_OVER_COLOR);
	label->enableShadow(Color4B::BLACK, Size(5, -5)); //�����Ӱ

	MenuItemLabel* re = MenuItemLabel::create(label, CC_CALLBACK_1(GameScene::restart, this)); //�����˵������ʱ���ÿ�ʼ����Ϸ����
	Menu* menu = Menu::create(re, NULL);
	addChild(menu, 1000);
}


//��ʼ����Ϸ
void GameScene::restart(Ref* pSender)
{
	Scene* s = GameScene::create();
	Director::getInstance()->replaceScene(s); //���µ�Game�����滻ԭ��������ʼ����Ϸ
}

//�����˳���Ϸ��ť
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
//�˳���Ϸ
void GameScene::quitGame(Ref* pSender)
{
	Director::getInstance()->popScene(); //������һ����
}

//����״̬��ָ��
StateMachine* GameScene::getStateMachine()
{
	return stateMachine;
}
//��Ϸ��ѭ��
void GameScene::update(float dt)
{
	stateMachine->update(dt); //��Ϸ��ѭ����״̬������
}