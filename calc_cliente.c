#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>

#define BUFLEN 512  //tamanho maximo do buffer
#define PORT 8888
#define SERVER "127.0.0.1"
#define OPERANDOS 11
 
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
	double num1, r1 = 0, r1Real = 0, r2Real = 0, r1Imag = 0, r2Imag = 0;
    int n2, j;
	struct addrinfo hints, *res;
    char op;
    int recv_len;
    double array[3];
    int intArray[2], x;
    int countArray[OPERANDOS];
    int numPrint;
    int ret;
    int readCharCount = 0, offset = 0;
    char c;
    for (j=0; j<OPERANDOS; j++) {
		countArray[j] = 0;
    }

    if (argc != 3) {
        printf("O numero da porta e o ip devem ser passados como parametro!");
	    return -1;
    }

	bzero(&hints, sizeof(hints)); //limpa a vari�vel


	hints.ai_family = PF_UNSPEC; //tipo do endere�o n�o especificado
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
        fflush(stdin);
        scanf (" %c", &op);

        switch (op) {
            case '+':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                numPrint = sprintf(message,"%c|%lf|%lf",op,array[0],array[1]);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf",&r1);
                printf ("\n%.2lf + %.2lf = %.2lf\n", array[0], array[1], r1);
                break;
            case '-':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                numPrint = sprintf(message,"%c|%lf|%lf",op,array[0],array[1]);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf",&r1);
                printf ("\n%.2lf - %.2lf = %.2lf\n", array[0], array[1], r1);
            break;
            case '*':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                numPrint = sprintf(message,"%c|%lf|%lf",op,array[0],array[1]);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf",&r1);
                printf ("\n%.2lf * %.2lf = %.2lf\n", array[0], array[1], r1);
            break;
            case ':':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                numPrint = sprintf(message,"%c|%lf|%lf",op,array[0],array[1]);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf",&r1);
                printf ("\n%.2lf / %.2lf = %.2lf\n", array[0], array[1], r1);
            break;
            case 'r':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                numPrint = sprintf(message,"%c|%lf|%lf",op,array[0],array[1]);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf",&r1);
                printf ("\nResto de %lf/%lf = %lf\n", array[0], array[1], r1);
            break;
            case 'e':
                printf("Digite os dois numeros desejados para a operacao selecionada:");
                scanf ("%lf", array);
                scanf ("%lf", array + 1);
                numPrint = sprintf(message,"%c|%lf|%lf",op,array[0],array[1]);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf",&r1);
                printf ("\n%.2lf ^ %.2lf = %.2lf\n", array[0], array[1], r1);
            break;
            case 's':
                printf("Digite um numero para se obter sua raiz quadrada: ");
                scanf ("%lf",&num1);
                numPrint = sprintf(message,"%c|%lf",op,num1);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf%*c%lf",&r1Real, &r1Imag);
                printf("\nraiz quadrada de %.2lf = %.2lf + %.2lf i\n", num1, r1Real, r1Imag);
            break;

            case '!':
                printf("Digite um numero para se obter o fatorial do mesmo:");
                scanf ("%lf", &num1);
                numPrint = sprintf(message,"%c|%lf",op,num1);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf",&r1);
                if (r1 == 0) 
                    printf("\n Operacao invalida para operandos negativos. (%lf!)\n", num1);
                else 
                    printf("\n%lf! = %lf\n", num1, r1);
            break;
            
			case 'c':
				printf("Digite o raio do circulo: ");
				scanf("%lf", &num1);
                numPrint = sprintf(message,"%c|%lf",op,num1);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf",&r1);
				printf("\n pi*%lf ^2 = %lf\n", num1, r1);
			break;

			case 'a':
                printf("Digite o raio da esfera: ");
				scanf("%lf", &num1);
                numPrint = sprintf(message,"%c|%lf",op,num1);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf",&r1);
				printf("\n 4*pi*%lf ^2 = %lf\n", num1, r1);
			break;

			case 'b':
				printf("Digite os tres coeficientes da formula de Bhaskara: ");
				scanf("%lf", array);
				scanf("%lf", array+1);
				scanf("%lf", array+2);
                numPrint = sprintf(message,"%c|%lf|%lf|%lf",op,array[0],array[1],array[2]);
                message[numPrint] = '\0';
                if (send(s,message,numPrint,0) == -1) {
                    imprimeErro("send");
                }
                if ((recv_len = recv(s,buf, sizeof(buf),0)) == -1) {
                    imprimeErro("recv");
                }
                sscanf(buf,"%lf%*c%lf%*c%lf%*c%lf",&r1Real, &r1Imag, &r2Real, &r2Imag);

				printf("\n %lf*x^2 + %lf*x + %lf = 0, x1 = %lf + %lfi, x2 = %lf + %lfi \n", array[0], array[1], array[2], r1Real, r1Imag, r2Real, r2Imag);
			break;

	    case 'h':
            numPrint = sprintf(message,"%c",op);
            message[numPrint] = '\0';
            if (send(s,message,numPrint,0) == -1) {
                imprimeErro("send");
            }
			if ((recv_len = recv(s, buf, sizeof(buf), 0)) == -1) {
				imprimeErro("recv()");
            }
            buf[recv_len] = '\0';
            sscanf(buf, "%d%*c%d%*c%d%*c%d%*c%d%*c%d%*c%d%*c%d%*c%d%*c%d%*c%d", countArray, countArray + 1, countArray+ 2, countArray+ 3, countArray + 4, countArray + 5, countArray + 6, countArray + 7, countArray + 8, countArray + 9, countArray + 10);
	    	printf ("\nsoma: %d \nsubtracao: %d \nmultiplicacao: %d\ndivisao: %d \nresto: %d \nexponencial: %d\nraiz: %d\nfatorial: %d\n area do circulo: %d\n area da esfera: %d\n bhaskara: %d\n\n", countArray[0], countArray[1], countArray[2], countArray[3], countArray[4], countArray[5], countArray[6], countArray[7], countArray[8], countArray[9], countArray[10]);
	    break;
           
            default:
                printf("\nERRO: operacao incorreta\n");
                break;
        }
        
    }
 
    
    close(s);
    return 0;
}
