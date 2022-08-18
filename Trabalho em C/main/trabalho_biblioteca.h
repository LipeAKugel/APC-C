// ***BIBLIOTECA DE FUNÇÕES E DEFINIÇÕES PARA SEREM USADAS NO TRABALHO***

#define TRABALHO_BIBLIOTECA_H

#include <stdio.h>
#include <stdlib.h>

#define CADASTRO_USINA 1
#define CADASTRO_CONSUMIDOR 2
#define CADASTRO_CONTRATO 3
#define CONSULTAR_USINA 4
#define CONSULTAR_CONSUMIDOR 5
#define EXCLUIR_USINA 6
#define EXCLUIR_CONSUMIDOR 7
#define SAIR 8

#define TAM_DATA 10
#define TAM_CNPJ 14
#define TAM_CPF 11
#define TAM_NOME 100

void menu() // Exibe o menu de opções
{ 
    printf("1)Cadastrar Usina\n");
    printf("2)Cadastrar Consumidor\n");
    printf("3)Cadastrar Contrato entre Consumidor e Usina\n");
    printf("4)Consultar Usina Cadastrada\n");
    printf("5)Consultar Consumidor Cadastrado\n");
    printf("6)Excluir Usina\n");
    printf("7)Excluir Consumidor\n");
    printf("8)Sair\n");
}

void limpar_tela() // Limpa o terminal
{
	#if defined(linux) || defined(unix) || defined(APPLE)
		system("clear");
	#endif
	
	#if defined(_WIN32) || defined(_WIN64)
		system("cls");
	#endif
}


