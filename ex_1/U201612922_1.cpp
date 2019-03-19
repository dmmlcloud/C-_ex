#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

struct STACK {
	int  *elems;	//�����ڴ����ڴ��ջ��Ԫ��
	int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;	//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
};

void initSTACK(STACK *const p, int m);	//��ʼ��pָ���ջ�����m��Ԫ��
void initSTACK(STACK *const p, const STACK&s); //��ջs��ʼ��pָ���ջ
int  size(const STACK *const p);		//����pָ���ջ�����Ԫ�ظ���max
int  howMany(const STACK *const p);	//����pָ���ջ��ʵ��Ԫ�ظ���pos
int  getelem(const STACK *const p, int x);	//ȡ�±�x����ջԪ��
STACK *const push(STACK *const p, int e); 	//��e��ջ��������p
STACK *const pop(STACK *const p, int &e); 	//��ջ��e��������p
STACK *const assign(STACK*const p, const STACK&s); //��s��pָ��ջ,������p
void print(const STACK*const p);			//��ӡpָ���ջ
void destroySTACK(STACK*const p);		//����pָ���ջ

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

void initSTACK(STACK *const p, int m)//��ʼ��pָ���ջ�����m��Ԫ��
{
	p->elems = new int[m];
	p->max = m;
	p->pos = 0;
}

void initSTACK(STACK *const p, const STACK&s)//��ջs��ʼ��pָ���ջ
{
	p->elems = s.elems;
	p->pos = s.pos;
	p->max = s.max;
}

int size(const STACK *const p)//����pָ���ջ�����Ԫ�ظ���max
{
	return p->max;
}

int  howMany(const STACK *const p)//����pָ���ջ��ʵ��Ԫ�ظ���pos
{
	return p->pos;
}

int  getelem(const STACK *const p, int x)//ȡ�±�x����ջԪ��
{
	if (p->pos <= x || x < 0)
		return EOF;
	return p->elems[x];
}

STACK *const push(STACK *const p, int e)//��e��ջ��������p
{
	if (p->pos >= p->max)
		return NULL;
	p->elems[p->pos] = e;
	p->pos++;
	return p;
}
STACK *const pop(STACK *const p, int &e)//��ջ��e��������p
{
	e = p->elems[p->pos - 1];
	p->pos--;
	return p;
}

STACK *const assign(STACK*const p, const STACK&s)//��s��pָ��ջ,������p
{
	p->elems = new int[s.max];
	for (int i = 0; i < s.pos; i++)
		p->elems[i] = s.elems[i];
	p->pos = s.pos;
	p->max = s.max;
	return p;
}
void print(const STACK*const p)//��ӡpָ���ջ
{
	for (int i = 0; i < p->pos; i++)
	{
		printf("  %d", p->elems[i]);
		fprintf(fp, "  %d", p->elems[i]);
	}

}

void destroySTACK(STACK*const p)//����pָ���ջ
{
	free(p->elems);
	p->elems = NULL;
}


