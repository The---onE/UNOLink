#include "Players.h"

bool Players::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Node::init());

		master = NULL;

		bRet = true;
	} while (0);
	return bRet;
}

//������
PlayerUnit* Players::createPlayer(int id, int score /* = 0 */)
{
	PlayerUnit* p = PlayerUnit::create();
	p->setId(id);
	p->setScore(score);
	addChild(p);

	return p;
}

//��Ӷ���
PlayerUnit* Players::createAlly(int id, int score /* = 0 */)
{
	PlayerUnit* p = createPlayer(id, score);
	allies.insert(id, p);

	return p;
}

//��Ӷ���
PlayerUnit* Players::createEnemy(int id, int score /* = 0 */)
{
	PlayerUnit* p = createPlayer(id, score);
	enemies.insert(id, p);

	return p;
}

//ͨ����Ż�����ָ��
PlayerUnit* Players::findPlayer(int id)
{
	PlayerUnit* p = allies.at(id);

	if (!p)
		p = enemies.at(id);

	if (!p)
		return NULL;

	return p;
}

//�����������
bool Players::setMaster(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return false;

	master = p;
	masterId = id;
	return true;
}

//������ҷ���
void Players::setScore(int score)
{
	setScore(masterId, score); //Ĭ������������ҷ���
}
void Players::setScore(int id, int score)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return;

	p->setScore(score);
}

//������ҷ���
int Players::getScore()
{
	return getScore(masterId); //Ĭ�ϻ�ȡ������ҷ���
}
int Players::getScore(int id)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->getScore();
}

//��ҷ�����ߣ�������ߺ�ķ���
int Players::scoreUp(int delta)
{
	return scoreUp(masterId, delta); //Ĭ������������ҷ���
}
int Players::scoreUp(int id, int delta)
{
	PlayerUnit* p = findPlayer(id);
	if (!p)
		return -1;

	return p->scoreUp(delta);
}