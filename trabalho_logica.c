#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char var[20];
    int valor;
} tabela;

void processando(int n, int m, tabela tab[][100], int linhas) {
    // Processando sentenças comuns
    for (int i = n; i < n + m; i++) {
        int p1 = -1, p2 = -1;
        char operador = '\0';

        // Negação (!P)
        if (tab[i][0].var[0] == '!') {
            char p1_var = tab[i][0].var[1];

            // Encontrar a variável
            for (int k = 0; k < n; k++) {
                if (tab[k][0].var[0] == p1_var) {
                    p1 = k;
                    break;
                }
            }

            if (p1 == -1) {
                printf("Erro: Variavel \"%c\" nao encontrada.\n", p1_var);
                return;
            }

            for (int j = 0; j < linhas; j++) {
                tab[i][j].valor = !tab[p1][j].valor;
            }
            continue;
        }else{
            // Para operações binárias (ex: P^Q, S>P)
            char p1_var = tab[i][0].var[0];
            operador = tab[i][0].var[1];
            char p2_var = tab[i][0].var[2];

            // Procurando p1 na tabela
            for (int k = 0; k < n; k++) {
                if (tab[k][0].var[0] == p1_var) {
                    p1 = k;
                    break;
                }
            }
            
            // Procurando p2 na tabela
            for (int k = 0; k < n; k++) {
                if (tab[k][0].var[0] == p2_var) {
                    p2 = k;
                    break;
                }
            }

            if (p1 == -1 || p2 == -1) {
                printf("Erro: Variavel nao reconhecida.\n");
                return;
            }
        }

        // Calculando a sentença
        for (int j = 0; j < linhas; j++) {
            if (operador == '^') { // AND (conjunção)
                tab[i][j].valor = tab[p1][j].valor && tab[p2][j].valor;
            } else if (operador == 'v') { // OR (disjunção)
                tab[i][j].valor = tab[p1][j].valor || tab[p2][j].valor;
            } else if (operador == '>') { // Implicação (P -> Q)
                tab[i][j].valor = !tab[p1][j].valor || tab[p2][j].valor;
            } else if (operador == '=') { // Bi-condicional (P <-> Q)
                tab[i][j].valor = (tab[p1][j].valor) == (tab[p2][j].valor);
            } else {
                printf("Erro: Operador nao reconhecido.\n");
                return;
            }
        }
    }
}

int main() {
    int n, m, o = 0;
    printf("Quantas variaveis tem a preposicao? ");
    scanf("%d", &n);
    printf("Quantas sentencas comuns sao? ");
    scanf("%d", &m);
    printf("Quantas sentencas multiplas sao? ");
    scanf("%d", &o);
    system("cls");

    int linhas = pow(2, n);
    tabela tab[n + m + o][100]; 

    for (int i = 0; i < n; i++) {
        printf("Digite a variavel %d: ", i + 1);
        scanf(" %s", tab[i][0].var);
    }

    for (int i = n; i < n + m; i++) {
        printf("Digite a sentenca logica comum (ex: P^Q, !P, S>P): ");
        scanf(" %s", tab[i][0].var);
    }

    // Preenchendo a tabela-verdade para as variáveis
    for (int i = 0; i < n; i++) {
        int intervalo = pow(2, n - (i + 1));
        int valor = 1;
        for (int j = 0; j < linhas; j++) {
            tab[i][j].valor = valor;
            if ((j + 1) % intervalo == 0) {
                valor = !valor;
            }
        }
    }

    processando(n, m, tab, linhas);
    system("cls");

    for(int l = 0; l < o; l++){
        int p1, p2, operacao;
        printf("Qual sentenca voce deseja usar como P1\n");
        printf("[");
        for(int i = n; i < n+m+l; i++){
            printf("(%d) %s", i-n+1, tab[i][0].var);
            if(i != (n+m+l)-1){
                printf(" - ");
            }
        }
        printf("]\n");
        printf("Digite o numero da sentenca: ");
        scanf("%d", &p1);

        printf("\nQual sentenca voce deseja usar como P2:\n");
        printf("[");
        for(int i = n; i < n+m+l; i++){
            printf("(%d) %s", i-n+1, tab[i][0].var);
            if(i != (n+m+l)-1){
                printf(" - ");
            }
        }
        
        printf("]\n");
        printf("Digite o numero da sentenca: ");
        scanf("%d", &p2);

        printf("\n[(1) \">\" - (2) \"=\" - (3) \"^\" - (4) \"v\"]\n");
        printf("Digite o numero da operacao: ");
        scanf("%d", &operacao);
        int i = n+m+l;
        printf("\nComo voce quer que apareca na tabela? ");
        scanf(" %s", tab[i][0].var);
        puts("");

        p1 += (n-1);
        p2 += (n-1);

        for (int j = 0; j < linhas; j++) {
            if (operacao == 3) { // AND (conjunção)
                tab[i][j].valor = (tab[p1][j].valor & tab[p2][j].valor)?1:0;
            } else if (operacao == 4) { // OR (disjunção)
                tab[i][j].valor = (tab[p1][j].valor || tab[p2][j].valor)?1:0;
            } else if (operacao == 1) { // Implicação (P -> Q)
                tab[i][j].valor = (!tab[p1][j].valor || tab[p2][j].valor)?1:0;
            } else if (operacao == 2) { // Bi-condicional (P <-> Q)
                tab[i][j].valor = (tab[p1][j].valor == tab[p2][j].valor)?1:0;
            } else {
                printf("Erro: Operador nao reconhecido.\n");
                return 1;
            }
        }
        system("cls");
    }
    
    int opcao;
    printf("O que deseja fazer? \n");
    puts("1 - Exibir Tabela-Verdade");
    puts("2 - Comparar");
    scanf("%d", &opcao);

    if(opcao == 1){
        printf("\nTABELA VERDADE\n");
        for (int i = 0; i < n + m + o; i++) {
            printf("%s\t", tab[i][0].var);
        }
        printf("\n");
    
        for (int j = 0; j < linhas; j++) {
            for (int i = 0; i < n + m + o; i++) {
                printf("%d\t", tab[i][j].valor);
            }
            printf("\n");
        }
        puts("");
    }else if(opcao == 2){
        int p1, p2;
        system("cls");
        printf("[");
        for(int i = n; i < n+m+o; i++){
            printf("(%d) %s", i-n+1, tab[i][0].var);
            if(i != (n+m+o)-1){
                printf(" - ");
            }
        }
        printf("]\n");
        printf("Digite a setenca 1: ");
        scanf("%d", &p1);

        printf("[");
        for(int i = n; i < n+m+o; i++){
            printf("(%d) %s", i-n+1, tab[i][0].var);
            if(i != (n+m+o)-1){
                printf(" - ");
            }
        }
        printf("]\n");
        printf("Digite a setenca 2: ");
        scanf("%d", &p2);

        p1 += (n-1);
        p2 += (n-1);

        for (int j = 0; j < linhas; j++) {
            if(tab[p1][j].valor != tab[p2][j].valor){
                printf("As sentencas NAO sao validas!");
                return 1;
            }
        }
        printf("As sentencas sao validas!");
    }else{
        puts("OPCAO INVALIDA");
    }

    return 0;
}