#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>        
/* netbd.h es necesitada por la estructura hostent ;-) */

#define PORT 3550       /* El Puerto Abierto del nodo remoto */

#define MAXDATASIZE 100   /* El n�mero m�ximo de datos en bytes */

int main(int argc, char *argv[])
{
	while (1){
   int fd, numbytes;       
 /* ficheros descriptores */

   char buf[MAXDATASIZE];  
/* en donde es almacenar� el texto recibido *numbytes=recv(*/

   struct hostent *he;         
   /* estructura que recibir� informaci�n sobre el nodo remoto */

   struct sockaddr_in server;  
   /* informaci�n sobre la direcci�n del servidor */

   if (argc !=2) { 
      /* esto es porque nuestro programa s�lo necesitar� un
      argumento, (la IP) */
      printf("Uso: %s <Direcci�n IP>\n",argv[0]);
      exit(-1);
   }

   if ((he=gethostbyname(argv[1]))==NULL){       
      /* llamada a gethostbyname() */
      printf("gethostbyname() error\n");
      exit(-1);
   }
	
   if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){  
      /* llamada a socket() */
      printf("socket() error\n");
      exit(-1);
   }

		
   server.sin_family = AF_INET;
   server.sin_port = htons(PORT); 
   /* htons() es necesaria nuevamente ;-o */
   server.sin_addr = *((struct in_addr *)he->h_addr);  
   /*he->h_addr pasa la informaci�n de ``*he'' a "h_addr" */
   bzero(&(server.sin_zero),8);
   if(connect(fd, (struct sockaddr *)&server,
      sizeof(struct sockaddr))==-1){ 
      /* llamada a connect() */
      printf("connect() error\n");
      exit(-1);
   }

	
   
   if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){  
      /* llamada a recv() */
      printf("Error en recv() \n");
      exit(-1);
   }

	
   //buf[numbytes]='\0';

   printf("Usuario1: %s\n",buf); 

   /* muestra el mensaje de bienvenida del servidor =) */

   close(fd);    /*cerramos fd =) */
}
}
