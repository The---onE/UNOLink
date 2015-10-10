#pragma once

#include "cocos2d.h"
USING_NS_CC;

using namespace std; //ʹ��string�ȱ�׼������

#include "Custom/Vibrator.h" //����
using namespace Custom; //�����������Զ��������ռ���

//ʹ��cocos studio�������ļ�
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace ui;

//ʹ��������Ч����
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

const int WIDTH = 720; //��Ļ���
const int HEIGHT = 1280; //��Ļ�߶�

const Size visibleSize = Size(WIDTH, HEIGHT);  //��Ļ�ߴ�

const float DATUM = HEIGHT; //���Ȼ�׼
const float DEFAULT_WIDTH = WIDTH; //Ĭ����Ļ���
const float PARAM = (DATUM / DEFAULT_WIDTH); //�ٶȱ�׼������

void setSize(Node* s, float size); //ͨ��ͼƬĿ��߶��볤�Ȼ�׼��������ͼƬ

int randNum(int size, int probability[]); //ͨ����Ŷ�Ӧ���ʵ������ȡ�����
bool randFlag(int no, int yes); //ͨ������ȷ���Ƿ���

int stdStoI(string s); //�ַ���ת������
string stdItoS(int x); //������ת�ַ���
float stdStoF(string s); //�ַ���ת������
string stdFtoS(float x); //������ת�ַ���

void addSprite(Sprite* & s, string img, Point pos, float size, Node* n, int zOrder = 0); //��Sprite��ӵ����ڵ���

//����ṹ��
class Coord
{
public:
	int line, row;
};

//���̿���
/*#define KEYBOARD_FUNCTION void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);\
void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

#define KEYBOARD_LISTENER(CLASS) EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();\
keyboardListener->onKeyPressed = CC_CALLBACK_2(CLASS::onKeyPressed, this); \
keyboardListener->onKeyReleased = CC_CALLBACK_2(CLASS::onKeyReleased, this); \
Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);*/
