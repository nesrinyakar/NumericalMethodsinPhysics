#include <stdio.h>
#include <math.h>
#include <stdlib.h> // to use fabs() function
#define PI 3.14159
double f(double x);
int main()
{

double h, x, a=0, b=PI;
double area_rect, area_rect_low, area_rect_high, area_trapezoid, area_simpson;
double prcerror_1, prcerror_2, prcerror_3, prcerror_4, actual_area;
int i, n;

puts("The integral of function sin(x) is calculated between 0 to pi");
puts("Enter number of subintervals");
scanf("%d", &n);

while(n%2 != 0){
    puts("Please enter an even number for subintervals!");
    scanf("%d", &n);
}

h = (b-a)/n;
area_rect_low = 0;
area_rect_high = 0;
area_trapezoid = 0;
area_simpson = 0;

for(i=1; i<n; i++){
    area_rect = area_rect + f(a + i*h);
    if(i % 2 == 0)
        area_simpson = area_simpson + 2*f(a + i*h);
    else
        area_simpson = area_simpson + 4*f(a + i*h);
}
area_rect_low = (area_rect + f(a))*h;
area_rect_high = (area_rect + f(b))*h;
area_trapezoid = (area_rect + (f(a)+f(b))/2)*h;
area_simpson = (area_simpson + f(a)+ f(b))*(h/3);

actual_area = 2;
prcerror_1 = fabs(area_rect_low - actual_area)/actual_area;
prcerror_2 = fabs(area_rect_high - actual_area)/actual_area;
prcerror_3 = fabs(area_trapezoid - actual_area)/actual_area;
prcerror_4 = fabs(area_simpson - actual_area)/actual_area;

printf("Area calculated by low rectangular method is %f with percent error %f\n", area_rect_low, prcerror_1);
printf("Area calculated by high rectangular method is %f with percent error %f\n", area_rect_high, prcerror_2);
printf("Area calculated by trapezoid method is %f with percent error %f\n", area_trapezoid, prcerror_3);
printf("Area calculated by Simpson 1/3 method is %f with percent error %f\n", area_simpson, prcerror_4);

return 0;
}
double f(double x){
return sin(x);
}

