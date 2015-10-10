#pragma once

#include "Global.h"
#include "State/StateMachine.h"
#include "Data/Data.h"
#include "Interface/Interface.h"
#include "User/User.h"

//��Ϸ������

class GameScene : public Scene
{
protected:
	BackgroundLayer* background; //������
	MatrixTLayer* matrix; //�����
	InformationLayer* information; //��Ϣ��

	Players* players; //�����Ϣ

	float time; //һ����Ϸ�ѽ��е�ʱ��
	float timeLapse(float dt); //ʱ������
	void showTime(float t); //��ʾ��Ϸʣ��ʱ��

	void restart(Ref* pSender); //��ʼ����Ϸ

	void createQuitButton(string normal, string selected); //�����˳���Ϸ��ť
	void quitGame(Ref* pSender); //�˳���Ϸ

public:
	CREATE_FUNC(GameScene);
	bool init();

	void initGame(); //��ʼ��һ����Ϸ

	void initBackground(); //��ʼ��������
	void initMatrix(); //��ʼ�������
	void initInformation(); //��ʼ����Ϣ��

	void initPlayers(); //��ʼ�����
	void initMaster(); //��ʼ���������

	float timeLapseShow(float dt); //ʱ�����Ų���ʾ

	int showScoreUp(); //һ�������������߲���ʾ��������ߺ�ķ���
	int showScoreUp(int delta); //������߲���ʾ��������ߺ�ķ���

	bool elementsFall(); //����Ԫ�����䣬�����Ƿ���������޿�λ
	
	void allowLink(); //����ʼ���ӣ�ʹ�������Ӧ����
	void forbiddenLink(); //��ֹ��ʼ���ӣ�ʹ����㲻��Ӧ����
	bool isLinkFinish(); //�Ƿ�����Ч�����ӽ���
	void prepareLink(); //׼����һ������

	void removeLink(); //�������������������ӵ�Ԫ�أ���������ʧЧ

	void gameOver(); //��Ϸ��������ʾ��������ʾ��ʼ����Ϸ

public:
	StateMachine* stateMachine; //״̬��
	StateMachine* getStateMachine(); //����״̬��ָ��
	void update(float dt);
};

