#pragma once

#include "Global.h"

//�ɴ�����̳нӿ�
//�̳к���ʵ��onTouchBegan��onTouchMoved��onTouchEnded����

class TouchableLayer : public Layer //�ɴ��ز���չ
{
protected:
	bool responseFlag; //�Ƿ���Ӧ����

public:
	void onEnter(); //���մ�����Ϣ�����಻Ҫ����

	void allowResponse(); //������
	void forbiddenResponse(); //�������أ����ڻص���������isResponse���������ж�

	bool isResponse(); //�Ƿ�������

	bool onTouchBegan(Touch *touch, Event *unused_event) = 0; //��ʼ���ؽӿ�
 	void onTouchMoved(Touch *touch, Event *unused_event) = 0; //�����ƶ��ӿ�
	void onTouchEnded(Touch *touch, Event *unused_event) = 0; //���ؽ����ӿ�
};