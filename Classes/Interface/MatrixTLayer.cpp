#include "MatrixTLayer.h" //�����

#include "Data/MatrixData.h"
#include "Data/ElementData.h"
#include "Data/LinkData.h"
#include "Data/SettingData.h"
#include "Data/AudioData.h"
#include "Data/VibrateData.h"

//Ϊ�������ռ�
MatrixTLayer::MatrixTLayer()
{
	//�������Ԫ�ؿռ�
	elements = new ElementUnit* *[MATRIX_LINE];
	for (int i = 0; i < MATRIX_LINE; i++)
		elements[i] = new ElementUnit*[MATRIX_ROW];

	//����������Ŀռ�
	blocksCenter = new Point*[MATRIX_LINE];
	for (int i = 0; i < MATRIX_LINE; i++)
		blocksCenter[i] = new Point[MATRIX_ROW];

	//�����ǿռ�
	signFlag = new bool*[MATRIX_LINE];
	for (int i = 0; i < MATRIX_LINE; i++)
		signFlag[i] = new bool[MATRIX_ROW];

	//�����Ԫ�������ռ�
	elementCount = new int[ELEMENT_COUNT + 1]; //ע������Ԫ�ؿռ�

	//����������Ԫ�ص������ռ�
	removeCount = new int[ELEMENT_COUNT + 1]; //ע������Ԫ�ؿռ�
}

//��������ռ�
MatrixTLayer::~MatrixTLayer()
{
	//���ո���Ԫ�ؿռ�
	for (int i = 0; i < MATRIX_LINE; i++)
		delete[] elements[i];
	delete[] elements;

	//���ո������Ŀռ�
	for (int i = 0; i < MATRIX_LINE; i++)
		delete[] blocksCenter[i];
	delete[] blocksCenter;

	//���ձ�ǿռ�
	for (int i = 0; i < MATRIX_LINE; i++)
		delete[] signFlag[i];
	delete[] signFlag;

	//���ո�Ԫ�������ռ�
	delete[] elementCount;

	//����������Ԫ�ص������ռ�
	delete[] removeCount;
}

bool MatrixTLayer::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		initBlocks(); //��ʼ�����󣬳�ʼΪ�վ���ͨ��elementsFall����������
		initSign(); //��ʼ�����

		drawGuideLine(MATRIX_BOTTOM_LEFT, MATRIX_TOP_RIGHT); //���ƾ���������Χ�ĸ�����

		forbiddenResponse(); //��ʱ��ֹ�������ڽ���ȴ�����״̬��ͨ��allowResponse�������������̳���TouchableLayer��

		touchedFlag = false; //û����Ч�Ĵ���
		linkFinishFlag = false; //û�����ӽ���

		bRet = true;
	} while (0);
	return bRet;
}

//���ƾ��θ�����
void MatrixTLayer::drawGuideLine(Point leftBottom, Point rightTop)
{
	DrawNode* b = DrawNode::create(); //������ˢ
	addChild(b);

	//ͨ���Ľǻ��ƾ��θ�����
	Point leftTop = Point(leftBottom.x, rightTop.y);
	Point rightBottom = Point(rightTop.x, leftBottom.y);
	b->drawSegment(leftBottom, leftTop, GUIDELINE_WIDTH, GUIDELINE_COLOR);
	b->drawSegment(rightBottom, rightTop, GUIDELINE_WIDTH, GUIDELINE_COLOR);
	b->drawSegment(leftBottom, rightBottom, GUIDELINE_WIDTH, GUIDELINE_COLOR);
	b->drawSegment(leftTop, rightTop, GUIDELINE_WIDTH, GUIDELINE_COLOR);
}

//������������Ԫ�ص���
void MatrixTLayer::drawLine(Coord from, Coord to)
{
	DrawNode* brush = DrawNode::create();
	addChild(brush, -1);
	brush->drawSegment(getCenterByCoord(from), getCenterByCoord(to), LINKLINE_WIDTH, LINKLINE_COLOR); //������������Ԫ�ص���
	linkBrush.push_back(brush); //������������ӵ���������
}

//ɾ�����һ��������
bool MatrixTLayer::removeLatestLine()
{
	if (linkBrush.empty())
		return false; //��������Ϊ�գ��򲻲���
	DrawNode* brush = linkBrush.back();
	removeChild(brush);
	linkBrush.pop_back(); //ɾ���������е����һ��

	return true;
}

//ɾ����������
void MatrixTLayer::removeAllLine()
{
	while (removeLatestLine()); //����ɾ�������������һ�������ߣ�ֱ��Ϊ��
}

//��ʼ����
bool MatrixTLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (isResponse()) //���������
	{
		if (touchedFlag)
			return false; //��������Ч����������Դ˴δ���

		Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView()); //��ô�����

		ERGODIC_BLOCK(i, j) //�������и���
		{
			if (blocksCenter[i][j].getDistance(touchPoint) < containsDis) //����������ڸ�����Ч�뾶��
			{
				linkStart(i, j); //�ø�����Ϊ�������
				touchedFlag = true; //��Ϊ��Ч����
				return true; //�Ըôδ����ĺ�������������ӳ
			}
		}
	}
	
	return false; //������������δ�����κθ��ӣ���Ϊ��Ч���������Ժ�������
}

//�������ƶ�
void MatrixTLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	if (isResponse()) //���������
	{
		Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView()); //��ô�����

		Coord latestPos = linkIndex.back(); //���ߵ����һ��Ԫ��
		int line = latestPos.line;
		int row = latestPos.row;
		if (blocksCenter[line][row].getDistance(touchPoint) < containsDis)
		{
			return; //������������ͬһ��������򲻲���
		}

		if (linkIndex.size() > 1) //���Ѿ��γ����ߣ�������������Ԫ�����ӣ�
		{
			Coord linkPos = *(linkIndex.end() - 2); //���ߵĵ����ڶ���Ԫ��
			if (blocksCenter[linkPos.line][linkPos.row].getDistance(touchPoint) < containsDis)
			{
				undoLink(); //��������ص���һ�����ӵ�Ԫ�أ��������һ������
				return;
			}
		}

		//�����������һ��Ԫ����Χ������Ԫ��
		for (int i = max(line - 1, 0); i <= min(line + 1, MATRIX_LINE-1); ++i)
		{
			for (int j = max(row - 1, 0); j <= min(row + 1, MATRIX_ROW-1); ++j)
			{
				if (blocksCenter[i][j].getDistance(touchPoint) < containsDis) //����������ڸ�����Ч�뾶��
				{
					if (!signFlag[i][j]) //�����Ԫ��δ�����ӹ�
					{
						if (checkLink(latestPos, { i, j })) //�������Ԫ�ط������ӵ���������ɫ��������ͬ��������һ��������Ԫ�أ�
						{
							linkElement(latestPos, { i, j }); //��������Ԫ��
						}
					}
				}
			}
		}
	}
}

//��������
void MatrixTLayer::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (isResponse()) //���������
	{
		Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
		
		removeLink(); //����һ���������жϷ����������������ߵ�Ԫ��
	}

	touchedFlag = false; //��������
}

//����Ƿ�����������Ԫ�أ�ͨ���޸ĸú�������ʵ�ֶ���������
bool MatrixTLayer::checkLink(Coord from, Coord to)
{
	if (getElement(from) == getElement(to)) //Ԫ��������ͬ
		return true;
	if (getNum(from) == getNum(to)) //������ͬ
		return true;

	//����һ��������Ԫ��
	if (getElement(from) == WILD_NUM)
		return true;
	if (getElement(to) == WILD_NUM)
		return true;

	return false; //��������
}

//�������ߵ����
void MatrixTLayer::linkStart(int line, int row)
{
	linkIndex.clear(); //�����������
	signOnlyBlock(line, row); //���ΨһԪ��
	linkIndex.push_back({ line, row }); //��ӵ���������
	if (UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->playEffect(START_LINK_EFFECT); //������Ч
	if (UserDefault::getInstance()->getBoolForKey(VIBRATE_UD, VIBRATE_DEFAULT_FLAG))
		Vibrator::vibrate(START_LINK_VIBRATOR_TIME); //��
}

//��������Ԫ��
void MatrixTLayer::linkElement(Coord from, Coord to)
{
	signElement(to); //���Ԫ��
	drawLine(from, to); //��������
	linkIndex.push_back(to); //��ӵ���������
	if (UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->playEffect(LINK_EFFECT); //������Ч
	if (UserDefault::getInstance()->getBoolForKey(VIBRATE_UD, VIBRATE_DEFAULT_FLAG))
		Vibrator::vibrate(LINK_VIBRATOR_TIME); //��
}

//�������һ������
void MatrixTLayer::undoLink()
{
	Coord latest = linkIndex.back();
	linkIndex.pop_back(); //����������е����һ��Ԫ��
	removeLatestLine(); //ɾ�����һ��������
	unsignElement(latest); //ȡ�����һ��Ԫ�صı��
	if (UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG))
		SimpleAudioEngine::getInstance()->playEffect(UNDO_EFFECT); //������Ч
	if (UserDefault::getInstance()->getBoolForKey(VIBRATE_UD, VIBRATE_DEFAULT_FLAG))
		Vibrator::vibrate(UNDO_VIBRATOR_TIME); //��
}

//�������������������ӵ�Ԫ�أ���������ʧЧ
void MatrixTLayer::removeLink()
{
	if (linkIndex.size() >= MIN_ROMOVE_COUNT) //������ӵ�Ԫ�ظ����ﵽҪ��
	{
		removeSignedElement(); //���������ӵ�Ԫ��
		removeAllLine(); //ɾ��������
		linkFinishFlag = true; //���һ������
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG))
			SimpleAudioEngine::getInstance()->playEffect(REMOVE_EFFECT); //������Ч
		if (UserDefault::getInstance()->getBoolForKey(VIBRATE_UD, VIBRATE_DEFAULT_FLAG))
			Vibrator::vibrate(REMOVE_VIBRATOR_TIME); //��
	}
	else //������ӵ�Ԫ�ظ���δ�ﵽҪ��
	{
		signClear(); //ȡ����Ԫ�صı��
		removeAllLine(); //ɾ��������
		if (UserDefault::getInstance()->getBoolForKey(EFFECT_UD, EFFECT_DEFAULT_FLAG))
			SimpleAudioEngine::getInstance()->playEffect(WRONG_REMOVE_EFFECT); //������Ч
		if (UserDefault::getInstance()->getBoolForKey(VIBRATE_UD, VIBRATE_DEFAULT_FLAG))
			Vibrator::vibrate(WRONG_REMOVE_VIBRATOR_TIME); //��
	}

	linkIndex.clear(); //�����������
}

//��ʼ�����ӣ���ʼ״̬����Ϊ��
void MatrixTLayer::initBlocks()
{
	containsDis = (BLOCK_WIDTH + BLOCK_HEIGHT) / 4 * TOUCH_RADIUS;

	ERGODIC_BLOCK(i, j)
	{
		blocksCenter[i][j] = getCenterByCoord(i, j); //ȷ����������λ��
		elements[i][j] = NULL;
	}

	//��ʼ������
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		elementCount[i] = 0;
		removeCount[i] = 0;
	}
	removeAllCount = 0;
}

//��վ���Ԫ��
void MatrixTLayer::clearElements()
{
	ERGODIC_BLOCK(i, j)
	{
		removeElement(i, j); //���ÿ�����ӵ�Ԫ��
	}
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		elementCount[i] = 0;
	}
}

//��ָ��λ�ô����������͵�Ԫ��
int MatrixTLayer::createElement(int element, int num, int line, int row)
{
	ElementUnit* &temp = elements[line][row]; //������ʱ���ñ������򻯴���
	temp = ElementUnit::create();
	elementCount[element]++; //��ӦԪ�����ͼ�������
	temp->createElement(element, num, getCenterByCoord(line, row)); //����һ��Ԫ�ز���ӵ���Ļ

	return element;
}

//����ָ��λ�õ�Ԫ�أ�����Ԫ������
int MatrixTLayer::removeElement(int line, int row)
{
	ElementUnit* &temp = elements[line][row]; //������ʱ���ñ������򻯴���
	if (!temp)
		return -1; //��ָ��λ����Ԫ�أ��򲻲���
	int ele = temp->getElement(); //���Ԫ������
	elementCount[ele]--; //��ӦԪ�����ͼ�������
	temp->disappear(FALL_TIME); //Ԫ������С����ʧ
	temp = NULL;
	signFlag[line][row] = false;;
	return ele;
}

//��������ǵ�Ԫ�أ�������������
int MatrixTLayer::removeSignedElement()
{
	removeAllCount = 0;
	ERGODIC_BLOCK(i, j)
	{
		if (signFlag[i][j])
		{
			removeCount[removeElement(i, j)]++; //��������ǵ�Ԫ�أ���ӦԪ�����ͼ�������¼��������
			removeAllCount++;
		}
	}
	signClear();

	return removeAllCount;
}

//��ȡָ��λ�õ�Ԫ������
int MatrixTLayer::getElement(int line, int row)
{
	return elements[line][row]->getElement();
}

//��ȡָ��λ�õ�Ԫ������
int MatrixTLayer::getElement(Coord c)
{
	return elements[c.line][c.row]->getElement();
}

//��ȡָ��λ�õ�Ԫ������
int MatrixTLayer::getNum(int line, int row)
{
	return elements[line][row]->getNum();
}

//��ȡָ��λ�õ�Ԫ������
int MatrixTLayer::getNum(Coord c)
{
	return elements[c.line][c.row]->getNum();
}

//Ԫ�����䣬���������Ԫ�أ������Ƿ���˿�λ��ÿһ��ֻ�����һ����λ
bool MatrixTLayer::elementsFall()
{
	bool flag = false; //�Ƿ���˿�λ

	for (int j = 0; j < MATRIX_ROW; ++j) //��ÿһ�е�������
	{
		for (int i = 0; i < MATRIX_LINE; ++i)
		{
			if (elements[i][j] == NULL)
			{
				rowFall(j, i); //�����·���ʼ��һ�����ֿ�λ�������Ϸ�Ԫ�����䣬���λ
				flag = true; //��˿�λ
				break; //ÿһ��ֻ�����һ����λ
			}
		}
	}

	return flag;
}

//ָ���е�ȫ����λ�Ϸ�Ԫ������һ�񣬶��˳�����Ԫ��
void MatrixTLayer::rowFall(int row, int bottom)
{
	for (int i = bottom; i < MATRIX_LINE - 1; ++i)
	{
		elements[i][row] = elements[i + 1][row];
		if (elements[i][row])
		{
			elements[i][row]->moveToPosition(getCenterByCoord(i, row), FALL_TIME); //�Ϸ�Ԫ�ص���һ��
		}
	}
	appear(row); //���˳�����Ԫ��
}

//ָ���еĶ��˳���һ����Ԫ��
void MatrixTLayer::appear(int row)
{
	int top = MATRIX_LINE - 1;

	int ele = randElement(); //���Ԫ������
	int num = randNumber(); //�������
	createElement(ele, num, top, row); //��ָ��λ�����Ԫ��
	this->addChild(elements[top][row]);
	elements[top][row]->appear(FALL_TIME); //Ԫ���𽥱��
}

//ͨ������Ԫ�����ͷֲ���������һ��Ԫ������
int MatrixTLayer::randElement()
{
	bool wildFlag = randFlag(WILD_PROBABILITY-1, 1); //��������Ԫ�صĸ����� 1/WILD_PROBABILITY
	if (wildFlag)
	{
		return WILD_NUM; //�������������Ԫ��
	}

	int *num = new int[ELEMENT_COUNT]; //���ڴ�Ÿ�Ԫ�����͵ĸ���

	//��ȡԪ�����������������Сֵ
	int max = 0;
	int min = 0x7FFFFFFF;
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		int temp = elementCount[i];
		if (temp > max)
			max = temp;
		if (temp < min)
			min = temp;
	}

	if (max-min <= MAX_GAP)
		max++; //������Ԫ��������Ԫ�ز��û�й��������Ԫ�����п��ܳ���
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		num[i] = max - elementCount[i]; //����Ԫ����������ȷ�����ʣ��Ѵ�������Խ�࣬����ԽС
	}

	int re = randNum(ELEMENT_COUNT, num); //���ݸ���������һ�����
	delete[] num;

	return re;
}

//������һ��Ԫ������
int MatrixTLayer::randNumber()
{
	//���ȷ��һ���������Сֵ֮�����
	float r = rand_0_1();
	int gap = MAX_NUMBER - MIN_NUMBER + 1;
	int re = r*gap + MIN_NUMBER;

	return re;
}

//��ʼ�����
void MatrixTLayer::initSign()
{
	signClear();
}

//���Ԫ��
int MatrixTLayer::signElement(int line, int row)
{
	if (!elements[line][row])
		return -1; //���ָ��λ����Ԫ�أ��򲻲���
	signFlag[line][row] = true;

	return 0;
}

//���Ԫ��
int MatrixTLayer::signElement(Coord c)
{
	return signElement(c.line, c.row); //�������غ���
}

//ȡ�����Ԫ��
int MatrixTLayer:: unsignElement(int line, int row)
{
	if (!elements[line][row])
		return -1; //���ָ��λ����Ԫ�أ��򲻲���
	signFlag[line][row] = false;

	return 0;
}

//ȡ�����Ԫ��
int MatrixTLayer::unsignElement(Coord c)
{
	return unsignElement(c.line, c.row); //�������غ���
}

//������б��
void MatrixTLayer::signClear()
{
	ERGODIC_BLOCK(i, j)
	{
		unsignElement(i, j);
	}
}

//�����������
void MatrixTLayer::removeCountClear()
{
	for (int i = 0; i < ELEMENT_COUNT; ++i)
	{
		removeCount[i] = 0;
	}
}

//ֻ���һ��Ԫ�أ�������Ǳ�ȡ����
void MatrixTLayer::signOnlyBlock(int line, int row)
{
	signClear();
	signElement(line, row);
}

//��ȡ�ϴ�����������������������Ϊ��һ��׼��
int MatrixTLayer::getRemoveCount()
{
	int r = removeAllCount;
	removeAllCount = 0;
	return r;
}

//�Ƿ�����Ч�����ӽ���
bool MatrixTLayer::isLinkFinish()
{
	return linkFinishFlag;
}

//׼����һ������
void MatrixTLayer::prepareLink()
{
	linkFinishFlag = false;
}