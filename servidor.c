/* Estos son los ficheros de cabecera usuales */
#include <stdio.h>          
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* codigo de servidor

socket()
bind()
listen()
while (1)
{
   accept()
   while (x)
{
      read()
      write()
}
   close()
}
close()
*/

#define PORT 3550 //puerto
#define BACKLOG 2 //conexiones permitidas

main()
{
	
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

	printf("Usando: la direccion %d\n",inet_ntoa(server.sin_addr) ); 
	
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
		  //printf("Se obtuvo una conexi�n desde %s\n",inet_ntoa(client.sin_addr) ); 
		  /* que mostrar� la IP del cliente */
      
      
      
		 // Codigo de blablas 
			  char cad[20];
			  char* cad2;
			  printf("Escribe el mensaje :");
			  gets(cad);
			  send(fd2,cad,22,0); 
			  // Envia el mensaje

			  close(fd2); /* cierra fd2 */
			  
			  
			  
			}

}
