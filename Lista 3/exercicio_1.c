#include <stdio.h>

int main ()
{
	// Declarações
	int N, menor, posicao;
	
	// Instruções
	
	// Entrada de dados:
	scanf("%i", &N);
	
	int X[N];
	
	for (int i = 0; i <N; i++) {
		scanf("%i", &X[i]);	
	}
	
	menor = calcula_menor(X, N);
	posicao = informa_posicao(menor, N, X);
	
	// Saída de dados:
	printf("Menor valor: %i\n", menor);
	printf("Posicao: %i\n", posicao);
	
	return 0;
}

// Função que calcula o menor valor de um vetor:
int calcula_menor(int vetor[], int num_elementos)
{
	int menor = vetor[0];
	
	for (int i = 0; i < num_elementos; i++) {
		if (vetor[i] < menor) {
			menor = vetor[i];
		}
	}
	
	return menor;
}

// Função que informa a posição de um valor em um vetor
int informa_posicao(int valor, int num_elementos, int vetor[])
{
	int posicao;
	
	for (int i = 0; i < num_elementos; i++){
		if (valor == vetor[i]) {
			posicao = i;
		}
	}
	
	return posicao;
}
