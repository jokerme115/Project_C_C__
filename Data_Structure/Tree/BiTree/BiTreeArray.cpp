#include <cstdio>
#include <cstdlib>
#include <cmath>
/* 树的顺序结构 */

//定义状态
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100                             /* 存储空间初始分配量 */
#define MAX_TREE_SIZE 100                       /* 二叉树最大结点数 */

typedef int Status;                             /* 状态代码 OK and ERROR */
typedef int TElemType;                          /* 树的数据类型，暂定为int */
typedef TElemType SqBiTree[MAX_TREE_SIZE];      /* 0号单元存储的根节点 */

typedef struct {
    int level, order;                           /* 结点的层，本层序号（满二叉树计算） */
}Position;/* 位置 */

TElemType Nil = 0;

Status visit(TElemType c) {
    printf("%d ", c);
    return OK;
}

/* 构造空二叉树 */
Status InitBiTree(SqBiTree T) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        T[i] = Nil; /* 初值都为空 */
    }
    return OK;
}
/* 按照层序的顺序输入二叉树的值，构造顺序存储二叉树 */
Status CreateBiTree(SqBiTree T) {
    int i = 0;
    while (i < 10) {
        T[i] = i + 1;  /* 此处可以更改为赋值，循环条件 */
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != 0) {
            printf("出现无双亲的非根节点%d\n", T[i]);
            exit(ERROR);
        }
        i++;
    }

    //将i之后的结点赋值为空
    while (i < MAX_TREE_SIZE) {
        T[i] = Nil;
        i++;
    }

    return OK;
}

#define ClearBiTree InitBiTree      /* 顺序存储中两函数一样的 */

/* 初始条件：二叉树T存在 */
/* 操作结果：如果二叉树不存在返回TRUE，存在返回FALSE */
Status BiTreeEmpty(SqBiTree T) {
    //只需要判断根节点是否为空
    if (T[0] == Nil) {
        return TRUE;
    }
    return FALSE;
}

/* 初始条件：二叉树T存在 */
/* 操作结果：返回T的深度 */
int BiTreeDepth(SqBiTree T) {
    int i, j = -1;
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--) {
        if (T[i] != Nil) break;
    }

    i++;/* 不加之前是该节点的下标，加完之后i就为最深的节点位置 */

    //计算2的j幂，直到比i大
    do
    {
        j++;
    } while (i >= pow(2, j));
 
    return j;
}

/* 初始条件：二叉树T存在 */
/* 操作结果：当T不为空，用e返回T的根，return OK;否则返回ERROR,e无定义 */
Status Root(SqBiTree T, TElemType* e) {
    if (BiTreeEmpty(T)) {
        return ERROR;
    }
    else {
        *e = T[0];
        return OK;
    }
}

/* 初始条件：二叉树T存在,e是T中某个结点的位置 */
/* 操作结果： 返回处于位置e(层，本层序号Position)的结点值*/
TElemType Value(SqBiTree T, Position e) {
    return T[int(pow(2, e.level - 1)) - 1 + e.order - 1];
}

/* 初始条件：二叉树T存在,e是T中某个结点的位置 */
/* 操作结果： 给处于位置e(层，本层序号Position)的结点赋新值value*/
Status Assign(SqBiTree T, Position e, TElemType value) {
    int i = int(pow(2, e.level - 1)) - 1 + e.order - 1;//e的下标

    if (value != Nil && T[(i + 1) / 2 - 1] == Nil)    /* 叶子不为空但双亲为空 */
    {
        return ERROR;
    }
    else if (value == Nil && T[i * 2 + 1] == Nil && T[i * 2 + 2] == Nil)   /* 为有子叶的双亲赋空值 */
    {
        return ERROR;
    }

    T[i] = value;
    return OK;
}

/* 初始条件：二叉树T存在,e是T中某个结点的位置 */
/* 操作结果：若处于位置e为非根节点,则返回他的双亲结点,否则返回空 */
TElemType Parent(SqBiTree T, TElemType e) {
    int i = 0;
    if (T[i] == Nil) {
        return Nil;
    }
    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e) {
            return T[(i + 1) / 2 - 1];/* 返回双亲结点 */
        }
    }
    return Nil;
}

/* 初始条件：二叉树T存在,e是T中某个结点的位置 */
/* 操作结果：返回e的左孩子,若无左孩子,则返回空 */
TElemType LeftChild(SqBiTree T, TElemType e) {
    int i = 0;
    if (T[i] == Nil) {   //空树
        return Nil;
    }
    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e) {
            return T[i * 2 + 1];//左孩子
        }
    }
    return Nil;//没找到
}


/* 初始条件：二叉树T存在,e是T中某个结点的位置 */
/* 操作结果：返回e的右孩子,若无右孩子,则返回空 */
TElemType RightChild(SqBiTree T, TElemType e) {
    int i = 0;
    if (T[i] == Nil) {   //空树
        return Nil;
    }
    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e) {
            return T[i * 2 + 2];//右孩子
        }
    }
    return Nil;//没找到
}

/* 初始条件：二叉树T存在,e是T中某个结点的位置 */
/* 操作结果：返回e的左兄弟,若e是T的左孩子或无左兄弟,则返回空 */
TElemType LeftSibling(SqBiTree T, TElemType e) {
    //左孩子没有左兄弟
    int i = 0;
    if (T[i] == Nil) {   //空树
        return Nil;
    }

    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e && (i & 2) == 0) {
            return T[i - 1];
        }
    }
    return Nil;
}

/* 初始条件：二叉树T存在,e是T中某个结点的位置 */
/* 操作结果：返回e的右兄弟,若e是T的右孩子或无右兄弟,则返回空 */
TElemType RightSibling(SqBiTree T, TElemType e) {
    //右孩子没有右兄弟
    int i = 0;
    if (T[i] == Nil) {   //空树
        return Nil;
    }

    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e && (i & 2) == 1) {
            return T[i + 1];
        }
    }
    return Nil;
}

/* PreOrderTraverse()调用 先序遍历*/
void PreTraverse(SqBiTree T, int e) {
    visit(T[e]); //打印根节点结点
    if (T[e * 2 + 1] != Nil) {
        PreTraverse(T, e * 2 + 1);
    }
    if (T[e * 2 + 2] != Nil) {
        PreTraverse(T, e * 2 + 2);
    }
}


/* 初始条件：二叉树存在 */
/* 操作结果：先序遍历T */
Status PreOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        PreTraverse(T, 0);
    }
    printf("\nPreOrderTraverse Over!\n");
    return OK;
}

/* InOrderTraverse()调用 中序遍历*/
void InTraverse(SqBiTree T, int e) {

    if (T[e * 2 + 1] != Nil) {
        InTraverse(T, e * 2 + 1);
    }

    visit(T[e]); //打印根节点结点 

    if (T[e * 2 + 2] != Nil) {
        InTraverse(T, e * 2 + 2);
    }
}


/* 初始条件：二叉树存在 */
/* 操作结果：中序遍历T */
Status InOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        InTraverse(T, 0);
    }
    printf("\nInOrderTraverse Over!\n");
    return OK;
}

/* PostOrderTraverse()调用 后序遍历*/
void PostTraverse(SqBiTree T, int e) {

    if (T[e * 2 + 1] != Nil) {
        PostTraverse(T, e * 2 + 1);
    }
    if (T[e * 2 + 2] != Nil) {
        PostTraverse(T, e * 2 + 2);
    }
    visit(T[e]); //打印根节点结点 
}


/* 初始条件：二叉树存在 */
/* 操作结果：后序遍历T */
Status PostOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        PostTraverse(T, 0);
    }
    printf("\nPostOrderTraverse Over!\n");
    return OK;
}

/* 层序遍历二叉树 */
void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE - 1;
    while (T[i] != Nil) {
        i--;/* 找到最后一个结点 */
    }
    for (int j = 0; j <= i; j++) {
        if (T[j] != Nil) {
            visit(T[j]);
        }
    }
    printf("\nLevelOrderTraverse Over!\n");
}

/* 按层、按本层序号输出二叉树 */
void Print(SqBiTree T) {
    int i, j;
    Position p;
    TElemType e;

    for (i = 1; i <= BiTreeDepth(T); i++) {
        printf("第%d层", i);
        for (j = 1; j <= pow(2, j - 1); j++) {
            p.level = i;
            p.order = j;
            e = Value(T, p);
            if (e != Nil) printf("%d:%d", i, e);
        }
    }
    printf("\nPrint Over!\n");
}
int main()
{
    Status i;
    Position p;
    TElemType e;
    SqBiTree T;
    InitBiTree(T);
    CreateBiTree(T);
    printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("二叉树的根为：%d\n", e);
    else
        printf("树空，无根\n");
    printf("层序遍历二叉树:\n");
    LevelOrderTraverse(T);
    printf("前序遍历二叉树:\n");
    PreOrderTraverse(T);
    printf("中序遍历二叉树:\n");
    InOrderTraverse(T);
    printf("后序遍历二叉树:\n");
    PostOrderTraverse(T);
    printf("修改结点的层号3本层序号2。");
    p.level = 3;
    p.order = 2;
    e = Value(T, p);
    printf("待修改结点的原值为%d请输入新值:50 ", e);
    e = 50;
    Assign(T, p, e);
    printf("前序遍历二叉树:\n");
    PreOrderTraverse(T);
    printf("结点%d的双亲为%d,左右孩子分别为", e, Parent(T, e));
    printf("%d,%d,左右兄弟分别为", LeftChild(T, e), RightChild(T, e));
    printf("%d,%d\n", LeftSibling(T, e), RightSibling(T, e));
    ClearBiTree(T);
    printf("清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("二叉树的根为：%d\n", e);
    else
        printf("树空，无根\n");


    return 0;
}