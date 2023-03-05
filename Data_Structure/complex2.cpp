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
    printf("复数:%f+i*%f\n",C.x,C.y);
}

//和、差、积
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
    printf("输入第一个复数的实部x1和虚部y1：");
    scanf("%f %f",&c1,&c2);
    a=Complex_Create(c1,c2);
    printf("输入第二个复数的实部x2和虚部y2：");
    scanf("%f %f",&c3,&c4);
    b=Complex_Create(c3,c4);
    outputc(a);
    outputc(b);
    printf("复数1 = %f + %fi\n", a.x,a.y);
    printf("复数2 = %f + %fi\n", b.x,b.y);

    printf("两个复数之和:\n");
    outputc(Add(a,b));
    printf("两个复数之差:\n");
    outputc(Sub(a,b));
    printf("两个复数之积:\n");
    outputc(Mul(a,b));
}