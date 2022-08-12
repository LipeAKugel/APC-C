#include <stdio.h>

int main()
{
    char data[8];
    
    scanf("%s", data);
    
    printf("%c", data[3]);
    printf("%c/", data[4]);
    printf("%c", data[0]);
    printf("%c/", data[1]);
    printf("%c", data[6]);
    printf("%c\n", data[7]);
    
    printf("%c", data[6]);
    printf("%c/", data[7]);
    printf("%c", data[3]);
    printf("%c/", data[4]);
    printf("%c", data[0]);
    printf("%c\n", data[1]);
    
    printf("%c", data[0]);
    printf("%c-", data[1]);
    printf("%c", data[3]);
    printf("%c-", data[4]);
    printf("%c", data[6]);
    printf("%c\n", data[7]);
    
    return 0;
}
