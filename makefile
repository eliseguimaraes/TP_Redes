all: cliente servidor

cliente:
	gcc calc_cliente.c -o calc_cliente 

servidor:
	gcc calc_server.c -o calc_server -lm

runs:
	./calc_server 1314
runc:
	./calc_cliente 127.0.0.1 1314
