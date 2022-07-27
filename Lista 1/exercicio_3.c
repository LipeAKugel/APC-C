#include <stdio.h>

int main() {
	
	int duracao, seg, min, hora;
	
	scanf("%i", &duracao);
	
	hora = duracao / 3600;
	min = (duracao / 60) - (hora * 60);
	seg = duracao - (min * 60) - (hora * 3600);
	
	printf("%i:%i:%i\n", hora, min, seg);

	return 0;
}
