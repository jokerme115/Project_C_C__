/*����˫���㷨�ڵ�ṹ��ʾ*/
#include <stdio.h>

#define MAX_TREE_SIZE 100

typedef int TElemType;              /*����������������*/
typedef struct PTnode {
    TElemType data;                 /*�����������ͣ��ݶ�Ϊ����*/
    int parent;                     /*˫�׵�λ��*/
}PTnode;

typedef struct {
    PTnode nodes[MAX_TREE_SIZE];    /*����һ���ṹ���飬��СΪMAX_TREE_SIZE*/
    int r, n;                       /*�������λ���Լ������*/
}PTree;

int main() {
    printf("a");
    getchar();
    return 0;
}