//
// Created by 15351 on 2022/10/16.
//
#include <cstdio>

//定义常量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100              /*顶点数*/
#define GRAPH_INFINITY 65535    /*无穷用65535表示*/

typedef int Status;             /* 状态代码 OK and ERROR */
typedef char VertexType;        /*顶点类型*/
typedef int EdgeType;           /*边上权值类型*/

/*定义抽象数据类型 领接矩阵*/
typedef struct {
    VertexType vexs[MAXVEX];    /* 顶点表 */
    EdgeType arc[MAXVEX][MAXVEX];   /*邻接矩阵,可以看做边表*/
    int numNodes, numEdges;     /*图中当前的顶点数和边数*/
}MGraph;

void CreateMGraph(MGraph *G){
    int i, j, k, w;
    printf("输入顶点数和边数:\n");
    scanf_s("%d %d", &G->numNodes, &G->numEdges);     /*输入顶点数和边数*/
    for (i = 0 ; i < G->numNodes; i++){
        scanf(&G->vexs[i]);                         /*读入顶点*/
    }
    for (i = 0 ; i < G->numNodes; i++){
        for (j = 0; j < G->numNodes; j++){
            G->arc[i][j] = GRAPH_INFINITY;                 /*初始化邻接矩阵，NA代表没有相连接的边*/
        }
    }
    for (k = 0; k < G->numEdges; k++){
        printf("输入边(vi,vj)的i,j值,以及权值i->j,w: \n");
        scanf("%d,%d,%d", &i, &j, &w);
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];    /*对称的*/
    }
}
int main(){
    MGraph G;
    CreateMGraph(&G);

    return 0;
}