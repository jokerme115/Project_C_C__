//
// Created by HeTao on 2023/3/1.
//
/**/
#include <stdio.h>
#include <stdlib.h>
/*
struct
{
    char name[20]; //定义一个学生的名字字符数组
    int age; //定义一个学生的年龄
    float score; //定义一个学生的分数
}student;

int main(){
    scanf("%s", student.name);
    scanf("%d", &student.age);
    scanf("%f", &student.score);

    printf("%s\n", student.name);
    printf("%d\n", student.age);
    printf("%f\n", student.score);
}*/

/*
struct stu //表示一个结构体的类型，而不是变量
{
    char name[20];  //定义一个学生的名字字符数组
    int age;        //定义一个学生的年龄
    float score;    //定义一个学生的分数
};
int main(){
    struct stu student;
    scanf("%s", student.name);
    scanf("%d", &student.age);
    scanf("%f", &student.score);

    printf("%s\n", student.name);
    printf("%d\n", student.age);
    printf("%f\n", student.score);
}*/
 /*typedef struct { //表示一个结构体的类型，而不是变量
    char name[20];  //定义一个学生的名字字符数组
    int age;        //定义一个学生的年龄
    float score;    //定义一个学生的分数
}Student;
int main(){
    Student student;
    Student student1;

    scanf("%s", student.name);
    scanf("%d", &student1.age);
    scanf("%f", &student.score);

    printf("%s\n", student.name);
    printf("%d\n", student1.age);
    printf("%f\n", student.score);
}*/
/*
 typedef int INT;       //给int取一个别名叫INT
 typedef double DOUBLE; //给double取一个别名叫DOUBLE
 typedef char CHAR;     //给char取一个别名叫CHAR

 int main(){
     INT a = 1;
     DOUBLE b = 1.1;
     CHAR c = 'c';

     printf("%d\n", a);
     printf("%lf\n", b);
     printf("%c\n", c);
 }*/
/*
int main(){
    int a = 0;
    int * b = NULL;

    printf("%d\n", a);
    printf("%X\n", &a); // 输出a的内存地址16进制
    printf("%d\n", b);
    printf("----------------------\n");

    b = &a;
    printf("%d\n", a);
    printf("%X\n", &a); // 输出a的内存地址16进制
    printf("%d\n", *b);
    printf("%X\n", b); // 输出b的内存地址16进制
    printf("----------------------\n");

    *b = 1;

    printf("%d\n", a);
    printf("%X\n", &a); // 输出a的内存地址16进制
    printf("%d\n", *b);
    printf("%X\n", b); // 输出b的内存地址16进制
    printf("----------------------\n");

    a = 2;

    printf("%d\n", a);
    printf("%X\n", &a); // 输出a的内存地址16进制
    printf("%d\n", *b);
    printf("%X\n", b); // 输出b的内存地址16进制
    printf("----------------------\n");

}*/
/*
void showAddress(int& a, int& b){
    printf("%X\n", &a); // 输出a的内存地址16进制
    printf("%X\n", &b); // 输出b的内存地址16进制
}
int main(){
    int a = 1;
    int b = 0;

    printf("%X\n", &a); // 输出a的内存地址16进制
    printf("%X\n", &b); // 输出b的内存地址16进制

    printf("----------------------\n");

    showAddress(a, b);
}*/

/*
int main(){
    int* p=(int*)malloc(10*sizeof(int));

    if (p != NULL){
        *p = 1;			//p相当于是开辟了10块连续内存的首地址
        *(p+1) = 2;		//在第二块区域赋值

        printf("%d\n", *p);		//第一种取值方式 *+指针（地址）
        printf("%d\n", p[1]);	//第二种数组方式 p[第几个]
    }
}*/

/*
int main(){
    int a = 1;
    int b = 2;
    int *p[2];
    p[0] = &a;
    p[1] = &b;

    printf("%p\n", p[0]); //a的地址
    printf("%p\n", &a); //a的地址
    printf("%p\n", p[1]); //b的地址
    printf("%p\n", &b); //b的地址
    printf("%d\n", *p[0]); //p[0]表示a的地址，则*p[0]表示a的值
    printf("%d\n", *p[1]); //p[1]表示a的地址，则*p[1]表示a的值

}*/
/*
typedef struct { //表示一个结构体的类型，而不是变量
   char name[20];  //定义一个学生的名字字符数组
   int age;        //定义一个学生的年龄
   float score;    //定义一个学生的分数
}Student;
int main(){
    Student student[10];        // 10个学生的数组

    scanf("%s", student[0].name);       //第一种使用属性的方式, 结构体.属性
    scanf("%d", &student->age);         //第二种使用属性的方式, 结构体地址->属性
    scanf("%f", &(student+1)->score);   //student+1 = student[1]

    printf("%s\n", student[0].name);
    printf("%d\n", student->age);
    printf("%f\n", (student+1)->score);
}*/
typedef struct { //表示一个结构体的类型，而不是变量
    char name[20];  //定义一个学生的名字字符数组
    int age;        //定义一个学生的年龄
    float score;    //定义一个学生的分数
}Student;
int main(){
    Student * student;
    Student student1 = {"aaa", 11, 2.6};

    student = &student1;

    printf("%s\n", student->name);
    printf("%d\n", student->age);
    printf("%f\n", student->score);
}