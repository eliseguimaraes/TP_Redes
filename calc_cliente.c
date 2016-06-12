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
	double num1, num2, r1 = 0, r2 = 0;
    int r12, n1, n2, j;
	struct addrinfo hints, *res;
    char op;
    int recv_len;
    double array[3];
    int intArray[2], x;
    int countArray[8];

    for (j=0; j<8; j++) {
		countArray[j] = 0;
    }

    if (argc != 3) {
        printf("O numero da porta e o ip devem ser passados como parametro!");
	    return -1;
    }

	bzero(&hints, sizeof(hints)); //limpa a variável


	hints.ai_family = PF_UNSPEC; //tipo do endereço não especificado
	hints.ai_flags = AI_NUMERICHOST;

	ret = getaddrinfo(argv[1], argv[2], &hints, &res);

	if (ret) {
		printf("Endereco invalido.");
		exit(1);
	}

	if ((s = socket(res->ai_family, SOCK_STREAM, 0)) == -1) {
		imprimeErro("socket");
	}


	if (connect(s, res->ai_addr, res->ai_addrlen) == -1) {
		imprimeErro("connect");
	}
    
    while(1) {
        
        printf ("SELECIONE A OPERACAO DESEJADA:\n Soma: + \n Subtracao: - \n Multiplicacao: * \n Divisao: : \n Resto: r \n Exponencial: e \n Raiz Quadrada: s \n Fatorial: ! \n Area do Circulo: c \n Area da esfera: a \n Raizes da formula de Bhaskara: b \n Relatorio de operacoes efetuadas pelo servidor: h \n Sair: ctrl+c\n\n");
        scanf ("%c", &op);

        switch (op) {
            case '+':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);

                printf ("\n%.2lf + %.2lf = %.2lf\n", array[0], array[1], r1);
                break;
            case '-':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);

                printf ("\n%.2lf - %.2lf = %.2lf\n", array[0], array[1], r1);
            break;
            case '*':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);

                printf ("\n%.2lf * %.2lf = %.2lf\n", array[0], array[1], r1);
            break;
            case ':':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);

                printf ("\n%.2lf / %.2lf = %.2lf\n", array[0], array[1], r1);
            break;
            case 'r':
                printf("Digite dois numeros inteiros para se obter o resto da divisao: ");
                scanf ("%d", intArray);
                scanf ("%d", intArray + 1);

                printf ("\nResto de %d/%d = %d\n", intArray[0], intArray[1], r12);
            break;
            case 'e':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);

                printf ("\n%.2lf ^ %.2lf = %.2lf\n", array[0], array[1], r1);
            break;
            case 's':
                printf("Digite um numero para se obter sua raiz quadrada: ");
                scanf ("%lf",&num1);

                printf("\nraiz quadrada de %.2lf = %.2lf\n", num1, r1);
            break;

            case '!':
                printf("Digite um numero inteiro para se obter o fatorial do mesmo:");
                scanf ("%d", &n1);

                printf("\n%d! = %d\n", n1, r12);
            break;
            
			case 'c':
				printf("Digite o raio do circulo: ");
				scanf("%lf", array);

				printf("\n 2*pi*%lf ^2 = %lf\n", array[0], r1);
			break;

			case 'a':
				printf("Digite o raio do circulo: ");
				scanf("%lf", array);

				printf("\n 2*pi*%lf ^2 = %lf\n", array[0], r1);
			break;

			case 'b':
				printf("Digite os tres coeficientes da formula de Bhaskara: ");
				scanf("%lf", array);
				scanf("%lf", array+1);
				scanf("%lf", array+2);


				printf("\n %lf*x^2 + %lf*x + %lf = 0, x1 = %lf, x2 = %lf \n", array[0], array[1], array[2], r1, r2);
			break;

	    case 'h':
			if ((recv_len = recv(s, buf, sizeof(buf), 0)) == -1) {
				imprimeErro("recv()");
            }

			//while (sscanf(str + offset, "%c%d%*c%n", &col, &line, &readCharCount) == 2) {
			//	printf("%c, %d\n", col, line);
			//	offset += readCharCount;
			//}
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
