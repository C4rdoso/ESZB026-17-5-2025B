#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
int main(){
	int pino_PWM = 23;                         // pwm por software na GPIO23
	int brilho, count, file;
	int range = 100;                           // periodo do PWM = 100us*range
	wiringPiSetupGpio();                       // usar a numeracao GPIO, nao WPi
	pinMode(pino_PWM,OUTPUT);	           // configura GPIO23 como saida
	softPwmCreate(pino_PWM, 1, range);         // inicializa PWM por software
   
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
      
       // Loop infinito para leitura
       char buf[256];
       while (1) {
           int n = read(file, buf, sizeof(buf) - 1);
           if (n > 0) {
               buf[n] = '\0'; // termina a string
               printf("Recebido: %s\n", buf);
           } else {
               usleep(10000); // espera 10ms para evitar busy loop
           }
           
            brilho = atoi(buf);
            brilho = brilho/10;
            printf("Valor ajustado: %d\n",brilho);
            softPwmWrite (pino_PWM, brilho); // altera o duty cycle do PWM
            delay (100) ;                     // aguarda 10ms
       }
      close(file);
	}
}
