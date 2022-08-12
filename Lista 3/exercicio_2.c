#include <stdio.h>

int main()
{
    int casos_teste;
    double total, media, acima_media;
    int num_alunos;
    int notas[1000];
    
    scanf("%i", &casos_teste);
    
    double porcentagem[casos_teste];
    
    for (int i = 0; i < casos_teste; i++) {
        scanf("%i", &num_alunos);
        for (int j = 0; j < num_alunos; j++) {
            scanf("%i", &notas[j]);
        }
        
        // Cálculo da média
        total = 0;
        for (int j = 0; j < num_alunos; j++) {
            total = total + notas[j];
        }
            
        media = total / num_alunos;
        
        // Cálculo da quantidade de alunos acima da média
        acima_media = 0;
        for (int j = 0; j < num_alunos; j++) {
            if (notas[j] > media) {
                acima_media = acima_media + 1;
            }    
        }
        
        // Cálculo da porcentagem
        porcentagem[i] = ((acima_media/num_alunos)*100);
    }
    
    for (int i = 0; i < casos_teste; i++) {
        printf("%.3lf%%\n", porcentagem[i]);
    }
    
    return 0;
}
