#include "ElementData.h" //�뵥��Ԫ���йص���Ϸ����

const int ELEMENT_COUNT = 4; //Ԫ����������
const string ELEMENT_NORMAL_IMG[] = { "images/red.png", "images/blue.png", "images/green.png", "images/yellow.png", "images/wild.png" }; //��Ԫ��δ����״̬ͼƬ������Ԫ�ر�ŵ�������Ԫ��ͼƬ
const float ELEMENT_NORMAL_SIZE = 0.09f; //ͼƬ�ߴ�
const int WILD_NUM = ELEMENT_COUNT; //����Ԫ�صı��
const int WILD_PROBABILITY = 20; //��������Ԫ�صĸ��ʣ�1/����

const string NUMBER_FONT = "fonts/num.ttf"; //Ԫ����������
const int NUMBER_FONTSIZE = 100; //Ԫ�����������С
const Size NUMBER_SHADOW_OFFSET = Size(3, -3); //Ԫ�������ı���Ӱƫ��
const Color4B NUMBER_COLOR = Color4B(191, 191, 191, 255); //Ԫ������������ɫ
const float NUMBER_SIZE = 0.06f; //Ԫ�������ı��ߴ�

const int MAX_NUMBER = 9; //���Ԫ������
const int MIN_NUMBER = 0; //��СԪ������
