// ***BIBLIOTECA DE FUNÇÕES E DEFINIÇÕES PARA SEREM USADAS NO TRABALHO***

#define TRABALHO_BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

#define CADASTRO_USINA 1
#define CADASTRO_CONSUMIDOR 2
#define CADASTRO_CONTRATO 3
#define CONSULTAR_USINA 4
#define CONSULTAR_CONSUMIDOR 5
#define EXCLUIR_USINA 6
#define EXCLUIR_CONSUMIDOR 7
#define SAIR 8

#define TAM_DATA 10
#define TAM_CNPJ 15
#define TAM_CPF 12
#define TAM_NOME 100

void limpar_tela() // Limpa o terminal
{
	#if defined(linux) || defined(unix) || defined(APPLE)
		system("clear");
	#endif
	
	#if defined(_WIN32) || defined(_WIN64)
		system("cls");
	#endif
}

void menu() // Exibe o menu de opções
{ 
	limpar_tela();
	
	printf("-----------------------------\n");
	printf("SISTEMA DE GERACAO COMPARTILHADA\n");
	printf("-----------------------------\n\n");

    printf("1)Cadastrar Usina\n");
    printf("2)Cadastrar Consumidor\n");
    printf("3)Cadastrar Contrato entre Consumidor e Usina\n");
    printf("4)Consultar Usina Cadastrada\n");
    printf("5)Consultar Consumidor Cadastrado\n");
    printf("6)Excluir Usina\n");
    printf("7)Excluir Consumidor\n");
    printf("8)Encerrar programa\n");
}

typedef struct {
	int dia;
	int mes;
	int ano;
} DATA;

typedef struct {
	char nome[TAM_NOME];
	char cnpj[TAM_CNPJ];
	DATA data;
	float potencia;
} USINA;

typedef struct {
	char nome[TAM_NOME];
	char id[TAM_CNPJ];
} CONSUMIDOR;

typedef struct {
	char cnpj_usina[TAM_CNPJ];
	DATA data;
	char id_con[TAM_CNPJ];
	float potencia;
} CONTRATO;

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
	if (cnpj[TAM_CNPJ-1] != '\0') {
		dado_valido = 0; // Caso chegou aqui, há mais caracteres que o devido.
	}
	
	// Verificação dos valores numéricos
	for (int i = 0; i < (TAM_CNPJ-1); i++) {
		if (!(cnpj[i] >= 48 && cnpj[i] <= 57)) {
			dado_valido = 0; // Caso chegou aqui, um caracter do CNPJ não é um número.
		}
	}
	
	// Verificação do 0001 ou "matriz"
	// Como estamos cadastrando uma usina, e não uma filial, o CNPJ terá somente o 0001.
	for (int i = 8; i < (TAM_CNPJ-5); i++) {
		if (cnpj[i] != '0') dado_valido = 0; // Caso chegou aqui, há um valor incorreto.
	}
	
	//if (cnpj[TAM_CNPJ-3] != '1') dado_valido = 0; // Caso chegou aqui, há um valor incorreto.
	
	// Armazenamento dos valores númericos do CNPJ
	for (int i = 0; i < (TAM_CNPJ-1); i++) {
		valores_cnpj[i] = (cnpj[i] - '0'); // Pega os valores numéricos do CNPJ e guarda num vetor int.
	}
	
	
	
	//Verificação dos digitos verificadores:
	
	// Primeiro digito verificador
	
	digito_verificador = 0;
	for (int i = 0; i < TAM_CNPJ-3; i++) {
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
	
	if (valores_cnpj[TAM_CNPJ-3] != digito_verificador) { // Compara o digito do CNPJ e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o primeiro digito verificador do CNPJ está incorreto.
	}
	
	// Segundo digito verificador
	
	digito_verificador = 0;
	for (int i = 0; i < TAM_CNPJ-2; i++) {
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
	
	if (valores_cnpj[TAM_CNPJ-2] != digito_verificador) { // Compara o digito do CNPJ e o digito encontrado no algoritmo anterior.
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
    if (cpf[TAM_CPF-1] != '\0') {
        dado_valido = 0; // Caso chegou aqui, existem caracteres além tamanho máximo.
    }
    
    // Verificação dos valores númericos
    for (int i = 0; i < TAM_CPF-1; i++) {
    	if (!(cpf[i] >= 48 && cpf[i] <= 57)) {
    		dado_valido = 0; // Caso chegou aqui, existem caracteres que não são números.
		}
	}
    
    // Armazenamento dos valores númericos do CPF
    j = 0;
    for (int i = 0; i < TAM_CPF-1; i++) {
        if (cpf[i] >= 48 && cpf[i] <= 57) {
            valores_cpf[j] = (cpf[i] - '0'); // Guarda os caracteres numéricos do CPF em um vetor inteiro
            j++;
        }
    }
    
    
    
    // Verificação dos digitos verificadores
    
    // Primeiro digito verificador
    
    k = 10;
    digito_verificador = 0;
    for (int i = 0; i < TAM_CPF-3; i++) {
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
    
    if (valores_cpf[TAM_CPF-3] != digito_verificador) { // Compara o digito do CPF e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o primeiro digito verificador do CPF está incorreto.
	}
    
    // Segundo dígito verificador
    
    k = 11;
    digito_verificador = 0;
    for (int i = 0; i < TAM_CPF-2; i++) {
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
	
	if (valores_cpf[TAM_CPF-2] != digito_verificador) { // Compara o digito do CPF e o digito encontrado no algoritmo anterior.
		dado_valido = 0; // Caso chegou aqui, o segundo digito verificador do CPF está incorreto.
	}
    
    return dado_valido; // Retorna o se o dado é inválido (0) ou válido (1).
}

void listar_usinas() // Lista todas as usinas cadastradas.
{
	/*
	USINAS CADASTRADAS:
	-------------------------------
	NOME1:
	NOME2:
	-------------------------------
	*/

	// Declarações de variáveis
	FILE *arq_usinas; // Ponteiro do arquivo.
	USINA usina_ler; // Variável tipo USINA, usada para ler os dados do arquivo.

	// Instruções

	printf("USINAS CADASTRADAS:\n");

	printf("-------------------------------------------------------\n");

	arq_usinas = fopen("usinas.txt", "rb"); // Abre o arquivo.
	fseek(arq_usinas, 0, SEEK_SET); // Coloca o ponteiro no início do arquivo.

	while (!feof(arq_usinas)) { // Executa até o final do arquivo.
		fread(&usina_ler, sizeof(USINA), 1, arq_usinas); // Lê toda a struct.
		if (!feof(arq_usinas)) { // Executa se ainda não for o final do arquivo.
			printf("NOME: %s\n", usina_ler.nome); // Printa o nome.
			printf("-------------------------------------------------------\n");
		}
	}

	fclose(arq_usinas); // Fecha o arquivo de usinas.
}

void listar_consumidores() // Lista todos os consumidores localizados.
{
	/*
	CONSUMIDORES CADASTRADOS:
	--------------------------
	NOME1:
	NOME2:
	--------------------------
	*/

	// Declarações de variáveis
	FILE *arq_consum; // Ponteiro do arquivo.
	CONSUMIDOR consum_ler; // Variável tipo CONSUMIDOR, usada para ler os dados do arquivo.

	// Instruções

	printf("CONSUMIDORES CADASTRADOS:\n");

	printf("-------------------------------------------------------\n");

	arq_consum = fopen("consumidores.txt", "rb"); // Abre o arquivo.
	fseek(arq_consum, 0, SEEK_SET); // Coloca o ponteiro no início do arquivo.

	while (!feof(arq_consum)) { // Executa até o final do arquivo.
		fread(&consum_ler, sizeof(CONSUMIDOR), 1, arq_consum); // Lê toda a struct.
		if (!feof(arq_consum)) { // Executa se ainda não for o final do arquivo.
			printf("NOME: %s\n", consum_ler.nome); // Printa o nome.
			printf("-------------------------------------------------------\n");
		}
	}

	fclose(arq_consum); // Fecha o arquivo de consumidores.
}

int localizar_usina(char cnpj_usina[]) // Localiza uma usina a partir do CNPJ.
{
	/* LOCALIZAR USINA
	Essa função tenta localizar uma usina a partir de um CNPJ inserido
	Returna 1 se localizar e 0 se não localizar.
	*/

	// Declaração de variáveis
	FILE *arq_usinas; // Ponteiro do arquivo de usinas.
	
	USINA usina_ler; // Variável tipo USINA, usada para ler os dados.

	int usina_localizada; // Recebe 1 se a usina for localizada e 0 se não

	// Localização da usina:
	arq_usinas = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas.

	if (arq_usinas != NULL) { // Executar apenas se o arquivo existir.
		fseek(arq_usinas, 0, SEEK_SET); // Coloca o ponteiro no início do arquivo.

		usina_localizada = 0;
		while (!feof(arq_usinas)) { // Executa até o fim do arquivo.
			fread(&usina_ler, sizeof(USINA), 1, arq_usinas); // Lê toda a struct da usina.
			if (strstr(usina_ler.cnpj, cnpj_usina) != 0) {
				// Se chegou aqui, a usina foi identificada.
				usina_localizada = 1;
				break;
			}
		}
	}

	fclose(arq_usinas);

	return usina_localizada;
}

int localizar_consumidor(char id_consumidor[]) // Localiza um consumidor apartir da identificação.
{
	/* LOCALIZAR CONSUMIDOR
	Essa função tenta localizar um consumidor a partir de um CNPJ ou CPF inserido
	Returna 1 se localizar e 0 se não localizar.
	*/

	// Declaração de variáveis
	FILE *arq_consum; // Ponteiro do arquivo de consumidor.
	
	CONSUMIDOR consum_ler; // Variável tipo CONSUMIDOR, usada para ler os dados.

	int consum_localizado; // Recebe 1 se o consumidor for localizada e 0 se não

	// Localização do consumidor:
	arq_consum = fopen("consumidores.txt", "rb"); // Abre o arquivo de consumidores.

	if (arq_consum != NULL) { // Executar apenas se o arquivo existir.
		fseek(arq_consum, 0, SEEK_SET); // Coloca o ponteiro no início do arquivo.

		consum_localizado = 0;
		while (!feof(arq_consum)) { // Executa até o fim do arquivo.
			fread(&consum_ler, sizeof(CONSUMIDOR), 1, arq_consum); // Lê toda a struct da consumidor.
			if (strstr(consum_ler.id, id_consumidor) != 0) {
				// Se chegou aqui, o consumidor foi identificada.
				consum_localizado = 1;
				break;
			}
		}
	}

	fclose(arq_consum);

	return consum_localizado;
}
