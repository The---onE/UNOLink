#include "Global.h"

//ͨ��ͼƬĿ��߶��볤�Ȼ�׼��������ͼƬ
void setSize(Node* s, float size)
{
	s->setScale(DATUM*size / s->getContentSize().height);
}

//ͨ����Ŷ�Ӧ���ʵ������ȡ�����
int randNum(int size, int probability[])
{
	int sum = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += probability[i];
	}
	float r = rand_0_1()*sum;

	sum = 0;
	for (int i = 0; i < size; ++i)
	{
		sum += probability[i];
		if (r < sum)
		{
			return i;
		}
	}
	return -1; //�����ʲ��Ϸ�����-1
}

//ͨ������ȷ���Ƿ���
bool randFlag(int no, int yes)
{
	int sum = no + yes;
	float r = rand_0_1()*sum;

	if (r < no)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//��Sprite��ӵ����ڵ���
void addSprite(Sprite* & s, string img, Point pos, float size, Node* n, int zOrder)
{
	s = Sprite::create(img);
	s->setPosition(pos);
	setSize(s, size);
	n->addChild(s, zOrder);
}

//����10^x
int pow10(int x)
{
	int t = 1;
	for (int i = 0; i < x; ++i)
		t *= 10;
	return t;
}

//�ַ���ת������
int stdStoI(string s)
{
	if (s.empty())
		return -1;

	if (s[0] == '-')
		return -stdStoI(string(s.begin() + 1, s.end()));

	int num = 0, temp = s.length() - 1;

	for (string::iterator i = s.begin(); i < s.end(); ++i, --temp)
	{
		if (*i<'0' || *i>'9')
		{
			return -1;
		}
		else
		{
			int x = *i - '0';
			num += x * pow10(temp);
		}
	}

	return num;
}

//������ת�ַ���
string stdItoS(int x)
{
	char text[128];
	sprintf(text, "%d", x);
	string str = text;
	return str;
}

//�ַ���ת������
float stdStoF(string s)
{
	int nc=0, pc=0;
	for (string::iterator i = s.begin(); i < s.end(); ++i)
	{
		if (*i >= '0'&&*i <= '9')
		{
			nc++;
		}
		else if (*i == '.')
		{
			pc++;
		}
		else
		{
			return -1;
		}
	}
	if (!nc)
		return -1;
	if (pc > 1)
		return -1;

	float temp = 10;
	bool ispnum = true;
	float ans = 0;
	if (s[0] == '-')
	{
		ispnum = false;
		s = string(s.begin() + 1, s.end());
	}
	else if (s[0] == '-')
	{
		s = string(s.begin() + 1, s.end());
	}
	string::iterator i;
	for (i = s.begin(); i < s.end(); ++i)
	{
		if (*i == '.')
			break;
		ans = ans * 10 + (*i - '0');
	}
	for (++i; i < s.end(); ++i)
	{
		ans = ans + (*i - '0') / temp;
		temp *= 10;
	}
	if (ispnum)
		return ans;
	else
		return -ans;
	return ans;
}

//������ת�ַ���
string stdFtoS(float x)
{
	char text[128];
	sprintf(text, "%.2f", x);
	string str = text;
	return str;
}