
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10

int main() {

FILE *fp = fopen("LRegression.txt", "w");
if (fp == NULL)
{
    puts("Error opening the file");
    return -1;
}

double x[N],y[N];
double aactual=3., bactual=5, afound, bfound, yfound=0, XY=0, X=0, XX=0, Y=0;
double randomerror;
int i;
srand((unsigned int) time(NULL));
for (i=0 ; i<N ; i++){
    randomerror= 10* (  ((double) rand() / (double)(RAND_MAX)) -0.5);
    x[i]=i;
    y[i]= aactual * x[i] + bactual + randomerror;
    //printf("%f %f %f\n",x[i],y[i], aactual*x[i]+bactual);
  }
//  now calculate the estimates of a and b from the values of x[i] and y[i]
for(i=0 ; i<N; i++){
    XY = XY + x[i]*y[i];
    X = X + x[i];
    XX = XX + x[i]*x[i];
    Y = Y + y[i];
}
afound = ((N*XY)-(X*Y))/((N*XX)- X);
bfound = (Y-(afound*X))/N;

for(i=0 ; i<N; i++){
    yfound = afound*x[i] + bfound;
    printf("%f %f %f\n",x[i],y[i], yfound);
    fprintf(fp, "%lf %lf %lf\n", x[i], y[i], yfound);
}

printf("%lf %lf\n", afound, bfound);
printf("Deviation from a: %lf\n", aactual-afound);
printf("Deviation from b: %lf", bactual-bfound);

fclose(fp);
return 0;
}
