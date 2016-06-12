#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include "calc_cliente.h"

#define BUFLEN 512  //tamanho maximo do buffer
#define PORT 8888
#define SERVER "127.0.0.1"
 
void imprimeErro(char *s)
{
    perror(s);
    exit(1);
}
 
int main(int argc, char *argv[])
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
    double num1, num2, result=0;
    int res, n1, n2, j;
    char op;
    int recv_len;
    double array[2];
    int intArray[2], x;
    int countArray[8];

    for (j=0; j<8; j++) {
	countArray[j] = 0;
    }

    if (argc != 3) {
        printf("O numero da porta e o ip devem ser passados como parametro!");
	    return -1;
    }
 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        imprimeErro("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(atoi(argv[2]));
     
    if (inet_aton(argv[1] , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
    
    while(1) {
        
        printf ("SELECIONE A OPERACAO DESEJADA:\n Soma: + \n Subtracao: - \n Multiplicacao: * \n Divisao: : \n Resto: r \n Exponencial: e \n Raiz Quadrada: s \n Fatorial: ! \n Area do Circuito: c \n Area da esfera: a \n Raizes da formula de Bhaskara: b \n Relatorio de operacoes efetuadas pelo servidor: h \n Sair: ctrl+c\n\n");
        scanf (" %c", &op);
        //envia a mensagem
        if (sendto(s, &op, sizeof(op) , 0 , (struct sockaddr *) &si_other, slen)==-1) {
            imprimeErro("sendto()");
        }
            
        //recebe e imprime a resposta
        memset(buf,'\0', BUFLEN); // limpa o buffer
        //tenta receber algum dado, chamada de bloqueio
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1) {
            imprimeErro("recvfrom()");
        }
        if (strcmp(buf, "ack")) {
            printf("\nResposta inesperada recebida do seridor. Encerrando...");
            exit(1);
        }
        
        switch (op) {
            case '+':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                //envia a mensagem
                if (sendto(s, array, sizeof(array) , 0 , (struct sockaddr *) &si_other, slen)==-1) {
                    imprimeErro("sendto()");
                }
                if (recvfrom(s, &result, sizeof(result), 0, (struct sockaddr *) &si_other, &slen) == -1) {
                    imprimeErro("recvfrom()");
                }
                printf ("\n%.2lf + %.2lf = %.2lf\n", array[0], array[1], result);
                break;
            case '-':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                //envia a mensagem
                if (sendto(s, array, sizeof(array) , 0 , (struct sockaddr *) &si_other, slen)==-1) {
                    imprimeErro("sendto()");
                }
                if (recvfrom(s, &result, sizeof(result), 0, (struct sockaddr *) &si_other, &slen) == -1) {
                    imprimeErro("recvfrom()");
                }
                printf ("\n%.2lf - %.2lf = %.2lf\n", array[0], array[1], result);
            break;
            case '*':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                //envia a mensagem
                if (sendto(s, array, sizeof(array) , 0 , (struct sockaddr *) &si_other, slen)==-1) {
                    imprimeErro("sendto()");
                }
                if (recvfrom(s, &result, sizeof(result), 0, (struct sockaddr *) &si_other, &slen) == -1) {
                    imprimeErro("recvfrom()");
                }
                printf ("\n%.2lf * %.2lf = %.2lf\n", array[0], array[1], result);
            break;
            case ':':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                //envia a mensagem
                if (sendto(s, array, sizeof(array) , 0 , (struct sockaddr *) &si_other, slen)==-1) {
                    imprimeErro("sendto()");
                }
                if (recvfrom(s, &result, sizeof(result), 0, (struct sockaddr *) &si_other, &slen) == -1) {
                    imprimeErro("recvfrom()");
                }
                printf ("\n%.2lf / %.2lf = %.2lf\n", array[0], array[1], result);
            break;
            case 'r':
                printf("Digite dois numeros inteiros para se obter o resto da divisao: ");
                scanf ("%d", intArray);
                scanf ("%d", intArray + 1);
                //envia a mensagem
                if (sendto(s, intArray, sizeof(intArray) , 0 , (struct sockaddr *) &si_other, slen)==-1) {
                    imprimeErro("sendto()");
                }
                if (recvfrom(s, &res, sizeof(res), 0, (struct sockaddr *) &si_other, &slen) == -1) {
                    imprimeErro("recvfrom()");
                }
                printf ("\nResto de %d/%d = %d\n", intArray[0], intArray[1], res);
            break;
            case 'e':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                //envia a mensagem
                if (sendto(s, array, sizeof(array) , 0 , (struct sockaddr *) &si_other, slen)==-1) {
                    imprimeErro("sendto()");
                }
                if (recvfrom(s, &result, sizeof(result), 0, (struct sockaddr *) &si_other, &slen) == -1) {
                    imprimeErro("recvfrom()");
                }
                printf ("\n%.2lf ^ %.2lf = %.2lf\n", array[0], array[1], result);
            break;
            case 's':
                printf("Digite um numero para se obter sua raiz quadrada: ");
                scanf ("%lf",&num1);
                //envia a mensagem
                if (sendto(s, &num1, sizeof(num1) , 0 , (struct sockaddr *) &si_other, slen)==-1) {
                    imprimeErro("sendto()");
                }
                if (recvfrom(s, &result, sizeof(result), 0, (struct sockaddr *) &si_other, &slen) == -1) {
                    imprimeErro("recvfrom()");
                }
                printf("\nraiz quadrada de %.2lf = %.2lf\n", num1, result);
            break;

            case '!':
                printf("Digite um numero inteiro para se obter o fatorial do mesmo:");
                scanf ("%d", &n1);
                //envia a mensagem
                if (sendto(s, &n1, sizeof(n1) , 0 , (struct sockaddr *) &si_other, slen)==-1) {
                    imprimeErro("sendto()");
                }
                if (recvfrom(s, &res, sizeof(res), 0, (struct sockaddr *) &si_other, &slen) == -1) {
                    imprimeErro("recvfrom()");
                }
                printf("\n%d! = %d\n", n1, res);
            break;
            
	    case 'h':
                if (recvfrom(s, &countArray, sizeof(countArray), 0, (struct sockaddr *) &si_other, &slen) == -1) {
                    imprimeErro("recvfrom()");
                }
	    	printf ("\nsoma: %d \nsubtracao: %d \nmultiplicacao: %d\ndivisao: %d \nresto: %d \nexponencial: %d\nraiz: %d\nfatorial: %d\n\n", countArray[0], countArray[1], countArray[2], countArray[3], countArray[4], countArray[5], countArray[6], countArray[7]);
	    break;
           
            default:
                printf("\nERRO: operacao incorreta\n");
                break;
        }
        
    }
 
    
 
    close(s);
    return 0;
}
