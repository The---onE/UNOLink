#pragma once

#include "Global.h"

//单个元素信息

class ElementUnit : public Node
{
protected:
	Sprite* elementSprite; //元素图案
	int element; //元素类型
	int num; //元素数字
	Label* numLabel; //元素数字文本

public:
	CREATE_FUNC(ElementUnit);
	bool init();

	void createElement(int ele, int n, Point pos); //在指定位置创建指定类型元素
	void moveToPosition(Point pos); //瞬间移动至指定位置
	void moveToPosition(Point pos, float time); //匀速移动至指定位置
	void appear(float time); //图案瞬间缩小后逐渐变大至原大小
	void disappear(float time); //图案逐渐变小，消失后删除自身

	int getElement(); //返回元素类型
	int getNum(); //返回元素数字
};