// @title: lab1.c 
// @author: Chen Ang(PB17061250)
// @description: for Numerical Analysis(B) lab1
//

#include<stdio.h>
#include<math.h>
#define MAX_COUNT 30000

void calc(double x) {
    double y = 0;
    int i = 0;
    for (i = 1; i < MAX_COUNT; i++) {
        y += 1 / (i * (i + 1) * (i + x));
    }
    y = 1 + y * (1 - x);
    printf("x = %lf, y = %.15e\n", x, y);
}

int main() {
    double x;
    x = 0.0;
    calc(x);
    x = 0.5;
    calc(x);
    x = 1.0;
    calc(x);
    x = sqrt(2);
    calc(x);
    x = 10.0;
    calc(x);
    x = 100.0;
    calc(x);
    x = 300.0;
    calc(x);

    printf("Input other \'x\'s to calculate \'y\':\n");
    while(1) {
        scanf("%lf", &x);
        calc(x);
    }
    return 0;
}

