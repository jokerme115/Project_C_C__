//
// Created by 15351 on 2022/10/16.
//
#include <cstdio>

//���峣��
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100              /*������*/
#define GRAPH_INFINITY 65535    /*������65535��ʾ*/

typedef int Status;             /* ״̬���� OK and ERROR */
typedef char VertexType;        /*��������*/
typedef int EdgeType;           /*����Ȩֵ����*/

/*��������������� ��Ӿ���*/
typedef struct {
    VertexType vexs[MAXVEX];    /* ����� */
    EdgeType arc[MAXVEX][MAXVEX];   /*�ڽӾ���,���Կ����߱�*/
    int numNodes, numEdges;     /*ͼ�е�ǰ�Ķ������ͱ���*/
}MGraph;

void CreateMGraph(MGraph *G){
    int i, j, k, w;
    printf("���붥�����ͱ���:\n");
    scanf_s("%d %d", &G->numNodes, &G->numEdges);     /*���붥�����ͱ���*/
    for (i = 0 ; i < G->numNodes; i++){
        scanf(&G->vexs[i]);                         /*���붥��*/
    }
    for (i = 0 ; i < G->numNodes; i++){
        for (j = 0; j < G->numNodes; j++){
            G->arc[i][j] = GRAPH_INFINITY;                 /*��ʼ���ڽӾ���NA����û�������ӵı�*/
        }
    }
    for (k = 0; k < G->numEdges; k++){
        printf("�����(vi,vj)��i,jֵ,�Լ�Ȩֵi->j,w: \n");
        scanf("%d,%d,%d", &i, &j, &w);
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];    /*�ԳƵ�*/
    }
}
int main(){
    MGraph G;
    CreateMGraph(&G);

    return 0;
}