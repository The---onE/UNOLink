#include "StateList.h"

//�ȴ�����״̬

bool LinkState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	if (gameOverFlag)
	{
		CHANGE_TO_STATE(GameOverState); //��ʱ���þ����������Ϸ����״̬
	}
	else if (scene->isLinkFinish())
	{
		CHANGE_TO_STATE(RemoveState); //�����һ�����ߣ����������״̬
	}
	return false;
}

bool LinkState::entryState()
{
	scene->allowLink(); //������
	scene->prepareLink(); //Ϊ����׼��

	gameOverFlag = false;
 
 	return true;
}

void LinkState::onUpdate(float dt)
{
	time += dt;
	if (scene->timeLapseShow(dt) <= 0)
	{
		gameOverFlag = true; //��ʱ���þ�������Ϸ����
	}
}

bool LinkState::exitState()
{
 	scene->forbiddenLink(); //��������
 	return true;
}