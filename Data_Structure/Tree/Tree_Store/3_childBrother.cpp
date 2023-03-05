#include <stdio.h>
/*�����ֵܱ�ʾ�� ������һ���������Ľ��ĵ�һ������������ھ���Ψһ�ģ��������ֵ��������Ҳ��Ψһ�ġ���ˣ�������������ָ�룬�ֱ�ָ��ý��ĵ�һ�����Ӻʹ˽������ֵܡ� */

#define MAX_TREE_SIZE 100                   /* ��������󳤶� */
typedef int TElemType;                      /* ���������������� */

typedef struct CSNode {                      /* ���Ľ�� */
    TElemType data;
    struct CSNode* firstchild, * rightsib;   /* �����������ָ�룬һ��ָ���һ�����ӣ�һ��ָ�����ֵ� */
}CSNode, * CSTree;