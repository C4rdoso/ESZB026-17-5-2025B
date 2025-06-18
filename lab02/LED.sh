#!/bin/bash

#GPIOS usadas
LED_RED=20
LED_GREEN=21
LED_YELLOW=16

#Escreve algo na GPIO
writeGPIO() {
	echo "$2" > "/sys/class/gpio/gpio$1/$3"
}

#Habilita todas as GPIOS
setupGPIO() {
	for gpio in "$LED_RED" "$LED_GREEN" "$LED_YELLOW"; do
		echo "$gpio" > /sys/class/gpio/export
		sleep 0.1
		echo "out" > "/sys/class/gpio/gpio$gpio/direction"
	done
}

#Desabilita todas as GPIOS
cleanupGPIO() {
	for gpio in "$LED_RED" "$LED_GREEN" "$LED_YELLOW"; do
		echo "$gpio" > /sys/class/gpio/unexport
	done
}

#Faz o led piscar utilizando as função definida anteriormente
toggleLED() {
	gpio=$1
	delay=$2
	writeGPIO "$gpio" 1 "value"
	sleep "$delay"
	writeGPIO "$gpio" 0 "value"
}

#============== INICIO DO PROGRAMA ==============

#Habilita a GPIO
setupGPIO

#Executa a lógica de semáforo 5 vezes
for i in {1..5}; do
	toggleLED "$LED_RED" 2
	toggleLED "$LED_GREEN" 1
	toggleLED "$LED_YELLOW" 1
done

#Desabilita as GPIOS
cleanupGPIO

#Sinaliza o fim do script
echo "Fim do script bash"
