// SISTEMA DE GESTÃO COMPARTILHADA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho_biblioteca.h"

int valida_data(DATA data) // Verifica data.
{
	// Função que verifica a validação da data
	// DD MM AAAA
	
	int dado_valido;
	int valor_dia, valor_mes, valor_ano;
	
	dado_valido = 1;
	
	// Recebe os valores da data
	valor_dia = data.dia;
	valor_mes = data.mes;
	valor_ano = data.ano;
	
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
	
	return dado_valido;
	} 

int valida_cnpj(char cnpj[]) // Verifica CNPJ.
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

int valida_cpf(char cpf[]) // Verifica CPF.
{
    //XXX.XXX.XXX-XX
    int dado_valido, j, k;
    int valores_cpf[TAM_CPF];
    int digito_verificador;
    
    dado_valido = 1;
    
    // Verificação da estrutura
    
    // Verificação do formato
    if (cpf[TAM_CPF] != '\0') {
        dado_valido = 0; // Caso chegou aqui, existem caracteres além tamanho máximo.
    }
    
    // Verificação dos valores númericos
    for (int i = 0; i < TAM_CPF; i++) {
    	if (!(cpf[i] >= 48 && cpf[i] <= 57)) {
    		dado_valido = 0; // Caso chegou aqui, existem caracteres que não são números.
		}
	}
    
    // Armazenamento dos valores númericos do CPF
    j = 0;
    for (int i = 0; i < TAM_CPF; i++) {
        if (cpf[i] >= 48 && cpf[i] <= 57) {
            valores_cpf[j] = (cpf[i] - '0'); // Guarda os caracteres numéricos do CPF em um vetor inteiro
            j++;
        }
    }
    
    
    
    // Verificação dos digitos verificadores
    
    // Primeiro digito verificador
    
    k = 10;
    digito_verificador = 0;
    for (int i = 0; i < TAM_CPF-2; i++) {
    	// Soma todos os resultados da multiplicação entre os números do CPF e dos respectivos números
		// da primeira sequência de verificação.
        digito_verificador = digito_verificador + (valores_cpf[i] * k);
        k--;
    }
    
    digito_verificador = digito_verificador % 11; // Divide o resultado por 11.
    
    if (digito_verificador < 2) { // Se o resto for menor que 2.
    	digito_verificador = 0; // Chegou aqui, o primeiro dígito verificador é 0. 
	} else { // Se o resto não for menor que 2.
		digito_verificador = 11 - digito_verificador; // Caso chegou aqui, o primeiro digito verificador é igual a 11 menos o resto.
	}
    
    if (valores_cpf[TAM_CPF-2] != digito_verificador) { // Compara o digito do CPF e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o primeiro digito verificador do CPF está incorreto.
	}
    
    // Segundo dígito verificador
    
    k = 11;
    digito_verificador = 0;
    for (int i = 0; i < TAM_CPF-1; i++) {
    	// Soma todos os resultados da multiplicação entre os números do CPF e dos respectivos números
		// da segunda sequência de verificação.
		digito_verificador = digito_verificador + (valores_cpf[i] * k);
		k--;
	}
    
    digito_verificador = digito_verificador % 11; // Divide o resultado por 11.
    
    if (digito_verificador < 2) { // Se o resto for menor que 2.
    	digito_verificador = 0; // Chegou aqui, o segundo dígito verificador é 0.
	} else { // Se o resto não for menor que 2.
		digito_verificador = 11 - digito_verificador; // Chegou aqui, o segundo dígito verificador é igual a 11 menos o resto. 
	}
	
	if (valores_cpf[TAM_CPF-1] != digito_verificador) { // Compara o digito do CPF e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o segundo digito verificador do CPF está incorreto.
	}
    
    return dado_valido; // Retorna o se o dado é inválido (0) ou válido (1).
}

void cadastro_usina() // Realiza o cadastro de uma usina.
{
    /* Cadastro da usina:
    cnpj - XXXXXXXX0001XX
    nome - literalmente um nome qualquer
    data_inicio_operacao - DD/MM/AA
    potencia_estimada - X(MW)
    */
	
	// Declarações de variáveis
	USINA usina_rg; // Variável registro USINA, usada para receber os dados inseridos.
	USINA usina_cm; // Variável registro USINA, usada para verificar o arquivo por usinas já existentes.

    int dado_valido; // Se o valor for 0, é inválido, se for 1, é válido.
    int usina_ex; // Recebe 1 se a usina já existir no banco de dados, e 0 se não.
    
    // Instruções
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
	    	gets(usina_rg.cnpj); // Recebe o dado do usuário.
	    	dado_valido = valida_cnpj(usina_rg.cnpj); // Chama a função para verificar o dado.
	    	
	    	if (dado_valido == 0) {
				printf("FORMATO DE DADO INCORRETO!\n"); // Se chegou aqui, o dado está incorreto.
			}
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	    
	    
	    // NOME
	    printf("Nome da Usina: ");
	    fflush(stdin); // Limpa o buffer.
		gets(usina_rg.nome); // Recebe o dado do usuário.
	    
		
		
		// DATA DE INÍCIO DE OPERAÇÃO
		do {
			printf("Data de inicio de operacao (DD MM AAAA): ");
			scanf("%d %d %d", &usina_rg.data.dia, &usina_rg.data.mes, &usina_rg.data.ano); // Recebe o dado do usuário.
			dado_valido = valida_data(usina_rg.data); // Chama a função para verificar o dado.
			 
			if (dado_valido == 0) {
				printf("DATA INVÁLIDA!\n"); // Se chegou aqui, o dado está incorreto.
			}
			
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
		
		
		// POTÊNCIA ESTIMADA
		do {
			printf("Potencia estimada (GW): ");
			scanf("%f", &usina_rg.potencia); // Recebe o dado do usuário.
			
			if (usina_rg.potencia <= 0) { // Verifica se a potência é maior que 0.
				dado_valido = 0; // Se chegou aqui, a potência é inválida.
			} else {
				dado_valido = 1; // Se chegou aqui, a potência é válida.
			}
			
			if (dado_valido == 0) {
				printf("VALOR DE POTÊNCIA INVÁLIDO!\n"); // Se chegou aqui, o dado está incorreto.
			}
			
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
		
		
		// ARMAZENAMENTO DOS DADOS EM ARQUIVO:
		
		FILE *arquivo; // Ponteiro do arquivo.
		
		arquivo = fopen("usinas.txt", "ab"); // Abre o arquivo.
		
		if (arquivo == NULL) { // Verifica se foi possível abrir o arquivo.
			printf("\nNão foi possível salvar os dados!\n"); // Se não foi possível, exibe uma mensagem de erro.
		}
		
		fclose(arquivo); // Fecha o arquivo.
		
		if (arquivo != NULL) {
			
			// VERIFICAÇÃO DE CONFLITO DE DADOS
			arquivo = fopen("usinas.txt", "rb"); // Abre o arquivo para leitura.
			fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.
			
			usina_ex = 0;
			while (!feof(arquivo)) { // Executa até o fim do arquivo.
				fread(&usina_cm, sizeof(USINA), 1, arquivo); // Lê a struct da usina no arquivo.
				
				if(strstr(usina_cm.cnpj, usina_rg.cnpj) != 0) {
					usina_ex = 1; // Se chegou aqui, a usina inserida já foi cadastrada anteriormente.
					printf("\nNao foi possível cadastrar\n"); 
					printf("CNPJ já cadastrado!\n");
					break;
				}
			}
			
			fclose(arquivo); // Fecha o arquivo.
			
			// ARMAZENAMENTO DOS DADOS
			arquivo = fopen("usinas.txt", "ab"); // Abre o arquivo para escrita.
			if (usina_ex != 1) { // Se a usina já não tiver sido cadastrada, armazene os dados.
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
	
	// Declarações de variáveis
	
	CONSUMIDOR consum_rg; // Variável tipo CONSUMIDOR, usada para receber os dados inseridos.
	CONSUMIDOR consum_cm; // Variável tipo CONSUMIDOR, usada para verificar conflitos de CPF ou CNPJ (identificação).
	USINA usina_cm; // Variável tipo USINA, usada para verificar conflitos de CNPJ.
	
	int dado_valido; // Se o valor for 0, é inválido, se for 1, é válido.
	int consum_ex; // Recebe 1 se o consumidor já existir no banco de dados, e 0 se não.
	
	// Instruções
	
	do {
		limpar_tela();
		    
		    printf("-----------------------------\n");
		    printf("CADASTRO DE CONSUMIDOR\n");
		    printf("-----------------------------\n");
		    
		    printf("\nINFORME OS DADOS:\n\n");
		
		
		// RECEBIMENTO DE DADOS:
		
		// IDENTIFICAÇÃO (CPF OU CNPJ)
	    do {
	    	printf("CPF ou CNPJ: (Apenas numeros) ");
	    	fflush(stdin); // Limpa o buffer
	    	gets(consum_rg.id); // Recebe o dado do usuário.
	    	
	    	if (strlen(consum_rg.id) == TAM_CNPJ) { // Verifica se o usuário digitou um CNPJ.
				dado_valido = valida_cnpj(consum_rg.id); // Chama a função para verificar o CNPJ.
			} else if (strlen(consum_rg.id) == TAM_CPF) { // Verifica se o usuário digitou um CPF.
				dado_valido = valida_cpf(consum_rg.id); // Chama a função para verificar o CPF.
			} else {
				dado_valido = 0; // Se chegou aqui, o dado está em formato incorreto.
			}
	    	
	    	if (dado_valido == 0) {
				printf("FORMATO DE DADO INCORRETO!"); // Se chegou aqui, o dado está incorreto.
			}
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	
		
		// NOME
		    printf("Nome do consumidor: ");
		    fflush(stdin); // Limpa o buffer.
			gets(consum_rg.nome); // Recebe o dado do usuário.
			
			
		// ARMAZENAMENTO DOS DADOS EM ARQUIVO:
		
		FILE *arquivo; // Ponteiro do arquivo.
		
		arquivo = fopen("consumidores.txt", "ab"); // Abre o arquivo.
		
		if (arquivo == NULL) { // Verifica se foi possível abrir o arquivo.
			printf("\nNão foi possível salvar os dados!\n"); // Se não foi possível, exibe uma mensagem de erro.
		}
		
		fclose(arquivo); // Fecha o arquivo.
		
		if (arquivo != NULL) {
			
			// VERIFICAÇÃO DE CONFLITO DE DADOS
			arquivo = fopen("consumidores.txt", "rb"); // Abre o arquivo para leitura.
			fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.
			
			consum_ex = 0;
			while (!feof(arquivo)) { // Executa até o fim do arquivo de consumidores.
				fread(&consum_cm, sizeof(CONSUMIDOR), 1, arquivo); // Lê a struct do consumidor no arquivo.
				
				if(strstr(consum_cm.id, consum_rg.id) != 0) {
					consum_ex = 1; // Se chegou aqui, o CPF ou CNPJ inserido já foi cadastrado anteriormente.
					break;
				}
			}
			
			arquivo = fopen("usinas.txt", "rb"); // Abre o arquivo para leitura.
			fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.
			
			while (!feof(arquivo)) { // Executa até o fim do arquivo de usinas.
				fread(&usina_cm, sizeof(USINA), 1, arquivo); // Lê a struct da usina no arquivo.
				
				if(strstr(usina_cm.cnpj, consum_rg.id) != 0) {
					consum_ex = 1; // Se chegou aqui, o CNPJ inserido já foi cadastrado anteriormente.
					break;
				}
			}
			
			if (consum_ex == 1) { // Exibir mensagem de erro para o usuário.
					printf("\nNao foi possivel cadastrar\n"); 
					printf("CNPJ/CPF ja cadastrado!\n");
			}
			
			fclose(arquivo); // Fecha o arquivo.
			
			// ARMAZENAMENTO DOS DADOS
			arquivo = fopen("consumidores.txt", "ab"); // Abre o arquivo para escrita.
			if (consum_ex != 1) { // Se o consumidor já não tiver sido cadastrado, armazene os dados.
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
    
    // Declarações de variáveis
    FILE *arquivo; // Ponteiro do arquivo.
    
    CONTRATO contrato_rg; // Variável tipo CONTRATO, usada para receber os dados.
    USINA usina_cm; // Variável tipo USINA, usada para comparar dados da usina. 
    CONSUMIDOR consum_cm; // Variável tipo CONSUMIDOR, usada para comparar dados do consumidor.
    
    int dado_valido; // Se o valor for 0, é inválido, se for 1, é válido.
    
    // Instruções
    
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
	    	gets(contrato_rg.cnpj_usina); // Recebe o dado do usuário.
	    	
	    	// Verificação da usina
	    	arquivo = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas para leitura.
	    	
	    	dado_valido = 0;
	    	while (!feof(arquivo)) { // Executa até o fim do arquivo
	    		fread(&usina_cm, sizeof(USINA), 1, arquivo); // Lê a struct da usina no arquivo.
	    		
	    		if(strstr(usina_cm.cnpj, contrato_rg.cnpj_usina) != 0) { // Compara o CNPJ da usina lida e o CNPJ inserido.
					dado_valido = 1; // Se chegou aqui, a usina existe.
					break;
				}
			}
			
			if (dado_valido == 0) {
				printf("Não existe usina com esse CNPJ!\n");
			}
	    	
		} while (dado_valido == 0);
		
	    // ID DO CONSUMIDOR
	    // DATA DE INÍCIO DO CONTRATO
	    // POTÊNCIA CONTRATADA
	    
	    
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
        scanf("%i", &menu_opcao); // Recebe a opção do usuário.
        
        switch (menu_opcao) { // De acordo com a instrução do usuário, abre a respectiva função.
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
        
    } while (menu_opcao != 8); // Mantém o programa executando até o usuário encerrar
    
    printf("\nPrograma encerrado!\n");
    
    return 0;
}
