#pragma once

#include "Global.h"
#include "Unit/PlayerUnit.h"

class Players : public Node
{
protected:
	Map<int, PlayerUnit*> allies;
	Map<int, PlayerUnit*> enemies;
	PlayerUnit* master; //�������
	int masterId; //������ұ��

	PlayerUnit* createPlayer(int id, int score = 0); //������

public:
	CREATE_FUNC(Players);
	bool init();

	PlayerUnit* createAlly(int id, int score = 0); //��Ӷ���
	PlayerUnit* createEnemy(int id, int score = 0); //��Ӷ���

	PlayerUnit* findPlayer(int id); //ͨ����Ż�����ָ��

	bool setMaster(int id); //�����������

	void setScore(int score); //������ҷ���
	void setScore(int id, int score); //������ҷ���
	int getScore(); //������ҷ���
	int getScore(int id); //������ҷ���
	int scoreUp(int delta); //��ҷ�����ߣ�������ߺ�ķ���
	int scoreUp(int id, int delta); //��ҷ�����ߣ�������ߺ�ķ���
};