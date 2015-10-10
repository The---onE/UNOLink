#include "ElementUnit.h" //单个元素信息

#include "Data/ElementData.h"

bool ElementUnit::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());


		bRet = true;
	} while (0);
	return bRet;
}

//在指定位置创建指定类型元素
void ElementUnit::createElement(int ele, int n, Point pos)
{
	element = ele;
	num = n;
	this->setPosition(pos); //设置自身位置，将子节点位置设为原点即可出现在屏幕对应位置上

	elementSprite = Sprite::create(ELEMENT_NORMAL_IMG[ele]); //根据元素类型选择图片
	elementSprite->setPosition(Point::ZERO);
	setSize(elementSprite, ELEMENT_NORMAL_SIZE); //设置图片尺寸
	addChild(elementSprite);

	char text[16];
	if (ele != WILD_NUM)
	{
		sprintf(text, "%d", n); //设置数字文本
	}
	else
	{
		num = -1;
		sprintf(text, " "); //万能元素没有数字
	}
	//创建元素数字标签
	numLabel = Label::createWithTTF(text, NUMBER_FONT, NUMBER_FONTSIZE);
	numLabel->setTextColor(NUMBER_COLOR);
	numLabel->enableShadow(Color4B::BLACK, NUMBER_SHADOW_OFFSET);
	numLabel->setPosition(Point::ZERO);
	setSize(numLabel, NUMBER_SIZE);
	addChild(numLabel);
}

//瞬间移动至指定位置
void ElementUnit::moveToPosition(Point pos)
{
	this->setPosition(pos);
}

//匀速移动至指定位置
void ElementUnit::moveToPosition(Point pos, float time)
{
	this->setScale(1);
	this->stopAllActions();
	Action* move = MoveTo::create(time, pos); //匀速移动
	this->runAction(move);
}

//图案瞬间缩小后逐渐变大至原大小
void ElementUnit::appear(float time)
{
	this->setScale(0); //缩小
	Action* scale = ScaleTo::create(time, 1); //逐渐放大
	this->runAction(scale);
}

//图案逐渐变小，消失后删除自身
void ElementUnit::disappear(float time)
{
	Action* scale = Sequence::create(ScaleTo::create(time, 0), RemoveSelf::create(), NULL); //先逐渐缩小，缩小消失后删除自身
	this->runAction(scale);
}

//返回元素类型
int ElementUnit::getElement()
{
	return element;
}

//返回元素数字
int ElementUnit::getNum()
{
	return num;
}