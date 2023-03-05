#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/* ����˳��ṹ */

//����״̬
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
 
#define MAXSIZE 100						/*�洢�ռ��ʼ������*/

typedef int Status;						/* ״̬���� OK and ERROR */

/* ���ڹ�������� */
int treeIndex = 1;
typedef char String[24];				/*0�ŵ�Ԫ��Ŵ��ĳ���  24��char����*/
String str;

/* ����һ���ַ���charָ����ӵ�T������ */
Status StrAssign(String T, const char* chars) {
	int i = 0;
	if (strlen(chars) > MAXSIZE) {
		return ERROR;
	}
	T[0] = strlen(chars);				/*T�������Ԫ�ش�Ŵ��ĳ���*/
	for (i = 1; i <= T[0]; i++) {
		T[i] = *(chars + i - 1);
	}
	return OK;
}

typedef char TElemType;					/*������charΪ��������*/
TElemType Nil = ' ';					/*�ַ�����spaceΪ��*/


/* ����e��� */
Status visit(TElemType e) {
	printf("%c ", e);
	return OK;
}

/* ���ṹ */
typedef struct BiTNode {
	TElemType data;						/*�������*/
	struct BiTNode* lchild, * rchild;	/*���Һ���ָ��*/
}BiTNode, *BiTree;

/* �����ն����� */
Status InitBiTree(BiTree* T) {
	*T = NULL;
	return OK;
}

/* ��ʼ������������T���� */
/* ������������ٶ�����T */
void DestroyBiTree(BiTree* T) {
	if (*T) {
		if ((*T)->lchild) {
			DestroyBiTree(&(*T)->lchild);//��������Ϊ�մݻ�������
		}
		if ((*T)->rchild) {
			DestroyBiTree(&(*T)->rchild);//��������Ϊ�մݻ�������
		}
		free(*T);						//�ͷŸ��ڵ�
		*T = NULL;						//���ڵ�Ϊ��
	}
}

/* ǰ������������еĽ��ֵ(һ���ַ�) */
/* #��ʾ������������������ʾ������T */
void CreateBiTree(BiTree* T) {
	TElemType ch;	//���ڽ��ս��ֵ
	/* scanf("%c", ch); */

	ch = str[treeIndex++];

	if (ch == '#') {
		*T = NULL;
	}
	else {
		*T = (BiTree)malloc(sizeof(BiTNode)); //������ǽṹָ��Ĵ�С�����ǽṹ�Ĵ�С���ṹָ���СΪ8���ṹ��СΪ24
		if (!*T) {						/*�ڴ����ʧ��*/
			exit(OVERFLOW);
		}

		(*T)->data = ch;
		CreateBiTree(&(*T)->lchild);		/*����������*/
		CreateBiTree(&(*T)->rchild);		/*����������*/
	}
}

/* ��ʼ���������������� */
/* �����������TΪ�ն��������򷵻�TRUE�����򻻻�FALSE */
Status BiTreeEmpty(BiTree T) {
	if (T) {
		return FALSE;					//�ǿ�
	}
	else {
		return TRUE;					//��
	}
}

#define ClearBiTree DestroyBiTree		/*������һ��*/

/* ��ʼ���������������� */
/* �������������T����� */
int BiTreeDepth(BiTree T) {
	int left, right;					/*ʹ���˵ݹ�˼�룬�������������ĸ���*/

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

/* ��ʼ���������������� */
/* �������������T�ĸ� */
TElemType Root(BiTree T) {
	if (BiTreeEmpty(T)) {
		return Nil;
	}
	else {
		return T->data;
	}
}

/* ��ʼ������������T����,pָ��T��ĳ����� */
/* �������������p��ָ����ֵ */
TElemType Value(BiTree p) {
	return p->data;
}

/* ��ʼ������������T����,pָ��T��ĳ����� */
/* �����������p��ָ����ֵ��ֵ */
void Assign(BiTree p, TElemType value) {
	p->data = value;
}

/* ��ʼ������������T���� */
/* ���������ǰ��ݹ����T */
void PreOrderTraverse(BiTree T) {
	if (!T) return ;
	printf("%c ", T->data);
	PreOrderTraverse(T->lchild);	/*��ӡ������*/
	PreOrderTraverse(T->rchild);	/*��ӡ������*/
}

/* ��ʼ������������T���� */
/* �������������ݹ����T */
void InOrderTraverse(BiTree T) {
	if (!T) return;
	InOrderTraverse(T->lchild);	/*��ӡ������*/
	printf("%c ", T->data);
	InOrderTraverse(T->rchild);	/*��ӡ������*/
}

/* ��ʼ������������T���� */
/* �������������ݹ����T */
void PostOrderTraverse(BiTree T) {
	if (!T) return;
	PostOrderTraverse(T->lchild);	/*��ӡ������*/
	PostOrderTraverse(T->rchild);	/*��ӡ������*/
	printf("%c ", T->data);
}
int main()
{
	int i;
	BiTree T;
	TElemType e1;
	InitBiTree(&T);


	StrAssign(str, "ABDH#K###E##CFI###G#J##");//����һ����ĸ�͵�����������������

	CreateBiTree(&T);

	printf("����ն�������,���շ�%d(1:�� 0:��) �������=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
	e1 = Root(T);
	printf("�������ĸ�Ϊ: %c\n", e1);

	printf("\nǰ�����������:");
	PreOrderTraverse(T);
	printf("\n�������������:");
	InOrderTraverse(T);
	printf("\n�������������:");
	PostOrderTraverse(T);
	ClearBiTree(&T);
	printf("\n�����������,���շ�%d(1:�� 0:��) �������=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
	i = Root(T);
	if (!i)
		printf("���գ��޸�\n");


	return 0;
}
