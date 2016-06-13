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
 

 
#define BUFLEN 512  //tamanho maximo do buffer
#define PORT 8888
#define MAXCLIENTS 50
 
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
 
int main(int argc, char *argv[])
{
    double array[2], result, number;
    int intArray[2], res, x, connectionSockets[MAXCLIENTS], activity, newSocket, sock;
    int s, i, j, recv_len, opt = 1;
    char buf[BUFLEN], message[BUFLEN];
    char op;
    int pid;
    int countArray[8];
    struct sockaddr_in6 cliaddr, servaddr;
    fd_set readfds;

    for (j=0; j<8; j++) {
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


    if ((s=socket(AF_INET6 ,SOCK_STREAM,0)) == 0) {
        imprimeErro("socket");
    }

    //Configura o socket para receber múltiplas conexões
    if( setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET6;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(argv[1]);


     if (bind(s,(struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
         imprimeErro("bind");
     }

    if (listen(s,10) < 0) {
        imprimeErro("listen");
    }

     
    //mantem a espera de dado
    while(1)
    {

        //clear the socket set
        FD_ZERO(&readfds);
 
        //add master socket to set
        FD_SET(sock, &readfds);
         
        //add child sockets to set
        for ( i = 0 ; i < MAXCLIENTS ; i++)
        {
            sock = connectionSockets[i];
            if(sock > 0)
            {
                FD_SET( sock , &readfds);
            }
        }
 
        //wait for an activity on one of the sockets , timeout is NULL , so wait indefinitely
        activity = select( MAXCLIENTS + 3 , &readfds , NULL , NULL , NULL);
   
        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }
         
        //If something happened on the master socket , then its an incoming connection
        if (FD_ISSET(s, &readfds))
        {
            //Aceita nova conexão e salva o cliente
        }
        // Verifica em qual cliente ocorreu a atividade e lida com a requisição
        



        printf("Aguardando dados...\n\n");
        fflush(stdout);
         
        //tenta receber algum dado, chamada de bloqueio
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
            imprimeErro("recvfrom()");
        }
        

         
                printf("Pacote recebido de: %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
                buf[recv_len] = '\0';
                printf("Data: %s\n" , buf);
                sscanf(buf, "%c", &op);
                
                //envia ack para o cliente
                if (sendto(s, "ack", 3, 0, (struct sockaddr*) &si_other, slen) == -1) {
                    imprimeErro("sendto()");
                }
            
                switch (op) {
                    //verifica a operação recebida, e recebe os demais números
                    case '+':
                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                                imprimeErro("recvfrom()");
                        }
                        result = array[0] + array[1];
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            imprimeErro("sendto()");
                        }
			countArray[0]++;
                        break;
                    case '-':

                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                                imprimeErro("recvfrom()");
                        }
                        result = array[0] - array[1];
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            imprimeErro("sendto()");
                        }
			countArray[1]++;
                        break;
                    case '*':
                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                            imprimeErro("recvfrom()");
                        }
                        result = array[0]*array[1];
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            imprimeErro("sendto()");
                        }
			countArray[2]++;
                        break;
                    case ':':
                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                            imprimeErro("recvfrom()");
                        }
                        result = array[0]/array[1];
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            imprimeErro("sendto()");
                        }
			countArray[3]++;
                    break;
                    case 'r':
                        if ((recv_len = recvfrom(s, intArray, sizeof(intArray), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                                imprimeErro("recvfrom()");
                        }
                        res = intArray[0]%intArray[1];
                        if (sendto(s, &res, sizeof(res), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            imprimeErro("sendto()");
                        }
			countArray[4]++;
                    break;
                    case 'e':
                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                            imprimeErro("recvfrom()");
                        }
                        result = pow(array[0],array[1]);
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            imprimeErro("sendto()");
                        }
			countArray[5]++;
                    break;
                    case 's':
                        if ((recv_len = recvfrom(s, &number, sizeof(number), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                            imprimeErro("recvfrom()");
                        }
                        result = sqrt(number);
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            imprimeErro("sendto()");
                        }
			countArray[6]++;
                    break;

                    case '!':
                        if ((recv_len = recvfrom(s, &x, sizeof(x), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                                imprimeErro("recvfrom()");
                        }
                        res = fatorial(x);
                        if (sendto(s, &res, sizeof(res), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            imprimeErro("sendto()");
                        }
			countArray[7]++;
                    break;
		    
  		    case 'h':
                        if (sendto(s, &countArray, sizeof(countArray), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            imprimeErro("sendto()");
                        }
			break;

		 

                    default:
                        printf("ERRO: operacao incorreta\n\n");
                        break;
                }
            }

 
    close(s);
    return 0;
}
