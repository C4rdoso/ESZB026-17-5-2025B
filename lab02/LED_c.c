/** Programa baseado no código disponibilizado em:
* Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
* Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define GPIO_YELLOW "/sys/class/gpio/gpio16/"
#define GPIO_RED "/sys/class/gpio/gpio20/"
#define GPIO_GREEN "/sys/class/gpio/gpio21/"
#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(char filename[], char value[]){
   FILE* fp;                           // cria um ponteiro fp
   fp = fopen(filename, "w+");         // abre o arquivo para escrita
   fprintf(fp, "%s", value);           // grava o valor no arquivo
   fclose(fp);                         // fecha o arquivo
}

void toggleGPIO(char LED_number[], char LED_path[], int time){
	char fullpath[128];

	//Habilitando porta
	writeGPIO(GPIO_SYSFS "export", LED_number);
	usleep(100000);

	snprintf(fullpath, sizeof(fullpath), "%sdirection", LED_path);
	writeGPIO(fullpath, "out");

	snprintf(fullpath, sizeof(fullpath), "%svalue", LED_path);
	writeGPIO(fullpath, "1");

	sleep(time);

	snprintf(fullpath, sizeof(fullpath), "%svalue", LED_path);
	writeGPIO(fullpath, "0");

	writeGPIO(GPIO_SYSFS "unexport", LED_number);
}

int main(){
	for(int i=0; i<5; i++){
		toggleGPIO("20", GPIO_RED, 2);
		toggleGPIO("21", GPIO_GREEN,1);
		toggleGPIO("16", GPIO_YELLOW, 1);
	}
	printf("Fim do programa em C\n");
}
