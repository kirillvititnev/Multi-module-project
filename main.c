#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
int itr;
extern double f1(double);
extern double f2(double);
extern double f3(double);

extern double Derivative_f1(double);
extern double Derivative_f2(double);
extern double Derivative_f3(double);

double root(double (*f) (double), double (*g) (double), double a, double b, double eps1, double(*fp)(double), double (*gp)(double))
{// функци€ вычисл€ет по методу хорд и касательных
	itr = 0;
    do {
		double q1 = f(b) - f(a);
		double q2 = -f((a + b) / 2) + f(a) / 2 + f(b) / 2;
		q1*=q2;
        if ((f(a)-g(a)) * q1 < 0)
		{//”словие начальной точки дл€ метода хорд
            a = a + (b - a) / ((f(a)-g(a)) - (f(b)-g(b)))*(f(a)-g(a)); //формулы расчета по методу хорд
            b = b - (f(b)-g(b)) / (fp(b)-gp(b));
        }
        if ((f(a)-g(a)) * q1 > 0) {//”словие начальной точки дл€ метода касательных
            a = a - (f(a)-g(a)) / (fp(a)-gp(a)); //формулы расчета по методу касательных
            b = b + (b - a) / ((f(b) - g(b)) - (f(a) - g(a)))*(f(b)-g(b));
        }
        itr++;
    } while (fabs(b - a) > eps1);//ѕостроение хорд и касательных продолжаетс€ до достижени€ необходимой точности решени€ е
    return (a + b) / 2.0;
}
double integral(double (*f)(double), double a, double b, double eps2)
{

	int k1 = 10;
	int k2 = 20;
	double I1 = 0;
	double I2 = 0;
	double h1 = (b - a) / k1;
	double h2 = (b - a) / k2;
	for (int i = 0; i <= k1; i++)
	{
		if( i == 0 || i == k1)
			I1 += 0.5*f(a+i*h1);
		else
			I1 += f(a + i * h1);
	}
	I1 *= h1;
	for (int i = 0; i <= k2; i++)
	{
		if( i == 0 || i == k2)
			I2 += 0.5 * f(a+i*h2);
		else
			I2 += f(a + i * h2);
	}
	I2 *= h2;
	double e1 = I1 - I2;//calculating the accuracy when dividing a segment into k2 parts i1->i2!!!!
	if (e1 < 0)
		e1 = -e1;
	e1 = e1 / 3;
	while (e1 > eps2)
	{
		I1 = I2;
		k2*=2;
		I2 = 0;
		h2 = (b - a) / k2;
		for (int i = 0; i <= k2; i++)
		{
			if( i == 0 || i ==  k2)
				I2 += 0.5 * f(a+i*h2);
			else
				I2 += f(a + i * h2);
		}
		I2 *= h2;
	    e1 = I1 - I2;
		if (e1 < 0)
			e1 = -e1;
		e1 = e1 / 3;
	}
	return I2;
}

int main(int argc, char *argv[])
{
    //double tmp;
    //scanf("%lf", &tmp);
    //printf("f1(x) = %lf ; f2(x) =  %lf; f3(x) =  %lf", f1(tmp), f2(tmp), f3(tmp));
   char *com;
   for (int i = 1;i < argc; i++)
   	{
		com = argv[i];
   		if (!strcmp(com,"-help"))
   		{
   			printf("available commands:\n-help : shows the available commands\n");
   			printf("-points : shows the intersection points of functions\n");
   			printf("-iter : shows the number of iterations when solving equations\n");
   			printf("-area : prints the area\n");
			printf("-testintegral (function number) (a) (b) (eps)\n-testroot (1st function number) (2nd function number) (a) (b) (eps)\n");
			continue;
		}
		if (!strcmp(com,"-points"))
		{
			printf("the intersection point of the 1st and 2nd curves: ");
			double p1;
			p1 = root(f1,f2,-2,-0.1,0.001,Derivative_f1,Derivative_f2);
			printf("x = %.3lf   y = %.3lf\n",p1,f1(p1));
			printf("the intersection point of the 1st and 3rd curves: ");
			p1 = root(f1,f3,-4.5,-3.5,0.001,Derivative_f1,Derivative_f3);
			printf("x = %.3lf   y = %.3lf\n",p1,f3(p1));
			printf("the intersection point of the 2nd and 3rd curves: ");
			p1 = root(f2,f3,-2,-1,0.001,Derivative_f2,Derivative_f3);
			printf("x = %.3lf   y = %.3lf\n",p1,f3(p1));
			continue;
		}
		if (!strcmp(com,"-testroot"))
   		{
   			int nf1,nf2;
   			double ta,tb,teps;
   			scanf("%d %d %lf %lf %lf",&nf1,&nf2,&ta,&tb,&teps);
			if ((nf1 < 0) ||  (nf2 < 0) || (nf1 > 3) || (nf2 > 3) || (nf1 == nf2))
			{
				printf("invalid function numbers\n");
				continue;
			}
			if (((nf1 == 1) && (nf2 == 2)) || ((nf1 == 2) && (nf2 == 1)))
			{
				double tx = root(f1,f2,ta,tb,teps,Derivative_f1, Derivative_f2);
				printf("x = %lf\n",tx);
			}
			if (((nf1 == 1) && (nf2 == 3)) || ((nf1 == 3) && (nf2 == 1)))
			{
				double tx = root(f1,f3,ta,tb,teps,Derivative_f1,Derivative_f3);
				printf("x = %lf\n",tx);
			}
			if (((nf1 == 2) && (nf2 == 3)) || ((nf1 == 3) && (nf2 == 2)))
			{
				double tx = root(f2,f3,ta,tb,teps,Derivative_f2,Derivative_f3);
				printf("x = %lf\n",tx);
			}
			continue;
		}
		if (!strcmp(com,"-testintegral"))
		{
			double ta,tb,teps,ti;
			int nf;
			scanf("%d %lf %lf %lf",&nf,&ta,&tb,&teps);
			if ((nf < 0) || (nf > 3))
			{
				printf("invalid function number\n");
				continue;
			}
			if (nf == 1)
				ti = integral(f1,ta,tb,teps);
			if (nf == 2)
				ti = integral(f2,ta,tb,teps);
			if (nf == 3)
				ti = integral(f3,ta,tb,teps);
			printf("I = %lf\n",ti);
			continue;
		}
		if (!strcmp(com,"-iter"))
		{
			printf("number of iterations when solving <<f1(x) - f2 (x) = 0>> : ");
			root(f1,f2,-2,-0.1,0.001,Derivative_f1,Derivative_f2);
			printf("%d\n",itr);
			printf("number of iterations when solving <<f2(x) - f3 (x) = 0>> : ");
			root(f2,f3,-2,-1,0.001,Derivative_f2,Derivative_f3);
			printf("%d\n",itr);
			printf("number of iterations when solving <<f1(x) - f3 (x) = 0>> : ");
			root(f1,f3,-4.5,-3.5,0.001,Derivative_f1,Derivative_f3);
			printf("%d\n",itr);
			continue;
		}
		if (!strcmp(com,"-area"))
		{
			double x1,x2,x3;
			x1 = root(f1,f3,-4.5,-3.5,0.001,Derivative_f1,Derivative_f3);
			x2 = root(f2,f3,-2,-1,0.001,Derivative_f2,Derivative_f3);
			x3 = root(f1,f2,-2,-0.1,0.001,Derivative_f1,Derivative_f2);
			printf("%lf %lf %lf \n f1(-1) = %lf; f2(-1) = %lf f3(-1) = %lf\n f1(-2) = %lf; f2(-2) = %lf f3(-2) = %lf\n f1(1) = %lf; f2(1) = %lf f3(1) = %lf\n", x1, x2, x3, f1(-1.0), f2(-1.0), f3(-1), f1(-2.0), f2(-2.0)  , f3(-2), f1(1), f2(1), f3(1));
			double sqr = integral(f1,x1,x3,0.0001);//1!!!!!
			sqr -= integral(f3,x1,x2,0.0001);//!!!!!!
			sqr -= integral(f2,x2,x3,0.0001);//!!!!!
			printf("square = %.3lf\n",sqr);
			continue;
		}
		if (!strcmp)
		if (strcmp(com,"-end"))
			printf("unknown command\n");
   }
	return 0;
}
