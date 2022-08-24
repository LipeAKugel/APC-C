// SISTEMA DE GEST�O COMPARTILHADA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho_biblioteca.h"

int valida_data(DATA data) // Verifica data.
{
	// Fun��o que verifica a valida��o da data
	// DD MM AAAA
	
	int dado_valido;
	int valor_dia, valor_mes, valor_ano;
	
	dado_valido = 1;
	
	// Recebe os valores da data
	valor_dia = data.dia;
	valor_mes = data.mes;
	valor_ano = data.ano;
	
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
	
	return dado_valido;
	} 

int valida_cnpj(char cnpj[]) // Verifica CNPJ.
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

int valida_cpf(char cpf[]) // Verifica CPF.
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

void cadastro_usina() // Realiza o cadastro de uma usina.
{
    /* Cadastro da usina:
    cnpj - XXXXXXXX0001XX
    nome - literalmente um nome qualquer
    data_inicio_operacao - DD/MM/AA
    potencia_estimada - X(MW)
    */
	
	// Declara��es de vari�veis
	USINA usina_rg; // Vari�vel registro USINA, usada para receber os dados inseridos.
	USINA usina_cm; // Vari�vel registro USINA, usada para verificar o arquivo por usinas j� existentes.

    int dado_valido; // Se o valor for 0, � inv�lido, se for 1, � v�lido.
    int usina_ex; // Recebe 1 se a usina j� existir no banco de dados, e 0 se n�o.
    
    // Instru��es
    do {
	    limpar_tela();
	    
	    printf("-----------------------------\n");
	    printf("CADASTRO DE USINA\n");
	    printf("-----------------------------\n");
	    
	    printf("\nINFORME OS DADOS:\n\n");
	    
	    
	    // RECEBIMENTO DE DADOS:
	    
	    // CNPJ
	    do {
	    	printf("CNPJ: (Apenas numeros) ");
	    	fflush(stdin); // Limpa o buffer.
	    	gets(usina_rg.cnpj); // Recebe o dado do usu�rio.
	    	dado_valido = valida_cnpj(usina_rg.cnpj); // Chama a fun��o para verificar o dado.
	    	
	    	if (dado_valido == 0) {
				printf("FORMATO DE DADO INCORRETO!\n"); // Se chegou aqui, o dado est� incorreto.
			}
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	    
	    
	    // NOME
	    printf("Nome da Usina: ");
	    fflush(stdin); // Limpa o buffer.
		gets(usina_rg.nome); // Recebe o dado do usu�rio.
	    
		
		
		// DATA DE IN�CIO DE OPERA��O
		do {
			printf("Data de inicio de operacao (DD MM AAAA): ");
			scanf("%d %d %d", &usina_rg.data.dia, &usina_rg.data.mes, &usina_rg.data.ano); // Recebe o dado do usu�rio.
			dado_valido = valida_data(usina_rg.data); // Chama a fun��o para verificar o dado.
			 
			if (dado_valido == 0) {
				printf("DATA INV�LIDA!\n"); // Se chegou aqui, o dado est� incorreto.
			}
			
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
		
		
		// POT�NCIA ESTIMADA
		do {
			printf("Potencia estimada (GW): ");
			scanf("%f", &usina_rg.potencia); // Recebe o dado do usu�rio.
			
			if (usina_rg.potencia <= 0) { // Verifica se a pot�ncia � maior que 0.
				dado_valido = 0; // Se chegou aqui, a pot�ncia � inv�lida.
			} else {
				dado_valido = 1; // Se chegou aqui, a pot�ncia � v�lida.
			}
			
			if (dado_valido == 0) {
				printf("VALOR DE POT�NCIA INV�LIDO!\n"); // Se chegou aqui, o dado est� incorreto.
			}
			
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
		
		
		// ARMAZENAMENTO DOS DADOS EM ARQUIVO:
		
		FILE *arquivo; // Ponteiro do arquivo.
		
		arquivo = fopen("usinas.txt", "ab"); // Abre o arquivo.
		
		if (arquivo == NULL) { // Verifica se foi poss�vel abrir o arquivo.
			printf("\nN�o foi poss�vel salvar os dados!\n"); // Se n�o foi poss�vel, exibe uma mensagem de erro.
		}
		
		fclose(arquivo); // Fecha o arquivo.
		
		if (arquivo != NULL) {
			
			// VERIFICA��O DE CONFLITO DE DADOS
			arquivo = fopen("usinas.txt", "rb"); // Abre o arquivo para leitura.
			fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no in�cio do arquivo.
			
			usina_ex = 0;
			while (!feof(arquivo)) { // Executa at� o fim do arquivo.
				fread(&usina_cm, sizeof(USINA), 1, arquivo); // L� a struct da usina no arquivo.
				
				if(strstr(usina_cm.cnpj, usina_rg.cnpj) != 0) {
					usina_ex = 1; // Se chegou aqui, a usina inserida j� foi cadastrada anteriormente.
					printf("\nNao foi poss�vel cadastrar\n"); 
					printf("CNPJ j� cadastrado!\n");
					break;
				}
			}
			
			fclose(arquivo); // Fecha o arquivo.
			
			// ARMAZENAMENTO DOS DADOS
			arquivo = fopen("usinas.txt", "ab"); // Abre o arquivo para escrita.
			if (usina_ex != 1) { // Se a usina j� n�o tiver sido cadastrada, armazene os dados.
				fseek(arquivo, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
				fwrite(&usina_rg, sizeof(USINA), 1, arquivo); // Guarda os dados no arquivo.
			
				printf("\nUsina cadastrada com sucesso!\n");
			}
		}
		
		fclose(arquivo); // Fecha o arquivo.
		
		printf("\nDeseja continuar [s/n]?\n");
	} while (getche() == 's' || getche() == 'S');
}

void cadastro_consumidor() // Realiza o cadastro de um consumidor.
{
	/* Cadastro do consumidor:
	cpf - XXXXXXXXXYY
	cnpj - XXXXXXXX000XXX
	nome - literalmente qualquer nome
	*/
	
	// Declara��es de vari�veis
	
	CONSUMIDOR consum_rg; // Vari�vel tipo CONSUMIDOR, usada para receber os dados inseridos.
	CONSUMIDOR consum_cm; // Vari�vel tipo CONSUMIDOR, usada para verificar conflitos de CPF ou CNPJ (identifica��o).
	USINA usina_cm; // Vari�vel tipo USINA, usada para verificar conflitos de CNPJ.
	
	int dado_valido; // Se o valor for 0, � inv�lido, se for 1, � v�lido.
	int consum_ex; // Recebe 1 se o consumidor j� existir no banco de dados, e 0 se n�o.
	
	// Instru��es
	
	do {
		limpar_tela();
		    
		    printf("-----------------------------\n");
		    printf("CADASTRO DE CONSUMIDOR\n");
		    printf("-----------------------------\n");
		    
		    printf("\nINFORME OS DADOS:\n\n");
		
		
		// RECEBIMENTO DE DADOS:
		
		// IDENTIFICA��O (CPF OU CNPJ)
	    do {
	    	printf("CPF ou CNPJ: (Apenas numeros) ");
	    	fflush(stdin); // Limpa o buffer
	    	gets(consum_rg.id); // Recebe o dado do usu�rio.
	    	
	    	if (strlen(consum_rg.id) == TAM_CNPJ) { // Verifica se o usu�rio digitou um CNPJ.
				dado_valido = valida_cnpj(consum_rg.id); // Chama a fun��o para verificar o CNPJ.
			} else if (strlen(consum_rg.id) == TAM_CPF) { // Verifica se o usu�rio digitou um CPF.
				dado_valido = valida_cpf(consum_rg.id); // Chama a fun��o para verificar o CPF.
			} else {
				dado_valido = 0; // Se chegou aqui, o dado est� em formato incorreto.
			}
	    	
	    	if (dado_valido == 0) {
				printf("FORMATO DE DADO INCORRETO!"); // Se chegou aqui, o dado est� incorreto.
			}
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	
		
		// NOME
		    printf("Nome do consumidor: ");
		    fflush(stdin); // Limpa o buffer.
			gets(consum_rg.nome); // Recebe o dado do usu�rio.
			
			
		// ARMAZENAMENTO DOS DADOS EM ARQUIVO:
		
		FILE *arquivo; // Ponteiro do arquivo.
		
		arquivo = fopen("consumidores.txt", "ab"); // Abre o arquivo.
		
		if (arquivo == NULL) { // Verifica se foi poss�vel abrir o arquivo.
			printf("\nN�o foi poss�vel salvar os dados!\n"); // Se n�o foi poss�vel, exibe uma mensagem de erro.
		}
		
		fclose(arquivo); // Fecha o arquivo.
		
		if (arquivo != NULL) {
			
			// VERIFICA��O DE CONFLITO DE DADOS
			arquivo = fopen("consumidores.txt", "rb"); // Abre o arquivo para leitura.
			fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no in�cio do arquivo.
			
			consum_ex = 0;
			while (!feof(arquivo)) { // Executa at� o fim do arquivo de consumidores.
				fread(&consum_cm, sizeof(CONSUMIDOR), 1, arquivo); // L� a struct do consumidor no arquivo.
				
				if(strstr(consum_cm.id, consum_rg.id) != 0) {
					consum_ex = 1; // Se chegou aqui, o CPF ou CNPJ inserido j� foi cadastrado anteriormente.
					break;
				}
			}
			
			arquivo = fopen("usinas.txt", "rb"); // Abre o arquivo para leitura.
			fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no in�cio do arquivo.
			
			while (!feof(arquivo)) { // Executa at� o fim do arquivo de usinas.
				fread(&usina_cm, sizeof(USINA), 1, arquivo); // L� a struct da usina no arquivo.
				
				if(strstr(usina_cm.cnpj, consum_rg.id) != 0) {
					consum_ex = 1; // Se chegou aqui, o CNPJ inserido j� foi cadastrado anteriormente.
					break;
				}
			}
			
			if (consum_ex == 1) { // Exibir mensagem de erro para o usu�rio.
					printf("\nNao foi possivel cadastrar\n"); 
					printf("CNPJ/CPF ja cadastrado!\n");
			}
			
			fclose(arquivo); // Fecha o arquivo.
			
			// ARMAZENAMENTO DOS DADOS
			arquivo = fopen("consumidores.txt", "ab"); // Abre o arquivo para escrita.
			if (consum_ex != 1) { // Se o consumidor j� n�o tiver sido cadastrado, armazene os dados.
				fseek(arquivo, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
				fwrite(&consum_rg, sizeof(CONSUMIDOR), 1, arquivo); // Guarda os dados no arquivo.
			
				printf("\nConsumidor cadastrado com sucesso!\n");
			}
		}
		
		fclose(arquivo); // Fecha o arquivo.
		
		printf("\nDeseja continuar [s/n]?\n");
	} while (getch() == 's' || getch() == 'S');
}

void cadastro_contrato() // Realiza o cadastro de um contrato.
{
	/* Cadastro de contrato:
    cnpj_usina - XXXXXXXX0001XX
    id_consumidor - literalmente um nome qualquer
    data_inicio_contrato - DD MM AAAA
    potencia_contratada - X(MW)
    */
    
    // Declara��es de vari�veis
    FILE *arquivo; // Ponteiro do arquivo.
    
    CONTRATO contrato_rg; // Vari�vel tipo CONTRATO, usada para receber os dados.
    USINA usina_cm; // Vari�vel tipo USINA, usada para comparar dados da usina. 
    CONSUMIDOR consum_cm; // Vari�vel tipo CONSUMIDOR, usada para comparar dados do consumidor.
    
    int dado_valido; // Se o valor for 0, � inv�lido, se for 1, � v�lido.
    
    // Instru��es
    
    do {
    	limpar_tela();
	    
	    printf("-----------------------------\n");
	    printf("CADASTRO DE CONTRATO\n");
	    printf("-----------------------------\n");
	    
	    printf("\nINFORME OS DADOS:\n\n");
	    
	    
	    // RECEBIMENTO DE DADOS:
	    
	    // CNPJ DA USINA
	    do {
	    	printf("CNPJ da usina: ");
	    	fflush(stdin); // Limpa o buffer.
	    	gets(contrato_rg.cnpj_usina); // Recebe o dado do usu�rio.
	    	
	    	// Verifica��o da usina
	    	arquivo = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas para leitura.
	    	
	    	dado_valido = 0;
	    	while (!feof(arquivo)) { // Executa at� o fim do arquivo
	    		fread(&usina_cm, sizeof(USINA), 1, arquivo); // L� a struct da usina no arquivo.
	    		
	    		if(strstr(usina_cm.cnpj, contrato_rg.cnpj_usina) != 0) { // Compara o CNPJ da usina lida e o CNPJ inserido.
					dado_valido = 1; // Se chegou aqui, a usina existe.
					break;
				}
			}
			
			if (dado_valido == 0) {
				printf("N�o existe usina com esse CNPJ!\n");
			}
	    	
		} while (dado_valido == 0);
		
	    // ID DO CONSUMIDOR
	    // DATA DE IN�CIO DO CONTRATO
	    // POT�NCIA CONTRATADA
	    
	    
	    // ARMAZENAMENTO DO CONTRATO EM ARQUIVO:
	    
	    printf("\nDeseja continuar [s/n]?\n");
	} while (getche() == 's' || getche() == 'S');
}

int main()
{
    int menu_opcao;
    
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
                cadastro_contrato();
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
