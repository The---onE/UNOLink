#include "InformationData.h" //����Ϸ��Ϣ�йص���Ϸ����

const string INFORMATION_FONT = "fonts/Marker Felt.ttf"; //��Ϸ��Ϣ����
const int INFORMATION_FONTSIZE = 100; //��Ϸ��Ϣ�����С
const Size INFORMATION_SHADOW_OFFSET = Size(3, 3); //��Ϸ��Ϣ��Ӱƫ����

const Point TIME_POSITION = Point(0, HEIGHT * 0.95); //ʱ����Ϣλ��
const Point TIME_ANCHOR = Point(0, 0.5); //ʱ����Ϣê��
const float TIME_SIZE = 0.05f; //ʱ����Ϣ��С
const Color4B TIME_NORMAL_COLOR = Color4B(0, 255, 0, 255); //ʣ��ʱ���ԣʱ����ɫ
const Color4B TIME_LITTLE_COLOR = Color4B(255, 0, 0, 255); //ʣ��ʱ�����ʱ����ɫ

const Point SCORE_POSITION = Point(WIDTH / 2, HEIGHT * 0.88f); //������Ϣλ��
const Point SCORE_ANCHOR = Point(0.5, 0.5); //������Ϣê��
const float SCORE_SIZE = 0.06f; //������Ϣ��С
const Color4B SCORE_COLOR = Color4B(0, 0, 255, 255); //������Ϣ��ɫ

const Point SCORE_UP_POSITION = Point(WIDTH / 2, HEIGHT / 2); //����������Ϣλ��
const Point SCORE_UP_ANCHOR = Point(0.5, 0.5); //����������Ϣê��
const float SCORE_UP_SIZE = 0.1f; //����������Ϣ��С
const Color4B SCORE_UP_COLOR = Color4B(0, 255, 0, 255); //����������Ϣ��ɫ
const float SCORE_UP_TIME = 1.0f; //����������Ϣ����ʱ��

const Color4B GAME_OVER_COLOR = Color4B(0, 255, 255, 255); //��Ϸ������ǩ��ɫ
const int GAME_OVER_SIZE = 60; //��Ϸ������Ϣ��С�����أ�
const Size GAME_OVER_SHADOW_OFFSET = Size(5, 5); //��Ϸ��Ϣ��Ӱƫ����
