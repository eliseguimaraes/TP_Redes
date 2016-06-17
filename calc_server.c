#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <math.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#include <netdb.h>
 

 
#define BUFLEN 512  //tamanho maximo do buffer
#define PORT 8888
#define MAXCLIENTS 50
#define OPERANDOS 11
 
void imprimeErro(char *s)
{
    perror(s);
    exit(1);
}

int fatorial (int n)
{
    int i,y;
    for (i = n-1; i!=1; i--)
    {
        n = n*i;
    }
    y = n;
    return y;
}

double areaCirculo(double raio) {
	return M_PI*pow(raio,2);
}

double areaEsfera(double raio) {
	return 4 * M_PI*pow(raio,2);
}
// Calcula as duas raizes de uma equação quadrática
void bhaskara(double a, double b, double c, double *r1Real, double *r1Imag, double *r2Real, double *r2Imag) {
	double delta;
	delta = pow(b, 2) - 4 * a*c;
	if (delta >= 0) {
		*r1Real = (-b + sqrt(delta)) / (2 * a);
		*r2Real = (-b - sqrt(delta)) / (2 * a);
		*r1Imag = 0;
		*r2Imag = 0;
	}
	else {
		*r1Real = -b / (2 * a);
		*r1Imag = sqrt(-1 * delta) / (2 * a);
		*r2Real = -b / (2 * a);
		*r2Imag = -sqrt(-1 * delta) / (2 * a);
	}
}
 
int main(int argc, char *argv[])
{
	double operando[3], result, number, r1Real, r1Imag, r2Real, r2Imag;
	int connectionSockets[MAXCLIENTS], activity, newSocket, readCount, cSock;
	int passiveSocket, i, j, recvLen, opt = 1, addrlen, charsImpressos = 0;
	int operandoInt1, operandoInt2;
    char buf[BUFLEN], message[BUFLEN];
	char operador, barraDeSeparacao;
    int countArray[OPERANDOS];
    struct sockaddr_in6 cliaddr, servaddr;
	struct addrinfo hints, *res;
	int ret;
	char straddr[INET6_ADDRSTRLEN];
    fd_set readfds;

    for (j=0; j<OPERANDOS; j++) {
	    countArray[j] = 0;
    }

    for (i = 0; i < MAXCLIENTS; i++)
    {
        connectionSockets[i] = 0;
    }


    //a porta precisa receber o parametro, caso contrario erro
    if (argc != 2) {
        printf("O numero da porta deve ser passado como parametro!");
	    return -1;
    }

	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;

	ret = getaddrinfo(NULL, argv[1], &hints, &res);
	if (ret) {
		imprimeErro("getaddrinfo");
	}


    if ((passiveSocket=socket(res->ai_family ,SOCK_STREAM,0)) == 0) {
        imprimeErro("socket");
    }

    //Configura o socket para receber múltiplas conexões
    if( setsockopt(passiveSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        imprimeErro("setsockopt");
    }


     if (bind(passiveSocket, res->ai_addr, res->ai_addrlen) < 0) {
         imprimeErro("bind");
     }

    if (listen(passiveSocket,10) < 0) {
        imprimeErro("listen");
    }

	addrlen = sizeof(cliaddr);

     
    //mantem a espera de dado
    while(1)
    {

        //Limpa o conjunto de sockets
        FD_ZERO(&readfds);
 
        //Adiciona o socket passivo (principal) ao conjunto
        FD_SET(passiveSocket, &readfds);
         
        //Adiciona os connectionSockets ao conjunto
        for ( i = 0 ; i < MAXCLIENTS ; i++)
        {
            if(connectionSockets[i] > 0)
            {
                FD_SET(connectionSockets[i], &readfds);
            }
        }
 
        // Aguarda infinitamente até que haja atividade em algum dos sockets adicionados ao conjunto
		// (Função bloqueante)
        activity = select( MAXCLIENTS + 10 , &readfds , NULL , NULL , NULL);
   
        if ((activity < 0) && (errno!=EINTR))
        {
            printf("Erro: select");
        }
         
		// Acontecimento no socket principal: nova conexão
        if (FD_ISSET(passiveSocket, &readfds))
        {
            //Aceita nova conexão e salva o cliente
			if ((newSocket = accept(passiveSocket, (struct sockaddr *)&cliaddr, (socklen_t*)&addrlen))<0)
			{
				imprimeErro("accept");
			}
			//Adiciona o novo socket ao array de connectionSockets
			for (i = 0; i < MAXCLIENTS; i++)
			{
				if (connectionSockets[i] == 0)
				{
					connectionSockets[i] = newSocket;
					break;
				}
			}
        }
        // Verifica em qual cliente ocorreu a atividade e lida com a requisição
		for (i = 0; i < MAXCLIENTS; i++) {
			cSock = connectionSockets[i];
			if (FD_ISSET(cSock, &readfds)) {
				if ((recvLen = recv(cSock, buf, BUFLEN, 0)) < 0) {
					imprimeErro("recv");
				}
				else if (recvLen == 0) {
					close(cSock);
					connectionSockets[i] = 0;
				}
				else {
					buf[recvLen] = '\0';
					getpeername(cSock, (struct sockaddr*)&cliaddr, (socklen_t*)&addrlen);
					inet_ntop(AF_INET6, &cliaddr.sin6_addr, straddr, sizeof(straddr));
					printf("Pacote recebido de: %s:%d\n", straddr, ntohs(cliaddr.sin6_port));
					printf("Data: %s\n", buf);
					sscanf(buf, "%c", &operador);

					switch (operador) { //verifica a operação recebida, e lê os demais números

						case '+':
							sscanf(buf+2, "%lf%*c%lf", operando, operando + 1);
							result = operando[0] + operando[1];
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[0]++;
							break;
						case '-':
							sscanf(buf + 2, "%lf%*c%lf", operando, operando + 1);
							result = operando[0] - operando[1];
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[1]++;
							break;
						case '*':
							sscanf(buf + 2, "%lf%*c%lf", operando, operando + 1);
							result = operando[0] * operando[1];
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[2]++;
							break;
						case ':':
							sscanf(buf + 2, "%lf%*c%lf", operando, operando + 1);
							result = operando[0] / operando[1];
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[3]++;
							break;
						case 'r':
							sscanf(buf + 2, "%lf%*c%lf", operando, operando + 1);
							operandoInt1 = (int)operando[0];
							operandoInt2 = (int)operando[1];
							result = operandoInt1 % operandoInt2;
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[4]++;
							break;
						case 'e':
							sscanf(buf + 2, "%lf%*c%lf", operando, operando + 1);
							result = pow(operando[0], operando[1]);
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[5]++;
							break;
						case 's':
							sscanf(buf + 2, "%lf", operando);
							result = sqrt(operando[0]);
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[6]++;
							break;

						case '!':
							sscanf(buf + 2, "%lf", operando);
							result = fatorial((int)operando[0]);
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[7]++;
							break;
						case 'c':
							sscanf(buf + 2, "%lf", operando);
							result = areaCirculo(operando[0]);
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[8]++;
							break;
						case 'a':
							sscanf(buf + 2, "%lf", operando);
							result = areaEsfera(operando[0]);
							sprintf(message, "%lf", result);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[9]++;
							break;
						case 'b':
							sscanf(buf + 2, "%lf%*c%lf%*c%lf", operando, operando+1,operando+2);
							bhaskara(operando[0], operando[1], operando[2], &r1Real, &r1Imag, &r2Real, &r2Imag);
							sprintf(message, "%lf|%lf|%lf|%lf", r1Real, r1Imag, r2Real, r2Imag);
							if (send(cSock, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							countArray[10]++;
							break;

						case 'h':
							sprintf(message, "%d|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d", countArray[0], countArray[1], countArray[2], countArray[3], countArray[4], countArray[5], countArray[6], countArray[7], countArray[8], countArray[9], countArray[10]);
							if (send(passiveSocket, message, strlen(message), 0) == -1) {
								imprimeErro("send()");
							}
							break;



						default:
							printf("ERRO: operacao incorreta\n\n");
							break;
					}
				}
			}
		}


    }

 
    close(passiveSocket);
    return 0;
}
