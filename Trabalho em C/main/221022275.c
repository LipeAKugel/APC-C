/* ****** SISTEMA DE GERAÇÃO COMPARTILHADA *******
 Aluno: Felipe Amorim de Araújo
 Matrícula: 221022275
*/

#include "221022275.h"

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

	NOME1:
	CNPJ1:
	----------------------------
	NOME2:
	CNPJ2:
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
			printf("CNPJ: %s\n", usina_ler.cnpj); // Printa o CNPJ.
			printf("-------------------------------------------------------\n");
		}
	}

	fclose(arq_usinas); // Fecha o arquivo de usinas.
}

void listar_consumidores() // Lista todos os consumidores localizados.
{
	/*
	CONSUMIDORES CADASTRADOS:

	NOME1:
	IDENTIFICACAO1:
	----------------------------
	NOME2:
	IDENTIFICACAO2:
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
			printf("ID: %s\n", consum_ler.id); // Printa a identificação.
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

	fclose(arq_consum);

	return consum_localizado;
}

// FUNÇÕES PRINCIPAIS DO PROGRAMA:

void cadastro_usina() // Realiza o cadastro de uma usina.
{
    /* Cadastro da usina:
    cnpj - XXXXXXXX0001XX
    nome - literalmente um nome qualquer
    data_inicio_operacao - DD/MM/AA
    potencia_estimada - X(MW)
    */
	
	// Declarações de variáveis
	USINA usina_rg; // Variável tipo USINA, usada para receber os dados inseridos.
	USINA usina_cm; // Variável tipo USINA, usada para comparar os dados.
	CONSUMIDOR consum_cm; // Variável tipo CONSUMIDOR, usada para comparar os dados. 

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
	    	scanf("%[^\n]", usina_rg.cnpj); // Recebe o dado do usuário.
	    	dado_valido = valida_cnpj(usina_rg.cnpj); // Chama a função para verificar o dado.
	    	
	    	if (dado_valido == 0) {
				printf("CNPJ INCORRETO!\n"); // Se chegou aqui, o dado está incorreto.
			}
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	    
	    
	    // NOME
	    printf("Nome da Usina: ");
		fflush(stdin); // Limpa o buffer.
		scanf("%[^\n]", usina_rg.nome); // Recebe o dado do usuário.
		
		
		// DATA DE INÍCIO DE OPERAÇÃO
		do {
			printf("Data de inicio de operacao (DD MM AAAA): ");
			fflush(stdin); // Limpa o buffer.
			scanf("%d %d %d", &usina_rg.data.dia, &usina_rg.data.mes, &usina_rg.data.ano); // Recebe o dado do usuário.
			dado_valido = valida_data(usina_rg.data); // Chama a função para verificar o dado.
			 
			if (dado_valido == 0) {
				printf("DATA INVALIDA!\n"); // Se chegou aqui, o dado está incorreto.
			}
			
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
		
		
		// POTÊNCIA ESTIMADA
		do {
			printf("Potencia estimada (MW): ");
			fflush(stdin); // Limpa o buffer.
			scanf("%f", &usina_rg.potencia); // Recebe o dado do usuário.
			
			if (usina_rg.potencia <= 0) { // Verifica se a potência é maior que 0.
				dado_valido = 0; // Se chegou aqui, a potência é inválida.
			} else {
				dado_valido = 1; // Se chegou aqui, a potência é válida.
			}
			
			if (dado_valido == 0) {
				printf("VALOR DE POTENCIA INVALIDO!\n"); // Se chegou aqui, o dado está incorreto.
			}
			
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
		
		
		// ARMAZENAMENTO DOS DADOS EM ARQUIVO:
		
		FILE *arq_usinas; // Ponteiro do arquivo de usinas.
		FILE *arq_consum; // Ponteiro do arquivo de usinas.

		// VERIFICAÇÃO DE CONFLITO DE DADOS

		usina_ex = 0;

		//Consumidores:
		arq_consum = fopen("consumidores.txt", "rb"); // Abre o arquivo para leitura.

		if (arq_consum != NULL) {
			// Se chegou aqui o arquivo de consumidores existe.
			fseek(arq_consum, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.
			
			while (!feof(arq_consum)) { // Executa até o fim do arquivo.
				fread(&consum_cm, sizeof(CONSUMIDOR), 1, arq_consum); // Lê a struct do consumidor no arquivo.
				if(strstr(consum_cm.id, usina_rg.cnpj) != 0) {
					usina_ex = 1; // Se chegou aqui, o CNPJ inserido já foi cadastrada anteriormente.
					break;
				}
			}
		}

		fclose (arq_consum); // Fecha o arquivo.

		// Usinas:
		arq_usinas = fopen("usinas.txt", "rb"); // Abre o arquivo para leitura.

		if (arq_usinas != NULL) {
			// Se chegou aqui o arquivo de usinas existe.
			fseek(arq_usinas, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.
			
			while (!feof(arq_usinas)) { // Executa até o fim do arquivo.
				fread(&usina_cm, sizeof(USINA), 1, arq_usinas); // Lê a struct da usina no arquivo.
				if(strstr(usina_cm.cnpj, usina_rg.cnpj) != 0) {
					usina_ex = 1; // Se chegou aqui, a usina inserida já foi cadastrada anteriormente.
					break;
				}
			}
		}
			
		fclose(arq_usinas); // Fecha o arquivo.
			
		if (usina_ex == 0) {
			// Se chegou aqui, não existem usinas ou consumidores cadastrados com os mesmos dados.

			// ARMAZENAMENTO DOS DADOS
			arq_usinas = fopen("usinas.txt", "ab"); // Abre o arquivo para escrita.
			if (usina_ex != 1) { // Se a usina já não tiver sido cadastrada, armazene os dados.
				fseek(arq_usinas, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
				fwrite(&usina_rg, sizeof(USINA), 1, arq_usinas); // Guarda os dados no arquivo.
			
				printf("\nUsina cadastrada com sucesso!\n");
			}

			fclose (arq_usinas);

		} else {
			// Se chegou aqui, já existem usinas ou consumidores cadastrados com os mesmos dados.
			printf("\nNao foi possivel cadastrar\n"); 
			printf("CNPJ ja cadastrado!\n");
		}
		
		printf("\nDeseja continuar [s/n]?\n");
		while ((getchar()) != '\n'); // Limpa o buffer.
	} while (getchar() == 's' || getchar() == 'S');
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
	    	fflush(stdin); // Limpa o buffer.
	    	scanf("%[^\n]", consum_rg.id); // Recebe o dado do usuário.
	    	
	    	if (strlen(consum_rg.id) == TAM_CNPJ-1) { // Verifica se o usuário digitou um CNPJ.
				dado_valido = valida_cnpj(consum_rg.id); // Chama a função para verificar o CNPJ.
			} else if (strlen(consum_rg.id) == TAM_CPF-1) { // Verifica se o usuário digitou um CPF.
				dado_valido = valida_cpf(consum_rg.id); // Chama a função para verificar o CPF.
			} else {
				dado_valido = 0; // Se chegou aqui, o dado está em formato incorreto.
			}
	    	
	    	if (dado_valido == 0) {
				printf("CNPJ ou CPF INCORRETO!\n"); // Se chegou aqui, o dado está incorreto.
			}
		} while (dado_valido == 0); // Caso o dado esteja incorreto, repete o processo.
	
		
		// NOME
		    printf("Nome do consumidor: ");
		    fflush(stdin); // Limpa o buffer.
			scanf("%[^\n]", consum_rg.nome); // Recebe o dado do usuário.
			
			
		// ARMAZENAMENTO DOS DADOS EM ARQUIVO:

		FILE *arq_consum;
		FILE *arq_usina;
		
		/* VERIFICAÇÃO DE CONFLITO DE DADOS
		Não permitir o cadastro de consumidores com o mesmo CNPJ de outro consumidor ou usina.
		*/

		consum_ex = 0;

		// Usinas:
		arq_usina = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas para leitura.

		if (arq_usina != NULL) {
			// Se chegou aqui o arquivo existe.
			fseek(arq_usina, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.

			while (!feof(arq_usina)) { // Executa até o fim do arquivo de usinas.
				fread(&usina_cm, sizeof(USINA), 1, arq_usina); // Lê a struct da usina no arquivo.
				if(strstr(usina_cm.cnpj, consum_rg.id) != 0) {
					consum_ex = 1; // Se chegou aqui, o ID inserido já foi cadastrado em uma usina.
					break;
				}
			}

		}

		fclose (arq_usina); // Fecha o arquivo.

		// Consumidores:
		arq_consum = fopen("consumidores.txt", "rb"); // Abre o arquivo de consumidores para leitura.
		
		if (arq_consum != NULL) {
			// Se chegou aqui o arquivo existe.
			fseek(arq_consum, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.

			while (!feof(arq_consum)) { // Executa até o fim do arquivo de consumidores.
				fread(&consum_cm, sizeof(CONSUMIDOR), 1, arq_consum); // Lê a struct do consumidor no arquivo.
				if(strstr(consum_cm.id, consum_rg.id) != 0) {
					consum_ex = 1; // Se chegou aqui, o CPF ou CNPJ inserido já foi cadastrado anteriormente.
					break;
				}
			}
		}

		fclose (arq_consum); // Fecha o arquivo.
		
		if (consum_ex == 0) {
			// Se chegou aqui, não existe consumidor nem usina com os dados inseridos.

			// ARMAZENAMENTO DOS DADOS
			arq_consum = fopen("consumidores.txt", "ab"); // Abre o arquivo para escrita.
			if (consum_ex != 1) { // Se o consumidor já não tiver sido cadastrado, armazene os dados.
				fseek(arq_consum, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
				fwrite(&consum_rg, sizeof(CONSUMIDOR), 1, arq_consum); // Guarda os dados no arquivo.
			
				printf("\nConsumidor cadastrado com sucesso!\n");
			}

			fclose(arq_consum); // Fecha o arquivo.

		} else {
			// Se chegou aqui, já existe um consumidor ou usina com os dados inseridos.
			printf("\nNao foi possivel cadastrar\n"); 
			printf("CNPJ/CPF ja cadastrado!\n");
		}
		
		fflush(stdin); // Limpa o buffer.
		printf("\nDeseja continuar [s/n]?\n");
	} while (getchar() == 's' || getchar() == 'S');
}

void cadastro_contrato() // Realiza o cadastro de um contrato.
{
	/* Cadastro de contrato:
    cnpj_usina - XXXXXXXX0001XX
    id_consumidor - CPF ou CNPJ
    data_inicio_contrato - DD MM AAAA
    potencia_contratada - X(MW)
    */
    
    // Declarações de variáveis
    FILE *arquivo; // Ponteiro do arquivo.
    
    CONTRATO contrato_rg; // Variável tipo CONTRATO, usada para receber os dados.
	CONTRATO contrato_cm; // Variável tipo CONTRATO, usada para comparar os dados.
    USINA usina_cm; // Variável tipo USINA, usada para comparar dados da usina. 
    CONSUMIDOR consum_cm; // Variável tipo CONSUMIDOR, usada para comparar dados do consumidor.
    
    int dado_valido; // Se o valor for 0, é inválido, se for 1, é válido.
	int dados_disponiveis; // Se o valor for 0, é inválido, se for 1, é válido.
	int contrato_ex; // Recebe 1 se o contrato já existir no banco de dados, e 0 se não.
	float potencia_dp; // Potência disponível da empresa.
    
    // Instruções
		
	do {
		limpar_tela();
		
		printf("-----------------------------\n");
		printf("CADASTRO DE CONTRATO\n");
		printf("-----------------------------\n");
		
		printf("\nINFORME OS DADOS:\n\n");

		/* VERIFICAR SE É POSSÍVEL CADASTRAR CONTRATO:
		É necessário que exista alguma usina e algum consumidor já cadastrado para ser
		possível cadastrar um contrato.
		*/

		dados_disponiveis = 1;
		arquivo = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas.
		if (arquivo == NULL) {
			dados_disponiveis = 0; // Se chegou aqui, o arquivo está vazio.
		}
		fclose(arquivo); // Fecha o arquivo.
		
		arquivo = fopen("consumidores.txt", "rb"); // Abre o arquivo de consumidores.
		if (arquivo == NULL) {
			dados_disponiveis = 0; // Se chegou aqui, o arquivo está vazio.
		}
		fclose(arquivo); // Fecha o arquivo.

		if (dados_disponiveis == 0) { // Se não existir dados para cadastrar o contrato
			printf("Nao e possivel cadastrar contrato!\n");
			printf("Nao existe usinas ou consumidores cadastrados\n");
		}
		
		if (dados_disponiveis == 1) { // Se existir dados para cadastrar o contrato

			// RECEBIMENTO DE DADOS:
			
			// CNPJ DA USINA
			do {
				printf("CNPJ da usina (Apenas numeros): ");
				fflush(stdin); // Limpa o buffer.
				scanf("%[^\n]", contrato_rg.cnpj_usina); // Recebe o dado do usuário.

				dado_valido = valida_cnpj(contrato_rg.cnpj_usina); // Valida o CNPJ
				
				if (dado_valido == 1) {
					// Verificação se o existe usina com o CNPJ inserido
					arquivo = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas para leitura.
					fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.
					
					dado_valido = 0;
					while (!feof(arquivo)) { // Executa até o fim do arquivo
						fread(&usina_cm, sizeof(USINA), 1, arquivo); // Lê a struct da usina no arquivo.
						
						// Comparar o CNPJ da usina lida e o CNPJ inserido.
						if(strstr(usina_cm.cnpj, contrato_rg.cnpj_usina) != 0) {
							dado_valido = 1; // Se chegou aqui, a usina existe.
							break;
						}
					}
					
					fclose(arquivo); // Fecha o arquivo

					if (dado_valido == 0) {
						printf("Nao existe usina com esse CNPJ!\n"); // Se chegou aqui, a usina não existe.
					} else {

						// EXIBIR OS DADOS DA USINA:
						printf("-----------------------------\n");
						printf("DADOS DA EMPRESA:\n");

						printf("CNPJ: %s\n", usina_cm.cnpj); // CNPJ.
						printf("Nome: %s\n", usina_cm.nome); // Nome.

						// Data
						printf("Data de inicio de operacao: ");
						printf("%i/", usina_cm.data.dia); // Dia.
						printf("%i/", usina_cm.data.mes); // Mês.
						printf("%i\n", usina_cm.data.ano); // Ano.

						// Potência disponível
						potencia_dp = usina_cm.potencia; // Recebe o valor total da potência da usina.

						arquivo = fopen("contratos.txt", "rb"); // Abre o arquivo de contratos.	

						if (arquivo != NULL) {
							fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.

							while (!feof(arquivo)) { // Executa até o fim do arquivo.
								// Lê a struct da usina no arquivo:
								fread(&contrato_cm, sizeof(CONTRATO), 1, arquivo);
								if (!feof(arquivo)) { // Verifica se atingiu o fim do arquivo.
									if (strstr(contrato_cm.cnpj_usina, contrato_rg.cnpj_usina) != 0) {
										// Se chegou aqui, existe um contrato com essa usina.
										// Subtraia da potência disponível a potência contratada.
										potencia_dp = (potencia_dp - contrato_cm.potencia);
									}
								}
							}
						}

						fclose(arquivo); // Fecha o arquivo.

						printf("Potencia disponivel: %.2fMW\n", potencia_dp);
						printf("-----------------------------\n");
					}
				} else {
					printf("CNPJ INCORRETO!\n"); // Se chegou aqui, o dado foi inserido incorretamente.
				}
			} while (dado_valido == 0); // Executa enquanto o dado não for válido.
			
			if (potencia_dp > 0) { // Se houver potência disponível, receba os outros dados:

				// ID DO CONSUMIDOR
				do {
					printf("CPF ou CNPJ do consumidor (Apenas numeros): ");
					fflush(stdin); // Limpa o buffer.
					scanf("%[^\n]", contrato_rg.id_con); // Recebe o dado do usuário.

					if (strlen(contrato_rg.id_con) == TAM_CNPJ) { // Verifica se o usuário digitou um CNPJ.
						dado_valido = valida_cnpj(contrato_rg.id_con); // Chama a função para verificar o CNPJ.
					} else if (strlen(contrato_rg.id_con) == TAM_CPF) { // Verifica se o usuário digitou um CPF.
						dado_valido = valida_cpf(contrato_rg.id_con); // Chama a função para verificar o CPF.
					} else {
						dado_valido = 0; // Se chegou aqui, o dado está em formato incorreto.
					}
					
					if(dado_valido == 1) {
						// Verificação se existe consumidor com tal identificação
						arquivo = fopen("consumidores.txt", "rb"); // Abre o arquivo de consumidores para leitura.
						fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.
						
						dado_valido = 0;
						while (!feof(arquivo)) { // Executa até o fim do arquivo
							fread(&consum_cm, sizeof(CONSUMIDOR), 1, arquivo); // Lê a struct do consumidor no arquivo.
							
							// Comparar o id do consumidor lido e o id inserido.
							if(strstr(consum_cm.id, contrato_rg.id_con) != 0) {
								dado_valido = 1; // Se chegou aqui, o consumidor existe.
								break;
							}
						}
						
						fclose(arquivo);

						if(dado_valido == 0) {
							printf("Nao existe consumidor com essa identificacao!\n");
						}
					} else {
						printf("CPF OU CNPJ INVÁLIDO!\n");
					}
				} while (dado_valido == 0); // Executa enquanto o dado não for válido.
				
				// DATA DE INÍCIO DO CONTRATO
				do {
					printf("Data de inicio do contrato (DD MM AAAA): ");
					fflush(stdin); // Limpa o buffer.
					// Recebe o dado do usuário:
					scanf("%d %d %d", &contrato_rg.data.dia, &contrato_rg.data.mes, &contrato_rg.data.ano);

					dado_valido = valida_data(contrato_rg.data); // Valida a data.

					if (dado_valido == 1) {

						/* VERIFIQUE A DATA
						A data de início do contrato não pode ser anterior a data de início
						de operação da usina.
						*/

						// Localize a usina contratada
						arquivo = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas.
						fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.

						while (!feof(arquivo)) { // Executa até o fim do arquivo.
							fread(&usina_cm, sizeof(USINA), 1, arquivo); // Lê a struct da usina no arquivo.
							if (strstr(usina_cm.cnpj, contrato_rg.cnpj_usina) != 0) {
								// Se chegou aqui, a usina foi localizada.
								break;
							}
						}

						// Compare a data do contrato e da usina
							if (contrato_rg.data.ano < usina_cm.data.ano) {
								dado_valido = 0; // Se chegou aqui o ano do contrato é menor.
							}
							if (contrato_rg.data.ano == usina_cm.data.ano) {
								if (contrato_rg.data.mes < usina_cm.data.mes) {
									dado_valido = 0; // Se chegou aqui o mês do contrato é menor.
								}
								if (contrato_rg.data.mes == usina_cm.data.mes) {
									if (contrato_rg.data.dia < usina_cm.data.dia) {
										dado_valido = 0; // Se chegou aqui o dia do contrato é menor.
									}
								}
							}

						fclose(arquivo); // Fecha o arquivo.

						if (dado_valido == 0) {
							printf("Nao foi possivel cadastrar a data.\n");
							printf("A data de inicio do contrato deve ser posterior a data de inicio de"
							" operacao da usina!\n");
						}
					} else {
						printf("DATA INCORRETA!\n");
					}
				} while(dado_valido == 0); // Executa enquanto o dado não for válido.

				// POTÊNCIA CONTRATADA
				do {
					printf("Potencia a ser contratada (MW): ");
					fflush(stdin); // Limpa o buffer.
					scanf("%f", &contrato_rg.potencia); // Recebe o dado do usuário.

					dado_valido = (contrato_rg.potencia <= 0) ? 0 : 1; // Valida a potência.

					if (dado_valido == 1) {

						/* VERIFIQUE A POTÊNCIA
						A potência a ser contratada não pode ser maior que a potência disponível.
						*/
						
						if (contrato_rg.potencia > potencia_dp) {
							dado_valido = 0; // Se chegou aqui, a potência inserida é maior que a disponível.
							printf("Nao foi possivel cadastrar a potencia\n");
							printf("A potencia inserida nao pode ser maior do que o disponivel pela usina!\n");
						} 

					} else {
						printf("VALOR INCORRETO!\n");
					}
				} while (dado_valido == 0); // Executa enquanto o dado não for válido.
				
				// ARMAZENAMENTO DO CONTRATO EM ARQUIVO:
				
				arquivo = fopen("contratos.txt", "ab"); // Abre o arquivo de contratos.

				if (arquivo == NULL) { // Verifica se foi possível abrir o arquivo.
					// Se não foi possível, exibe uma mensagem de erro.
					printf("\nNao foi possivel salvar os dados!\n");
				}

				fclose(arquivo); // Fecha o arquivo.

				if (arquivo != NULL) {

					/* VERIFICAÇÃO DE CONFLITO DE DADOS:
					Não podem existir contratos com os mesmos dados.
					*/
					arquivo = fopen("contratos.txt", "rb"); // Abre o arquivo de contratos.
					fseek(arquivo, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.

					while(!feof(arquivo)) { // Executa até o fim do arquivo.
						fread(&contrato_cm, sizeof(CONTRATO), 1, arquivo); // Lê toda a struct do contrato.
						if (strstr(contrato_cm.cnpj_usina, contrato_rg.cnpj_usina) != 0) {
							// Se chegou aqui, um contrato com a mesma empresa foi identificado.
							if (strstr(contrato_cm.id_con, contrato_rg.id_con) != 0) {
								// Se chegou aqui, o contrato já existe.
								contrato_ex = 1;
							}
						}
					}
					
					fclose(arquivo); // Fecha o arquivo.

					if (contrato_ex == 0) { // Se o contrato não existir.

						// ARMAZENAMENTO DOS DADOS:
						arquivo = fopen("contratos.txt", "ab"); // Abre o arquivo de contratos.
						fseek(arquivo, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
						fwrite(&contrato_rg, sizeof(CONTRATO), 1, arquivo); // Guarda os dados no arquivo.

						fclose(arquivo); // Fecha o arquivo.

						printf("Contrato cadastrado com sucesso!\n");

					} else { // Se o contrato já existir.
						printf("\nNao foi possivel cadastrar o contrato.\n");
						printf("Ja existe um contrato entre este consumidor e a usina!\n");
					}
				}
			}	
		}

		if (potencia_dp <= 0) {
			// Se chegou aqui, a usina não tem potência disponível para contrato
			printf("A usina nao possui potencia disponivel para contratar!\n");
		}

		fflush(stdin); // Limpa o buffer.
		printf("\nDeseja continuar [s/n]?\n");
	} while (getchar() == 's' || getchar() == 'S');
}

void consulta_usina() // Consulta usina cadastrada.
{
	/* CONSULTA DE USINA:
	Listar os dados da usina e os contratos vinculados ao CNPJ inserido pelo usuário. 
	*/

	// Declarações de variáveis
	FILE *arq_usinas; // Ponteiro do arquivo de usinas.
	FILE *arq_contratos; // Ponteiro do arquivo de contratos.
	FILE *arq_consu; // Ponteiro do arquivo de consumidores.

	char cnpj_usina[TAM_CNPJ]; // Recebe o CNPJ da usina que será consultada.
	USINA usina_ler; // Variável tipo USINA, usada para comparar e ler os dados.
	CONTRATO contrato_cm; // Varíavel tipo CONTRATO, usada para comparar os dados.
	CONSUMIDOR consum_cm; // Varíavel tipo CONSUMIDOR, usada para comparar dados.

	int dado_valido; // Se o valor for 0, é inválido, se for 1, é válido.
	int contrato_localizado; // 0 - não existe contrato vinculado, 1 - existe contrato vinculado.
	float potencia_dp; // Potência disponível da usina.
	float potencia_per; // Percentual de potência disponíval da usina.


	// Instruções
	do {
		limpar_tela();
		    
		    printf("-----------------------------\n");
		    printf("CONSULTA DE USINA CADASTRADA\n");
		    printf("-----------------------------\n\n");
		
			/* VERIFICAÇÃO DA EXISTÊNCIA DE DADOS:
			Só possível consultar usinas se já houver usinas cadastradas.
			*/
			arq_usinas = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas.
			fclose(arq_usinas); // Fecha o arquivo.

			if (arq_usinas != NULL) {
				// Se chegou aqui, o arquivo de usinas existe.

				listar_usinas(); // Listar todas as usinas cadastradas.

				// RECEBIMENTO DE DADOS:

				// CNPJ
				do {
					printf("\nCNPJ da Usina: (Apenas numeros) ");
					fflush(stdin); // Limpa o buffer.
					scanf("%[^\n]", cnpj_usina); // Recebe o dado do usuário.

					dado_valido = valida_cnpj(cnpj_usina); // Valida o CNPJ.

					if (dado_valido != 0) {
						// Se chegou aqui o CNPJ foi inserido corretamente.

						dado_valido = localizar_usina(cnpj_usina); // Verifica se a usina existe.

						if (dado_valido == 0) {
							// Se chegou aqui, a usina não foi localizada.
							printf("Nao foi possivel localizar a usina\n");
							printf("Nao existe usina cadastrada com esse CNPJ!\n");
						}

					} else {
						// Se chegou aqui, o CNPJ foi inserido incorretamente.
						printf("CNPJ INVALIDO!\n");
					}

				} while (dado_valido == 0);
				

				// LISTAR OS DADOS:

				arq_usinas = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas.
				fseek(arq_usinas, 0, SEEK_SET); // Coloca o ponteiro no início do arquivo.

				while (!feof(arq_usinas)) { // Executa até o fim do arquivo.
					fread(&usina_ler, sizeof(USINA), 1, arq_usinas); // Lê toda a struct da usina.
					if (strstr(usina_ler.cnpj, cnpj_usina) != 0) {
						// Se chegou aqui, a usina foi identificada.
						break;
					}
				}

				fclose(arq_usinas);

				/* DADOS DA USINA
				CNPJ:
				Nome:
				Data de início de operação:
				Potência disponível e percentual:
				*/
				printf("\n-----------------------------\n");
				printf("DADOS DA USINA:\n\n");

				printf("CNPJ: %s\n", usina_ler.cnpj); // CNPJ.
				printf("Nome: %s\n", usina_ler.nome); // Nome.

				// Data de início de operação:
				printf("Data de inicio de operacao: ");
				printf("%i/", usina_ler.data.dia); // Dia.
				printf("%i/", usina_ler.data.mes); // Mês.
				printf("%i\n", usina_ler.data.ano); // Ano.

				// Percentural de potência disponível:
				potencia_dp = usina_ler.potencia; // Recebe o valor total da potência da usina.

				arq_contratos = fopen("contratos.txt", "rb"); // Abre o arquivo de contratos.	

				if (arq_contratos != NULL) {
					// Se chegou aqui o arquivo não estava vazio.
					fseek(arq_contratos, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.

					while (!feof(arq_contratos)) { // Executa até o fim do arquivo.
						// Lê a struct da usina no arquivo:
						fread(&contrato_cm, sizeof(CONTRATO), 1, arq_contratos);
						if (!feof(arq_contratos)) { // Verifica se atingiu o fim do arquivo.
							if (strstr(contrato_cm.cnpj_usina, cnpj_usina) != 0) {
								// Se chegou aqui, existe um contrato com essa usina.
								// Subtraia da potência disponível a potência contratada.
								potencia_dp = (potencia_dp - contrato_cm.potencia);
							}
						}
					}
				}

				fclose(arq_contratos); // Fecha o arquivo.

				// Calcula a porcentagem do total que já foi contratada
				potencia_per = ((potencia_dp / usina_ler.potencia) * 100);

				printf("Potencia disponivel: %.2fMW (%.2f%%)\n", potencia_dp, potencia_per);
				printf("-----------------------------\n");


				/* DADOS DOS CONSUMIDORES VINCULADOS
				Nome:
				CNPJ ou CPF:
				Data de início do contrato:
				Potência contratada:
				*/
				printf("\n-----------------------------\n");
				printf("CONSUMIDORES VINCULADOS:");

				arq_contratos = fopen("contratos.txt", "rb"); // Abre o arquivo de contratos.
				if (arq_contratos != NULL) {
					// Se chegou aqui, o arquivo de contratos não está vazio.

					contrato_localizado = 0;
					fseek (arq_contratos, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.
					while (!feof(arq_contratos)) { // Executa até o fim do arquivo.
						fread (&contrato_cm, sizeof(CONTRATO), 1, arq_contratos); // Lê toda a struct.
						if (feof(arq_contratos)) break; // Se estiver no fim do arquivo, encerra.
						if (strstr(contrato_cm.cnpj_usina, usina_ler.cnpj) != 0) {
							// Se chegou aqui, um contrato com a usina foi localizado.
							contrato_localizado = 1;
							
							arq_consu = fopen("consumidores.txt", "rb");
							fseek (arq_consu, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.
							while (!feof(arq_consu)) { // Executa até o fim do arquivo.
								fread (&consum_cm, sizeof(CONSUMIDOR), 1, arq_consu);
								if (strstr(consum_cm.id, contrato_cm.id_con) != 0) {
									// Se chegou aqui, um consumidor vinculado foi localizado.

									printf("\n\nNome: %s\n", consum_cm.nome); // Nome.
									printf("CNPJ ou CPF: %s\n", consum_cm.id); // Identificação.

									// Data de início de contrato:
									printf("Data de inicio de contrato: ");
									printf("%d/", contrato_cm.data.dia); // Dia.
									printf("%d/", contrato_cm.data.mes); // Mês.
									printf("%d\n", contrato_cm.data.ano); // Ano.

									printf("Potencia contratada: ");
									printf("%.2fMW", contrato_cm.potencia); // Potência contratada.
									break;
								}
							}

							fclose(arq_consu); // Fecha o arquivo de consumidores.
						}
					}
					if(contrato_localizado == 0) {
						// Se chegou aqui, não existem contratos vinculados com a usina inserida.
						printf("\nNao existem contratos vinculados a essa usina!");
					}

				} else {
					// Se chegou aqui, o arquivo de contratos está vazio.
					printf("\nNao existem contratos cadastrados!\n");
				}
				fclose(arq_contratos); // Fecha o arquivo de contratos.

				printf("\n-----------------------------\n");

			} else {
				printf("Nao existem usinas cadastradas!\n");
			}

		fflush(stdin); // Limpa o buffer.
		printf("\nDeseja continuar [s/n]?\n");
	} while (getchar() == 's' || getchar() == 'S');
}

void consulta_consumidor() // Consulta consumidor cadastrado.
{
	/* CONSULTA DE CONSUMIDOR:
	Listar os dados do consumidor e as usinas vinculadas ao CPF ou CNPJ inserido pelo usuário.
	*/

	// Declaração de variáveis
	FILE *arq_usinas; // Ponteiro do arquivo de usinas.
	FILE *arq_contratos; // Ponteiro do arquivo de contratos.
	FILE *arq_consu; // Ponteiro do arquivo de consumidores.

	char consum_id[TAM_CNPJ]; // Recebe o CPF ou CNPJ do consumidor que será consultado.
	CONSUMIDOR consum_ler; // Variável tipo CONSUMIDOR, usada para ler os dados no arquivo de consumidores.
	CONTRATO contrato_ler; // Variável tipo CONTRATO, usada para ler os dados no arquivo de contratos.
	USINA usina_ler; // Variável tipo USINA, usada para ler os dados no arquivo de usinas.

	int dado_valido; // Se o valor for 0 é inválido, se for 1 é válido.
	int contrato_localizado; // 0 - não existe contrato vinculado, 1 - existe contrato vinculado.

	// Instruções
	do {
		limpar_tela();

		printf("-----------------------------\n");
		printf("CONSULTAR CONSUMIDOR\n");
		printf("-----------------------------\n\n");

		/* VERIFICAÇÃO DA EXISTÊNCIA DE DADOS:
		Só possível consultar consumidores se já houver consumidores cadastrados.
		*/

		arq_consu = fopen ("consumidores.txt", "rb"); // Abre o arquivo de consumidores.
		fclose(arq_consu); // Fecha o arquivo.

		if (arq_consu != NULL) {
			// Se chegou aqui, o arquivo de consumidores existe.

			listar_consumidores();

			// RECEBIMENTO DE DADOS

			// CPF ou CNPJ
			do {
				printf("\nCPF ou CNPJ: (Apenas numeros) ");
				fflush(stdin); // Limpa o buffer.
				scanf("%[^\n]", consum_id); // Recebe o dado do usuário.

				if (strlen(consum_id) == TAM_CNPJ-1) { // Verifica se o usuário digitou um CNPJ.
					dado_valido = valida_cnpj(consum_id); // Chama a função para verificar o CNPJ.
				} else if (strlen(consum_id) == TAM_CPF-1) { // Verifica se o usuário digitou um CPF.
					dado_valido = valida_cpf(consum_id); // Chama a função para verificar o CPF.
				} else {
					dado_valido = 0; // Se chegou aqui, o dado está em formato incorreto.
				}

	    		if (dado_valido == 1) {
					// Se chegou aqui, o CNPJ ou CPF é válido.

					dado_valido = localizar_consumidor(consum_id);

					if (dado_valido == 0) {
						// Se chegou aqui, o consumidor não foi localizado.
						printf("Nao foi possivel localizar o consumidor\n");
						printf("Nao existe consumidor cadastrado com essa identificacao!\n");
					}

				} else {
					printf("CNPJ OU CPF INCORRETO!\n"); // Se chegou aqui, o dado está incorreto.
				}

			} while (dado_valido == 0);


			// LISTAMENTO DOS DADOS

			/* DADOS DO CONSUMIDOR
			Identificacao:
			Nome:
			*/

			arq_consu = fopen("consumidores.txt", "rb"); // Abre o arquivo de consumidores.
			fseek (arq_consu, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.

			while (!feof(arq_consu)) { // Executa até o fim do arquivo.
				fread (&consum_ler, sizeof(CONSUMIDOR), 1, arq_consu); // Lê toda a struct
				if (strstr(consum_ler.id, consum_id) != 0) {
					// Se chegou aqui, o consumidor foi localizado.
					break;
				}
			}
			fclose(arq_consu); // Fecha o arquivo de consumidores.

			printf("\n-----------------------------\n");
			printf("DADOS DO CONSUMIDOR:\n\n");

			printf("Identificacao: %s\n", consum_ler.id); // CPF ou CNPJ.
			printf("Nome: %s\n", consum_ler.nome); // Nome.

			printf("-----------------------------\n");

			/* DADOS DAS USINAS VINCULADAS
			CNPJ:
			Nome:
			Data de início do contrato:
			Potência contratada:
			*/
			printf("\n-----------------------------\n");
			printf("USINAS VINCULADAS:\n\n");

			// Localizar os contratos e usinas vinculadas
			arq_contratos = fopen("contratos.txt", "rb"); // Abre o arquivo de contratos.

			if (arq_contratos != NULL) {
				// Se chegou aqui, o arquivo de contratos existe.
				contrato_localizado = 0;
				fseek (arq_contratos, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.

				while (!feof(arq_contratos)) { // Executa o arquivo até o fim.
					fread(&contrato_ler, sizeof(CONTRATO), 1, arq_contratos); // Lê toda a struct.
					if (feof(arq_contratos)) break; // Se estiver no final do arquivo, pare o loop.
					if (strstr(contrato_ler.id_con, consum_ler.id)) {
						// Se chegou aqui um contrato vinculado à esse consumidor foi localizado.
						contrato_localizado = 1;

						// Localizar a usina vinculada
						arq_usinas = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas.
						fseek (arq_usinas, 0, SEEK_CUR); // Coloca o ponteiro no início do arquivo.

						while (!feof(arq_usinas)) {
							fread(&usina_ler, sizeof(USINA), 1, arq_usinas); // Lê toda a struct.
							if (strstr(usina_ler.cnpj, contrato_ler.cnpj_usina) != 0) {
								// Se chegou aqui, a usina vinculada foi localizada.
								break;
							}
						}

						printf("CNPJ: %s\n", usina_ler.cnpj); // CNPJ da Usina.
						printf("Nome: %s\n", usina_ler.nome); // Nome da Usina.
						// Data de início do contrato:
						printf("Data de inicio do contrato: ");
						printf("%i/", contrato_ler.data.dia); // Dia.
						printf("%i/", contrato_ler.data.mes); // Mês.
						printf("%i\n", contrato_ler.data.ano); // Ano.

						printf("Potencia contratada: %.2fMW\n\n", contrato_ler.potencia);

						fclose(arq_usinas); // Fecha o arquivo de usinas.
					}
				}
			} else {
				// Se chegou aqui o arquivo de contratos não existe.
				contrato_localizado = 0;
			}

			fclose(arq_contratos); // Fecha o arquivo de contratos.

			if (contrato_localizado == 0) {
				// Se chegou aqui, não existem contratos nem usinas vinculadas.
				printf("Nao existem usinas vinculadas com esse consumidor!\n");
			}

			printf("-----------------------------\n\n");

		} else {
			printf("Nao existem consumidores cadastrados!\n");
		}

		fflush(stdin); // Limpa o buffer
		printf("Deseja continuar? [s/n]\n");
	} while (getchar() == 's' || getchar() == 'S');
}

void excluir_usina() // Excluir usina cadastrada.
{
	// Declarações de variáveis
	FILE *arq_usinas; // Ponteiro do arquivo de usinas.
	FILE *arqtemp_usinas; // Ponteiro do arquivo temporário de usinas.
	FILE *arq_contratos; // Ponteiro do arquivo de contratos.
	FILE *arqtemp_contratos; // Ponteiro do arquivo temporário de contratos.

	USINA usina_ler; // Variável tipo USINA, usada para comparar e ler os dados.
	CONTRATO contrato_ler; // Variável tipo CONTRATO, usada para comparar e ler os dados.

	char cnpj_usina[TAM_CNPJ]; // Usada pra receber o dado do usuário.
	int dado_valido; // Se o valor for 0, é inválido, se for 1, é válido.

	// Instruções

	do {
		limpar_tela();

		printf("-----------------------------\n");
		printf("EXCLUIR USINA\n");
		printf("-----------------------------\n\n");

		/* VERIFICAÇÃO DA EXISTÊNCIA DO ARQUIVO
		Não é possível excluir dados se o arquivo de usinas não existe.
		*/

		arq_usinas = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas.
		fclose(arq_usinas); // Fecha o arquivo.

		if (arq_usinas != NULL) {
			// Se chegou aqui, o arquivo de usinas já foi criado.

			listar_usinas(); // Listar todas as usinas cadastradas.

			// RECEBER O CNPJ DA USINA
			do {
				printf("\nCNPJ da Usina: (Apenas numeros) ");
				fflush(stdin); // Limpa o buffer.
				scanf("%[^\n]", cnpj_usina); // Recebe o dado do usuário.

				dado_valido = valida_cnpj(cnpj_usina); // Valida o CNPJ.

				if (dado_valido != 0) {
					// Se chegou aqui o CNPJ foi inserido corretamente.

					dado_valido = localizar_usina(cnpj_usina); // Verifica se a usina existe.

					if (dado_valido == 0) {
						// Se chegou aqui, a usina não foi localizada.
						printf("Nao foi possivel localizar a usina\n");
						printf("Nao existe usina cadastrada com esse CNPJ!\n");
					}

				} else {
					// Se chegou aqui, o CNPJ foi inserido incorretamente.
					printf("CNPJ INVALIDO!\n");
				}

			} while (dado_valido == 0);


			// REMOVER OS DADOS

			// Usina
			arq_usinas = fopen("usinas.txt", "rb"); // Abre o arquivo de usinas.

			fseek(arq_usinas, 0, SEEK_SET); // Coloca o ponteiro no início do arquivo.

			while (!feof(arq_usinas)) { // Executa até o fim do arquivo.
				fread(&usina_ler, sizeof(USINA), 1, arq_usinas); // Lê toda a struct da usina.
				if (feof(arq_usinas)) break;
				if (strstr(usina_ler.cnpj, cnpj_usina) == 0) {
					printf("\n%s\n", usina_ler.cnpj);
					printf("%s\n", cnpj_usina);
					// Se chegou aqui, uma usina diferente da que vai ser excluída foi localizada.

					arqtemp_usinas = fopen("usinas_temp.txt", "ab"); // Abre o arquivo temporário.
					fseek(arqtemp_usinas, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
					fwrite(&usina_ler, sizeof(USINA), 1, arqtemp_usinas); // Armazena os dados.
					fclose(arqtemp_usinas); // Fecha o arquivo temporário.
				}
			}

			fclose(arq_usinas); // Fecha o arquivo de usinas.
			remove("usinas.txt"); // Excluí o arquivo de usinas.
			rename("usinas_temp.txt", "usinas.txt"); // Renomeía o arquivo temporário.

			// Contratos
			arq_contratos = fopen("contratos.txt", "rb"); // Abre o arquivo de contratos.

			fseek(arq_contratos, 0, SEEK_SET); // Coloca o ponteiro no início do arquivo.

			while (!feof(arq_contratos)) { // Executa até o fim do arquivo.
				fread(&contrato_ler, sizeof(CONTRATO), 1, arq_contratos); // Lê toda a struct do contrato.
				if (feof(arq_contratos)) break;
				if (strstr(contrato_ler.cnpj_usina, cnpj_usina) == 0) {
					// Se chegou aqui, um contrato diferente do que vai ser excluído foi localizado.

					arqtemp_contratos = fopen("contratos_temp.txt", "ab"); // Abre o arquivo temporário.
					fseek(arqtemp_contratos, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
					fwrite(&contrato_ler, sizeof(CONTRATO), 1, arqtemp_contratos); // Armazena os dados.
					fclose(arqtemp_contratos); // Fecha o arquivo temporário.
				}
			}

			fclose(arq_contratos); // Fecha o arquivo de contratos.
			remove("contratos.txt"); // Excluí o arquivo de contratos.
			rename("contratos_temp.txt", "contratos.txt"); // Renomeía o arquivo temporário.

			printf("\nUsina removida com sucesso!\n");

		} else {
			// Se chegou aqui, o arquivo de usinas ainda não foi criado.
			printf("Nao existem usinas cadastradas!\n");
		}

		printf("\nDeseja continuar? [s/n]\n");
	} while (getchar() == 'S' || getchar() == 's');
}

void excluir_consumidor() // Excluir consumidor cadastrada.
{
	// Declarações de variáveis
	FILE *arq_consum; // Ponteiro do arquivo de consumidores.
	FILE *arqtemp_consum; // Ponteiro do arquivo temporário de consumidores.
	FILE *arq_contratos; // Ponteiro do arquivo de contratos.
	FILE *arqtemp_contratos; // Ponteiro do arquivo temporário de contratos.

	CONSUMIDOR consum_ler; // Variável tipo USINA, usada para comparar e ler os dados.
	CONTRATO contrato_ler; // Variável tipo CONTRATO, usada para comparar e ler os dados.

	char consum_id[TAM_CNPJ]; // Usada pra receber o dado do usuário.
	int dado_valido; // Se o valor for 0, é inválido, se for 1, é válido.

	// Instruções

	do {
		limpar_tela();

		printf("-----------------------------\n");
		printf("EXCLUIR USINA\n");
		printf("-----------------------------\n\n");

		/* VERIFICAÇÃO DA EXISTÊNCIA DO ARQUIVO
		Não é possível excluir dados se o arquivo de usinas não existe.
		*/

		arq_consum = fopen("consumidores.txt", "rb"); // Abre o arquivo.
		fclose(arq_consum); // Fecha o arquivo.

		if (arq_consum != NULL) {
			// Se chegou aqui o arquivo de consumidores existe.

			listar_consumidores(); // Listar todos os consumidores cadastrados.

			// RECEBER O CPF OU CNPJ DO CONSUMIDOR
			do {
				printf("\nCPF ou CNPJ: (Apenas numeros) ");
				fflush(stdin); // Limpa o buffer.
				scanf("%[^\n]", consum_id); // Recebe o dado do usuário.

				if (strlen(consum_id) == TAM_CNPJ-1) { // Verifica se o usuário digitou um CNPJ.
					dado_valido = valida_cnpj(consum_id); // Chama a função para verificar o CNPJ.
				} else if (strlen(consum_id) == TAM_CPF-1) { // Verifica se o usuário digitou um CPF.
					dado_valido = valida_cpf(consum_id); // Chama a função para verificar o CPF.
				} else {
					dado_valido = 0; // Se chegou aqui, o dado está em formato incorreto.
				}

	    		if (dado_valido == 1) {
					// Se chegou aqui, o CNPJ ou CPF é válido.

					dado_valido = localizar_consumidor(consum_id);

					if (dado_valido == 0) {
						// Se chegou aqui, o consumidor não foi localizado.
						printf("Nao foi possivel localizar o consumidor\n");
						printf("Nao existe consumidor cadastrado com essa identificacao!\n");
					}

				} else {
					printf("CNPJ OU CPF INCORRETO!\n"); // Se chegou aqui, o dado está incorreto.
				}
			} while (dado_valido == 0); // Executa enquanto o dado for inválido.

			// REMOVER OS DADOS

			// Consumidor
			arq_consum = fopen("consumidores.txt", "rb"); // Abre o arquivo de consumidores.
			fseek(arq_consum, 0, SEEK_SET); // Coloca o ponteiro no início do arquivo.

			while (!feof(arq_consum)) { // Executa até o fim do arquivo.
				fread(&consum_ler, sizeof(CONSUMIDOR), 1, arq_consum); // Lê toda a struct.
				if (feof(arq_consum)) break; // Se não estiver no final do arquivo executa.
				if (strstr(consum_ler.id, consum_id) == 0) {
					// Se chegou aqui, um consumidor diferente do que vai ser excluído foi localizado.

					arqtemp_consum = fopen("consumidores_temp.txt", "ab"); // Abre o arquivo temporário.
					fseek(arqtemp_consum, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
					fwrite(&consum_ler, sizeof(CONSUMIDOR), 1, arqtemp_consum); // Armazena os dados.
					fclose(arqtemp_consum); // Fecha o arquivo temporário.
				}
			}

			fclose(arq_consum);
			remove("consumidores.txt");
			rename("consumidores_temp.txt", "consumidores.txt");

			// Contratos vinculados
			arq_contratos = fopen("contratos.txt", "rb"); // Abre o arquivo de contratos.

			fseek(arq_contratos, 0, SEEK_SET); // Coloca o ponteiro no início do arquivo.

			while (!feof(arq_contratos)) { // Executa até o fim do arquivo.
				fread(&contrato_ler, sizeof(CONTRATO), 1, arq_contratos); // Lê toda a struct do contrato.
				if (feof(arq_contratos)) break;
				if (strstr(contrato_ler.id_con, consum_id) == 0) {
					// Se chegou aqui, um contrato diferente do que vai ser excluído foi localizado.

					arqtemp_contratos = fopen("contratos_temp.txt", "ab"); // Abre o arquivo temporário.
					fseek(arqtemp_contratos, 0, SEEK_END); // Coloca o ponteiro no final do arquivo.
					fwrite(&contrato_ler, sizeof(CONTRATO), 1, arqtemp_contratos); // Armazena os dados.
					fclose(arqtemp_contratos); // Fecha o arquivo temporário.
				}
			}

			fclose(arq_contratos); // Fecha o arquivo de contratos.
			remove("contratos.txt"); // Excluí o arquivo de contratos.
			rename("contratos_temp.txt", "contratos.txt"); // Renomeía o arquivo temporário.

			printf("\nConsumidor removido com sucesso!\n");

		} else {
			// Se chegou aqui o arquivo de consumidores ainda não foi criado.
			printf("Nao existem consumidores cadastrados!\n");
		}

		printf("\nDeseja continuar? [s/n]\n");
	} while (getchar() == 'S' || getchar() == 's');
}

int main() // Função main.
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
                consulta_usina();
                break;
            }
            case CONSULTAR_CONSUMIDOR: {
				consulta_consumidor();
                break;
            }
            case EXCLUIR_USINA: {
				excluir_usina();
                break;
            }
            case EXCLUIR_CONSUMIDOR: {
				excluir_consumidor();
                break;
            }
            case SAIR: {
             	break;   
            }
            default: {
            	limpar_tela();
            	printf("OPÇAO INVALIDA!\n\n");
             	break;   
            }
        }
        
    } while (menu_opcao != 8); // Mantém o programa executando até o usuário encerrar
    
    printf("\nPrograma encerrado!\n");
    
    return 0;
}