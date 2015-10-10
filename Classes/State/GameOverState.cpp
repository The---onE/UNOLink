#include "StateList.h"

//��Ϸ����״̬

bool GameOverState::checkStateChange() //״̬�ı䷵��true��״̬δ�ı䷵��false��
{
	return false;
}

bool GameOverState::entryState()
{
	scene->removeLink(); //����ǰ�������ӵ�Ԫ������
	scene->showScoreUp();
	scene->forbiddenLink(); //����������

	scene->gameOver(); //��Ϸ����

	return true;
}

void GameOverState::onUpdate(float dt)
{
	time += dt;
}

bool GameOverState::exitState()
{
	return true;
}