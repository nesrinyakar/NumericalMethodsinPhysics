#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
double T[101][101], TF[101][101], dt=0.001, dx=0.25, c=1;  // TF accounts for T forward, dx=dy assumed
int n=100, i, j, t;

FILE *fp = fopen("HeatEqn.txt", "w");
if (fp == NULL)
{
    puts("Error opening the file");
    return -1;
}

//Initial condition T=10 at t=0
for(i=1; i<n; i++){
    for(j=1; j<n; j++){
        T[i][j] = 10;
    }
}

for(t=1; t<=10; t++){ // 10 time steps due to not opening txt file for t>10
    for(i=1; i<n-1; i++){
        for(j=1; j<n-1; j++){
            TF[i][j]=T[i][j]+(dt/dx*dx)*c*(T[i-1][j]-4*T[i][j]+T[i+1][j]+T[i][j-1]+T[i][j+1]);
        }
    }
    //BCs
    for(i=0; i<n; i++){
        TF[i][0]=5;
        TF[i][101]=5;
    }
    for(j=0; j<n; j++){
        TF[0][j]=5;
        TF[101][j]=5;
    }

    for(i=0; i<=n; i++){
        for(j=0; j<=n; j++){
            T[i][j]=TF[i][j];
            fprintf(fp, "%f ", T[i][j]);
        }
    }
    t=t;
}

return 0;
}
