#include <stdio.h>
#include <math.h>

int main() 
{
	int n;
	
	scanf("%i", &n);
	
	sequencia(n);
	
	return 0;
}

void sequencia(int n) 
{
	long int n_sequencia;
	
	for (long int i = 1; i <= n; i++) {
		printf("%li", i);
		for (int j = 2; j <= 3; j++) {
			n_sequencia = pow(i, j);
			printf(" %li", n_sequencia);
		}
		printf("\n");
		printf("%i", i);
		for (int j = 2; j <= 3; j++) {
			n_sequencia = (pow(i, j) + 1);
			printf(" %li", n_sequencia);
		}
		printf("\n");
	}
}
