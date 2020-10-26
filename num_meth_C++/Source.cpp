#include <iostream>
#include <cmath>
#define M abs(log(0.9477+1)/(4*sqrt(pow(0.9477+1,3))));
using namespace std;

double f(double x)
{
	return sqrt(x + 1) * log(x + 1);
}

double I(double x)
{
	return 2 * pow(x + 1, 1.5) * (3 * log(x + 1) - 2) / 9;
}

double trapI(double h, double n)
{
	double x0 = 0.1; double x1 = x0 + h;
	double I = 0;
	for (int i = 1; i <= n; i++)
	{
		I += (f(x0) + f(x1)) * h / 2;
		x0 = x1;
		x1 += h;
	}
	return I;
}

class sympson
{
private:
	double summ1;
	double summ2;
	double a, b;
	double h; int n;
	double* x;
	double* y;
public:
	sympson(double a, double b, double h, int n)
	{
		this->h = h / 2;
		this->n = 2 * (n);
		this->a = a; this->b = b;
		this->summ1 = 0; this->summ2 = 0;
		x = new double[this->n];
		y = new double[this->n];
	}
	void initializePoints()
	{
		int i = 0;
		for (double m = a; m <= b; m += h) //Вычисление значений точек для каждого шага
		{
			x[i] = m;
			y[i] = f(m);
			i++;
		}
	}
	double calculate()
	{
		initializePoints();
		for (int i = 1; i < n; i += 2)
		{
			summ1 += y[i]; //Сумма для нечетных точек	
		}
		for (int i = 2; i < n; i += 2)
		{
			summ2 += y[i]; //Сумма для четных точек
		}
		return (h / 3) * (y[0] + 4 * summ1 + 2 * summ2 + y[n]); //Получившийся интеграл
	}
};

int main()
{
	double eps = 0.0001;
	double a = 0.1; double b = 1.1;
	double m = M;
	double h = sqrt(12 * eps / (m * abs(b - a)));
	int n = ((b - a) / h) + 1;
	n += (4 - n % 4);
	h = (b - a) / n;
	cout << "n: " << n << " h: " << h << endl;
	double Ia = I(b) - I(a);
	double It = trapI(h, n);
	double I2t = trapI(2 * h, n / 2);
	sympson s1(a, b, h, n), s2(a, b, 2 * h, n / 2);
	double Is = s1.calculate();
	double I2s = s2.calculate();
	cout << "Trapezoid method: " << It << " eps: " << abs(I2t - It) / 3 << endl;
	cout << "Sympson method: " << Is << " eps: " << abs(I2s - Is) / 15 << endl;
	cout << "Analytic solution: " << Ia << endl;
	cout << "Best method: "; if (abs(I2t - It) / 3 > abs(I2s - Is) / 15) cout << "Sympson method" << endl; else cout << "Trapezoid method" << endl;
	return 0;
}