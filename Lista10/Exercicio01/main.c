#include <stdio.h>
#include <stdlib.h>

int main()
{
    int largura, altura, valor_maximo;
    char buffer[255];

    FILE *arquivo = fopen("tucano.ppm", "r");
    FILE *saida = fopen("tucano_cinza.ppm", "w");

    if (arquivo == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        return 1;
    }

    // Leitura do cabeçalho do arquivo PPM
    fgets(buffer, sizeof(buffer), arquivo); // Lê a primeira linha do arquivo (P3)
    fprintf(saida, "%s", buffer);           // Escreve o cabeçalho no arquivo de saída

    fgets(buffer, sizeof(buffer), arquivo); // Lê a segunda linha do arquivo (comentário)
    fprintf(saida, "%s", buffer);           // Escreve o comentário no arquivo de saída

    fscanf(arquivo, "%d %d", &largura, &altura); // Lê a largura e altura
    fprintf(saida, "%d %d\n", largura, altura);  // Escreve a largura e altura no arquivo de saída

    fscanf(arquivo, "%d", &valor_maximo); // Lê o valor máximo de cor
    fprintf(saida, "%d\n", valor_maximo); // Escreve o valor máximo de cor no arquivo de saída

    // Alocação dinâmica da matriz para evitar problemas de tamanho
    int ***matriz = (int ***)malloc(altura * sizeof(int **));
    for (int i = 0; i < altura; i++)
    {
        matriz[i] = (int **)malloc(largura * sizeof(int *));
        for (int j = 0; j < largura; j++)
        {
            matriz[i][j] = (int *)malloc(3 * sizeof(int));
        }
    }

    // Leitura dos pixels da imagem colorida
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            fscanf(arquivo, "%d %d %d", &matriz[i][j][0], &matriz[i][j][1], &matriz[i][j][2]);
        }
    }

    // Conversão para escala de cinza e escrita no arquivo de saída
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            int pixel = (matriz[i][j][0] + matriz[i][j][1] + matriz[i][j][2]) / 3;
            fprintf(saida, "%d %d %d ", pixel, pixel, pixel);
        }
        fprintf(saida, "\n");
    }

    // Liberação da memória alocada
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            free(matriz[i][j]);
        }
        free(matriz[i]);
    }
    free(matriz);

    printf("Arquivo gerado com sucesso.\n");
    fclose(arquivo);
    fclose(saida);

    return 0;
}
