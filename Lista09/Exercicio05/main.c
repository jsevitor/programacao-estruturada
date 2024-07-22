#include <stdio.h>

int main() {
    int maze[11][11] = {
        {1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,1,},
        {1,0,1,1,1,1,1,1,1,1,1},
        {0,0,0,0,1,0,1,0,0,0,0},
        {1,1,1,0,1,0,1,0,1,0,1},
        {1,0,0,0,1,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1}
    };

    FILE *arquivo;
    arquivo = fopen("imagem5.pbm", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fprintf(arquivo, "P1\n");
    fprintf(arquivo, "#imagem.pbm\n");
    fprintf(arquivo, "11 11\n");

    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            fprintf(arquivo, "%d ", maze[i][j]);
        }
        fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    printf("Arquivo PBM gerado com sucesso!\n");
    return 0;
}
