#pragma once

#include "Global.h"

//����Ԫ����Ϣ

class ElementUnit : public Node
{
protected:
	Sprite* elementSprite; //Ԫ��ͼ��
	int element; //Ԫ������
	int num; //Ԫ������
	Label* numLabel; //Ԫ�������ı�

public:
	CREATE_FUNC(ElementUnit);
	bool init();

	void createElement(int ele, int n, Point pos); //��ָ��λ�ô���ָ������Ԫ��
	void moveToPosition(Point pos); //˲���ƶ���ָ��λ��
	void moveToPosition(Point pos, float time); //�����ƶ���ָ��λ��
	void appear(float time); //ͼ��˲����С���𽥱����ԭ��С
	void disappear(float time); //ͼ���𽥱�С����ʧ��ɾ������

	int getElement(); //����Ԫ������
	int getNum(); //����Ԫ������
};