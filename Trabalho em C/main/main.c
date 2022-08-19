// SISTEMA DE GEST�O COMPARTILHADA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho_biblioteca.h"

int valida_data(char data[]) // Verifica data
{
	// Fun��o que verifica a valida��o da data
	// DD/MM/AAAA
	
	int dado_valido;
	int valor_dia, valor_mes, valor_ano;
	char dia[2], mes[2], ano[4];
	
	dado_valido = 1;
	
	// Verifica a estrutura DD/MM/AAAA
	if (data[10] != '\0') {
		dado_valido = 0;
	}
	
	// Verifica se o dia, m�s e ano s�o valores num�ricos
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
	
	// Verifica os s�mbolos
	if (data[2] != 47 && data[5] != 47) {
		dado_valido = 0;
		
	} else {
		
		// Guarda o valor n�mero do dia
		dia[0] = data[0];
		dia[1] = data[1];
		valor_dia = atoi(dia);
		
		// Guarda o valor n�mero do m�s
		mes[0] = data[3];
		mes[1] = data[4];
		valor_mes = atoi(mes);
		
		// Guarda o valor n�mero do ano
		ano[0] = data[6];
		ano[1] = data[7];
		ano[2] = data[8];
		ano[3] = data[9];
		valor_ano = atoi(ano);
		
		// Verifica se os valores s�o inv�lidos
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
				
				// Ano n�o bissexto:
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
	
	// Declara��es
	int dado_valido;
	int valores_cnpj[TAM_CNPJ];
	int sequencia_verificacao1[] = {5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2}; // Para primeiro digito verificador
	int sequencia_verificacao2[] = {6, 5, 4, 3, 2, 9, 8, 7, 6, 5, 4, 3, 2}; // Para segundo digito verificador
	int digito_verificador;
	
	// Instru��es
	dado_valido = 1;
	
	// Verifica��o do formato
	if (cnpj[TAM_CNPJ] != '\0') {
		dado_valido = 0; // Caso chegou aqui, h� mais caracteres que o devido.
	}
	
	// Verifica��o dos valores num�ricos
	for (int i = 0; i < (TAM_CNPJ); i++) {
		if (!(cnpj[i] >= 48 && cnpj[i] <= 57)) {
			dado_valido = 0; // Caso chegou aqui, um caracter do CNPJ n�o � um n�mero.
		}
	}
	
	// Verifica��o do 0001 ou "matriz"
	// Como estamos cadastrando uma usina, e n�o uma filial, o CNPJ ter� somente o 0001.
	for (int i = 8; i < (TAM_CNPJ-4); i++) {
		if (cnpj[i] != '0') dado_valido = 0; // Caso chegou aqui, h� um valor incorreto.
	}
	
	//if (cnpj[TAM_CNPJ-3] != '1') dado_valido = 0; // Caso chegou aqui, h� um valor incorreto.
	
	// Armazenamento dos valores n�mericos do CNPJ
	for (int i = 0; i < (TAM_CNPJ); i++) {
		valores_cnpj[i] = (cnpj[i] - '0'); // Pega os valores num�ricos do CNPJ e guarda num vetor int.
	}
	
	
	
	//Verifica��o dos digitos verificadores:
	
	// Primeiro digito verificador
	
	digito_verificador = 0;
	for (int i = 0; i < TAM_CNPJ-2; i++) {
		// Soma todos os resultados da multiplica��o entre os n�meros do CNPJ e dos respectivos n�meros
		// na posi��es da primeira sequ�ncia de verifica��o.
		digito_verificador = (digito_verificador + (valores_cnpj[i] * sequencia_verificacao1[i]));
	}
	
	digito_verificador = digito_verificador % 11; // Divide o resultado por 11.
	
	if (digito_verificador < 2) { // Resto da divis�o for menor que 2.
		digito_verificador = 0; // Caso chegou aqui, o primeiro digito verificador � 0.
		
	} else { // Resto da divis�o n�o for menor 2.
		digito_verificador = (11 - digito_verificador); // Caso chegou aqui, o primeiro digito verificador � igual a 11 menos o resto.
	}
	
	if (valores_cnpj[TAM_CNPJ-2] != digito_verificador) { // Compara o digito do CNPJ e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o primeiro digito verificador do CNPJ est� incorreto.
	}
	
	// Segundo digito verificador
	
	digito_verificador = 0;
	for (int i = 0; i < TAM_CNPJ-1; i++) {
		// Soma todos os resultados da multiplica��o entre os n�meros do CNPJ e dos respectivos n�meros
		// na posi��es da segunda sequ�ncia de verifica��o.
		digito_verificador = (digito_verificador + (valores_cnpj[i] * sequencia_verificacao2[i]));
	}
	
	digito_verificador = digito_verificador % 11;
	
	if (digito_verificador < 2) { // Resto da divis�o for menor que 2.
		digito_verificador = 0; // Caso chegou aqui, o segundo digito verificador � 0.
		
	} else { // Resto da divis�o n�o for menor 2.
		digito_verificador = (11 - digito_verificador); // Caso chegou aqui, o segundo digito verificador � igual a 11 menos o resto.
	}
	
	if (valores_cnpj[TAM_CNPJ-1] != digito_verificador) { // Compara o digito do CNPJ e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o segundo digito verificador do CNPJ est� incorreto.
	}
	
	return dado_valido;
}

int valida_cpf(char cpf[]) 
{
    //XXX.XXX.XXX-XX
    int dado_valido, j, k;
    int valores_cpf[TAM_CPF];
    int digito_verificador;
    
    dado_valido = 1;
    
    // Verifica��o da estrutura
    
    // Verifica��o do formato
    if (cpf[TAM_CPF] != '\0') {
        dado_valido = 0; // Caso chegou aqui, existem caracteres al�m tamanho m�ximo.
    }
    
    // Verifica��o dos valores n�mericos
    for (int i = 0; i < TAM_CPF; i++) {
    	if (!(cpf[i] >= 48 && cpf[i] <= 57)) {
    		dado_valido = 0; // Caso chegou aqui, existem caracteres que n�o s�o n�meros.
		}
	}
    
    // Armazenamento dos valores n�mericos do CPF
    j = 0;
    for (int i = 0; i < TAM_CPF; i++) {
        if (cpf[i] >= 48 && cpf[i] <= 57) {
            valores_cpf[j] = (cpf[i] - '0'); // Guarda os caracteres num�ricos do CPF em um vetor inteiro
            j++;
        }
    }
    
    
    
    // Verifica��o dos digitos verificadores
    
    // Primeiro digito verificador
    
    k = 10;
    digito_verificador = 0;
    for (int i = 0; i < TAM_CPF-2; i++) {
    	// Soma todos os resultados da multiplica��o entre os n�meros do CPF e dos respectivos n�meros
		// da primeira sequ�ncia de verifica��o.
        digito_verificador = digito_verificador + (valores_cpf[i] * k);
        k--;
    }
    
    digito_verificador = digito_verificador % 11; // Divide o resultado por 11.
    
    if (digito_verificador < 2) { // Se o resto for menor que 2.
    	digito_verificador = 0; // Chegou aqui, o primeiro d�gito verificador � 0. 
	} else { // Se o resto n�o for menor que 2.
		digito_verificador = 11 - digito_verificador; // Caso chegou aqui, o primeiro digito verificador � igual a 11 menos o resto.
	}
    
    if (valores_cpf[TAM_CPF-2] != digito_verificador) { // Compara o digito do CPF e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o primeiro digito verificador do CPF est� incorreto.
	}
    
    // Segundo d�gito verificador
    
    k = 11;
    digito_verificador = 0;
    for (int i = 0; i < TAM_CPF-1; i++) {
    	// Soma todos os resultados da multiplica��o entre os n�meros do CPF e dos respectivos n�meros
		// da segunda sequ�ncia de verifica��o.
		digito_verificador = digito_verificador + (valores_cpf[i] * k);
		k--;
	}
    
    digito_verificador = digito_verificador % 11; // Divide o resultado por 11.
    
    if (digito_verificador < 2) { // Se o resto for menor que 2.
    	digito_verificador = 0; // Chegou aqui, o segundo d�gito verificador � 0.
	} else { // Se o resto n�o for menor que 2.
		digito_verificador = 11 - digito_verificador; // Chegou aqui, o segundo d�gito verificador � igual a 11 menos o resto. 
	}
	
	if (valores_cpf[TAM_CPF-1] != digito_verificador) { // Compara o digito do CPF e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o segundo digito verificador do CPF est� incorreto.
	}
    
    return dado_valido; // Retorna o se o dado � inv�lido (0) ou v�lido (1).
}

void cadastro_usina() // Realiza o cadastro de uma usina
{
    /* Cadastro da usina:
    cnpj - XXXXXXXX0001XX
    nome - literalmente um nome qualquer
    data_inicio_operacao - DD/MM/AA
    potencia_estimada - X(MW)
    */
	
	// Declara��es de vari�veis
	USINA usina_registro; // Vari�vel registro USINA, usada para receber os dados inseridos.
	USINA usina_compara; // Vari�vel registro USINA, usada para verificar o arquivo por usinas j� existentes.

    float potencia_estimada;
    int dado_valido; // Se o valor for 0, � inv�lido, se for 1, � v�lido.
    
    // Instru��es
    limpar_tela();
    
    printf("CADASTRO DE USINA\n");
    printf("\nINFORME OS DADOS -\n");
    
    
    // RECEBIMENTO DE DADOS:
    
    // CNPJ
    do {
    	printf("\nCNPJ: (ATENCAO! Digite apenas numeros!) ");
    	scanf("%s", usina_registro.cnpj); // Recebe o dado do usu�rio.
    	dado_valido = valida_cnpj(usina_registro.cnpj); // Chama a fun��o para verificar o dado.
    	
    	if (dado_valido == 0) {
			printf("FORMATO DE DADO INCORRETO!"); // Se chegou aqui, o dado est� incorreto.
		}
	} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
    
    
    // NOME
    printf("\nNome da Usina: ");
	scanf("%s", usina_registro.nome);
    
	
	
	// DATA DE IN�CIO DE OPERA��O
	do {
		printf("\nData de inicio de operacao (DD/MM/AAAA): ");
		scanf("%s", usina_registro.data); // Recebe o dado do usu�rio.
		dado_valido = valida_data(usina_registro.data); // Chama a fun��o para verificar o dado.
		 
		if (dado_valido == 0) {
			printf("DATA INV�LIDA!"); // Se chegou aqui, o dado est� incorreto.
		}
	} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	
	
	// POT�NCIA ESTIMADA
	do {
		printf("\nPotencia estimada (GW): ");
		scanf("%f", &usina_registro.potencia); // Recebe o dado do usu�rio.
		
		if (usina_registro.potencia <= 0) { // Verifica se a pot�ncia � maior que 0.
			dado_valido = 0; // Se chegou aqui, a pot�ncia � inv�lida.
		} else {
			dado_valido = 1; // Se chegou aqui, a pot�ncia � v�lida.
		}
		
		if (dado_valido == 0) {
			printf("VALOR DE POT�NCIA INV�LIDO!"); // Se chegou aqui, o dado est� incorreto.
		}
		
	} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	
	// ARMAZENAMENTO DOS DADOS EM ARQUIVO:
	
	FILE *arquivo; // Ponteiro do arquivo.
	
	arquivo = fopen("dados.txt", "r+"); // Abre o arquivo.
	
	if (arquivo == NULL) { // Verifica se o arquivo existe.
		fopen("dados.txt", "w+"); // Se n�o existir, cria o arquivo.
	}
	
	//fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no in�cio do arquivo.
	
	fseek(arquivo, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
	fwrite(&usina_registro, sizeof(usina_registro), 1, arquivo); // Guarda os dados no arquivo.
	
	fclose(arquivo); // Fecha o arquivo.
	
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
	
	// Declara��es de vari�veis
	
	CONSUMIDOR consumidor_reg; // Vari�vel tipo CONSUMIDOR, usada para receber os dados inseridos.
	CONSUMIDOR consumidor_com; // Vari�vel tipo CONSUMIDOR, usada para verificar o arquivo por consumidores j� existentes.
	int dado_valido; // Se o valor for 0, � inv�lido, se for 1, � v�lido. 
	
	// Instru��es
	
	limpar_tela();
	printf("CADASTRO DE CONSUMIDOR\n");
	printf("\nINFORME OS DADOS -\n");
	
	
	// RECEBIMENTO DE DADOS:
	
	// IDENTIFICA��O (CPF OU CNPJ)
    do {
    	printf("\nCPF ou CNPJ: (ATENCAO! Digite apenas numeros!) ");
    	scanf("%s", consumidor_reg.id); // Recebe o dado do usu�rio.
    	
    	if (strlen(consumidor_reg.id) == TAM_CNPJ) { // Verifica se o usu�rio digitou um CNPJ.
			dado_valido = valida_cnpj(consumidor_reg.id); // Chama a fun��o para verificar o CNPJ.
		} else if (strlen(consumidor_reg.id) == TAM_CPF) { // Verifica se o usu�rio digitou um CPF.
			dado_valido = valida_cpf(consumidor_reg.id); // Chama a fun��o para verificar o CPF.
		} else {
			dado_valido = 0; // Se chegou aqui, o dado est� em formato incorreto.
		}
    	
    	if (dado_valido == 0) {
			printf("FORMATO DE DADO INCORRETO!"); // Se chegou aqui, o dado est� incorreto.
		}
	} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
    
    
    // NOME
    
    printf("\nNome: ");
    scanf("%s", consumidor_reg.nome);
	
	// ARMAZENAMENTO DOS DADOS:
	
	limpar_tela();
	printf("Consumidor cadastrado com sucesso!\n\n");
}

int main()
{
    int menu_opcao;
    
    printf("SISTEMA DE GESTAO COMPARTILHADA\n\n");
    
    do {
        menu(); // Exibe o menu.
    
        printf("\nOpcao: ");
        scanf("%i", &menu_opcao); // Recebe a op��o do usu�rio.
        
        switch (menu_opcao) { // De acordo com a instru��o do usu�rio, abre a respectiva fun��o.
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
        
    } while (menu_opcao != 8); // Mant�m o programa executando at� o usu�rio encerrar
    
    printf("\nPrograma encerrado!\n");
    
    return 0;
}
