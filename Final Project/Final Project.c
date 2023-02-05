#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double LJ_Potential(double r); // For H2 Molecule
double Force(double r);
double Force_RK(double t, double r, double v); // For Runge-Kutta calculations
double Velocity(double t, double v);
double D_Force(double r); // 2nd derivative of potential to determine a limit potential value

int main(){

FILE *fp1 = fopen("Tvsrave.txt", "w");
if (fp1 == NULL)
{
    puts("Error opening the file");
    return -1;
}

FILE *fp2 = fopen("FP_Data.txt", "w");
if (fp2 == NULL)
{
    puts("Error opening the file");
    return -2;
}

FILE *fp3 = fopen("One_Vib.txt", "w");  //To see LJ Potential graph shape in one period of vibraton of the molecule.
if (fp3 == NULL)
{
    puts("Error opening the file");
    return -3;
}

double S=(8.62e-5); //Boltzmann constant in unit eV/K
int i,j,l, N, T=10000, p=0;
double a, b, c, d, eps, bahalf, dchalf, r0, rmax, rmin, ri, rf, ri_nu, rf_nu, rsum, rave[20], Temperature[20], Umin, U_limit, U;
double r, rave_sum=0, dT, drave, ec, h, vn=0, rn, tn[T], vn_plus1[T], rn_plus1[T], k1v, k2v, k3v, k4v, k1r, k2r, k3r, k4r;


//Finding r0 by calculating Umin, at equilibrium
a = 0.06;
b = 0.073;
eps = 0.01;
if(Force(a)*Force(b) >= 0){
    printf("Choose a different interval");
        return 1;
    }
while( b-a > eps){
    bahalf = (a+b)/2;
    if(Force(bahalf)*Force(a) < 0){
        b = bahalf;
    }
    else if(Force(bahalf)==0){
        break;
    }
    else{
        a = bahalf;
    }
}
r0 = (a+b)/2;
printf("%lf\n", r0);


//Finding rmin by calculating root of potential, at U=0
a = 0.06;
b = r0;
if(LJ_Potential(a)*LJ_Potential(b) >= 0){
    printf("Choose a different interval");
        return 1;
    }
while( b-a > eps){
    bahalf = (a+b)/2;
    if(Force(bahalf)*LJ_Potential(a) < 0){
        b = bahalf;
    }
    else if(LJ_Potential(bahalf)==0){
        break;
    }
    else{
        a = bahalf;
    }
}
rmin = (a+b)/2;
printf("%lf\n", rmin);


//Finding rmax by calculating root of second derivative of potential
a = r0;
b = 0.08;
if(D_Force(a)*D_Force(b) >= 0){
    printf("Choose a different interval");
        return 1;
    }
while( b-a > eps){
    bahalf = (a+b)/2;
    if(Force(bahalf)*D_Force(a) < 0){
        b = bahalf;
    }
    else if(D_Force(bahalf)==0){
        break;
    }
    else{
        a = bahalf;
    }
}
rmax = (a+b)/2;
printf("%lf\n", rmax);


Umin = LJ_Potential(r0);
U_limit = LJ_Potential(rmax);
for(l=0; l<20; l++){   // T=0 Kelvin to 2K by 20 steps with 0.1 increments
    Temperature[l] = 0.1*(l+1);
    U = Umin + (3/2)*S*Temperature[l];
    rsum=0;
    if(U < U_limit){
        //Root finding for ri & rf values
        for (j=0; j<2; j++){
            if(j==0){
                c=rmin;
                d=0.07;
            }
            else{
                c=0.071;
                d=0.078;
            }

            if((LJ_Potential(c)-U)*(LJ_Potential(d)-U) >= 0){
                printf("Choose a different interval");
                return 1;
            }

            while( c-d > eps){
                dchalf = (c+d)/2;
                if((LJ_Potential(dchalf)-U)*(LJ_Potential(c)-U) < 0){
                    d = dchalf;
                }
                else if((LJ_Potential(dchalf)-U)==0){
                    break;
                }
                else{
                    c = dchalf;
                }
            }
            if(j==0){
                ri=(c+d)/2;
            }
            else{
                rf=(c+d)/2;
            }
        }
        printf("%lf %lf\n", ri, rf);


        //Time steps for r values
        h=0.001;
        N = 10/h;

        tn[0]=0;
        rn=ri;

        for(i=0; i<=N; i++){
                k1v = Velocity(tn[i], vn);
                k1r = Force_RK(tn[i], rn, vn);
                k2v = Velocity(tn[i]+(h/2), vn+(k1r*h/2));
                k2r = Force_RK(tn[i]+(h/2), rn+(k1v*h/2), vn+(k1r*h/2));
                k3v = Velocity(tn[i]+(h/2), vn+(k2r*h/2));
                k3r = Force_RK(tn[i]+(h/2), rn+(k2v*h/2), vn+(k2r*h/2));
                k4v = Velocity(tn[i]+(h/2), vn+(k3r*h));
                k4r = Force_RK(tn[i]+(h/2), rn+(k3v*h), vn+(k3r*h));

                vn_plus1[i] = vn + (k1r+2*k2r+2*k3r+k4r)*h/6;
                rn_plus1[i] = rn + (k1v+2*k2v+2*k3v+k4v)*h/6;

                if(i==0){
                    fprintf(fp2, "%lf %lf %lf %lf\n", tn[i], rn, vn, LJ_Potential(rn));
                }
                else{
                    fprintf(fp2, "%lf %lf %lf %lf\n", tn[i], rn_plus1[i], vn_plus1[i], LJ_Potential(rn));
                }

                tn[i+1] = tn[i]+h/1000;  // t=0 sec to 0.1 sec in 100 steps for chosen h=0.1
                vn = vn_plus1[i];
                rn = rn_plus1[i];
                rsum = rsum + rn;

                if(i<13){ // After 12th iteration, molecule goes backward
                     if(i==0){
                        fprintf(fp3, "%lf %lf %lf %lf\n", tn[i], rn, vn, LJ_Potential(rn));
                     }
                     else{
                        fprintf(fp3, "%lf %lf %lf %lf\n", tn[i], rn_plus1[i], vn_plus1[i], LJ_Potential(rn));
                     }
                }
        }
        rave[l] = rsum /(N+1);
        fprintf(fp1, "%lf  %lf\n", Temperature[l], rave[l]);
    }
    else{
        break;
    }
}

//average expansion coefficient calculation
for(i=0; i<20; i++){
    rave_sum = rave_sum + rave[i];
}
dT = Temperature[19]-0; //change in temperature which is 0 to 2.0 K
drave = (rave_sum/20)-r0; //average change in average distances
ec = (1/0.074)*(drave/dT);
printf("expansion coefficient:%lf\n", ec);

fclose(fp1);
fclose(fp2);
fclose(fp3);
return 0;
}

double LJ_Potential(double r){
    return ((0.1*pow(10, -12)/pow(r,12))-(1.5*pow(10, -6)/pow(r,6)));
}

double Force(double r){
    return ((12*0.1*pow(10, -12)/pow(r,13))-(6*1.5*pow(10, -6)/pow(r,7)));
}

double Force_RK(double t, double r, double v){
    return ((12*0.1*pow(10, -12)/pow(r,13))-(6*1.5*pow(10, -6)/pow(r,7)));
}

double Velocity(double t, double v){
    return v;
}

double D_Force(double r){
    return ((-156*0.1*pow(10, -12)/pow(r,14))+(42*1.5*pow(10, -6)/pow(r,8)));
}
