#include "StateList.h"

//��ʼ���׶�

bool InitState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	if (matrixFinishFlag)
		CHANGE_TO_STATE(LinkState); //�������������ɣ������ȴ�����״̬
	return false;
}

bool InitState::entryState()
{
	scene->initGame(); //��ʼ��һ����Ϸ
	scene->initPlayers(); //��ʼ�����
	scene->initMaster(); //�����������

	matrixFinishFlag = false;
	matrixTime = FALL_TIME;
	return true;
}

void InitState::onUpdate(float dt)
{
	time += dt;
	matrixTime += dt;
	if (matrixTime > FALL_TIME)
	{
		matrixTime = 0;
		matrixFinishFlag = !scene->elementsFall(); //��һ����������� ��ʼ������һ�㣬ֱ�����������
	}
}

bool InitState::exitState()
{
	return true;
}