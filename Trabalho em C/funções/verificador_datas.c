#include <stdio.h>
#include <stdlib.h>
#define TAM_DATA 10

int valida_data(char data[])
{
	// Função que verifica a validação da data
	// DD/MM/AAAA
	
	int dado_valido;
	int valor_dia, valor_mes, valor_ano;
	char dia[2], mes[2], ano[4];
	
	dado_valido = 1;
	
	// Verifica a estrutura DD/MM/AAAA
	if (data[10] != '\0') {
		dado_valido = 0;
	}
	
	// Verifica se o dia, mês e ano são valores numéricos
	for (int i = 0; i < TAM_DATA - 8; i++) {
			if (!(data[i] >= 48 && data[i] <= 57)) {
			dado_valido = 0;
			}
		}
		
	for (int i = 3; i < TAM_DATA - 5; i++) {
			if (!(data[i] >= 48 && data[i] <= 57)) {
			dado_valido = 0;
			}
		}
		
	for (int i = 6; i < TAM_DATA; i++) {
			if (!(data[i] >= 48 && data[i] <= 57)) {
			dado_valido = 0;
			}
		}
	
	// Verifica os símbolos
	if (data[2] != 47 && data[5] != 47) {
		dado_valido = 0;
		
	} else {
		
		// Guarda o valor número do dia
		dia[0] = data[0];
		dia[1] = data[1];
		valor_dia = atoi(dia);
		
		// Guarda o valor número do mês
		mes[0] = data[3];
		mes[1] = data[4];
		valor_mes = atoi(mes);
		
		// Guarda o valor número do ano
		ano[0] = data[6];
		ano[1] = data[7];
		ano[2] = data[8];
		ano[3] = data[9];
		valor_ano = atoi(ano);
		
		// Verifica se os valores são inválidos
		if (valor_dia < 1 || valor_mes < 1 || valor_mes > 12 || valor_ano < 1900) {
			dado_valido = 0;
			
		} else {
			if (valor_ano % 4 == 0 && valor_ano % 100 != 0 || valor_ano % 400 == 0) {
				
				// Ano bissexto:
				if (valor_mes == 1 || valor_mes == 3 || valor_mes == 5 || valor_mes == 7 || valor_mes == 8 || valor_mes == 10 || valor_mes == 12) {
					if (valor_dia > 31) dado_valido = 0;
				} else {
					if (valor_mes == 2) {
						// Em ano bissexto fevereiro tem 29 dias
						if (valor_dia > 29) {
							dado_valido = 0;
						}
					} else {
						if (valor_dia > 30) {
							dado_valido = 0;
						}
					}
				}
				
			} else {
				
				// Ano não bissexto:
				if (valor_mes == 1 || valor_mes == 3 || valor_mes == 5 || valor_mes == 7 || valor_mes == 8 || valor_mes == 10 || valor_mes == 12) {
					if (valor_dia > 31) dado_valido = 0;
				} else {
					if (valor_mes == 2) {
						// Em ano bissexto fevereiro tem 29 dias
						if (valor_dia > 28) {
							dado_valido = 0;
						}
					} else {
						if (valor_dia > 30) {
							dado_valido = 0;
						}
					}
				}
			}
		}
	}
	
	return dado_valido;
	} 

int main()
{
	char data_operacao[TAM_DATA], dado_valido;
	
	scanf("%s", data_operacao);
	
	dado_valido = valida_data(data_operacao);
	
	printf("%i", dado_valido);
	
	return 0;	
}
