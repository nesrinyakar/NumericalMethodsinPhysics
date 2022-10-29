#include <stdio.h>
#include <math.h>
double f(double x);
int main()
{
double h, x, area, a, b;
int i, n;

puts("Area under the curve -x^3+3x^2+7x-6 will be calculated according to chosen limits by Simpson 1/3 method!");
puts("Enter lower limit");
scanf("%lf", &a);
puts("Enter higher limit");
scanf("%lf", &b);
puts("Enter number of subintervals");
scanf("%d", &n);

while(n%2 != 0){
    puts("Please enter an even number for subintervals!"); //This methods works for only even number subintervals
    scanf("%d", &n);
}

h = (b-a)/n;
area = 0;

for(i=1; i<n; i++)
    if(i % 2 == 0)
        area = area + f(a + 2*(i*h));
    else
        area = area + f(a + 4*(i*h));

area = (area + f(a)+ f(b))*(h/3);

printf("Area is approximately %f", area);
return 0;
}
double f(double x){
return -x*x*x+3*x*x+7*x-6;
}
