/*
 * Trabalho Final Parte 1 de Programação Estruturada
 *
 * Autores: José Vitor Oliveira Reis e Vinícius Nunes de Lima Gabriel
 * Data: 8 de agosto de 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>

int escalaCinza()
{
    int largura, altura, valor_maximo;
    char buffer[255];

    FILE *arquivo = fopen("imagem.ppm", "r");
    FILE *saida = fopen("imagem_cinza.ppm", "w");

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
    entrada = fopen("imagem.ppm", "r");
    saida = fopen("imagem_virado_horizontal.ppm", "w");

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
    entrada = fopen("imagem.ppm", "r");
    saida = fopen("imagem_virado_vertical.ppm", "w");

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

int divisaoVertical()
{
    FILE *entrada, *saidaEsquerda, *saidaDireita;
    entrada = fopen("imagem.ppm", "r");
    saidaEsquerda = fopen("imagem_metade_esquerda.ppm", "w");
    saidaDireita = fopen("imagem_metade_direita.ppm", "w");

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int largura, altura, v_max;
    char buffer[255];

    // Leitura do cabeçalho
    fgets(buffer, 255, entrada);
    fprintf(saidaEsquerda, "%s", buffer);
    fprintf(saidaDireita, "%s", buffer);

    fgets(buffer, 255, entrada);
    fprintf(saidaEsquerda, "%s", buffer);
    fprintf(saidaDireita, "%s", buffer);

    fscanf(entrada, "%d %d", &largura, &altura);
    fprintf(saidaEsquerda, "%d %d\n", largura / 2, altura);
    fprintf(saidaDireita, "%d %d\n", largura / 2, altura);

    fscanf(entrada, "%d", &v_max);
    fprintf(saidaEsquerda, "%d\n", v_max);
    fprintf(saidaDireita, "%d\n", v_max);

    int matriz[largura][3];

    // Processamento dos pixels
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fscanf(entrada, "%d", &matriz[j][k]);
            }
        }

        // Gravar metade esquerda
        for (int j = 0; j < largura / 2; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fprintf(saidaEsquerda, "%d ", matriz[j][k]);
            }
        }
        fprintf(saidaEsquerda, "\n");

        // Gravar metade direita
        for (int j = largura / 2; j < largura; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fprintf(saidaDireita, "%d ", matriz[j][k]);
            }
        }
        fprintf(saidaDireita, "\n");
    }

    printf("Imagem dividida com sucesso.\n");

    fclose(entrada);
    fclose(saidaEsquerda);
    fclose(saidaDireita);

    return 0;
}

int divisaoHorizontal()
{
    FILE *entrada, *saidaSuperior, *saidaInferior;
    entrada = fopen("imagem.ppm", "r");
    saidaSuperior = fopen("imagem_metade_superior.ppm", "w");
    saidaInferior = fopen("imagem_metade_inferior.ppm", "w");

    if (entrada == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int largura, altura, v_max;
    char buffer[255];

    // Leitura do cabeçalho
    fgets(buffer, 255, entrada); // Tipo P3
    fprintf(saidaSuperior, "%s", buffer);
    fprintf(saidaInferior, "%s", buffer);

    fgets(buffer, 255, entrada); // Comentário
    fprintf(saidaSuperior, "%s", buffer);
    fprintf(saidaInferior, "%s", buffer);

    fscanf(entrada, "%d %d", &largura, &altura); // Largura e altura
    fprintf(saidaSuperior, "%d %d\n", largura, altura / 2);
    fprintf(saidaInferior, "%d %d\n", largura, altura / 2);

    fscanf(entrada, "%d", &v_max); // Valor máximo
    fprintf(saidaSuperior, "%d\n", v_max);
    fprintf(saidaInferior, "%d\n", v_max);

    int linha[largura][3];

    // Processamento dos pixels
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < largura; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                fscanf(entrada, "%d", &linha[j][k]);
            }
        }

        if (i < altura / 2)
        {
            // Gravar metade superior
            for (int j = 0; j < largura; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    fprintf(saidaSuperior, "%d ", linha[j][k]);
                }
            }
            fprintf(saidaSuperior, "\n");
        }
        else
        {
            // Gravar metade inferior
            for (int j = 0; j < largura; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    fprintf(saidaInferior, "%d ", linha[j][k]);
                }
            }
            fprintf(saidaInferior, "\n");
        }
    }

    printf("Imagem dividida com sucesso.\n");

    fclose(entrada);
    fclose(saidaSuperior);
    fclose(saidaInferior);

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
    printf("0. Sair\n");
    printf("Opção: ");
    scanf("%d", &option);

    return option;
}

int main()
{
    int option;
    do
    {
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
            printf("\nDividindo a imagem em metade esquerda e metade direita...\n");
            divisaoVertical();
            break;
        case 5:
            printf("\nDividindo a imagem em metade superior e metade inferior...\n");
            divisaoHorizontal();
            break;
        case 0:
            printf("\nSaindo...\n");
            break;
        default:
            printf("\nOpção Inválida!\n");
            break;
        }

        printf("\n\n");
    } while (option != 0);

    return 0;
}