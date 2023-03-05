#include <stdio.h>

#include <stdlib.h>

#include <math.h>
int main() {
    int str[9001], str1[9001];//应该定义为int类型,另外四位素数有9000,数组大小不合适
    int a, b, c, d, i, j = 0, k, m, l = 0, n = 0;
    for (m = 1000; m < 10000; m++) {

        k = sqrt(m);
        for (i = 2; i <= k; i++)//判断应该从2开始,直接对0求余,运行时会报错
            if (m % i == 0)
                break;
        if (i > k) {
            str[j] = m;
            j++;
        }
    }


    for (i = 0; i < j; i++) {

        a = str[i] / 1000;

        b = (str[i] % 1000) / 100;

        c = (str[i] % 100) / 10;

        d = str[i] % 10;

        str1[l] = d * 1000 + c * 100 + b * 10 + a;

        l++;

    }

    for (i = 0; i < l; i++) {

        k = sqrt(str1[i]); //应该是数组str1[i]

        for (j = 2; j <= k; j++)//for循环内层参数与外层相同,均为i,可用j,同样需从2开始

            if (str1[i] % j == 0)//是str1[i]而不是m

                break;

        if (j > k)

            printf("%d",str1[i]);//直接输出即可,不用添加多余的数组保存

//

        {

//

            str2[n] = str1[i];

//

            n++;


        }

    }


    for (i = 0; i < n; i++)


        printf("%d ", str2[i]);

    return 0;

}