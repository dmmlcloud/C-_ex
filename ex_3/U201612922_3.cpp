#include <iostream>
#include <string.h>
#include <stdlib.h>


using namespace std;

FILE *fp;

class STACK {
	int  *const  elems;    //�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;    //ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;            //ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);        //��ʼ��ջ�����m��Ԫ��
	STACK(const STACK&s);             //��ջs������ʼ��ջ
	virtual int  size() const;            //����ջ�����Ԫ�ظ���max
	virtual operator int() const;            //����ջ��ʵ��Ԫ�ظ���pos
	virtual int operator[ ] (int x) const;    //ȡ�±�x����ջԪ��
	virtual STACK& operator<<(int e);     //��e��ջ,������ջ
	virtual STACK& operator>>(int &e);    //��ջ��e,������ջ
	virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	virtual void print() const;            //��ӡջ
	virtual ~STACK();                    //����ջ
};

STACK::STACK(int m) :elems(new int[m]), max(m) {//��ʼ��ջ�����m��Ԫ��
	pos = 0;
}

STACK::STACK(const STACK&s) : elems(new int[s.max]), max(s.max) {//��ջs������ʼ��ջ
	for (int i = 0; i < s.pos; i++)
		elems[i] = s.elems[i];
	pos = s.pos;
}

int STACK::size() const {
	return max;
}

STACK:: operator int() const {
	return pos;
}

int STACK:: operator[ ] (int x) const {
	if (pos <= x || x < 0)
		return EOF;
	return elems[x];
}

STACK& STACK:: operator<<(int e) {
	elems[pos] = e;
	pos++;
	return *this;
}

STACK& STACK:: operator>>(int &e) {
	e = elems[--pos];
	return *this;
}

STACK& STACK:: operator=(const STACK&s) {
	delete this->elems;
	*(int **)(&this->elems) = new int[s.max];
	for (int i = 0; i < s.pos; i++)
		elems[i] = s.elems[i];
	*(int *)(&this->max) = s.max;
	pos = s.pos;
	return *this;
}

void STACK::print() const {//��ӡջ
	for (int i = 0; i < pos; i++)
	{
		cout << "  " << elems[i];
		fprintf(fp, "  %d", elems[i]);
	}
}

STACK::~STACK() {//����ջ
	delete[]elems;
	pos = 0;
}

int main(int argc, char *argv[])
{

	fp = fopen("U201612922_3.txt", "w");
	int count = 1;
	int flag = 0;

	STACK *s = NULL;//��ʼջ
	STACK *p = NULL;//������ջ
	STACK *t = NULL;//��ֵ��ջ

	while (count < argc)
	{
		if (!strcmp(argv[count], "-S"))
		{
			cout << "S";
			fprintf(fp, "S");

			if (s == NULL)//�Ƿ��ʼ��
			{
				int max = atoi(argv[++count]);
				s = new STACK(max);
				cout << "  " << max;
				fprintf(fp, "  %d", max);
				count++;
			}
			else
			{
				flag = 1;
				break;
			}
		}

		else if (!strcmp(argv[count], "-I"))
		{
			if (s == NULL)//�Ƿ��ʼ��
			{
				cout << "Input Error!";
				break;
			}

			cout << "  I";
			fprintf(fp, "  I");

			if ((count + 1) != argc)
			{
				while (argv[++count][0] != '-')
				{
					if ((*s) >= s->size())//ջ�Ƿ���
					{
						flag = 1;
						break;
					}

					(*s) << (atoi(argv[count]));//��ջ

					if ((count + 1) == argc)//�Ƿ�Ϊ���һ��Ԫ��
					{
						count++;
						break;
					}
				}
			}

			if (flag == 0)
				s->print();
		}

		else if (!strcmp(argv[count], "-O"))
		{
			if (s == NULL)//�Ƿ��ʼ��
			{
				cout << "Input Error!";
				break;
			}
			cout << "  O";
			fprintf(fp, "  O");

			int i = atoi(argv[++count]);

			if (i > (*s))//ջ��Ԫ���Ƿ��㹻��ջ
				flag = 1;

			if (flag == 0)
			{
				while (i--)
				{
					int elem = 0;
					(*s) >> (elem);//��ջ
				}
				s->print();
				count++;
			}
		}

		else if (!strcmp(argv[count], "-A"))
		{
			if (s == NULL)//�Ƿ��ʼ��
			{
				cout << "Input Error!";
				break;
			}
			cout << "  A";
			fprintf(fp, "  A");
			t = new STACK(atoi(argv[++count]));
			(*t) = (*s);
			delete s;
			s = t;
			s->print();
			count++;
		}

		else if (!strcmp(argv[count], "-C"))
		{
			if (s == NULL)//�Ƿ��ʼ��
			{
				cout << "Input Error!";
				break;
			}
			cout << "  C";
			fprintf(fp, "  C");
			p = new STACK(*s);
			delete s;
			s = p;
			s->print();
			count++;
		}

		else if (!strcmp(argv[count], "-N"))
		{
			if (s == NULL)//�Ƿ��ʼ��
			{
				cout << "Input Error!";
				break;
			}
			cout << "  N";
			fprintf(fp, "  N");
			cout << "  " << (*s);
			fprintf(fp, "  %d", int(*s));
			count++;
		}

		else if (!strcmp(argv[count], "-G"))
		{
			if (s == NULL)//�Ƿ��ʼ��
			{
				cout << "Input Error!";
				break;
			}
			cout << "  G";
			fprintf(fp, "  G");
			int elem = (*s)[atoi(argv[++count])];
			if (elem == EOF)
				flag = 1;
			if (flag == 0)
			{
				cout << "  " << elem;
				fprintf(fp, "  %d", elem);
				count++;
			}
		}

		else
			flag = 1;


		if (flag == 1)
		{
			cout << "  E";
			fprintf(fp, "  E");
			break;
		}
	}

	delete s;
	fclose(fp);
	return 0;
}
