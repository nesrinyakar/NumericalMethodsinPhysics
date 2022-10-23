#include <stdio.h>
#include <math.h>
int main()
{

double f(double x);
double a, b, eps, bahalf;
int i, p=0;

//x^2+x-2 is the chosen function
//Roots are -2 and 1

for (i=0; i<2; i++){
    printf("Enter starting point of the interval\n");
    scanf("%lf", &a);
    printf("Enter ending point of the interval\n");
    scanf("%lf", &b);
    printf("Enter precision\n");
    scanf("%lf", &eps);

    if(f(a)*f(b) >= 0){
        printf("Choose a different interval");
        return 1;
    }

    while( b-a > eps){
        bahalf = (a+b)/2;
        if(f(bahalf)*f(a) < 0){
            b = bahalf;
        }
        else if(f(bahalf)==0){
            p++;
            break; //to leave from while loop
        }
        else{
            a = bahalf;
        }
    }
    if(p==0)
        printf("%d. root is approximately %f\n", i+1, (a+b)/2);
    else
        printf("%d. root is exactly %f\n", i+1, (a+b)/2);
    }
return 0;
}
double f(double x){
return x*x+x-2;
}
