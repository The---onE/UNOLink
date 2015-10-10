#include "ElementUnit.h" //����Ԫ����Ϣ

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

//��ָ��λ�ô���ָ������Ԫ��
void ElementUnit::createElement(int ele, int n, Point pos)
{
	element = ele;
	num = n;
	this->setPosition(pos); //��������λ�ã����ӽڵ�λ����Ϊԭ�㼴�ɳ�������Ļ��Ӧλ����

	elementSprite = Sprite::create(ELEMENT_NORMAL_IMG[ele]); //����Ԫ������ѡ��ͼƬ
	elementSprite->setPosition(Point::ZERO);
	setSize(elementSprite, ELEMENT_NORMAL_SIZE); //����ͼƬ�ߴ�
	addChild(elementSprite);

	char text[16];
	if (ele != WILD_NUM)
	{
		sprintf(text, "%d", n); //���������ı�
	}
	else
	{
		num = -1;
		sprintf(text, " "); //����Ԫ��û������
	}
	//����Ԫ�����ֱ�ǩ
	numLabel = Label::createWithTTF(text, NUMBER_FONT, NUMBER_FONTSIZE);
	numLabel->setTextColor(NUMBER_COLOR);
	numLabel->enableShadow(Color4B::BLACK, NUMBER_SHADOW_OFFSET);
	numLabel->setPosition(Point::ZERO);
	setSize(numLabel, NUMBER_SIZE);
	addChild(numLabel);
}

//˲���ƶ���ָ��λ��
void ElementUnit::moveToPosition(Point pos)
{
	this->setPosition(pos);
}

//�����ƶ���ָ��λ��
void ElementUnit::moveToPosition(Point pos, float time)
{
	this->setScale(1);
	this->stopAllActions();
	Action* move = MoveTo::create(time, pos); //�����ƶ�
	this->runAction(move);
}

//ͼ��˲����С���𽥱����ԭ��С
void ElementUnit::appear(float time)
{
	this->setScale(0); //��С
	Action* scale = ScaleTo::create(time, 1); //�𽥷Ŵ�
	this->runAction(scale);
}

//ͼ���𽥱�С����ʧ��ɾ������
void ElementUnit::disappear(float time)
{
	Action* scale = Sequence::create(ScaleTo::create(time, 0), RemoveSelf::create(), NULL); //������С����С��ʧ��ɾ������
	this->runAction(scale);
}

//����Ԫ������
int ElementUnit::getElement()
{
	return element;
}

//����Ԫ������
int ElementUnit::getNum()
{
	return num;
}