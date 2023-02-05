#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 10

int main() {

FILE *fp = fopen("NLLeastSquare.txt", "w");
if (fp == NULL)
{
    puts("Error opening the file");
    return -1;
}

double x[N],y[N];
double u1, u2, aactual=3., bactual=1.5, afound, bfound, Afound, Bfound, yfound=0, XY=0, LX, XX=0, LY, X=0, Y=0;
double meanerror=0, sigmaerror=1, randomerror;
double PI=4*atan(1.0);
int i;
srand((unsigned int) time(NULL));
  for (i=1 ; i<=N ; i++){
    u1 = ((double) rand() / (double)(RAND_MAX));
    u2 = ((double) rand() / (double)(RAND_MAX));
    randomerror = meanerror + sigmaerror * sqrt(-2.0*log(u1)) * cos(2*PI*u2);
    x[i]=i;
    y[i]= aactual * pow(x[i] , bactual)  + randomerror;
    //printf("%f %f %f %f\n",x[i],y[i], aactual*pow(x[i],bactual),randomerror);
  }
//  Calculate the estimates of a and b from the values of x[i] and y[i]
for(i=1 ; i<=N; i++){
    LX = log(x[i]);
    LY = log(y[i]);
    XY = XY + LX*LY;
    X = X + LX;
    XX = XX + LX*LX;
    Y = Y + LY;
    printf("%lf %lf\n", LX, LY);
}
Afound = ((N*XY)-(X*Y))/((N*XX)- (X*X));
Bfound = (Y-(Afound*X))/N;
afound = exp(Afound);
bfound = Bfound;

for(i=1 ; i<=N; i++){
    yfound = afound* pow(x[i] , bfound);
    printf("%lf %lf %lf\n",x[i],y[i], yfound);
    fprintf(fp, "%lf %lf %lf\n", x[i], y[i], yfound);
}

printf("%lf %lf\n", afound, bfound);
printf("Deviation from a: %lf\n", aactual-afound);
printf("Deviation from b: %lf", bactual-bfound);

fclose(fp);
return 0;
}
