#pragma once

#include "Global.h"

//与单个元素有关的游戏数据

extern const int ELEMENT_COUNT; //元素类型数量
extern const string ELEMENT_NORMAL_IMG[]; //各元素未连接状态图片，万能元素编号的是万能元素图片
extern const float ELEMENT_NORMAL_SIZE; //图片尺寸
extern const int WILD_NUM; //万能元素的编号
extern const int WILD_PROBABILITY; //出现万能元素的概率（1/？）

extern const string NUMBER_FONT; //元素数字字体
extern const int NUMBER_FONTSIZE; //元素数字字体大小
extern const Size NUMBER_SHADOW_OFFSET; //元素数字文本阴影偏移
extern const Color4B NUMBER_COLOR; //元素数字字体颜色
extern const float NUMBER_SIZE; //元素数字文本尺寸

extern const int MAX_NUMBER; //最大元素数字
extern const int MIN_NUMBER; //最小元素数字
