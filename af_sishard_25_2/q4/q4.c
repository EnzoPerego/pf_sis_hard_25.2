// Leia o arquivo README.md ou README.html antes de iniciar este exercício!
// para compilar use
// gcc  q4.c -g -o q4
// ./q4 caso1.txt caso2.txt
// valgrind --leak-check=yes ./q4 caso1.txt caso2.txt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINHA 100

char *le_palavra(int fd) {
    char c;
    char *palavra = malloc(MAX_LINE_LENGTH);
    if (!palavra) return NULL;
    int pos = 0;
    ssize_t r;

    while (1) {
        r = read(fd, &c, 1);
        if (r == 0) {
            // Fim do arquivo
            if (pos == 0) {
                free(palavra);
                return NULL;
            }
            palavra[pos] = '\0';
            return palavra;
        }

        if (r < 0) {
            free(palavra);
            return NULL;
        }

        // 👉 AGORA SEPARA POR '\n' em vez de ' '
        if (c == '\n') {
            palavra[pos] = '\0';
            return palavra;
        }

        // Guarda o caractere lido
        if (pos < MAX_LINE_LENGTH - 1) {
            palavra[pos++] = c;
        } else {
            palavra[pos] = '\0';
            return palavra;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Use:\n./q4 arquivo1.txt arquivo2.txt\n");
        return EXIT_FAILURE;
    }

    int leitura = 0;

    char *file_name_1 = argv[1];
    char *file_name_2 = argv[2];

    int fd1 = open(file_name_1, O_RDONLY);
    int fd2 = open(file_name_2, O_RDONLY);

    char *palavra;

    if(leitura == 0){
        palavra = read_word(arg->file_desc);
        if (palavra == NULL) break;
    }
    if(leitura == 1){
        palavra = read_word(arg->file_desc);
        if (palavra == NULL) break;
    }



    // Escreva a partir daqui o trecho de codigo que abre os dois arquivos de entrada
    // e cria o arquivo de saida ...
    


    return 0;
}