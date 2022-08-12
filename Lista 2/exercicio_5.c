#include <stdio.h>
#include <math.h>

long int fun_rafael(int x, int y)
{
	// (x, y) = (3x)² + y²
	long int resultado;
	resultado = (pow((3*x), 2) + pow(y, 2));
	return resultado;
}

long int fun_beto(int x, int y)
{
	// (x, y) = 2(x²) + (5y)²
	long int resultado;
	resultado = (2 * pow(x, 2) + pow((5*y), 2));
	return resultado;
}

long int fun_carlos(int x, int y)
{
	// (x, y) = -100x + y³
	long int resultado;
	resultado = (-100*x + pow(y, 3));
	return resultado;
}

int main()
{
	int i, j;
	int num_testes;
	long int resultado[3];
	
	scanf("%i", &num_testes);
	
	int x[num_testes], y[num_testes];
	
	for (i = 0; i < num_testes; i++) {
		scanf("%i %i", &x[i], &y[i]);
	}
	
	for (j = 0; j < num_testes; j++) {
		
		resultado[0] = fun_rafael(x[j], y[j]);
		resultado[1] = fun_beto(x[j], y[j]);
		resultado[2] = fun_carlos(x[j], y[j]);
		
		if (resultado[0] > resultado[1] && resultado[0] > resultado[2]) {
			printf("Rafael ganhou\n");
		} else if (resultado[1] > resultado[0] && resultado[1] > resultado[2]) {
			printf("Beto ganhou\n");
		} else {
			printf("Carlos ganhou\n");
		}
	}
	
	return 0;
}
