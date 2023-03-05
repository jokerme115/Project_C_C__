//
// Created by 15351 on 2022/10/18.
//
#include <stdio.h>
#include <stdlib.h>
//定义常量
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100              /*存储空间初始分配量*/

typedef int Status;             /* 状态代码 OK and ERROR */

/*二叉树的二叉链表结构定义*/
typedef struct BiTNode          /*结点结构*/
{
    int data;                   /*结点数据*/
    struct BiTNode * lChild, *rChild;   /*左右孩子指针*/
}BiTNode, *BiTree;

/* 查找 */
/* 递归查找二叉排序树T中是否存在key, */
/* 指针f指向T的双亲，其初始调用值为NULL */
/* 若查找成功，则指针p指向该数据元素结点，并返回TRUE */
/* 否则指针p指向查找路径上访问的最后一个结点并返回FALSE */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p){
    if (!T)                     /*T为空*/
    {
        *p = f;                 /*指向上一个结点*/
        return ERROR;
    }
    else if (key == T->data)
    {
        *p = T;
        return TRUE;
    }
    else if (key < T->data)
    {
//        f = T;不需要这一句,直接赋值T就行
        return SearchBST(T->lChild, key, T, p);//在左子树递归寻找
    }
    else
    {
        return SearchBST(T->rChild, key, T, p);//在右子树递归寻找
    }
}

/* 插入 */
/*  当二叉排序树T中不存在关键字等于key的数据元素时， */
/*  插入key并返回TRUE，否则返回FALSE */
Status InsertBST(BiTree *T, int key)
{
    BiTree p, s;            //p保存查找过程中最后访问的一个结点
    if (!SearchBST(*T, key, NULL, &p))
    {
        s = (BiTree) malloc(sizeof (BiTNode));
        s->data = key;
        s->lChild = s->rChild = NULL;   /*初始化左右孩子*/

        if (!p)                         /*如果是空树*/
        {
            *T = s;
        } else if (key < p->data)
        {
            p->lChild = s;              /*插入左子树*/
        }else{
            p->rChild = s;              /*插入右子树*/
        }
        return TRUE;
    }else{
        return FALSE;                   /*已经存在该结点*/
    }
}

/* 从二叉排序树中删除结点p，并重接它的左或右子树。 */
Status Delete(BiTree *p)
{
    BiTree q, s;                        /*q保存双亲,s保存前继*/
    if (!(*p)->rChild)                  /*p的右树为空,只需要重新连接左子树*/
    {
        q = *p;
        *p = (*p)->lChild;
        free(q);
    }
    else if (!(*p)->lChild)             /*p的左树为空,只需要重新连接右子树*/
    {
        q = *p;
        *p = (*p)->rChild;
        free(q);
    }else                               /*左右子树都不为空,有两种方式，1.用左子树中最大的代替  2.用右子树中最小的代替, 此处用1*/
    {
        q = *p;
        s = (*p)->lChild;               /*此处用方案一所以转左*/
        while (s->rChild)               /*循环查找最右下角的数字, q保存双亲, s指向最后一个结点*/
        {
            q = s;
            s = s->rChild;
        }
        (*p)->data = s->data;           /*重点:修改删掉结点的value,为左子树最大的结点*/
        if(q != *p){
            q->rChild = s->lChild;      /*重连q右子树*/
        }else{
            q->lChild = s->lChild;      /*重连q左子树*/
        }
        free(s);
    }
    return TRUE;
}

/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点, */
/* 并返回TRUE；否则返回FALSE。 */
Status DeleteBST(BiTree *T, int key){
    if (!T){
        return FALSE;                   /*空树*/
    } else{
        if (key == (*T)->data)
            return Delete(T);
        else if(key < (*T)->data)
            return DeleteBST(&(*T)->lChild, key);
        else
            return DeleteBST(&(*T)->rChild, key);
    }
}
void InOrderTraverse(BiTree T) {
    if (!T) return;
    InOrderTraverse(T->lChild);	/*打印左子树*/
    printf("%d ", T->data);
    InOrderTraverse(T->rChild);	/*打印右子树*/
}
int main(){
    int i;
    int a[10]={62,88,58,47,35,73,51,99,37,93};
    BiTree T=NULL;

    for(i=0;i<10;i++)
    {
        InsertBST(&T, a[i]);
    }
    printf("---Tree---\n");
    InOrderTraverse(T);
    DeleteBST(&T,93);
    printf("---Delete93---\n");
    InOrderTraverse(T);
    DeleteBST(&T,47);
    printf("---Delete47---\n");
    InOrderTraverse(T);
    return 0;

}