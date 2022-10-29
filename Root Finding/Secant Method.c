#include <stdio.h>
#include <math.h>
double f(double x);
int main(){

double a, b, c, eps, fofa, fofb, fofc;

puts("Roots of the function x^2-1 will be calculated");

//Reading the interval and precision value
puts("Enter starting point");
scanf("%lf", &a);
puts("Enter ending point");
scanf("%lf", &b);
puts("Enter precision");
scanf("%lf", &eps);

//Controling whether root is entered.
if(f(a) == 0.0){
    printf("%lf is the root", a);
    return 1;
}
if(f(b)== 0.0){
    printf("%lf is the root", b);
    return 2;
}

if(f(a)*f(b)>=0 ){
    puts("Choose a different interval!");
    return 4;
}
fofa = f(a);
fofb = f(b);
do{
    c = (a*fofb-b*fofa)/(fofb-fofa);
    fofc = f(c);
    if(fofc == 0.0){
        printf("%lf is the root", &c);
        return 3;
    }
    if(fofa*fofc < 0.0){
        a = c;
        fofa = fofc;
    }
    else{
        b = c;
        fofb = fofc;
    }
}while(b-a > eps);
printf("Root is approximately %lf", (a+b)/2);
return 0;
}

double f(double x){
    return x*x-1;
}
