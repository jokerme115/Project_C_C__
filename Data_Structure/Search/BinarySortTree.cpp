//
// Created by 15351 on 2022/10/18.
//
#include <stdio.h>
#include <stdlib.h>
//���峣��
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXVEX 100              /*�洢�ռ��ʼ������*/

typedef int Status;             /* ״̬���� OK and ERROR */

/*�������Ķ�������ṹ����*/
typedef struct BiTNode          /*���ṹ*/
{
    int data;                   /*�������*/
    struct BiTNode * lChild, *rChild;   /*���Һ���ָ��*/
}BiTNode, *BiTree;

/* ���� */
/* �ݹ���Ҷ���������T���Ƿ����key, */
/* ָ��fָ��T��˫�ף����ʼ����ֵΪNULL */
/* �����ҳɹ�����ָ��pָ�������Ԫ�ؽ�㣬������TRUE */
/* ����ָ��pָ�����·���Ϸ��ʵ����һ����㲢����FALSE */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p){
    if (!T)                     /*TΪ��*/
    {
        *p = f;                 /*ָ����һ�����*/
        return ERROR;
    }
    else if (key == T->data)
    {
        *p = T;
        return TRUE;
    }
    else if (key < T->data)
    {
//        f = T;����Ҫ��һ��,ֱ�Ӹ�ֵT����
        return SearchBST(T->lChild, key, T, p);//���������ݹ�Ѱ��
    }
    else
    {
        return SearchBST(T->rChild, key, T, p);//���������ݹ�Ѱ��
    }
}

/* ���� */
/*  ������������T�в����ڹؼ��ֵ���key������Ԫ��ʱ�� */
/*  ����key������TRUE�����򷵻�FALSE */
Status InsertBST(BiTree *T, int key)
{
    BiTree p, s;            //p������ҹ����������ʵ�һ�����
    if (!SearchBST(*T, key, NULL, &p))
    {
        s = (BiTree) malloc(sizeof (BiTNode));
        s->data = key;
        s->lChild = s->rChild = NULL;   /*��ʼ�����Һ���*/

        if (!p)                         /*����ǿ���*/
        {
            *T = s;
        } else if (key < p->data)
        {
            p->lChild = s;              /*����������*/
        }else{
            p->rChild = s;              /*����������*/
        }
        return TRUE;
    }else{
        return FALSE;                   /*�Ѿ����ڸý��*/
    }
}

/* �Ӷ�����������ɾ�����p�����ؽ���������������� */
Status Delete(BiTree *p)
{
    BiTree q, s;                        /*q����˫��,s����ǰ��*/
    if (!(*p)->rChild)                  /*p������Ϊ��,ֻ��Ҫ��������������*/
    {
        q = *p;
        *p = (*p)->lChild;
        free(q);
    }
    else if (!(*p)->lChild)             /*p������Ϊ��,ֻ��Ҫ��������������*/
    {
        q = *p;
        *p = (*p)->rChild;
        free(q);
    }else                               /*������������Ϊ��,�����ַ�ʽ��1.�������������Ĵ���  2.������������С�Ĵ���, �˴���1*/
    {
        q = *p;
        s = (*p)->lChild;               /*�˴��÷���һ����ת��*/
        while (s->rChild)               /*ѭ�����������½ǵ�����, q����˫��, sָ�����һ�����*/
        {
            q = s;
            s = s->rChild;
        }
        (*p)->data = s->data;           /*�ص�:�޸�ɾ������value,Ϊ���������Ľ��*/
        if(q != *p){
            q->rChild = s->lChild;      /*����q������*/
        }else{
            q->lChild = s->lChild;      /*����q������*/
        }
        free(s);
    }
    return TRUE;
}

/* ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ��, */
/* ������TRUE�����򷵻�FALSE�� */
Status DeleteBST(BiTree *T, int key){
    if (!T){
        return FALSE;                   /*����*/
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
    InOrderTraverse(T->lChild);	/*��ӡ������*/
    printf("%d ", T->data);
    InOrderTraverse(T->rChild);	/*��ӡ������*/
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