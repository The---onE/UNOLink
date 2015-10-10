#pragma once

#include "Global.h"
#include "Data/SettingData.h"

//��Ϸ��ʼ���泡��

class StartScene : public Scene
{
protected:
	MenuItemLabel* createItem(string text); //�����˵�ѡ��޻ص�����
	MenuItemLabel* createItem(string text, void(StartScene::*func)()); //�����˵�ѡ��лص�����

	void createBackGround(string filename); //��������
	void createMenu(); //�����˵�

	void StartGame(); //��ʼ��Ϸ
	void PlayStopBGM(); //���Ż�ֹͣ��������
	void OpenCloseEffect(); //�򿪻�ر���Ч
	void OpenCloseVibrate(); //�򿪻�ر���
	void QuitGame(); //�˳���Ϸ

public:
	CREATE_FUNC(StartScene);
	bool init();
};
