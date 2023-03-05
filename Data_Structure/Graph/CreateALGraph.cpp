//
// Created by 15351 on 2022/10/17.
//
#include <stdio.h>
//定义常量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100              /*顶点数*/

typedef int Status;             /* 状态代码 OK and ERROR */
typedef char VertexType;        /*顶点类型*/
typedef int EdgeType;           /*边上权值类型*/

/*边表结点*/
typedef struct EdgeNode{
    int adjvex;                 /*邻接点域， 存储该顶点对应的下标*/
    EdgeType info;              /*用来存储权值，对于非网图可以不需要*/
    struct EdgeNode *next;      /*链域，指向下一个邻接点*/
}EdgeNode;

typedef struct VertexNode       /*顶点表结点*/
{
    VertexType data;            /*顶点域，存储顶点信息*/
    EdgeNode *firstEdge;        /*边表头指针*/
}VertexNode, AdjList[MAXVEX];
