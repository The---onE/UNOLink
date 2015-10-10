#include "PlayerData.h" //与玩家有关的信息

const int MASTER_ID = 0; //主控玩家编号

const char* HIGH_SCORE_UD = "high_score"; //最高分在UserDefault中的标签

//通过一次连接消除的个数确定得分
int getScoreByLinkCount(int count)
{
	return count * count * 10;
}