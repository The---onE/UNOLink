#include "TouchableLayer.h" //�ɴ�����̳нӿ�

//���մ�����Ϣ�����಻Ҫ����
void TouchableLayer::onEnter()
{
	do
	{
		Layer::onEnter();

		//��Ӽ�����
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);
		listener->onTouchBegan = CC_CALLBACK_2(TouchableLayer::onTouchBegan, this);
		listener->onTouchMoved = CC_CALLBACK_2(TouchableLayer::onTouchMoved, this);
		listener->onTouchEnded = CC_CALLBACK_2(TouchableLayer::onTouchEnded, this);
		listener->onTouchCancelled = CC_CALLBACK_2(TouchableLayer::onTouchEnded, this);

		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	} while (0);
}

//������
void TouchableLayer::allowResponse()
{
	responseFlag = true;
}

//�������أ����ڻص���������isResponse���������ж�
void TouchableLayer::forbiddenResponse()
{
	responseFlag = false;
}

//�Ƿ�������
bool TouchableLayer::isResponse()
{
	return responseFlag;
}