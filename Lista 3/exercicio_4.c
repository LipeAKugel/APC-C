#include <stdio.h>

int main()
{
    char cpf[14];
    char teste;
    
    scanf("%s", cpf);
    
    for (int i = 0; i < 14; i++) {
        teste = cpf[i];
        if (teste == 46 || teste == 45) {
            printf("\n");
        } else {
            printf("%c", teste);
        }
        
    }
    
    printf("\n");

    return 0;
}
