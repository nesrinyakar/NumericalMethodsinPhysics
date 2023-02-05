#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
float A[10][10], x[10], Afactor, det=0, temp;
int i, ipivot, j, k, n, m, c;

printf("Enter number of variables:");
scanf("%d", &n);
m = n+1;
//Reading matrix
printf("Enter matrix of the system of equations\n");
for(i=0; i<n; i++){
    for(j=0; j<m; j++){
        printf("A[%d][%d]:", i,j);
        scanf("%f",&A[i][j]);
    }
}
// Checking uniqueness by calculating determinant
if (n==3){
    det = A[0][0] * ((A[1][1]*A[2][2]) - (A[2][1]*A[1][2])) - A[0][1] * (A[1][0]
   * A[2][2] - A[2][0] * A[1][2]) + A[0][2] * (A[1][0] * A[2][1] - A[2][0] * A[1][1]);
   if(det!=0){
    puts("Solution is unique");
   }
   else{
    puts("Solution is not unique!");
   }
}
//Gaussian elimination loop
//Checking for first element
for(i=0; i<n; i++){
    if(A[i][i]==0){
        c = 1;
        while((i+c)<n && A[i+c][i]==0)
            c++;
        if((i+c)==n){
            break;
        }
        for(j=i, k=0; k<m; k++){
            temp = A[j][k];
            A[j][k] = A[j+c][k];
            A[j+c][k] = temp;
        }
    }
}
//Creating diagonal matrix
for(ipivot=0; ipivot<n; ipivot++){
    for(j=0; j<m; j++){
        A[ipivot][j] = A[ipivot][j]/A[ipivot][ipivot];
    }
    for(i=0; i<n; i++){
        if(i != ipivot){
            Afactor = A[i][ipivot];
            for(j=0; j<m; j++){
                A[i][j] = A[i][j] - (Afactor * A[ipivot][j]);
            }
        }
    }
}

//Printing result
for(i=0; i<n; i++){
    printf("Solution of %d .variable is %f\n", i+1, A[i][n]);
}
//Printing diagonal matrix
for(i=0; i<n; i++){
    for(j=0; j<m; j++){
        printf("A[%d][%d]:%f\n", i, j, A[i][j]);
    }
}

return(0);
}

