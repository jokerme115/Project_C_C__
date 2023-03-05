//
// Created by 15351 on 2023/2/24.
//
#include <stdio.h>
typedef struct{
    float x;
    float y;
}complex;

complex Complex_Create(float e, float f)
{
    complex C;
    C.x = e;
    C.y = f;
    return C;
}

void outputc(complex C){
    printf("����:%f+i*%f\n",C.x,C.y);
}

//�͡����
complex Add(complex a,complex b){
    complex sum;
    sum.x=a.x+b.x;
    sum.y=a.y+b.y;
    return sum;
}
complex Sub(complex a,complex b){
    complex difference;
    difference.x=a.x-b.x;
    difference.y=a.y-b.y;
    return difference;
}
complex Mul(complex a,complex b){
    complex multiply;
    multiply.x=a.x*b.x+a.y*b.y;
    multiply.y=a.x*b.y+a.y*b.x;
    return multiply;
}

int main(){
    complex a,b;
    float c1,c2,c3,c4;
    printf("�����һ��������ʵ��x1���鲿y1��");
    scanf("%f %f",&c1,&c2);
    a=Complex_Create(c1,c2);
    printf("����ڶ���������ʵ��x2���鲿y2��");
    scanf("%f %f",&c3,&c4);
    b=Complex_Create(c3,c4);
    outputc(a);
    outputc(b);
    printf("����1 = %f + %fi\n", a.x,a.y);
    printf("����2 = %f + %fi\n", b.x,b.y);

    printf("��������֮��:\n");
    outputc(Add(a,b));
    printf("��������֮��:\n");
    outputc(Sub(a,b));
    printf("��������֮��:\n");
    outputc(Mul(a,b));
}