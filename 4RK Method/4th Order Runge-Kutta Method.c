#include <stdio.h>
#include <stdio.h>
#include <math.h>
#define T 10000
double f(double t, double v); // dx/dt = v, x(0)=1
double g1(double t, double x, double v); // dv/dt = -x-2v, v(0)=0
double g2(double t, double x, double v); // dv/dt = -x-4v, v(0)=0
double g3(double t, double x, double v); // dv/dt = -x-6v, v(0)=0
double h1(double t); //actual solution for B=2
double h2(double t); //actual solution for B=4
double h3(double t); //actual solution for B=6

int main(){

FILE *fp = fopen("RungeKutta_Method.txt", "w");
if (fp == NULL)
{
    puts("Error opening the file");
    return -1;
}
double x, h, vn_1=0., vn_2=0., vn_3=0., xn_1=1., xn_2=1., xn_3=1.;
double tn[T], vn_1_plus1[T], vn_2_plus1[T], vn_3_plus1[T], xn_1_plus1[T], xn_2_plus1[T], xn_3_plus1[T];
double k1v_1, k2v_1, k3v_1, k4v_1, k1v_2, k2v_2, k3v_2, k4v_2, k1v_3, k2v_3, k3v_3, k4v_3;
double k1x_1, k1x_2, k1x_3, k2x_1, k2x_2, k2x_3, k3x_1, k3x_2, k3x_3, k4x_1, k4x_2, k4x_3;
int i, N;
puts("Enter h:");
puts("For a good approximation do not enter value >0 !!");
scanf("%lf", &h);
N = 10/h;
if(N>T)
    puts("Enter high h value!!");
tn[0]=0;
for(i=0; i<=N; i++){
    k1v_1 = f(tn[i], vn_1);
    k1v_2 = f(tn[i], vn_2);
    k1v_3 = f(tn[i], vn_3);
    k1x_1 = g1(tn[i], xn_1, vn_1);
    k1x_2 = g2(tn[i], xn_2, vn_2);
    k1x_3 = g3(tn[i], xn_3, vn_3);
    k2v_1 = f(tn[i]+(h/2), vn_1+(k1x_1*h/2));
    k2v_2 = f(tn[i]+(h/2), vn_2+(k2x_1*h/2));
    k2v_3 = f(tn[i]+(h/2), vn_3+(k3x_1*h/2));
    k2x_1 = g1(tn[i]+(h/2), xn_1+(k1v_1*h/2), vn_1+(k1x_1*h/2));
    k2x_2 = g2(tn[i]+(h/2), xn_2+(k1v_2*h/2), vn_2+(k1x_2*h/2));
    k2x_3 = g3(tn[i]+(h/2), xn_3+(k1v_3*h/2), vn_3+(k1x_3*h/2));
    k3v_1 = f(tn[i]+(h/2), vn_1+(k2x_1*h/2));
    k3v_2 = f(tn[i]+(h/2), vn_2+(k2x_2*h/2));
    k3v_3 = f(tn[i]+(h/2), vn_3+(k2x_3*h/2));
    k3x_1 = g1(tn[i]+(h/2), xn_1+(k2v_1*h/2), vn_1+(k2x_1*h/2));
    k3x_2 = g2(tn[i]+(h/2), xn_2+(k2v_2*h/2), vn_2+(k2x_2*h/2));
    k3x_3 = g3(tn[i]+(h/2), xn_3+(k2v_3*h/2), vn_3+(k2x_3*h/2));
    k4v_1 = f(tn[i]+(h/2), vn_1+(k3x_1*h));
    k4v_2 = f(tn[i]+(h/2), vn_2+(k3x_2*h));
    k4v_3 = f(tn[i]+(h/2), vn_3+(k3x_3*h));
    k4x_1 = g1(tn[i]+(h/2), xn_1+(k3v_1*h), vn_1+(k3x_1*h));
    k4x_2 = g2(tn[i]+(h/2), xn_2+(k3v_2*h), vn_2+(k3x_2*h));
    k4x_3 = g3(tn[i]+(h/2), xn_3+(k3v_3*h), vn_3+(k3x_3*h));

    vn_1_plus1[i] = vn_1 + (k1x_1+2*k2x_1+2*k3x_1+k4x_1)*h/6;
    vn_2_plus1[i] = vn_2 + (k1x_2+2*k2x_2+2*k3x_2+k4x_2)*h/6;
    vn_3_plus1[i] = vn_3 + (k1x_3+2*k2x_3+2*k3x_3+k4x_3)*h/6;
    xn_1_plus1[i] = xn_1 + (k1v_1+2*k2v_1+2*k3v_1+k4v_1)*h/6;
    xn_2_plus1[i] = xn_2 + (k1v_2+2*k2v_2+2*k3v_2+k4v_2)*h/6;
    xn_3_plus1[i] = xn_3 + (k1v_3+2*k2v_3+2*k3v_3+k4v_3)*h/6;

    fprintf(fp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", tn[i], vn_1_plus1[i], xn_1_plus1[i], h1(tn[i]), vn_2_plus1[i], xn_2_plus1[i], h2(tn[i]), vn_3_plus1[i], xn_3_plus1[i], h3(tn[i]));

    tn[i+1] = tn[i]+h;
    vn_1 = vn_1_plus1[i];
    vn_2 = vn_2_plus1[i];
    vn_3 = vn_3_plus1[i];
    xn_1 = xn_1_plus1[i];
    xn_2 = xn_2_plus1[i];
    xn_3 = xn_3_plus1[i];

}

printf("Found x value of 1st equation: %lf\n", xn_1_plus1[N]);
printf("Found x value of 2nd equation: %lf\n", xn_2_plus1[N]);
printf("Found x value of 3rd equation: %lf\n", xn_3_plus1[N]);
fclose(fp);
return 0;
}
double f(double t, double v){
return v;
}
double g1(double t, double x, double v){
return -x-2*v;
}
double g2(double t, double x, double v){
return -x-4*v;
}
double g3(double t, double x, double v){
return -x-6*v;
}
double h1(double t){
return exp(-t)*(1+t);
}
double h2(double t){
    double a = sqrt(3);
return (((3+2*a)/6)*exp((-2+a)*t))+(((3-2*a)/6)*exp((-2-a)*t));
}
double h3(double t){
    double b = sqrt(2);
return (((4+3*b)/8)*exp((-3+2*b)*t))+(((4-3*b)/8)*exp((-3-2*b)*t));
}
