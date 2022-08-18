// SISTEMA DE GESTÃO COMPARTILHADA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho_biblioteca.h"

int valida_data(char data[]) // Verifica data
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

int valida_cnpj(char cnpj[]) // Verifica CNPJ
{
	// XXXXXXXX0001XX
	
	// Declarações
	int dado_valido;
	int valores_cnpj[TAM_CNPJ];
	int sequencia_verificacao1[] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2}; // Para primeiro digito verificador
	int sequencia_verificacao2[] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2}; // Para segundo digito verificador
	int digito_verificador;
	
	// Instruções
	dado_valido = 1;
	
	// Verificação do formato
	if (cnpj[TAM_CNPJ] != '\0') {
		dado_valido = 0; // Caso chegou aqui, há mais caracteres que o devido.
	}
	
	// Verificação dos valores numéricos
	for (int i = 0; i < (TAM_CNPJ); i++) {
		if (!(cnpj[i] >= 48 && cnpj[i] <= 57)) {
			dado_valido = 0; // Caso chegou aqui, um caracter do CNPJ não é um número.
		}
	}
	
	// Verificação do 0001 ou "matriz"
	// Como estamos cadastrando uma usina, e não uma filial, o CNPJ terá somente o 0001.
	for (int i = 8; i < (TAM_CNPJ-4); i++) {
		if (cnpj[i] != '0') dado_valido = 0; // Caso chegou aqui, há um valor incorreto.
	}
	
	//if (cnpj[TAM_CNPJ-3] != '1') dado_valido = 0; // Caso chegou aqui, há um valor incorreto.
	
	// Armazenamento dos valores númericos do CNPJ
	for (int i = 0; i < (TAM_CNPJ); i++) {
		valores_cnpj[i] = (cnpj[i] - '0'); // Pega os valores numéricos do CNPJ e guarda num vetor int.
	}
	
	
	
	//Verificação dos digitos verificadores:
	
	// Primeiro digito verificador
	
	digito_verificador = 0;
	for (int i = 0; i < TAM_CNPJ-2; i++) {
		// Soma todos os resultados da multiplicação entre os números do CNPJ e dos respectivos números
		// na posições da primeira sequência de verificação.
		digito_verificador = (digito_verificador + (valores_cnpj[i] * sequencia_verificacao1[i]));
	}
	
	digito_verificador = digito_verificador % 11; // Divide o resultado por 11.
	
	if (digito_verificador < 2) { // Resto da divisão for menor que 2.
		digito_verificador = 0; // Caso chegou aqui, o primeiro digito verificador é 0.
		
	} else { // Resto da divisão não for menor 2.
		digito_verificador = (11 - digito_verificador); // Caso chegou aqui, o primeiro digito verificador é igual a 11 menos o resto.
	}
	
	if (valores_cnpj[TAM_CNPJ-2] != digito_verificador) { // Compara o digito do CNPJ e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o primeiro digito verificador do CNPJ está incorreto.
	}
	
	// Segundo digito verificador
	
	digito_verificador = 0;
	for (int i = 0; i < TAM_CNPJ-1; i++) {
		// Soma todos os resultados da multiplicação entre os números do CNPJ e dos respectivos números
		// na posições da segunda sequência de verificação.
		digito_verificador = (digito_verificador + (valores_cnpj[i] * sequencia_verificacao2[i]));
	}
	
	digito_verificador = digito_verificador % 11;
	
	if (digito_verificador < 2) { // Resto da divisão for menor que 2.
		digito_verificador = 0; // Caso chegou aqui, o segundo digito verificador é 0.
		
	} else { // Resto da divisão não for menor 2.
		digito_verificador = (11 - digito_verificador); // Caso chegou aqui, o segundo digito verificador é igual a 11 menos o resto.
	}
	
	if (valores_cnpj[TAM_CNPJ-1] != digito_verificador) { // Compara o digito do CNPJ e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o segundo digito verificador do CNPJ está incorreto.
	}
	
	return dado_valido;
}

int valida_cpf(char cpf[]) // Verifica CPF (Função não finalizada)
{
	int dado_valido = 1;
	return dado_valido;
}

void cadastro_usina() // Realiza o cadastro de uma usina
{
    /* Cadastro da usina:
    cnpj - XXXXXXXX0001XX
    nome - literalmente um nome qualquer
    data_inicio_operacao - DD/MM/AA
    potencia_estimada - X(MW)
    */
	
	// Declarações de variáveis
    char cnpj_usina[TAM_CNPJ];
    char nome_usina[TAM_NOME];
    char data_usina[TAM_DATA];
    float potencia_estimada;
    int dado_valido; // Se o valor for 0, é inválido, se for 1, é válido.
    
    // Instruções
    limpar_tela();
    
    printf("CADASTRO DE USINA\n");
    printf("\nINFORME OS DADOS -\n");
    
    
    // RECEBIMENTO DE DADOS:
    
    // CNPJ
    do {
    	printf("\nCNPJ: (ATENCAO! Digite apenas numeros!) ");
    	scanf("%s", cnpj_usina); // Recebe o dado do usuário.
    	dado_valido = valida_cnpj(cnpj_usina); // Chama a função para verificar o dado.
    	
    	if (dado_valido == 0) {
			printf("FORMATO DE DADO INCORRETO!"); // Se chegou aqui, o dado está incorreto.
		}
	} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
    
    
    // NOME
    printf("\nNome da Usina: ");
	scanf("%s", nome_usina);
    
	
	
	// DATA DE INÍCIO DE OPERAÇÃO
	do {
		printf("\nData de inicio de operacao (DD/MM/AAAA): ");
		scanf("%s", data_usina); // Recebe o dado do usuário.
		dado_valido = valida_data(data_usina); // Chama a função para verificar o dado.
		 
		if (dado_valido == 0) {
			printf("DATA INVÁLIDA!"); // Se chegou aqui, o dado está incorreto.
		}
	} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	
	
	// POTÊNCIA ESTIMADA
	do {
		printf("\nPotencia estimada (GW): ");
		scanf("%f", &potencia_estimada); // Recebe o dado do usuário.
		
		if (potencia_estimada <= 0) { // Verifica se a potência é maior que 0.
			dado_valido = 0; // Se chegou aqui, a potência é inválida.
		} else {
			dado_valido = 1; // Se chegou aqui, a potência é válida.
		}
		
		if (dado_valido == 0) {
			printf("VALOR DE POTÊNCIA INVÁLIDO!"); // Se chegou aqui, o dado está incorreto.
		}
		
	} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	
	// ARMAZENAMENTO DOS DADOS EM ARQUIVO:
	
	limpar_tela();
	printf("Usina cadastrada com sucesso!\n\n");
}

void cadastro_consumidor() // Realiza o cadastro de um consumidor
{
	/* Cadastro do consumidor:
	cpf - XXXXXXXXXYY
	cnpj - XXXXXXXX000XXX
	nome - literalmente qualquer nome
	*/
	
	// Declarações de variáveis
	
	char id_consumidor[TAM_CNPJ];
	char nome_consumidor[TAM_NOME];
	int dado_valido; // Se o valor for 0, é inválido, se for 1, é válido. 
	
	// Instruções
	
	limpar_tela();
	printf("CADASTRO DE CONSUMIDOR\n");
	printf("\nINFORME OS DADOS -\n");
	
	
	// RECEBIMENTO DE DADOS:
	
	// IDENTIFICAÇÃO (CPF OU CNPJ)
    do {
    	printf("\nCPF ou CNPJ: (ATENCAO! Digite apenas numeros!) ");
    	scanf("%s", id_consumidor); // Recebe o dado do usuário.
    	
    	if (strlen(id_consumidor) == TAM_CNPJ) { // Verifica se o usuário digitou um CNPJ.
			dado_valido = valida_cnpj(id_consumidor); // Chama a função para verificar o CNPJ.
		} else if (strlen(id_consumidor) == TAM_CPF) { // Verifica se o usuário digitou um CPF.
			dado_valido = valida_cpf(id_consumidor); // Chama a função para verificar o CPF.
		} else {
			dado_valido = 0; // Se chegou aqui, o dado está em formato incorreto.
		}
    	
    	if (dado_valido == 0) {
			printf("FORMATO DE DADO INCORRETO!"); // Se chegou aqui, o dado está incorreto.
		}
	} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
    
    
    // NOME
    
    printf("\nNome: ");
    scanf("%s", nome_consumidor);
	
	// ARMAZENAMENTO DOS DADOS:
	
	limpar_tela();
	printf("Consumidor cadastrado com sucesso!\n\n");
}

int main()
{
    int menu_opcao;
    
    printf("SISTEMA DE GESTAO COMPARTILHADA\n\n");
    
    do {
        menu();
    
        printf("\nOpcao: ");
        scanf("%i", &menu_opcao);
        
        switch (menu_opcao) {
            case CADASTRO_USINA: {
                cadastro_usina();
                break;
            }
            case CADASTRO_CONSUMIDOR: {
                cadastro_consumidor();
                break;
            }
            case CADASTRO_CONTRATO: {
                //cadastro_contrato();
                break;
            }
            case CONSULTAR_USINA: {
                //consulta_usina();
                break;
            }
            case CONSULTAR_CONSUMIDOR: {
                break;
            }
            case EXCLUIR_USINA: {
                break;
            }
            case EXCLUIR_CONSUMIDOR: {
                break;
            }
            case SAIR: {
             	break;   
            }
            default: {
            	limpar_tela();
            	printf("OPCAO INVALIDA!\n\n");
             	break;   
            }
        }
        
    } while (menu_opcao != 8); // Mantém o programa executando até o usuário encerrar
    
    printf("\nPrograma encerrado!\n");
    
    return 0;
}
