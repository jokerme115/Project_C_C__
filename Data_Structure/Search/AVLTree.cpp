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
    int bf;                     /*结点的*/
    struct BiTNode * lChild, *rChild;   /*左右孩子指针*/
}BiTNode, *BiTree;

/* 对以p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转处理之前的左子树的根结点 */
void R_Rotate(BiTree *P)
{
    BiTree T;
    T = (*P)->lChild;
    (*P)->lChild = T->rChild;   /*如果该结点的左子树有右子树, 就把右子树给P的左子树*/
    T->rChild = *P;
    *P = T;
}

/* 对以p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，即旋转处理之前的右子树的根结点 */
void L_Rotate(BiTree *P)
{
    BiTree T;
    T = (*P)->rChild;
    (*P)->rChild = T->lChild;   /*如果该结点的右子树有左子树, 就把左子树给P的右子树*/
    T->lChild = *P;
    *P = T;
}

#define LH (+1)           /*左子树高于右子树*/
#define EH  0           /*左子树等于右子树*/
#define RH (-1)           /*左子树小于右子树*/

/*  对以指针T所指结点为根的二叉树作左平衡旋转处理 */
/*  本算法结束时，指针T指向新的根结点 */
void LeftBalance(BiTree *T){
    BiTree L, Lr;
    L = (*T)->lChild;                   /*L指向T的左子树*/
    switch (L->bf) {                    //检查T左子树的平衡度,并且做出一些处理
        case LH:                        //左高, 插入到了左子树，需要右旋调整
            (*T)->bf = L->bf = EH;      /*调整T和L的平衡因子*/
            R_Rotate(T);
            break;
        case RH:                        //右高, 插入到了右子树，需要双旋调整,先左旋,再右旋
            Lr = L->rChild;
            switch (Lr->bf)             /*调整bf的值*/
            {
                case LH:
                    (*T)->bf = RH;
                    L->bf = EH;
                    break;
                case EH:
                    (*T)->bf = Lr->bf = EH;
                    break;
                case RH:
                    (*T)->bf = EH;
                    L->bf = LH;
                    break;
            }
            Lr->bf = EH;
            L_Rotate(&(*T)->lChild);        /*对左子树左旋转*/
            R_Rotate(T);                    /*对T右旋转*/
            break;
    }
}

/*  对以指针T所指结点为根的二叉树作右平衡旋转处理， */
/*  本算法结束时，指针T指向新的根结点 */
void RightBalance(BiTree *T)
{
    BiTree R,Rl;
    R=(*T)->rChild; /*  R指向T的右子树根结点 */
    switch(R->bf)
    { /*  检查T的右子树的平衡度，并作相应平衡处理 */
        case RH: /*  新结点插入在T的右孩子的右子树上，要作单左旋处理 */
            (*T)->bf=R->bf=EH;
            L_Rotate(T);
            break;
        case LH: /*  新结点插入在T的右孩子的左子树上，要作双旋处理 */
            Rl=R->lChild; 			/*  Rl指向T的右孩子的左子树根 */
            switch(Rl->bf)
            { 						/*  修改T及其右孩子的平衡因子 */
                case RH: (*T)->bf=LH;
                    R->bf=EH;
                    break;
                case EH: (*T)->bf=R->bf=EH;
                    break;
                case LH: (*T)->bf=EH;
                    R->bf=RH;
                    break;
            }
            Rl->bf=EH;
            R_Rotate(&(*T)->rChild); /*  对T的右子树作右旋平衡处理 */
            L_Rotate(T); /*  对T作左旋平衡处理 */
    }
}

/*  若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个,数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树,
 *  失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。 */
Status InsertAVL(BiTree *T, int e, Status *taller)
{
    if (!*T){
        /*1.空树  2.该结点为空 并且让taller为TRUE*/
        //初始化T结点
        *T = (BiTree) malloc(sizeof (BiTNode));
        (*T)->data = e;
        (*T)->lChild = (*T)->rChild = NULL;
        (*T)->bf = EH;
        *taller = TRUE;
    } else
    {
        if (e == (*T)->data)    /*存在该结点*/
        {
            *taller = false;
            return FALSE;
        }else if(e < (*T)->data)/*在左子树中搜索*/
        {
            if (!InsertAVL(&(*T)->lChild, e, taller)) return FALSE; /*如果存在*/
            if (*taller)    /*如果插入成功*/
            {
                switch ((*T)->bf)   /*更新(*T)->br 和 taller*/
                {
                    case LH:        /*左子树高于右子树,插入后需要做平衡处理*/
                        LeftBalance(T); *taller = FALSE; break;
                    case EH:        /*左子树等于右子树,插入后左子树高于右子树*/
                        (*T)->bf = LH; *taller = TRUE; break;
                    case RH:        /*右子树高于左子树,插入后平衡*/
                        (*T)->bf = EH; *taller = FALSE; break;
                }
            }
        }else{
            if (!InsertAVL(&(*T)->rChild, e, taller)) return FALSE; /*如果存在*/
            if (*taller)    /*如果插入成功*/
            {
                switch ((*T)->bf)   /*更新(*T)->br 和 taller*/
                {
                    case LH:        /*右子树高于左子树,插入后平衡*/
                        (*T)->bf = EH; *taller = FALSE; break;
                    case EH:        /*左子树等于右子树,插入后右子树高于左子树*/
                        (*T)->bf = LH; *taller = TRUE; break;
                    case RH:        /*右子树高于左子树,插入后需要做平衡处理*/
                        RightBalance(T); *taller = FALSE; break;
                }
            }
        }
    }
    return TRUE;
}
void InOrderTraverse(BiTree T) {
    if (!T) return;
    InOrderTraverse(T->lChild);	/*打印左子树*/
    printf("%d ", T->data);
    InOrderTraverse(T->rChild);	/*打印右子树*/
}

int main()
{
    int i;
    int a[10]={3,2,1,4,5,6,7,10,9,8};
    BiTree T=NULL;
    Status taller;
    for(i=0;i<10;i++)
    {
        InsertAVL(&T,a[i],&taller);
    }
    InOrderTraverse(T);
    return 0;
}

