import sys
from time import sleep
LED_PATH = "/sys/class/gpio/gpio16/"
SYSFS_DIR = "/sys/class/gpio/"
LED_NUMBER = "16"

def writeLED ( filename, value, path=LED_PATH ):
	"Esta funcao escreve o valor 'value' no arquivo 'path+filename'"
	fo = open( path + filename,"w")
	fo.write(value)
	fo.close()
	return

def toggleLED( led_number, time ):
	#Caminho para a GPIO
	led_path = "/sys/class/gpio/gpio" + led_number + "/"

	#Export para habilitar o LED
	writeLED(filename="export", value=led_number, path=SYSFS_DIR)
	sleep(0.1)
	writeLED(filename="direction", value="out", path=led_path)

	#Liga o LED por x tempo
	writeLED(filename="value", value="1", path=led_path)
	sleep(time)
	writeLED(filename="value", value="0", path=led_path)

	#Unexport para desabilitar o LED
	writeLED(filename="unexport", value=led_number, path=SYSFS_DIR)


"""
Sequencia:
	1- LED Vermelho por 2 segundos
	2- LED Verde por 1 segundo
	3- LED Amarelo por 1 segundo
"""

for _ in range (5):
	toggleLED("20", 2)
	toggleLED("21", 1)
	toggleLED("16", 1)

print("Fim do script Python.")
