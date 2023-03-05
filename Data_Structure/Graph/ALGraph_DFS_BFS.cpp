//
// Created by 15351 on 2022/10/23.
//
#include <stdio.h>
//定义常量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0


typedef int Status;             /* 状态代码 OK and ERROR */
typedef int Boolean;
typedef char VertexType;        /*顶点类型*/
typedef int EdgeType;           /*边上权值类型*/

#define MAXSIZE 9               /*存储空间初始分配量*/
#define MAXEDGE 15
#define MAXVEX 9                /*顶点数*/

typedef struct{
    VertexType vexs[MAXVEX];    /*顶点表*/
    EdgeType arc[MAXVEX][MAXVEX];   /*领接矩阵*/
    int numVertexes, numEdges;  /*图中当前的顶点数和边数*/
}MGraph;

/*需要用到队列的顺序结构*/
typedef struct
{
    int data[MAXSIZE];
    int front;                  /*头指针*/
    int rear;                   /*尾指针, 如果队列不空，指向队列的尾元素得下一个位置*/
}Queue;

/*初始化一个空队列Q*/
Status InitQueue(Queue *Q){
    Q->front = 0;
    Q->rear = 0;
    return OK;
}

/* 若队列Q为空队列,则返回TRUE,否则返回FALSE */
Status QueueEmpty (Queue Q){
    if (Q.front == Q.rear)  return TRUE;
    else return FALSE;
}

/* 若队列未满，则插入元素e为Q新的队尾元素 */
Status EnQueue (Queue *Q, int e){
    if ((Q->rear + 1) % MAXSIZE == Q->front)    return ERROR;

    Q->data[Q->rear] = e;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

/* 若队列不空，则删除Q中队头元素，用e返回其值 */
Status DeQueue (Queue *Q, int *e){
    if (QueueEmpty(*Q))    return ERROR;

    *e = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}

void CreateMGraph(MGraph *G)
{
    int i, j;

    G->numEdges=15;
    G->numVertexes=9;

    /* 读入顶点信息，建立顶点表 */
    G->vexs[0]='A';
    G->vexs[1]='B';
    G->vexs[2]='C';
    G->vexs[3]='D';
    G->vexs[4]='E';
    G->vexs[5]='F';
    G->vexs[6]='G';
    G->vexs[7]='H';
    G->vexs[8]='I';


    for (i = 0; i < G->numVertexes; i++)/* 初始化图 */
    {
        for ( j = 0; j < G->numVertexes; j++)
        {
            G->arc[i][j]=0;
        }
    }

    G->arc[0][1]=1;
    G->arc[0][5]=1;

    G->arc[1][2]=1;
    G->arc[1][8]=1;
    G->arc[1][6]=1;

    G->arc[2][3]=1;
    G->arc[2][8]=1;

    G->arc[3][4]=1;
    G->arc[3][7]=1;
    G->arc[3][6]=1;
    G->arc[3][8]=1;

    G->arc[4][5]=1;
    G->arc[4][7]=1;

    G->arc[5][6]=1;

    G->arc[6][7]=1;


    for(i = 0; i < G->numVertexes; i++)
    {
        for(j = i; j < G->numVertexes; j++)
        {
            G->arc[j][i] =G->arc[i][j];     /*完善邻接矩阵*/
        }
    }

}

Boolean visited[MAXVEX]; /* 访问标志的数组 */

/* 邻接矩阵的深度优先递归算法 */
void DFS (MGraph G, int i){
    int j;
    visited[i] = TRUE;                      /*标记i顶点被访问过*/
    printf("%c ", G.vexs[i]);        /*对顶点i的操作*/

    for (j = 0; j < G.numVertexes; j++){
        if (G.arc[i][j] == 1 && !visited[j])/*i所连接的顶点, 并且没有被访问过*/
            DFS(G, j);                    /*递归访问*/
    }
}

/* 邻接矩阵的深度遍历操作 */
void DFSTraverse (MGraph G){
    int i;
    for (i = 0; i < MAXVEX; i++)
    {
        visited[i] = FALSE;                 /*初始化所有的顶点状态都是未访问的状态*/
    }

    for (i = 0; i < G.numVertexes; i++)
    {
        if(!visited[i]) DFS(G, i);          /*如果该顶点未被访问则访问它*/
    }
}

/* 邻接矩阵的广度遍历算法 */
void BFSTraverse (MGraph G)
{
    int i, j;
    Queue Q;
    for (i = 0; i < MAXVEX; i++)    visited[i] = FALSE;
    InitQueue(&Q);                      /*初始化队列*/

    for (i = 0; i < G.numVertexes; i++)     /*遍历所有的顶点*/
    {
        if (!visited[i])                    /*如果该顶点没有被访问过*/
        {
            visited[i] = TRUE;
            printf("%c ", G.vexs[i]);/*操作顶点数据*/
            EnQueue(&Q, i);           /*i是顶点的在顶点表位置*/
            while (!QueueEmpty(Q)){
                DeQueue(&Q, &i);      /*出队列赋值给i*/

                for (j = 0; j < G.numVertexes; j++)
                {
                    if (G.arc[i][j] == 1 && !visited[j]){
                        visited[j] = TRUE;
                        printf("%c ", G.vexs[j]);
                        EnQueue(&Q, j);
                    }
                }
            }
        }
    }
}
int main()
{
    MGraph G;
    CreateMGraph(&G);
    printf("\nDFSTraverse:");
    DFSTraverse(G);
    CreateMGraph(&G);
    printf("\nBFSTraverse:");
    BFSTraverse(G);
    return 0;
}
