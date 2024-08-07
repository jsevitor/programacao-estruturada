#include <stdio.h>
#include <stdlib.h>

int escalaCinza()
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
    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fgets(buffer, sizeof(buffer), arquivo);
    fprintf(saida, "%s", buffer);

    fscanf(arquivo, "%d %d", &largura, &altura);
    fprintf(saida, "%d %d\n", largura, altura);

    fscanf(arquivo, "%d", &valor_maximo);
    fprintf(saida, "%d\n", valor_maximo);

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

    printf("Imagem convertida com sucesso!\n");
    fclose(arquivo);
    fclose(saida);

    return 0;
}

int inverteHorizontal()
{
    FILE *entrada, *saida;
    entrada = fopen("tucano.ppm", "r");
    saida = fopen("tucano_virado_horizontal.ppm", "w");

    int i, j, k;
    int largura, altura, v_max;
    char buffer[255];

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    else
    {
        // Leitura do cabeçalho
        fgets(buffer, 255, entrada);
        fprintf(saida, "%s", buffer);
        fgets(buffer, 255, entrada);
        fprintf(saida, "%s", buffer);

        fscanf(entrada, "%d %d", &largura, &altura);
        fprintf(saida, "%d %d\n", largura, altura);
        fscanf(entrada, "%d", &v_max);
        fprintf(saida, "%d\n", v_max);

        int matriz[altura][largura][3];

        // Leitura dos pixels da imagem
        for (i = 0; i < altura; i++)
        {
            for (j = 0; j < largura; j++)
            {
                for (k = 0; k < 3; k++)
                {
                    fscanf(entrada, "%d", &matriz[i][j][k]);
                }
            }
        }

        // Escrita do arquivo de saída com espelhamento horizontal
        for (i = 0; i < altura; i++)
        {
            for (j = largura - 1; j >= 0; j--)
            {
                // Inverte horizontalmente
                for (k = 0; k < 3; k++)
                {
                    fprintf(saida, "%d ", matriz[i][j][k]);
                }
            }
            fprintf(saida, "\n");
        }

        printf("Imagem invertida com sucesso.\n");
        fclose(entrada);
        fclose(saida);
    }
    return 0;
}

int inverteVertical()
{
    FILE *entrada, *saida;
    entrada = fopen("tucano.ppm", "r");
    saida = fopen("tucano_virado_vertical.ppm", "w");

    int i, j, k;
    int largura, altura, v_max;
    char buffer[255];

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    else
    {
        // Leitura do cabeçalho
        fgets(buffer, 255, entrada);
        fprintf(saida, "%s", buffer);
        fgets(buffer, 255, entrada);
        fprintf(saida, "%s", buffer);

        fscanf(entrada, "%d %d", &largura, &altura);
        fprintf(saida, "%d %d\n", largura, altura);
        fscanf(entrada, "%d", &v_max);
        fprintf(saida, "%d\n", v_max);

        int matriz[altura][largura][3];

        // Leitura dos pixels da imagem
        for (i = 0; i < altura; i++)
        {
            for (j = 0; j < largura; j++)
            {
                for (k = 0; k < 3; k++)
                {
                    fscanf(entrada, "%d", &matriz[i][j][k]);
                }
            }
        }

        // Escrita do arquivo de saída com espelhamento vertical
        for (i = altura - 1; i >= 0; i--)
        {
            // Inverte verticalmente
            for (j = 0; j < largura; j++)
            {
                for (k = 0; k < 3; k++)
                {
                    fprintf(saida, "%d ", matriz[i][j][k]);
                }
            }
            fprintf(saida, "\n");
        }

        printf("Imagem inveritda com sucesso.\n");
        fclose(entrada);
        fclose(saida);
    }
    return 0;
}

int menu()
{
    int option;

    printf(" .:: MANIPULADOR DE IMAGENS ::. \n");
    printf("1. Converter uma imagem colorida para escala de cinza.\n");
    printf("2. Espelhar uma imagem horizontalmente.\n");
    printf("3. Espelhar uma imagem verticalmente.\n");
    printf("4. Dividir uma imagem em dois arquivos, metade esquerda e metade direita).\n");
    printf("5. Dividir uma imagem em dois arquivos, metade superior e metade inferior).\n");
    printf("Opção: ");
    scanf("%d", &option);

    return option;
}

int main()
{
    int option;
    option = menu();

    switch (option)
    {
    case 1:
        printf("\nConvertendo imagem para escala de cinza...\n");
        escalaCinza();
        break;

    case 2:
        printf("\nInvertendo imagem horizontalmente...\n");
        inverteHorizontal();
        break;

    case 3:
        printf("\nInvertendo imagem verticalmente...\n");
        inverteVertical();
        break;

    case 4:
        printf("Dividindo a imagem em metade esquerda e metade direita...");
        break;

    case 5:
        printf("Dividindo a imagem em metade superior e metade inferior...");
        break;

    default:
        printf("\nOpção Inválida!\n");
        break;
    }

    return 0;
}