#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

FILE *fp;

class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多m个元素
	STACK(const STACK&s); //用栈s拷贝初始化栈
	int  size() const;		//返回栈的最大元素个数max
	int  howMany() const;	//返回栈的实际元素个数pos
	int  getelem(int x) const;	//取下标x处的栈元素
	STACK& push(int e); 	//将e入栈,并返回栈
	STACK& pop(int &e); 	//出栈到e,并返回栈
	STACK& assign(const STACK&s); //赋s给栈,并返回被赋值的栈
	void print() const;		//打印栈
	~STACK();				//销毁栈
};

STACK::STACK(int m):elems(new int[m]),max(m){//初始化栈：最多m个元素
	pos = 0;
}

STACK::STACK(const STACK&s):elems(new int [s.max]),max(s.max) {//用栈s拷贝初始化栈
	for (int i = 0; i < s.pos; i++)
		elems[i] = s.elems[i];
	pos = s.pos;
}

int STACK::size() const{//返回栈的最大元素个数max
	return max;
}

int STACK::howMany() const {//返回栈的实际元素个数pos
	return pos;
}

int STACK::getelem(int x) const {//取下标x处的栈元素
	if (pos <= x || x < 0)
		return EOF;
	return elems[x];
}

STACK& STACK::push(int e) { //将e入栈,并返回栈
	elems[pos] = e;
	pos++;
	return *this;
}

STACK& STACK::pop(int &e) { //出栈到e,并返回栈
	e = elems[--pos];
	return *this;
}

STACK& STACK::assign(const STACK&s) { //赋s给栈,并返回被赋值的栈
	delete this->elems;
	*(int**)&this->elems=new int[s.max];
	for (int i = 0; i < s.pos; i++)
		this->elems[i] = s.elems[i];
	*(int*)&this->max=s.max;
	pos = s.pos;
	return *this;
}

void STACK::print() const {//打印栈
	for (int i = 0; i < pos; i++)
	{
		cout << "  " << elems[i];
		fprintf(fp, "  %d", elems[i]);
	}
}

STACK::~STACK() {//销毁栈
	delete elems;
	pos = 0;
}

int main(int argc, char *argv[])
{

	fp = fopen("U201612922_2.txt", "w");
	int count = 1;
	int flag = 0;

	STACK *s = NULL;//初始栈
	STACK *p = NULL;//创建新栈
	STACK *t = NULL;//赋值新栈

	while (count < argc)
	{
		if (!strcmp(argv[count], "-S"))
		{
			cout << "S";
			fprintf(fp, "S");

			if (s == NULL)//是否初始化
			{
				int max = atoi(argv[++count]);
				s = new STACK(max);
				cout<< "  " << max;
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
			if(s == NULL)//是否初始化
			{
				cout<<"Input Error!";
				break;
			}

			cout << "  I";
			fprintf(fp, "  I");

			if((count + 1) != argc)
			{
				while (argv[++count][0] != '-')
				{
					if (s->howMany() >= s->size())//栈是否满
					{
						flag = 1;
						break;
						}

					s->push(atoi(argv[count]));//入栈

					if ((count + 1) == argc)//是否为最后一个元素
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
			if(s == NULL)//是否初始化
			{
				cout<<"Input Error!";
				break;
			}
			cout << "  O";
			fprintf(fp, "  O");

			int i = atoi(argv[++count]);

			if (i > s->howMany())//栈中元素是否足够出栈
				flag = 1;

			if(flag == 0)
			{
				while (i--)
				{
					int elem = 0;
					s->pop(elem);//出栈
				}
				s->print();
				count++;
			}
		}

		else if (!strcmp(argv[count], "-A"))
		{
			if(s == NULL)//是否初始化
			{
				cout<<"Input Error!";
				break;
			}
			cout << "  A";
			fprintf(fp, "  A");
			t = new STACK(atoi(argv[++count]));
			t->assign(*s);
			delete s;
			s = t;
			s->print();
			count++;
		}

		else if (!strcmp(argv[count], "-C"))
		{
			if(s == NULL)//是否初始化
			{
				cout<<"Input Error!";
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
			if(s == NULL)//是否初始化
			{
				cout<<"Input Error!";
				break;
			}
			cout << "  N";
			fprintf(fp, "  N");
			cout << "  " << s->howMany();
			fprintf(fp, "  %d", s->howMany());
			count++;
		}

		else if (!strcmp(argv[count], "-G"))
		{
			if(s == NULL)//是否初始化
			{
				cout<<"Input Error!";
				break;
			}
			cout << "  G";
			fprintf(fp, "  G");
			int elem = s->getelem(atoi(argv[++count]));
			if (elem == EOF)
				flag = 1;
			if(flag == 0)
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
