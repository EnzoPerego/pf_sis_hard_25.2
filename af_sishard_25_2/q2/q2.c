// Leia o arquivo README.md ou README.html antes de iniciar este exercício!
// para compilar use:
// gcc q2.c -o q2
// para realizar testes com valgrind use:
// valgrind --leak-check=yes ./q2 < in4.txt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
    int maior_elemento;
    int posicao = 0;
    int posicao_maior;
    
    int n, k, status;

    //quantidade de processos
    scanf("%d", &k);

    //tamanho do array
    scanf("%d", &n);

    int *A = malloc(n * sizeof(int));

    //le os elementos do vetor
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
     
    printf("Processo pai cria os K=%d Processos Filhos para analisar o vetor com N=%d posicoes do Vetor A[]...\n",k,n);
    fflush(stdout);

    // Implemente aqui a criacao dos processos filhos
    for (int i=0; i < k; i++) {
        
        pid_t pid = fork();
        
        if (pid == 0) {
            sleep(5);
            if(A[posicao] > maior_elemento){
                maior_elemento = A[posicao];
                posicao_maior = posicao;
            } 
        }
        
        waitpid(pid, &status, 0);
        
        posicao++;
        if(posicao > n){
            break;
        }
    }


    // coloque as respostas obtida pelo processo pai, substituindo o primeiro `%d` pela ordem do filho 
    // e o segundo `%d` pelo maior elemento no vetor.
    printf("P%d Maior=%d\n", posicao_maior, maior_elemento);

    free(A);


    return 0;
}