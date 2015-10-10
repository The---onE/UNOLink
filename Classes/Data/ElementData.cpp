#include "ElementData.h" //与单个元素有关的游戏数据

const int ELEMENT_COUNT = 4; //元素类型数量
const string ELEMENT_NORMAL_IMG[] = { "images/red.png", "images/blue.png", "images/green.png", "images/yellow.png", "images/wild.png" }; //各元素未连接状态图片，万能元素编号的是万能元素图片
const float ELEMENT_NORMAL_SIZE = 0.09f; //图片尺寸
const int WILD_NUM = ELEMENT_COUNT; //万能元素的编号
const int WILD_PROBABILITY = 20; //出现万能元素的概率（1/？）

const string NUMBER_FONT = "fonts/num.ttf"; //元素数字字体
const int NUMBER_FONTSIZE = 100; //元素数字字体大小
const Size NUMBER_SHADOW_OFFSET = Size(3, -3); //元素数字文本阴影偏移
const Color4B NUMBER_COLOR = Color4B(191, 191, 191, 255); //元素数字字体颜色
const float NUMBER_SIZE = 0.06f; //元素数字文本尺寸

const int MAX_NUMBER = 9; //最大元素数字
const int MIN_NUMBER = 0; //最小元素数字
