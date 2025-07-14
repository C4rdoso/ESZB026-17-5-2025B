/** Programa baseado no codigo disponibilizado em:
* Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
* Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/
*/

// Ajustando o PWM por HARDWARE na Raspberry Pi

#include <stdio.h>
#include <wiringPi.h>

#define pino_PWM0 18                    // o PWM sera acionado na GPIO18

void pulso(int frequencia, unsigned long tempo_alto, unsigned long tempo_baixo) {
	pwmWrite(pino_PWM0, frequencia);
	usleep(tempo_alto);
	pwmWrite(pino_PWM0, 0);
	usleep(tempo_baixo);
}

int main() {                            // este programa deve ser rodado com 'sudo'
   int dc, ciclos;
   wiringPiSetupGpio();                 // usa a numeracao da GPIO
   pinMode(pino_PWM0, PWM_OUTPUT);      // configura a GPIO18 com o PWM por hardware

   // Ajustando a frequencia do PWM em 10kHz com 128 passos de duty cycle
   // frequencia PWM = 19,2 MHz / (divisor * range)
   // 10000 = 19200000 / (divisor * 128) => divisor = 15
   pwmSetMode(PWM_MODE_MS);             // usando frequencia fixa
   pwmSetRange(506);                   // passos do duty cycle (max=4096)
   pwmSetClock(145);                     // fornece uma frequencia de 10kHz (max=4096)
   printf("Iniciando...\n");

   for (int passo = 0; passo < 2; passo++) {
      pulso(258, 500000, 200000);
      pulso(258, 500000, 200000);
      pulso(258, 500000, 1000000);
      pulso(258, 500000, 200000);
      pulso(258, 500000, 2000000);
   }


   printf("Fim.\n");
   return 0;                            // a saida PWM permanece ligada apos o termino do programa
}
