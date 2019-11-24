#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

const int m=11;
int i, n=4;
double a=1., b=4., Xu[m+1], Yu[m+1], X2[22], Yt[22]; 


double Funk (double);
void end (void);

using namespace std;

void main (void)
{
	for (i=1; i<=m; i++)
	{
		Xu[i] = a + (i-1)*(b-a)/(m-1);
		Yu[i] = Funk(Xu[i]);
	}
	for (i=1; i<=21; i++)
	{
		X2[i] = a + (i-1)*(b-a)/20;
		Yt[i] = Funk(X2[i]);
	}

	cout << setw(5) << "'Xi'" << setw(15) << "'Yi'" << endl;
	for (i=1; i<=m; i++)
		cout << setw(5) << Xu[i] << setw(15) << Yu[i] << endl;
	cout << endl;



	int j, k, p;
	double *x2, *y2, k1, *e, **g, c, *x, s, *rr, r;


	x=new double[n+1];
	x2=new double[22];
	y2=new double[22];
	e=new double[22];


	double *ym, *c1, *c2, *c3, *c4;
		   ym=new double[n+1];
		   c1=new double[n+1];
		   c2=new double[n+1];
		   c3=new double[n+1];
		   c4=new double[n+1];

	 for(i=1;i<=n;i++) 
	 {
		ym[i]=0;
		c1[i]=0;
		c2[i]=0;
		c3[i]=0;
		c4[i]=0;

		for(j=1;j<=m;j++)
		{
			if (i==1)
				k1 = (-1);
			if (i==2)
				k1 = (-Xu[j]);
			if (i==3)
				k1 = (-pow(Xu[j], 2));
			if (i==4)
				k1 = (-pow(Xu[j], 3));
			ym[i] += -2*k1*Yu[j];
			c1[i] += 2*k1*(-1);
			c2[i] += 2*k1*(-Xu[j]);
			c3[i] += 2*k1*(-pow(Xu[j], 2));
			c4[i] += 2*k1*(-pow(Xu[j], 3));
		}
	}

	cout << endl << setw(10) << "Matrica koefficientov" << endl;
	cout << setw(10) << "'c1'" << setw(10) << "'c2'" << setw(10) << "'c3'" << setw(10) << "'c4'" << setw(5) << " = " << setw(8) << "'ym'" << endl;
	for(i=1;i<=n;i++)
	cout << setw(10) << c1[i] << setw(10) << c2[i]  << setw(10) << c3[i] << setw(10) << c4[i] << setw(5) << " = " << setw(10) << ym[i] << endl;


	g=new double*[n+1];
		 for(i=0;i<=n;i++)
		 g[i]=new double[n+1];

		 for(i=1;i<=n;i++)
		 {
			 switch(i) 
			 {
				case 1: {for(j=1;j<=n;j++) g[j][i]=c1[j]; break;}
				case 2: {for(j=1;j<=n;j++) g[j][i]=c2[j]; break;}
				case 3: {for(j=1;j<=n;j++) g[j][i]=c3[j]; break;}
				case 4: {for(j=1;j<=n;j++) g[j][i]=c4[j]; break;}
			 }
		 }
	int o;
	 for(k=1;k<=n;k++)
	 {
		p=k;
		for(o=k+1;m<=n;o++)
		if (fabs((float) g[p][k])<fabs((float)g[m][k]))
		p=o;

		rr=g[k];
		g[k]=g[p];
		g[p]=rr;

		r=ym[k];
		ym[k]=ym[p];
		ym[p]=r;

		// pryamoy hod Gaussa
		for(o=k+1;o<=n;o++)
		{
			c=g[o][k]/g[k][k];
			ym[o]=ym[o]-c*ym[k];
			for(i=k;i<=n;i++)
				g[o][i]=g[o][i]-c*g[k][i];
		}
	 }

	 // obratniy hod Gaussa
	 x[n]=ym[n]/g[n][n];
	 for(k=n-1;k>=1;k--) 
	 {
		s=0;
		for (i=k+1;i<=n;i++)
			s+=g[k][i]*x[i];
		x[k]=(ym[k]-s)/g[k][k];
	 }

	cout << endl << endl;
	for(i=1;i<=n;i++)
		cout << "c" << i << "=" << x[i] << endl;

	cout << endl << endl;
	cout << setw(5) << "'x'" << setw(28) << "'y=c1+c2*x+c3*x^2+c4*x^3'" << setw(25) << "'y = x - 5*(sin(x))^2'" << setw (17) << "pogreshnost'" << endl;

	for(i=1;i<=21;i++)
	{
		y2[i] = x[1] + x[2]*X2[i] + x[3]*pow(X2[i],2) + x[4]*pow(X2[i],3);
		e[i]=Yt[i]-y2[i];

		cout << setw(5) << X2[i] << setw(20) << y2[i] << setw(25) << Yt[i] << setw(23) << e[i] << endl;
	}

	 for(i=0;i<=n;i++)
	 delete []g[i];
	 delete []g;
	 delete []x;
	 delete []x2;
	 delete []y2;
	 delete []e;
	 delete []ym;
	 delete []c1;
	 delete []c2;
	 delete []c3;
	 delete []c4;

	end ();
}

double Funk (double x)
{
	double fx; 
	fx = x - 5 * pow(sin(x), 2);
	return fx;
}

void end (void)
{
	std::cout << "Press ENTER to continue... " << flush;
	std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
}