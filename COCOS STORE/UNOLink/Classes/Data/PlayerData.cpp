#include "PlayerData.h" //������йص���Ϣ

const int MASTER_ID = 0; //������ұ��

const char* HIGH_SCORE_UD = "high_score"; //��߷���UserDefault�еı�ǩ

//ͨ��һ�����������ĸ���ȷ���÷�
int getScoreByLinkCount(int count)
{
	return count * count * 10;
}