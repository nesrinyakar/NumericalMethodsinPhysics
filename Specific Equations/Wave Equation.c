#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(){
    FILE *fp = fopen("WaveEqn.txt", "w");
if (fp == NULL)
{
    puts("Error opening the file");
    return -1;
}
double f(double x);
double y[10], v[10];
double dx, dt, u, us;
int i, j, L=10, n=10; // L & n chosen to be 10

// initial & boundary conditions
y[0]=0;
y[L]=0;
v[0]=0;

dx=L/n;
u=0.5; // speed of the wave chosen as 0.5
us = u*u;
dt=dx/(3*u);
for(j=1; j<n; j++){
    for(i=1; i<(n-1); i++){
        v[i]=v[i]+dt*(us*((f(i+1)-2*f(i)-f(i-1))/(dx*dx)));
    }
    for(i=1; i<(n-1); i++){
        y[i]=y[i]+v[i]*dt;
    }
    for(i=0; i<n; i++){
    printf("y[%d]=%f\n", i,y[i]);
    fprintf(fp,"%f\n",y[i]);
    }
    dt=j*dt;
}

return 0;
}
double f(double x){
    double pi=3.14159, L=10;
    return sin(2*pi*x/L);
}
