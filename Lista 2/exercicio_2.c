#include <stdio.h>

int main()
{
	int x[20], y[20];
	
	// Entrada de dados
	for (int i = 0; i <= 20; i++) {
		// Insira as coordenadas dos pontos
		scanf("%i %i", &x[i], &y[i]);
		
		// Quebra a repetição se alguma coordenada for igual a 0
		if(x[i] == 0 || y[i] == 0) {
			break;
		}
	}
	
	int i = 0;
	while(x[i] != 0 || y[i] != 0) {
		// Chama a função e recebe o quadrante
		int quadrante = loc_quad(x[i], y[i]);
		
		switch(quadrante) {
			case 1:
				printf("primeiro\n");
				break;
			case 2:
				printf("segundo\n");
				break;
			case 3:
				printf("terceiro\n");
				break;
			case 4:
				printf("quarto\n");
				break;
		}
		i++;
	}
		
	return 0;
}

int loc_quad(int x, int y)
{
	int quadrante;
	
	if (x > 0 && y > 0) quadrante = 1;
	if (x < 0 && y > 0) quadrante = 2;
	if (x < 0 && y < 0) quadrante = 3;
	if (x > 0 && y < 0) quadrante = 4;
	
	return quadrante;
}
