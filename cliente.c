#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>        

#define PORT 3550       // puerto abierto

#define MAXDATASIZE 100   //numero maximo de datos en bytes

int main(int argc, char *argv[])
{
	while (1){
   int fd, numbytes;     //ficheros descriptores

   char buf[MAXDATASIZE];  //almacena el texto recibido

   struct hostent *he;   // estructura que recibe la informacion 

   struct sockaddr_in server;  //informacion de la direccion del servidor
   
   if (argc !=2) { // si no le dan nada de argumentos...
      printf("Uso: %s <Direcci�n IP>\n",argv[0]);
      exit(-1);
   }
//Asigna la informacion del servidor a he
   if ((he=gethostbyname(argv[1]))==NULL){   
      printf("gethostbyname() error\n");
      exit(-1);
   }
	//definicion del socket	
   if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){  
      printf("socket() error\n");
      exit(-1);
   }

//Datos de red del servidor		
   server.sin_family = AF_INET;
   server.sin_port = htons(PORT); 
   server.sin_addr = *((struct in_addr *)he->h_addr); //asigna la direccion del servidor a h_addr
   bzero(&(server.sin_zero),8);
   //conecta al servidor
   if(connect(fd, (struct sockaddr *)&server,
      sizeof(struct sockaddr))==-1){ 
      printf("connect() error\n");
      exit(-1);
   }

	
   //Recibe datos del servidor
   if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){  
      printf("Error en recv() \n");
      exit(-1);
   }

	
   buf[numbytes]='\0';

   printf("Usuario1: %s\n",buf); // muestra el mensaje del servidor

   close(fd);  
}
}
