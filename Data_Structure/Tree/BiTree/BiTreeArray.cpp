#include <cstdio>
#include <cstdlib>
#include <cmath>
/* ����˳��ṹ */

//����״̬
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 100                             /* �洢�ռ��ʼ������ */
#define MAX_TREE_SIZE 100                       /* ������������� */

typedef int Status;                             /* ״̬���� OK and ERROR */
typedef int TElemType;                          /* �����������ͣ��ݶ�Ϊint */
typedef TElemType SqBiTree[MAX_TREE_SIZE];      /* 0�ŵ�Ԫ�洢�ĸ��ڵ� */

typedef struct {
    int level, order;                           /* ���Ĳ㣬������ţ������������㣩 */
}Position;/* λ�� */

TElemType Nil = 0;

Status visit(TElemType c) {
    printf("%d ", c);
    return OK;
}

/* ����ն����� */
Status InitBiTree(SqBiTree T) {
    for (int i = 0; i < MAX_TREE_SIZE; i++) {
        T[i] = Nil; /* ��ֵ��Ϊ�� */
    }
    return OK;
}
/* ���ղ����˳�������������ֵ������˳��洢������ */
Status CreateBiTree(SqBiTree T) {
    int i = 0;
    while (i < 10) {
        T[i] = i + 1;  /* �˴����Ը���Ϊ��ֵ��ѭ������ */
        if (i != 0 && T[(i + 1) / 2 - 1] == Nil && T[i] != 0) {
            printf("������˫�׵ķǸ��ڵ�%d\n", T[i]);
            exit(ERROR);
        }
        i++;
    }

    //��i֮��Ľ�㸳ֵΪ��
    while (i < MAX_TREE_SIZE) {
        T[i] = Nil;
        i++;
    }

    return OK;
}

#define ClearBiTree InitBiTree      /* ˳��洢��������һ���� */

/* ��ʼ������������T���� */
/* �����������������������ڷ���TRUE�����ڷ���FALSE */
Status BiTreeEmpty(SqBiTree T) {
    //ֻ��Ҫ�жϸ��ڵ��Ƿ�Ϊ��
    if (T[0] == Nil) {
        return TRUE;
    }
    return FALSE;
}

/* ��ʼ������������T���� */
/* �������������T����� */
int BiTreeDepth(SqBiTree T) {
    int i, j = -1;
    for (i = MAX_TREE_SIZE - 1; i >= 0; i--) {
        if (T[i] != Nil) break;
    }

    i++;/* ����֮ǰ�Ǹýڵ���±꣬����֮��i��Ϊ����Ľڵ�λ�� */

    //����2��j�ݣ�ֱ����i��
    do
    {
        j++;
    } while (i >= pow(2, j));
 
    return j;
}

/* ��ʼ������������T���� */
/* �����������T��Ϊ�գ���e����T�ĸ���return OK;���򷵻�ERROR,e�޶��� */
Status Root(SqBiTree T, TElemType* e) {
    if (BiTreeEmpty(T)) {
        return ERROR;
    }
    else {
        *e = T[0];
        return OK;
    }
}

/* ��ʼ������������T����,e��T��ĳ������λ�� */
/* ��������� ���ش���λ��e(�㣬�������Position)�Ľ��ֵ*/
TElemType Value(SqBiTree T, Position e) {
    return T[int(pow(2, e.level - 1)) - 1 + e.order - 1];
}

/* ��ʼ������������T����,e��T��ĳ������λ�� */
/* ��������� ������λ��e(�㣬�������Position)�Ľ�㸳��ֵvalue*/
Status Assign(SqBiTree T, Position e, TElemType value) {
    int i = int(pow(2, e.level - 1)) - 1 + e.order - 1;//e���±�

    if (value != Nil && T[(i + 1) / 2 - 1] == Nil)    /* Ҷ�Ӳ�Ϊ�յ�˫��Ϊ�� */
    {
        return ERROR;
    }
    else if (value == Nil && T[i * 2 + 1] == Nil && T[i * 2 + 2] == Nil)   /* Ϊ����Ҷ��˫�׸���ֵ */
    {
        return ERROR;
    }

    T[i] = value;
    return OK;
}

/* ��ʼ������������T����,e��T��ĳ������λ�� */
/* ���������������λ��eΪ�Ǹ��ڵ�,�򷵻�����˫�׽��,���򷵻ؿ� */
TElemType Parent(SqBiTree T, TElemType e) {
    int i = 0;
    if (T[i] == Nil) {
        return Nil;
    }
    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e) {
            return T[(i + 1) / 2 - 1];/* ����˫�׽�� */
        }
    }
    return Nil;
}

/* ��ʼ������������T����,e��T��ĳ������λ�� */
/* �������������e������,��������,�򷵻ؿ� */
TElemType LeftChild(SqBiTree T, TElemType e) {
    int i = 0;
    if (T[i] == Nil) {   //����
        return Nil;
    }
    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e) {
            return T[i * 2 + 1];//����
        }
    }
    return Nil;//û�ҵ�
}


/* ��ʼ������������T����,e��T��ĳ������λ�� */
/* �������������e���Һ���,�����Һ���,�򷵻ؿ� */
TElemType RightChild(SqBiTree T, TElemType e) {
    int i = 0;
    if (T[i] == Nil) {   //����
        return Nil;
    }
    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e) {
            return T[i * 2 + 2];//�Һ���
        }
    }
    return Nil;//û�ҵ�
}

/* ��ʼ������������T����,e��T��ĳ������λ�� */
/* �������������e�����ֵ�,��e��T�����ӻ������ֵ�,�򷵻ؿ� */
TElemType LeftSibling(SqBiTree T, TElemType e) {
    //����û�����ֵ�
    int i = 0;
    if (T[i] == Nil) {   //����
        return Nil;
    }

    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e && (i & 2) == 0) {
            return T[i - 1];
        }
    }
    return Nil;
}

/* ��ʼ������������T����,e��T��ĳ������λ�� */
/* �������������e�����ֵ�,��e��T���Һ��ӻ������ֵ�,�򷵻ؿ� */
TElemType RightSibling(SqBiTree T, TElemType e) {
    //�Һ���û�����ֵ�
    int i = 0;
    if (T[i] == Nil) {   //����
        return Nil;
    }

    for (i = 1; i < MAX_TREE_SIZE; i++) {
        if (T[i] == e && (i & 2) == 1) {
            return T[i + 1];
        }
    }
    return Nil;
}

/* PreOrderTraverse()���� �������*/
void PreTraverse(SqBiTree T, int e) {
    visit(T[e]); //��ӡ���ڵ���
    if (T[e * 2 + 1] != Nil) {
        PreTraverse(T, e * 2 + 1);
    }
    if (T[e * 2 + 2] != Nil) {
        PreTraverse(T, e * 2 + 2);
    }
}


/* ��ʼ���������������� */
/* ����������������T */
Status PreOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        PreTraverse(T, 0);
    }
    printf("\nPreOrderTraverse Over!\n");
    return OK;
}

/* InOrderTraverse()���� �������*/
void InTraverse(SqBiTree T, int e) {

    if (T[e * 2 + 1] != Nil) {
        InTraverse(T, e * 2 + 1);
    }

    visit(T[e]); //��ӡ���ڵ��� 

    if (T[e * 2 + 2] != Nil) {
        InTraverse(T, e * 2 + 2);
    }
}


/* ��ʼ���������������� */
/* ����������������T */
Status InOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        InTraverse(T, 0);
    }
    printf("\nInOrderTraverse Over!\n");
    return OK;
}

/* PostOrderTraverse()���� �������*/
void PostTraverse(SqBiTree T, int e) {

    if (T[e * 2 + 1] != Nil) {
        PostTraverse(T, e * 2 + 1);
    }
    if (T[e * 2 + 2] != Nil) {
        PostTraverse(T, e * 2 + 2);
    }
    visit(T[e]); //��ӡ���ڵ��� 
}


/* ��ʼ���������������� */
/* ����������������T */
Status PostOrderTraverse(SqBiTree T) {
    if (!BiTreeEmpty(T)) {
        PostTraverse(T, 0);
    }
    printf("\nPostOrderTraverse Over!\n");
    return OK;
}

/* ������������� */
void LevelOrderTraverse(SqBiTree T) {
    int i = MAX_TREE_SIZE - 1;
    while (T[i] != Nil) {
        i--;/* �ҵ����һ����� */
    }
    for (int j = 0; j <= i; j++) {
        if (T[j] != Nil) {
            visit(T[j]);
        }
    }
    printf("\nLevelOrderTraverse Over!\n");
}

/* ���㡢������������������ */
void Print(SqBiTree T) {
    int i, j;
    Position p;
    TElemType e;

    for (i = 1; i <= BiTreeDepth(T); i++) {
        printf("��%d��", i);
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
    printf("������������,���շ�%d(1:�� 0:��) �������=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("�������ĸ�Ϊ��%d\n", e);
    else
        printf("���գ��޸�\n");
    printf("�������������:\n");
    LevelOrderTraverse(T);
    printf("ǰ�����������:\n");
    PreOrderTraverse(T);
    printf("�������������:\n");
    InOrderTraverse(T);
    printf("�������������:\n");
    PostOrderTraverse(T);
    printf("�޸Ľ��Ĳ��3�������2��");
    p.level = 3;
    p.order = 2;
    e = Value(T, p);
    printf("���޸Ľ���ԭֵΪ%d��������ֵ:50 ", e);
    e = 50;
    Assign(T, p, e);
    printf("ǰ�����������:\n");
    PreOrderTraverse(T);
    printf("���%d��˫��Ϊ%d,���Һ��ӷֱ�Ϊ", e, Parent(T, e));
    printf("%d,%d,�����ֱֵܷ�Ϊ", LeftChild(T, e), RightChild(T, e));
    printf("%d,%d\n", LeftSibling(T, e), RightSibling(T, e));
    ClearBiTree(T);
    printf("�����������,���շ�%d(1:�� 0:��) �������=%d\n", BiTreeEmpty(T), BiTreeDepth(T));
    i = Root(T, &e);
    if (i)
        printf("�������ĸ�Ϊ��%d\n", e);
    else
        printf("���գ��޸�\n");


    return 0;
}