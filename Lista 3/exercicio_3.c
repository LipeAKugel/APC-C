#include <stdio.h>

#define MAX 100

int valida_placa(char placa[])
{
	// Verifica se a placa segue o padrão
	
	int i;
	int teste;
	
	teste = 1;
	for (i = 0; i <= 2; i++) {
		if (!(placa[i] >= 65 && placa[i] <= 90)) teste = 0;
	}
	
	if (placa[3] != 45) teste = 0;
	
	for (i = 4; i <= 7; i++) {
		if (!(placa[i] >= 48 && placa[i] <= 57)) teste = 0;
	}
	
	if (placa[8] >= 1 && placa[8] <= 255) teste = 0;
	
	return teste;
}

int main ()
{
	int i;
	int n_testes;
	char placa[MAX];
	
	// Entrada de Dados
	scanf("%i", &n_testes);
	
	int dia_rodizio[n_testes];
	int teste_placa[n_testes];
	
	for (i = 0; i < n_testes; i++) {
		scanf("%s", &placa);
		
		// Verifica se a placa é valida
		teste_placa[i] = valida_placa(placa);
		
		if (teste_placa[i] == 1) {
			// Indica o dia de rodízio
			switch (placa[7]) {
				case 49: dia_rodizio[i] = 2; break;
				case 50: dia_rodizio[i] = 2; break;
				case 51: dia_rodizio[i] = 3; break;
				case 52: dia_rodizio[i] = 3; break;
				case 53: dia_rodizio[i] = 4; break;
				case 54: dia_rodizio[i] = 4; break;
				case 55: dia_rodizio[i] = 5; break;
				case 56: dia_rodizio[i] = 5; break;
				case 57: dia_rodizio[i] = 6; break;
				case 48: dia_rodizio[i] = 6; break;
			}
		}
	}
	
	// Saída
	for (i = 0; i < n_testes; i++) {
		if (teste_placa[i] == 1) {
			switch (dia_rodizio[i]) {
				case 2: printf("MONDAY\n"); break;
				case 3: printf("TUESDAY\n"); break;
				case 4: printf("WEDNESDAY\n"); break;
				case 5: printf("THURSDAY\n"); break;
				case 6: printf("FRIDAY\n"); break;
			}
		} else printf("FAILURE\n");
	}
	
	return 0;
}
