#include <stdio.h>

int main() {
    int numero;
    char resposta;

    do {
        // Solicita um número ao usuário
        printf("Digite um número para ver a tabuada: ");
        scanf("%d", &numero);

        // Exibe a tabuada do número
        printf("\nTabuada de %d:\n", numero);
        for (int i = 1; i <= 10; i++) {
            printf("%d x %d = %d\n", numero, i, numero * i);
        }

        // Pergunta se o usuário quer ver outra tabuada
        printf("\nDeseja ver outra tabuada? (s/n): ");
        scanf(" %c", &resposta);  // espaço antes de %c consome possíveis quebras de linha

    } while (resposta == 's' || resposta == 'S');

    printf("\nAté mais! Obrigado por jogar.\n");
    return 0;
}