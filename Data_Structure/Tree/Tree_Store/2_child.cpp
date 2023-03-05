#include <stdio.h>

/* ���ӱ�ʾ�� : ��ÿ�����ĺ��ӽ�������������Ե��������洢�ṹ����n�������n���������������Ҷ�ӽ����˵�����Ϊ�ա�Ȼ���ͷָ�������һ�����Ա�����˳��洢�ṹ����Ž�һ��һά���顣*/


#define MAX_TREE_SIZE 100               /* ��������󳤶� */
typedef int TElemType;                  /* ���������������� */

typedef struct CTNode {                  /* ���庢�ӽ�㣺 child + next */
    int child;                          /* ˫�׽��ĺ��������Ա��е��±� */
    struct CTNode* next;                /* ָ����һ��˫�׽�㺢�ӵĽ�� */
}*ChildPtr;

typedef struct child                    /* ���ı�ͷ�ṹ data + firstchild */
{
    TElemType data;                     /* �����±� */
    ChildPtr firstchild;                /* ָ���һ�����ӽ�� */
}CTBox;

typedef struct {                         /* ���Ľṹ */
    CTBox nodes[MAX_TREE_SIZE];         /* ����һ���ṹ���飬��СΪMAX_TREE_SIZE */
    int r, n;                           /* �������λ���Լ������ */
}PTree;
