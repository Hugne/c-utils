
client6: client6.c sockopt.c hexdump.c util.c 
	gcc -o hexdump.o -c hexdump.c
	gcc -o util.o -c util.c
	gcc -o sockopt.o -c sockopt.c
	gcc -o client6 client6.c util.o sockopt.o -I.

server6: server6.c
	gcc -o server6 server6.c -I.
	
clean:
	rm -rf client6
	rm -rf server6
	rm -rf *.o
