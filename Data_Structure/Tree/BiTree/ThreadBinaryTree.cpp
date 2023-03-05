#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <cmath>
/* ����˳��ṹ */

//����״̬
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100						/*�洢�ռ��ʼ������*/

typedef int Status;						/* ״̬���� OK and ERROR */
typedef char TElemType;					/*������charΪ��������*/
TElemType Nil = '#';					/*�ַ�����#Ϊ��*/
typedef enum { Link, Thread } PointerTag;	/*Link = 0��ʾָ�����Һ��ӵ�ָ�룬Thread = 1��ʾָ��ǰ�����ߺ�̵�����*/


typedef struct BiThrNode {
	TElemType data;						/*�������*/
	struct BiThrNode* lchild, * rchild; /*���Һ���ָ��*/
	PointerTag LTag;					/*���ұ�־*/
	PointerTag RTag;
}BiThrNode, * BiThrTree;

BiThrTree pre;							/*ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ��*/
/* ����e��� */
Status visit(TElemType e) {
	printf("%c ", e);
	return OK;
}

/* ǰ����������������еĽ��ֵ(һ���ַ�)���������������� */
/* #�ַ��ͱ�ʾ�ս�� */
Status CreateBiThrTree(BiThrTree* T) {
	TElemType h;
	scanf_s("%c", &h);
	if (h == Nil) {
		*T = NULL;
	}
	else {
		*T = (BiThrTree)malloc(sizeof(BiThrNode));
		if (!*T) exit(OVERFLOW);
		(*T)->data = h;
		CreateBiThrTree(&(*T)->lchild);				/*�ݹ鹹��������*/
		if (!(*T)->lchild)	(*T)->LTag = Link;		/*��������Ӹ���Link*/
		CreateBiThrTree(&(*T)->rchild);				/*�ݹ鹹��������*/
		if (!(*T)->rchild)	(*T)->RTag = Link;		/*������Һ��Ӹ���Link*/
	}
	return OK;
}

/* ��������������������� */
void InThreading(BiThrTree p) {
	if (p) {
		InThreading(p->lchild);
		if (!p->lchild) {			/*���p�����Ӳ����ڵĻ���˵����һ����ǰ�����pre������ֱ�Ӹ��ýڵ�����Ӹ���pre*/
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild) {			/*��Ϊ��û�з��ʵ�p�ĺ�̣����԰�pre�ĺ�̸������pre�ĺ�̾���p*/
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}
/* �����������������T(ͷ���)�ķǵݹ��㷨 */
Status InOrderTraverse_Thr(BiThrTree T)
{
	BiThrTree p;
	p = T->lchild; /* pָ������ */
	while (p != T)
	{ /* �������������ʱ,p==T */
		while (p->LTag == Link)
			p = p->lchild;
		if (!visit(p->data)) /* ������������Ϊ�յĽ�� */
			return ERROR;
		while (p->RTag == Thread && p->rchild != T)
		{
			p = p->rchild;
			visit(p->data); /* ���ʺ�̽�� */
		}
		p = p->rchild;
	}
	return OK;
}

/* �������������T,����������������,Thrtָ��ͷ��� */
Status InOrderThreading(BiThrTree* Thrt, BiThrTree T) {
	*Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!*Thrt)	exit(OVERFLOW);

	(*Thrt)->LTag = Link;		/*ͷ���*/
	(*Thrt)->RTag = Thread;
	(*Thrt)->rchild = (*Thrt);	/*��ָ��ָ���Լ�*/
	if (!T) (*Thrt)->lchild = (*Thrt);
	else {
		(*Thrt)->lchild = T;	/*��Thrtָ����*/
		pre = (*Thrt);			/*������ͷ���ָ��Thrt*/
		InThreading(T);
		pre->rchild = *Thrt;	/*�����һ��������ָ��ָ��Thrt*/
		(*Thrt)->rchild = pre;	/*Thrt����ָ�������һ�����*/
		pre->RTag = Thread;
	}

	return OK;
}

int main()
{
	BiThrTree H, T;
	printf("�밴ǰ�����������(��:'ABDH##I##EJ###CF##G##')\n");
	CreateBiThrTree(&T); /* ��ǰ����������� */
	InOrderThreading(&H, T); /* �������,������������������ */
	printf("�������(���)����������:\n");
	InOrderTraverse_Thr(H); /* �������(���)���������� */
	printf("\n");

	return 0;
}