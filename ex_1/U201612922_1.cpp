#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

struct STACK {
	int  *elems;	//申请内存用于存放栈的元素
	int   max;	//栈能存放的最大元素个数
	int   pos;	//栈实际已有元素个数，栈空时pos=0;
};

void initSTACK(STACK *const p, int m);	//初始化p指向的栈：最多m个元素
void initSTACK(STACK *const p, const STACK&s); //用栈s初始化p指向的栈
int  size(const STACK *const p);		//返回p指向的栈的最大元素个数max
int  howMany(const STACK *const p);	//返回p指向的栈的实际元素个数pos
int  getelem(const STACK *const p, int x);	//取下标x处的栈元素
STACK *const push(STACK *const p, int e); 	//将e入栈，并返回p
STACK *const pop(STACK *const p, int &e); 	//出栈到e，并返回p
STACK *const assign(STACK*const p, const STACK&s); //赋s给p指的栈,并返回p
void print(const STACK*const p);			//打印p指向的栈
void destroySTACK(STACK*const p);		//销毁p指向的栈

FILE *fp = NULL;


int main(int argc, char *argv[])
{
		fp = fopen("U201612922_1", "w");
		int flag = 0;
		int iflag = 0;
		STACK t, q;
		STACK *s = &t;
		STACK *p = &q;
		int count = 1;
		while (count < argc)
		{
			if (!strcmp(argv[count], "-S"))
			{
				printf("S");
				fprintf(fp, "S");
				if (iflag == 1)
					flag = 1;
				if (iflag == 0)
				{
					int max = atoi(argv[++count]);
					initSTACK(s, max);
					iflag = 1;
					printf("  %d", max);
					fprintf(fp, "  %d", max);
					count++;
				}
			}
			else if (!strcmp(argv[count], "-I"))
			{
				printf("  I");
				fprintf(fp, "  I");
				while (argv[++count][0] != '-')
				{
					int elem = atoi(argv[count]);
					s = push(s, elem);
					if (iflag == 0 || s == NULL)
					{
						flag = 1;
						break;
					}
					if ((count + 1) == argc)
					{
						count++;
						break;
					}
				}
				if (flag == 0)
					print(s);
			}
			else if (!strcmp(argv[count], "-O"))
			{
				printf("  O");
				fprintf(fp, "  O");
				int i = atoi(argv[++count]);
				if (iflag == 0 || i > s->pos)
					flag = 1;
				if (flag == 0)
				{
					while (i--)
					{
						int elem = 0;
						s = pop(s, elem);
					}
					print(s);
					count++;
				}

			}
			else if (!strcmp(argv[count], "-A"))
			{
				printf("  A");
				fprintf(fp, "  A");
				if (iflag == 0)
					flag = 1;
				if (flag == 0)
				{
					p = assign(p, *s);
					print(p);
					count = count + 2;
					STACK *temp = p;
					p = s;
					s = temp;
				}

			}
			else if (!strcmp(argv[count], "-C"))
			{
				printf("  C");
				fprintf(fp, "  C");
				if (iflag == 0)
					flag = 1;
				if (flag == 0)
				{

					initSTACK(p, *s);
					print(p);
					count++;
					STACK *temp = p;
					p = s;
					s = temp;
				}
			}
			else if (!strcmp(argv[count], "-N"))
			{
				printf("  N");
				fprintf(fp, "  N");
				if (iflag == 0)
					flag = 1;
				if (flag == 0)
				{
					printf("  %d", howMany(s));
					fprintf(fp, "  %d", howMany(s));
					count++;
				}
			}
			else if (!strcmp(argv[count], "-G"))
			{
				printf("  G");
				fprintf(fp, "  G");
				if (iflag == 0)
					flag = 1;
				if (flag == 0)
				{
					int elem = getelem(s, atoi(argv[++count]));
					if (elem == EOF)
						flag = 1;
					if (flag == 0)
					{
						printf("  %d", elem);
						fprintf(fp, "  %d", elem);
						count++;
					}
				}

			}
			else
				flag = 1;

			if (flag == 1)
			{
				printf("  E");
				fprintf(fp, "  E");
				break;
			}
		}
		fclose(fp);
	return 0;
}

void initSTACK(STACK *const p, int m)//初始化p指向的栈：最多m个元素
{
	p->elems = new int[m];
	p->max = m;
	p->pos = 0;
}

void initSTACK(STACK *const p, const STACK&s)//用栈s初始化p指向的栈
{
	p->elems = s.elems;
	p->pos = s.pos;
	p->max = s.max;
}

int size(const STACK *const p)//返回p指向的栈的最大元素个数max
{
	return p->max;
}

int  howMany(const STACK *const p)//返回p指向的栈的实际元素个数pos
{
	return p->pos;
}

int  getelem(const STACK *const p, int x)//取下标x处的栈元素
{
	if (p->pos <= x || x < 0)
		return EOF;
	return p->elems[x];
}

STACK *const push(STACK *const p, int e)//将e入栈，并返回p
{
	if (p->pos >= p->max)
		return NULL;
	p->elems[p->pos] = e;
	p->pos++;
	return p;
}
STACK *const pop(STACK *const p, int &e)//出栈到e，并返回p
{
	e = p->elems[p->pos - 1];
	p->pos--;
	return p;
}

STACK *const assign(STACK*const p, const STACK&s)//赋s给p指的栈,并返回p
{
	p->elems = new int[s.max];
	for (int i = 0; i < s.pos; i++)
		p->elems[i] = s.elems[i];
	p->pos = s.pos;
	p->max = s.max;
	return p;
}
void print(const STACK*const p)//打印p指向的栈
{
	for (int i = 0; i < p->pos; i++)
	{
		printf("  %d", p->elems[i]);
		fprintf(fp, "  %d", p->elems[i]);
	}

}

void destroySTACK(STACK*const p)//销毁p指向的栈
{
	free(p->elems);
	p->elems = NULL;
}


