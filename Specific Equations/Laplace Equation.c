#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main(){

FILE *fp = fopen("Laplace.txt", "w");
if (fp == NULL)
{
    puts("Error opening the file");
    return -1;
}

int i, j, n=100, m=100, iter=0, diff=0; // L=100 chosen
double psi[n][m], eps, oldpsi[n][m];

// BC: Y(x,0)=0, Y(0,y)=1, Y(L,y)=1, Y(x,L)=-1
for(i=0; i<n; i++){
    for(j=0; j<m; j++){
        psi[i][j]=0;
    }
}

for(i=1; i<n-1; i++){
    psi[i][0]= 1;
    psi[i][n-1]=1;
}

for(j=1; j<n-1; j++){
    psi[0][j]= -1;

}

eps=0.0001;
for(i=1; i<n-1; i++){
    for(j=1; j<m-1; j++){
        psi[i][j]=i*j;
    }
}
while((diff>eps) || (iter<10)){
    for(i=1; i<n-1; i++){
        for(j=1; j<m-1; j++){
            oldpsi[i][j] = psi[i][j];
            psi[i][j]=(psi[i-1][j]+psi[i+1][j]+psi[i][j-1]+psi[i][j+1])/4;
            diff=diff+pow((oldpsi[i][j]-psi[i][j]), 2);
        }
    }
    diff=diff/(n*m);
    iter++;
}
for(i=0;i<n;i++) {
    for(j=0;j<m;j++) {
        fprintf(fp,"%lf ",psi[i][j]);
    }
    fprintf(fp,"\n");
}
return 0;
}
