/* Programa baseado no codigo disponibilizado em:
* Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
* Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/ */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>
#include<string.h>

int main(int argc, char *argv[]){
   int file, count, valor;
   if(argc!=2){
       printf("Numero invalido de argumentos. Saindo...\n");
       return -2;
   }
   
   while (1) {
      if ((file = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
         perror("Falha ao abrir o arquivo.\n");
         return -1;
      }

      struct termios options;
      tcgetattr(file, &options);
      options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
      options.c_iflag = IGNPAR | ICRNL;
      tcflush(file, TCIFLUSH);
      tcsetattr(file, TCSANOW, &options);

      unsigned char receive[100];
      if ((count = read(file, (void*)receive, 100))<0){
         perror("Falha ao ler da entrada.\n");
         return -1;
      }
      if (count==0) printf("Nao havia dados para led.\n");


      usleep(100000);

      //Finaliza o programa e fecha a porta serial
      close(file);
   }
   
   return 0;
}
