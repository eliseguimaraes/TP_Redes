#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <math.h>
 
#define BUFLEN 512  //tamanho maximo do buffer
#define PORT 8888
 
void die(char *s)
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
    struct sockaddr_in si_me, si_other;
    double array[2], result, number;
    int intArray[2], res, x;
    int s, i, j, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];
    char op;
    int pid;
    int countArray[8];

    for (j=0; j<8; j++) {
	countArray[j] = 0;
    }


    //a porta precisa receber o parametro, caso contrario erro
    if (argc != 2) {
        printf("O numero da porta deve ser passado como parametro!");
	    return -1;
    }

    //criando socket UDP
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    // zera a estrutura
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //associa o socket a porta
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //mantem a espera de dado
    while(1)
    {


        printf("Aguardando dados...\n\n");
        fflush(stdout);
         
        //tenta receber algum dado, chamada de bloqueio
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1) {
            die("recvfrom()");
        }
        

         
                printf("Pacote recebido de: %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
                buf[recv_len] = '\0';
                printf("Data: %s\n" , buf);
                sscanf(buf, "%c", &op);
                
                //envia ack para o cliente
                if (sendto(s, "ack", 3, 0, (struct sockaddr*) &si_other, slen) == -1) {
                    die("sendto()");
                }
            
                switch (op) {
                    //verifica a operação recebida, e recebe os demais números
                    case '+':
                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                                die("recvfrom()");
                        }
                        result = array[0] + array[1];
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            die("sendto()");
                        }
			countArray[0]++;
                        break;
                    case '-':

                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                                die("recvfrom()");
                        }
                        result = array[0] - array[1];
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            die("sendto()");
                        }
			countArray[1]++;
                        break;
                    case '*':
                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                            die("recvfrom()");
                        }
                        result = array[0]*array[1];
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            die("sendto()");
                        }
			countArray[2]++;
                        break;
                    case ':':
                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                            die("recvfrom()");
                        }
                        result = array[0]/array[1];
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            die("sendto()");
                        }
			countArray[3]++;
                    break;
                    case 'r':
                        if ((recv_len = recvfrom(s, intArray, sizeof(intArray), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                                die("recvfrom()");
                        }
                        res = intArray[0]%intArray[1];
                        if (sendto(s, &res, sizeof(res), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            die("sendto()");
                        }
			countArray[4]++;
                    break;
                    case 'e':
                        if ((recv_len = recvfrom(s, array, sizeof(array), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                            die("recvfrom()");
                        }
                        result = pow(array[0],array[1]);
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            die("sendto()");
                        }
			countArray[5]++;
                    break;
                    case 's':
                        if ((recv_len = recvfrom(s, &number, sizeof(number), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                            die("recvfrom()");
                        }
                        result = sqrt(number);
                        if (sendto(s, &result, sizeof(result), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            die("sendto()");
                        }
			countArray[6]++;
                    break;

                    case '!':
                        if ((recv_len = recvfrom(s, &x, sizeof(x), 0, (struct sockaddr *) &si_other, &slen)) == -1) {
                                die("recvfrom()");
                        }
                        res = fatorial(x);
                        if (sendto(s, &res, sizeof(res), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            die("sendto()");
                        }
			countArray[7]++;
                    break;
		    
  		    case 'h':
                        if (sendto(s, &countArray, sizeof(countArray), 0, (struct sockaddr*) &si_other, slen) == -1) {
                            die("sendto()");
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
