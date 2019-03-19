#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

FILE *fp;
//STACK
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
	if(elems != NULL)
		delete elems;
}

//QUEUE
class QUEUE : public STACK {
	STACK  s2;
public:
	QUEUE(int m); //ÿ��ջ���m��Ԫ�أ�Ҫ��ʵ�ֵĶ����������2m��Ԫ��
	QUEUE(const QUEUE&s);             //�ö���s������ʼ������
	virtual operator int() const;            //���ض��е�ʵ��Ԫ�ظ���
	virtual int full() const;               //���ض����Ƿ�������������1�����򷵻�0
	virtual int operator[ ](int x)const;   //ȡ�±�Ϊx��Ԫ�أ���1��Ԫ���±�Ϊ0
	virtual QUEUE& operator<<(int e);  //��e�����,�����ض���
	virtual QUEUE& operator>>(int &e);    //�����е�e,�����ض���
	virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
	virtual void print() const;            //��ӡ����
	virtual ~QUEUE();                    //���ٶ���
};

QUEUE::QUEUE(int m) :STACK(m), s2(m) {}

QUEUE::QUEUE(const QUEUE&s) : STACK(s), s2(s.s2) {}

QUEUE:: operator int() const {
	return (s2.operator int() + STACK::operator int());
}

int QUEUE::full() const {
	if ((STACK::operator int() == STACK::size()) && s2.operator int())
		return 1;
	else
		return 0;
}

int QUEUE:: operator[ ](int x)const {
	if(x < 0 || x >= (s2.operator int() + STACK::operator int()))
		return EOF;
	if (x < s2.STACK::operator int())
		return s2.operator[](s2.operator int() - x - 1);
	else
		return STACK::operator[](x - s2.operator int());
}

QUEUE& QUEUE:: operator<<(int e) {
	if(STACK::operator int() == STACK::size())
	{
		if(s2.operator int())
			return (*this);
		else
		{
			while (STACK::operator int())
			{
				int e;
				STACK::operator>>(e);
				s2.operator<<(e);
			}
		}
	}
	STACK::operator<<(e);
	return (*this);
}

QUEUE& QUEUE:: operator>>(int &e) {
	if (s2.operator int() == 0)
	{
		if(STACK::operator int() == 0)
			return (*this);
		while (STACK::operator int())
		{
			int e;
			STACK::operator>>(e);
			s2 << e;
		}
	}
	s2 >> e;
	return (*this);
}

QUEUE& QUEUE:: operator=(const QUEUE&s) {
	STACK::operator=(s);
	s2 = s.s2;
	return (*this);
}

void QUEUE::print() const {
	for (int i = s2.operator int() - 1; i >= 0; i--)
	{
		cout << "  " << s2[i];
		fprintf(fp, "  %d", s2[i]);
	}
	STACK::print();
}

QUEUE::~QUEUE(){}


int main(int argc, char *argv[])
{
	if(argc == 1)
	{
		QUEUE* men = NULL;
		QUEUE* women = NULL;
		QUEUE* new_men = NULL;
		QUEUE* new_women = NULL;
		int men_num = 0;
		int women_num = 0;
		int men_selec = 0;
		int women_selec = 0;
		int men_dance = 0;
		int women_dance = 0;
		int quit = 0;
		int func = 0;
		int find_flag = 0;
		int counter = 0;
		while(1)
		{
			system("cls");
			int i = 1;
			counter = 0;
			cout<<"||=============================================||\n"
				<<"||                    Dance                    ||\n"
				<<"||=============================================||\n"
				<<"||            1.Set Number of people           ||\n"
				<<"||               2.Choose people               ||\n"
				<<"||                   3.Exit                    ||\n"
				<<"||=============================================||\n";
			if((men != NULL)||(women != NULL))
			{
				cout<<"||                    Queue                    ||\n"
					<<"||        man                      woman       ||\n";
				if((*men) > (*women))
				{
					for(int i = 0; i < (*women); i++)
						cout<<"||         "<<(*men)[i]<<"                         "<<(*women)[i]<<"         ||\n";
					for(int i = (*women);i < (*men); i++)
						cout<<"||         "<<(*men)[i]<<"                                   ||\n";
				}
				else
				{
					for(int i = 0; i < (*men); i++)
						cout<<"||         "<<(*men)[i]<<"                         "<<(*women)[i]<<"         ||\n";
					for(int i = (*men);i < (*women); i++)
						cout<<"||                                   "<<(*women)[i]<<"         ||\n";
				}
				cout<<"||=============================================||\n";
			}
			cout<<"Input the number of instruction\n";
			cin>>func;
			switch(func)
			{
				case 1:
					if(men != NULL)
						delete men;
					if(women != NULL)
						delete women;
					cout<<"Input number of men:\n";
					cin>>men_num;
					cout<<"Input number of women:\n";
					cin>>women_num;
					men = new QUEUE(men_num);
					for(i = 0; i < men_num; i++)
						(*men) << i;
					women = new QUEUE(women_num);
					for(i = 0; i < women_num; i++)
						(*women) << i;
					getchar();
					break;
				case 2:
					if((men == NULL) || (women == NULL))
					{
						cout<<"Havn't initialized number of people!\n";
						getchar();
						getchar();
						break;
					}
					cout<<"Choose one man(number):\n";
					cin>>men_selec;
					cout<<"Choose one woman(number):\n";
					cin>>women_selec;
					if((men_selec >= men_num) || (women_selec >= women_num))
					{
						cout<<"Number Error!\n";
						getchar();
						getchar();
						break;
					}
					while(1)
					{
						counter++;
						(*men)>>men_dance;
						(*women)>>women_dance;
						(*men)<<men_dance;
						(*women)<<women_dance;
						if((men_dance == men_selec) && (women_dance == women_selec))
						{
							cout<<"||=============================================||\n"
								<<"||                   Dancing                   ||\n"
								<<"||                      "<<counter<<"                      ||\n"
								<<"||        man                      woman       ||\n"
								<<"||         "<<men_selec<<"                         "<<women_selec<<"         ||\n"
								<<"||=============================================||\n"
								<<"||                    Queue                    ||\n";
							if((*men) > (*women))
							{
								for(i = 0; i < (*women) - 1; i++)
									cout<<"||         "<<(*men)[i]<<"                         "<<(*women)[i]<<"         ||\n";
								for(i = (*women) - 1;i < (*men) - 1; i++)
									cout<<"||         "<<(*men)[i]<<"                                   ||\n";
							}
							else
							{
								for(i = 0; i < (*men) - 1; i++)
									cout<<"||         "<<(*men)[i]<<"                         "<<(*women)[i]<<"         ||\n";
								for(i = (*men) - 1;i < (*women) - 1; i++)
									cout<<"||                                   "<<(*women)[i]<<"         ||\n";
							}
							cout<<"||=============================================||\n";
							break;
						}
					}
					getchar();
					getchar();
					new_men = new QUEUE(men_num);
					for(i = 0; i < men_num; i++)
						(*new_men)<<i;
					new_women = new QUEUE(women_num);
					for(i = 0; i < women_num; i++)
						(*new_women) << i;
					delete men;
					delete women;
					men = new_men;
					women = new_women;
					break;
				case 3:
					quit = 1;
					break;
				default:;
			}
			if(quit)
			{
				if(men != NULL)
					delete men;
				if(women != NULL)
					delete women;
				break;
			}
		}
	}
	else if(argc > 1)
	{
		fp = fopen("U201612922_4.txt", "w");
		int count = 1;
		int flag = 0;

		QUEUE *s = NULL;//��ʼջ
		QUEUE *p = NULL;//������ջ
		QUEUE *t = NULL;//��ֵ��ջ
		while (count < argc)
		{
			if (!strcmp(argv[count], "-S"))
			{
				cout << "S";
				fprintf(fp, "S");

				if (s == NULL)//�Ƿ��ʼ��
				{
					int max = atoi(argv[++count]);
					s = new QUEUE(max);
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
						if (s->full())//ջ�Ƿ���
						{
							flag = 1;
							break;
						}

						(*s) << atoi(argv[count]);//��ջ

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
						(*s) >> elem;//��ջ
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
				t = new QUEUE(atoi(argv[++count]));
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
				p = new QUEUE(*s);
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
		if(s != NULL)
			delete s;
		fclose(fp);
	}
	return 0;
}
