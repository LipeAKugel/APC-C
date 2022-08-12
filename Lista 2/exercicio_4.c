#include <stdio.h>

int main()
{
	int n_testes;
	int num[20];
	int verificacao;
	
	scanf("%i", &n_testes);
	
	for (int i = 0; i < n_testes; i++) {
		scanf("%i", &num[i]);
	}
	
	for (int i = 0; i < n_testes; i++) {
		verificacao = verificador(num[i]);
		
		if(verificacao == 1) {
			printf("%i eh perfeito\n", num[i]);
		} else {
			printf("%i nao eh perfeito\n", num[i]);
		}
	}
	
	return 0;
}

int verificador(int num)
{
	int divisor;
	int verificacao;
	
	divisor = 0;
	for (int i = (num-1); i > 0; i--) {
		if((num % i) == 0) {
			divisor = divisor + i; 
		}
	}
	
	if (divisor == num) verificacao = 1;
	else verificacao = 0;
	 
	return verificacao;
}
