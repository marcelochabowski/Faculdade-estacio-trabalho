#include <stdio.h> //biblioteca

int main() { // inicio de programa
    int numero; // variavel numero inteiro
    char resposta; // variavel de caracteres

    do { // funcao de loop
        // Solicita um número ao usuário
        printf("Digite um número para ver a tabuada: "); // comando de usuario
        scanf("%d", &numero); // leitura de comando

        // Exibe a tabuada do número
        printf("\nTabuada de %d:\n", numero); //  imprimir tabuada
        for (int i = 1; i <= 10; i++) {
            printf("%d x %d = %d\n", numero, i, numero * i); // imprimir de fatores
        }

        // Pergunta se o usuário quer ver outra tabuada
        printf("\nDeseja ver outra tabuada? (s/n): ");
        scanf(" %c", &resposta);  // espaço antes de %c consome possíveis quebras de linha

    } while (resposta == 's' || resposta == 'S'); // comando para caractere caixa alta ou baixa

    printf("\nAté mais! Obrigado.\n"); // fim de programa
    return 0;
}