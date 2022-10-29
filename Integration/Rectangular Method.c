#include <stdio.h>
#include <math.h>
double f(double x); 
int main()
{
double h, x, area, area_low, area_high, a, b;
int i, n;

puts("Area under the curve x^2-3x will be calculated according to chosen limits by rectangular method!");
puts("Enter lower limit");
scanf("%lf", &a);
puts("Enter higher limit");
scanf("%lf", &b);
puts("Enter number subintervals");
scanf("%d", &n);

h = (b-a)/n; // h accounts for delta x

area = 0;

for(i=1; i<n; i++)
    area = area + f(a+i*h); // to calculate f1+f2+...+fn-1

area_low = (area + f(a))*h;
area_high = (area + f(b))*h;

printf("Lower area is  %f and higher area is %f\n", area_low, area_high);
return 0;
}
double f(double x)
{
return x*x-3;
}
