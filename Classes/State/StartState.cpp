#include "StateList.h"

//��ʼ״̬

bool StartState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	if (time > 0)
		CHANGE_TO_STATE(InitState); //�����ʼ��״̬
	return false;
}

bool StartState::entryState()
{
	scene->initBackground(); //��ʼ������
	scene->initMatrix(); //��ʼ������
	scene->initInformation(); //��ʼ����Ϣ

	return true;
}

void StartState::onUpdate(float dt)
{
	time += dt;
}

bool StartState::exitState()
{
	return true;
}