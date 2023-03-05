#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* 树的顺序结构 */

//定义状态
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
 
#define MAXSIZE 100						/*存储空间初始分配量*/

typedef int Status;						/* 状态代码 OK and ERROR */

/* 用于构造二叉树 */
int treeIndex = 1;
typedef char String[24];				/*0号单元存放串的长度  24个char长度*/
String str;

/* 接受一个字符串char指针添加到T数组中 */
Status StrAssign(String T, const char* chars) {
	int i = 0;
	if (strlen(chars) > MAXSIZE) {
		return ERROR;
	}
	T[0] = strlen(chars);				/*T数组的首元素存放串的长度*/
	for (i = 1; i <= T[0]; i++) {
		T[i] = *(chars + i - 1);
	}
	return OK;
}

typedef char TElemType;					/*本树以char为基本类型*/
TElemType Nil = ' ';					/*字符型以space为空*/


/* 访问e结点 */
Status visit(TElemType e) {
	printf("%c ", e);
	return OK;
}

/* 结点结构 */
typedef struct BiTNode {
	TElemType data;						/*结点数据*/
	struct BiTNode* lchild, * rchild;	/*左右孩子指针*/
}BiTNode, *BiTree;

/* 创建空二叉树 */
Status InitBiTree(BiTree* T) {
	*T = NULL;
	return OK;
}

/* 初始条件：二叉树T存在 */
/* 操作结果：销毁二叉树T */
void DestroyBiTree(BiTree* T) {
	if (*T) {
		if ((*T)->lchild) {
			DestroyBiTree(&(*T)->lchild);//左子树不为空摧毁左子树
		}
		if ((*T)->rchild) {
			DestroyBiTree(&(*T)->rchild);//右子树不为空摧毁右子树
		}
		free(*T);						//释放根节点
		*T = NULL;						//根节点为空
	}
}

/* 前序输入二叉树中的结点值(一个字符) */
/* #表示空树，构造二叉链表表示二叉树T */
void CreateBiTree(BiTree* T) {
	TElemType ch;	//用于接收结点值
	/* scanf("%c", ch); */

	ch = str[treeIndex++];

	if (ch == '#') {
		*T = NULL;
	}
	else {
		*T = (BiTree)malloc(sizeof(BiTNode)); //这儿不是结构指针的大小，而是结构的大小，结构指针大小为8，结构大小为24
		if (!*T) {						/*内存分配失败*/
			exit(OVERFLOW);
		}

		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);		/*创建左子树*/
		CreateBiTree(&(*T)->rchild);		/*创建右子树*/
	}
}

/* 初始条件：二叉树存在 */
/* 操作结果：若T为空二叉树，则返回TRUE，否则换回FALSE */
Status BiTreeEmpty(BiTree T) {
	if (T) {
		return FALSE;					//非空
	}
	else {
		return TRUE;					//空
	}
}

#define ClearBiTree DestroyBiTree		/*俩函数一样*/

/* 初始条件：二叉树存在 */
/* 操作结果：返回T的深度 */
int BiTreeDepth(BiTree T) {
	int left, right;					/*使用了递归思想，传递左右子树的个数*/

	if (!T) return 0;
	if (T->lchild) {
		left = BiTreeDepth(T->lchild);
	}
	else {
		left = 0;
	}
	if (T->rchild) {
		right = BiTreeDepth(T->rchild);
	}
	else {
		right = 0;
	}

	return left > right ? left + 1 : right + 1;
}

/* 初始条件：二叉树存在 */
/* 操作结果：返回T的根 */
TElemType Root(BiTree T) {
	if (BiTreeEmpty(T)) {
		return Nil;
	}
	else {
		return T->data;
	}
}

/* 初始条件：二叉树T存在,p指向T的某个结点 */
/* 操作结果：返回p所指结点的值 */
TElemType Value(BiTree p) {
	return p->data;
}

/* 初始条件：二叉树T存在,p指向T的某个结点 */
/* 操作结果：给p所指结点的值赋值 */
void Assign(BiTree p, TElemType value) {
	p->data = value;
}

/* 初始条件：二叉树T存在 */
/* 操作结果：前序递归遍历T */
void PreOrderTraverse(BiTree T) {
	if (!T) return ;
	printf("%c ", T->data);
	PreOrderTraverse(T->lchild);	/*打印左子树*/
	PreOrderTraverse(T->rchild);	/*打印右子树*/
}

/* 初始条件：二叉树T存在 */
/* 操作结果：中序递归遍历T */
void InOrderTraverse(BiTree T) {
	if (!T) return;
	InOrderTraverse(T->lchild);	/*打印左子树*/
	printf("%c ", T->data);
	InOrderTraverse(T->rchild);	/*打印右子树*/
}

/* 初始条件：二叉树T存在 */
/* 操作结果：后序递归遍历T */
void PostOrderTraverse(BiTree T) {
	if (!T) return;
	PostOrderTraverse(T->lchild);	/*打印左子树*/
	PostOrderTraverse(T->rchild);	/*打印右子树*/
	printf("%c ", T->data);
}
int main()
{
	int i;
	BiTree T;
	TElemType e1;
	InitBiTree(&T);


	StrAssign(str, "ABDH#K###E##CFI###G#J##");//输入一个字母就得输入他的左右子树

	CreateBiTree(&T);

	printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
	e1 = Root(T);
	printf("二叉树的根为: %c\n", e1);

	printf("\n前序遍历二叉树:");
	PreOrderTraverse(T);
	printf("\n中序遍历二叉树:");
	InOrderTraverse(T);
	printf("\n后序遍历二叉树:");
	PostOrderTraverse(T);
	ClearBiTree(&T);
	printf("\n清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
	i = Root(T);
	if (!i)
		printf("树空，无根\n");


	return 0;
}
