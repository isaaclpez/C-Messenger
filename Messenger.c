#include <stdio.h>          
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define PORT 3550 //puerto
#define BACKLOG 2 //conexiones permitidas
#define MAXDATASIZE 100 //numero maximo de datos en bytes

int main(int argc, char *argv[]){
	
int pid;
pid=fork();

 if(pid>0){
	 
	 
	int fd, fd2; // ficheros descriptores del socket

   struct sockaddr_in server; // informacion del servidor

   struct sockaddr_in client; //informacion del cliente

   int sin_size;
	
   // socket() crea el socket
   if ((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1 ) {  
      printf("error en socket()\n");
      exit(-1);
   }

   //Datos del socket
   server.sin_family = AF_INET;  //familia       

   server.sin_port = htons(PORT); //puerto

   server.sin_addr.s_addr = INADDR_ANY; //Direccion 

   bzero(&(server.sin_zero),8); // 0s en el resto de la estructura

	printf("Usando la direccion %d\n",inet_ntoa(server.sin_addr) ); 
	
   // asigna el puerto a escuchar
   if(bind(fd,(struct sockaddr*)&server,sizeof(struct sockaddr))==-1) {
      printf("error en bind() \n");
      exit(-1);
   }     

	while(1) {
		//Escucha en el puerto
		if(listen(fd,BACKLOG) == -1) {  
			printf("error en listen()\n");
			exit(-1);
									 }
		sin_size=sizeof(struct sockaddr_in);
      
      
		 // Acepta la conexion entrante
		if ((fd2 = accept(fd,(struct sockaddr *)&client,&sin_size))==-1) {
			printf("error en accept()\n");
			exit(-1);
																		 }
																		 
																		 
		  //printf("Se obtuvo una conexi�n desde %s\n",inet_ntoa(client.sin_addr) ); no sirve
     
      
		 // Codigo de mensajes
			  char cad[20];
			  printf("Escribe el mensaje :");
			  gets(cad);
			  send(fd2,cad,22,0); 
			  // Envia el mensaje

			  close(fd2); /* cierra fd2 */
			  
			  
			  
			}


}
else if (pid==0){
	
	while (1){
    int fd, numbytes;   // ficheros descriptores
    char buf[MAXDATASIZE];  // donde se almacena el texto recibido del servidor
    struct hostent *he;   // estructura que va recibir la informacion de red
    struct sockaddr_in server;  //estructura que contendra la informacion del servidor

    if (argc !=2) { //pide los argumentos
      printf("Debe introducir: %s <Direcci�n IP>\n",argv[0]);
      exit(-1);
   }

    if ((he=gethostbyname(argv[1]))==NULL){      //captura la informacion del servidor
      printf("Error en el gethostbyname() \n");
      exit(-1);
   }
	
    if ((fd=socket(AF_INET, SOCK_STREAM, 0))==-1){  // crea el socket stream de la familia AF_INET
      printf("Error en el socket() \n");
      exit(-1);
   }
		//Datos de identificacion de la direccion de red
		
	   server.sin_family = AF_INET;
	   server.sin_port = htons(PORT); 
	   server.sin_addr = *((struct in_addr *)he->h_addr);  
	   bzero(&(server.sin_zero),8);
	   
	   
	// LLama al connect() que conecta al servidor
   if(connect(fd, (struct sockaddr *)&server,
      sizeof(struct sockaddr))==-1){ 
      printf("Error en el connect() \n");
      exit(-1);
   }

   //Recibe el mensaje del Servidor
   if ((numbytes=recv(fd,buf,MAXDATASIZE,0)) == -1){  
      printf("Error en recv() \n");
      exit(-1);
   }	
  
   //buf[numbytes]='\0';
   printf("Usuario1: %s\n",buf); 

   // muestra el mensaje del servidor

   close(fd);    //cierra el fichero descriptor
}
	
	
	
	}
}
