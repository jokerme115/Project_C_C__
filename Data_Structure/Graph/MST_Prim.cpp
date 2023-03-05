//
// Created by 15351 on 2022/10/26.
//
#include <stdio.h>
#include <stdlib.h>
//定义常量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define GRAPH_INFINITY 655356                   /*存储空间初始分配量*/
#define MAXEDGE 20
#define MAXVEX 20                               /*顶点数*/

typedef struct
{
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
}MGraph;

/*构建图*/
void CreateMGraph(MGraph *G)
{
    int i, j;

    /* printf("请输入边数和顶点数:"); */
    G->numEdges=15;
    G->numVertexes=9;

    for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
    {
        for ( j = 0; j < G->numVertexes; j++)
        {
            if (i==j)
                G->arc[i][j]=0;
            else
                G->arc[i][j] = G->arc[j][i] = GRAPH_INFINITY;
        }
    }

    G->arc[0][1]=10;
    G->arc[0][5]=11;
    G->arc[1][2]=18;
    G->arc[1][8]=12;
    G->arc[1][6]=16;
    G->arc[2][8]=8;
    G->arc[2][3]=22;
    G->arc[3][8]=21;
    G->arc[3][6]=24;
    G->arc[3][7]=16;
    G->arc[3][4]=20;
    G->arc[4][7]=7;
    G->arc[4][5]=26;
    G->arc[5][6]=17;
    G->arc[6][7]=19;

    for(i = 0; i < G->numVertexes; i++)
    {
        for(j = i; j < G->numVertexes; j++)
        {
            G->arc[j][i] =G->arc[i][j];
        }
    }

}

/*Prim算法的最小生成树*/
void MiniSpanTree (MGraph G)
{
    int min, i, j , k;
    int adjvex[MAXVEX];                     /*保存顶点下标*/
    int lowcost[MAXVEX];                    /*保存相关顶点的权值*/
    lowcost[0] = 0;                         /*把v0添加至生成树中*/
    adjvex[0] = 0;                          /*第一个顶点的下标为零*/

    for (i = 0; i < G.numVertexes; i++)     /*初始化lowcost*/
    {
        lowcost[i] = G.arc[0][i];
        adjvex[i] = 0;
    }

    for (i = 1; i < G.numVertexes; i++)
    {
        min = GRAPH_INFINITY;               /*初始化最小值*/
        j = 1, k = 0;
        while (j < G.numVertexes)           /*循环全部顶点, 找出当前lowcost包含的顶点中, 所连接的权值最小的, 顶点下标j*/
        {
            if (lowcost[j] != 0 && lowcost[j] < min)
            {
                min = lowcost[j];           /*更新最小值*/
                k = j;                      /*k保存最小顶点的下标*/
            }
            j++;
        }

        printf("(%d, %d) \n", adjvex[k], k); /*打印当前顶点边中权值最小的边*/

        lowcost[k] = 0;                     /*顶点可以入库且以后不再使用*/

        for (j = 1; j < G.numVertexes; j++) /*循环更新权值lowcost*/
        {
            if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
            {
                lowcost[j] = G.arc[k][j];
                adjvex[j] = k;              /*存入所连接顶点j的权值对应k, k->j*/
            }
        }
    }
}

int main()
{
    MGraph  G;
    CreateMGraph(&G);
    MiniSpanTree(G);
}