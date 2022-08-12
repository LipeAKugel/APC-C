#include <stdio.h>

int main()
{
	int n_testes, total_sapos, total_coelhos, total_ratos, quantia_cobaias;
	char tipo_cobaia;
	
	// Entrada de dados
	
	scanf("%i", &n_testes);
	
	total_coelhos = 0;
	total_sapos = 0;
	total_ratos = 0;	
	for (int i = 0; i < n_testes; i++) {
		scanf("%i %c", &quantia_cobaias, &tipo_cobaia);
		
		// S = sapo, C = coelho, R = rato
		
		if (tipo_cobaia == 83) {
			total_sapos = total_sapos + quantia_cobaias;
		}
		
		if (tipo_cobaia == 67) {
			total_coelhos = total_coelhos + quantia_cobaias;
		}
		
		if (tipo_cobaia == 82) {
			total_ratos = total_ratos + quantia_cobaias;
		}
	}
	
	// Chama o procedimento
	saida(total_sapos, total_coelhos, total_ratos);
	
	return 0;
}

void saida(int total_sapos, int total_coelhos, int total_ratos)
{
	float total_cobaias = total_sapos + total_coelhos + total_ratos;
	float per_coelhos, per_ratos, per_sapos;
	
	per_coelhos = ((total_coelhos/total_cobaias) * 100);
	per_ratos = ((total_ratos/total_cobaias)*100);
	per_sapos = ((total_sapos/total_cobaias) *100);
	
	// Saída de dados
	printf("Total: %.0f cobaias\n", total_cobaias);
	printf("Total de coelhos: %i\n", total_coelhos);
	printf("Total de ratos: %i\n", total_ratos);
	printf("Total de sapos: %i\n", total_sapos);
	printf("Percentual de coelhos: %.2f %%\n", per_coelhos);
	printf("Percentual de ratos: %.2f %%\n", per_ratos);
	printf("Percentual de sapos: %.2f %%\n", per_sapos);
}
