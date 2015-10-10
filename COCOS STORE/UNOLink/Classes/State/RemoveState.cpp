#include "StateList.h"

//����״̬

bool RemoveState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	if (gameOverFlag)
	{
		CHANGE_TO_STATE(GameOverState); //��ʱ���þ����������Ϸ����״̬
	}
	if (matrixFinishFlag)
		CHANGE_TO_STATE(LinkState); //��Ԫ����������ɣ������ȴ�����״̬
	return false;
}

bool RemoveState::entryState()
{
	scene->showScoreUp(); //��ʾ��������
	matrixFinishFlag = false;
	matrixTime = FALL_TIME;

	gameOverFlag = false;

	return true;
}

void RemoveState::onUpdate(float dt)
{
	time += dt;
	if (scene->timeLapseShow(dt) <= 0)
	{
		gameOverFlag = true; //��ʱ���þ�������Ϸ����
	}
	matrixTime += dt;
	if (matrixTime > FALL_TIME)
	{
		matrixTime = 0;
		matrixFinishFlag = !scene->elementsFall(); //��������λ��ֱ�����������
	}
}

bool RemoveState::exitState()
{
	return true;
}