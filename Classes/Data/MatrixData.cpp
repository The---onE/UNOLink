#include "MatrixData.h" //��Ԫ�ؾ����йص���Ϸ����

const int MATRIX_LINE = 8; //��������
const int MATRIX_ROW = 6; //��������

const int BLOCK_NUM = MATRIX_LINE * MATRIX_ROW; //������Ӹ���

const float BLOCK_WIDTH = DATUM*0.09f; //���ӿ�ȣ����أ�
const float BLOCK_HEIGHT = DATUM*0.09f; //���Ӹ߶ȣ����أ�
const float TOUCH_RADIUS = 0.8f; //�ɴ�������뾶��Ը��Ӵ�С

const Point MATRIX_CENTER = visibleSize / 2; //��������
const float MATRIX_LEFT = MATRIX_CENTER.x - BLOCK_WIDTH*(float(MATRIX_ROW) / 2); //�������Ե
const float MATRIX_RIGHT = MATRIX_CENTER.x + BLOCK_WIDTH*(float(MATRIX_ROW) / 2); //�����ұ�Ե
const float MATRIX_BOTTOM = MATRIX_CENTER.y - BLOCK_HEIGHT*(float(MATRIX_LINE) / 2); //����ױ�Ե
const float MATRIX_TOP = MATRIX_CENTER.y + BLOCK_HEIGHT*(float(MATRIX_LINE) / 2); //���󶥱�Ե

const Point MATRIX_BOTTOM_LEFT = Point(MATRIX_LEFT, MATRIX_BOTTOM); //�������½�
const Point MATRIX_BOTTOM_LEFT_CENTER = MATRIX_BOTTOM_LEFT + Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2); //���½Ǹ�������
const Point MATRIX_TOP_RIGHT = Point(MATRIX_RIGHT, MATRIX_TOP); //�������Ͻ�
const Point MATRIX_TOP_RIGHT_CENTER = MATRIX_TOP_RIGHT - Point(BLOCK_WIDTH / 2, BLOCK_HEIGHT / 2); //���ϽǸ�������

const Rect MATRIX_RECT = Rect(MATRIX_BOTTOM_LEFT.x, MATRIX_BOTTOM_LEFT.y, BLOCK_WIDTH*MATRIX_ROW, BLOCK_HEIGHT*MATRIX_LINE); //��������

const float GUIDELINE_WIDTH = 2.5f; //������Χ�����߿��
const Color4F GUIDELINE_COLOR = Color4F(0, 1, 0, 0.16f); //������Χ��������ɫ

const int MAX_GAP = 10; //Ԫ�������������Ԫ��������Ԫ�ص������

//ͨ�������ø�������
Point getCenterByCoord(int line, int row)
{
	Point center = MATRIX_BOTTOM_LEFT_CENTER;
	center += Point(BLOCK_WIDTH*row, BLOCK_HEIGHT*line);
	return center;
}
//ͨ�������ø�������
Point getCenterByCoord(Coord c)
{
	return getCenterByCoord(c.line, c.row);
}
