#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <cmath>
/* 树的顺序结构 */

//定义状态
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100						/*存储空间初始分配量*/

typedef int Status;						/* 状态代码 OK and ERROR */
typedef char TElemType;					/*本树以char为基本类型*/
TElemType Nil = '#';					/*字符型以#为空*/
typedef enum { Link, Thread } PointerTag;	/*Link = 0表示指向左右孩子的指针，Thread = 1表示指向前驱或者后继的线索*/


typedef struct BiThrNode {
	TElemType data;						/*结点数据*/
	struct BiThrNode* lchild, * rchild; /*左右孩子指针*/
	PointerTag LTag;					/*左右标志*/
	PointerTag RTag;
}BiThrNode, * BiThrTree;

BiThrTree pre;							/*全局变量，始终指向刚刚访问过的结点*/
/* 访问e结点 */
Status visit(TElemType e) {
	printf("%c ", e);
	return OK;
}

/* 前序输入二叉线索树中的结点值(一个字符)，构造线索二叉树 */
/* #字符型表示空结点 */
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
		CreateBiThrTree(&(*T)->lchild);				/*递归构造左子树*/
		if (!(*T)->lchild)	(*T)->LTag = Link;		/*如果有左孩子赋予Link*/
		CreateBiThrTree(&(*T)->rchild);				/*递归构造有子树*/
		if (!(*T)->rchild)	(*T)->RTag = Link;		/*如果有右孩子赋予Link*/
	}
	return OK;
}

/* 终须遍历进行中序线索化 */
void InThreading(BiThrTree p) {
	if (p) {
		InThreading(p->lchild);
		if (!p->lchild) {			/*如果p的左孩子不存在的话，说明上一个是前驱结点pre，所以直接给该节点的左孩子赋上pre*/
			p->LTag = Thread;
			p->lchild = pre;
		}
		if (!pre->rchild) {			/*因为还没有访问到p的后继，所以把pre的后继给标出，pre的后继就是p*/
			pre->RTag = Thread;
			pre->rchild = p;
		}
		pre = p;
		InThreading(p->rchild);
	}
}
/* 中序遍历二叉线索树T(头结点)的非递归算法 */
Status InOrderTraverse_Thr(BiThrTree T)
{
	BiThrTree p;
	p = T->lchild; /* p指向根结点 */
	while (p != T)
	{ /* 空树或遍历结束时,p==T */
		while (p->LTag == Link)
			p = p->lchild;
		if (!visit(p->data)) /* 访问其左子树为空的结点 */
			return ERROR;
		while (p->RTag == Thread && p->rchild != T)
		{
			p = p->rchild;
			visit(p->data); /* 访问后继结点 */
		}
		p = p->rchild;
	}
	return OK;
}

/* 中序遍历二叉树T,并将其中序线索化,Thrt指向头结点 */
Status InOrderThreading(BiThrTree* Thrt, BiThrTree T) {
	*Thrt = (BiThrTree)malloc(sizeof(BiThrNode));
	if (!*Thrt)	exit(OVERFLOW);

	(*Thrt)->LTag = Link;		/*头结点*/
	(*Thrt)->RTag = Thread;
	(*Thrt)->rchild = (*Thrt);	/*右指针指向自己*/
	if (!T) (*Thrt)->lchild = (*Thrt);
	else {
		(*Thrt)->lchild = T;	/*让Thrt指向树*/
		pre = (*Thrt);			/*让树的头结点指向Thrt*/
		InThreading(T);
		pre->rchild = *Thrt;	/*树最后一个结点的有指针指向Thrt*/
		(*Thrt)->rchild = pre;	/*Thrt的右指针树最后一个结点*/
		pre->RTag = Thread;
	}

	return OK;
}

int main()
{
	BiThrTree H, T;
	printf("请按前序输入二叉树(如:'ABDH##I##EJ###CF##G##')\n");
	CreateBiThrTree(&T); /* 按前序产生二叉树 */
	InOrderThreading(&H, T); /* 中序遍历,并中序线索化二叉树 */
	printf("中序遍历(输出)二叉线索树:\n");
	InOrderTraverse_Thr(H); /* 中序遍历(输出)二叉线索树 */
	printf("\n");

	return 0;
}