#pragma once

#include "Global.h"

//��Ԫ�ؾ����йص���Ϸ����

extern const int MATRIX_LINE; //��������
extern const int MATRIX_ROW; //��������
extern const int BLOCK_NUM; //������Ӹ���

extern const float BLOCK_WIDTH; //���ӿ�ȣ����أ�
extern const float BLOCK_HEIGHT; //���Ӹ߶ȣ����أ�
extern const float TOUCH_RADIUS; //�ɴ�������뾶��Ը��Ӵ�С

extern const Point MATRIX_CENTER; //��������
extern const float MATRIX_LEFT; //�������Ե
extern const float MATRIX_RIGHT; //�����ұ�Ե
extern const float MATRIX_BOTTOM; //����ױ�Ե
extern const float MATRIX_TOP; //���󶥱�Ե

extern const Point MATRIX_BOTTOM_LEFT; //�������½�
extern const Point MATRIX_BOTTOM_LEFT_CENTER; //���½Ǹ�������
extern const Point MATRIX_TOP_RIGHT; //�������Ͻ�
extern const Point MATRIX_TOP_RIGHT_CENTER; //���ϽǸ�������

extern const Rect MATRIX_RECT; //��������

extern const float GUIDELINE_WIDTH; //������Χ�����߿��
extern const Color4F GUIDELINE_COLOR; //������Χ��������ɫ

extern const int MAX_GAP; //Ԫ�������������Ԫ��������Ԫ�ص������

Point getCenterByCoord(int line, int row); //ͨ�������ø�������
Point getCenterByCoord(Coord c); //ͨ�������ø�������

//�������и���
#define ERGODIC_BLOCK(line, row) for(int (line)=0; (line)<MATRIX_LINE; ++(line)) for(int (row)=0; (row)<MATRIX_ROW; ++(row))