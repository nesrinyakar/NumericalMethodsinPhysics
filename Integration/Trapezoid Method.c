#include <stdio.h>
#include <math.h>
double f(double x);
int main(){
double h, x, area, a, b;
int i, n;

puts("Area under the function x^3-2x+5 will be calculated according to chosen bounds by Trapezoid method!");
puts("Enter lower limit");
scanf("%lf", &a);
puts("Enter higher limit");
scanf("%lf", &b);
puts("Enter number subintervals");
scanf("%d", &n);

h = (b-a)/n; // h accounts for delta x

area = 0;

for(i=1; i<n; i++)
    area = area + f(a+i*h);

area = (area + (f(a)+f(b))/2)*h;

printf("Area is approxitamely %f\n", area);
return 0;
}
double f(double x)
{
return x*x*x-2*x+5;
}

