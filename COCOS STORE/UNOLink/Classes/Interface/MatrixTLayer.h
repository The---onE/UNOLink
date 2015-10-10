#pragma once

#include "Global.h"
#include "Expand/TouchableLayer.h"
#include "Unit/ElementUnit.h"

//矩阵层

class MatrixTLayer : public TouchableLayer
{
protected:
	ElementUnit* **elements; //格子元素
	Point **blocksCenter; //格子中心
	//Rect **blocks; //格子区域
	bool **signFlag; //是否被标记

	float containsDis; //触点包含于格子内的最大距离

	int *elementCount; //矩阵中各元素数量
	int *removeCount; //消除各元素的数量

	vector<Coord> linkIndex; //一次连线中的连线顺序
	vector<DrawNode*> linkBrush; //连接两个元素的线

	int removeAllCount; //一次连线消除总数

	bool touchedFlag; //是否已经有有效的触摸
	bool linkFinishFlag; //是否有有效的连接结束

	bool onTouchBegan(Touch *touch, Event *unused_event); //开始触摸
	void onTouchMoved(Touch *touch, Event *unused_event); //触摸点移动
	void onTouchEnded(Touch *touch, Event *unused_event); //触摸结束

	void drawGuideLine(Point leftBottom, Point rightTop); //绘制矩形辅助线
	void drawLine(Coord from, Coord to); //绘制连接两个元素的线
	bool removeLatestLine(); //删除最后一条连接线，返回是否删除成功
	void removeAllLine(); //删除所有连线

	bool checkLink(Coord from, Coord to); //检查是否能连接两个元素，通过修改该函数即可实现多样化规则

	void linkStart(int line, int row); //设置连线的起点
	void linkElement(Coord from, Coord to); //连接两个元素
	void undoLink(); //撤销最后一次连接

	void initBlocks(); //初始化格子，确定格子区域，初始状态矩阵为空
	void clearElements(); //清空矩阵元素
	int createElement(int element, int num, int line, int row); //在指定位置创建给定类型的元素
	int removeElement(int line, int row); //消除指定位置的元素，返回元素类型
	int removeSignedElement(); //消除被标记的元素，返回消除个数
	int getElement(int line, int row); //获取指定位置的元素类型
	int getElement(Coord c); //获取指定位置的元素类型
	int getNum(int line, int row); //获取指定位置的元素数字
	int getNum(Coord c); //获取指定位置的元素数字

	void rowFall(int row, int bottom); //指定列的全部空位上方元素下落一格，顶端出现新元素
	void appear(int row); //指定列的顶端出现一个新元素

	int randElement(); //通过现有元素类型分布，随机获得一个元素类型
	int randNumber(); //随机获得一个元素数字

	void initSign(); //初始化标记
	int signElement(int line, int row); //标记元素
	int signElement(Coord c); //标记元素
	int unsignElement(int line, int row); //取消标记元素
	int unsignElement(Coord c); //取消标记元素
	void signClear(); //清除所有标记

	void removeCountClear(); //清空消除个数
	void signOnlyBlock(int line, int row); //只标记一个元素（其他标记被取消）

public:
	MatrixTLayer(); //构造函数，为数组分配空间
	~MatrixTLayer(); //析构函数，回收数组空间
	CREATE_FUNC(MatrixTLayer);
	bool init();

	void removeLink(); //符合条件则消除被连接的元素，否则连接失效

	int getRemoveCount(); //获取上次连线中消除个数，并清零为下一次准备

	bool elementsFall(); //元素下落，填补被消除的元素，返回是否填补了空位，每一列只填补最下一个空位
	bool isLinkFinish(); //是否有有效的连接结束
	void prepareLink(); //准备下一次连接
};