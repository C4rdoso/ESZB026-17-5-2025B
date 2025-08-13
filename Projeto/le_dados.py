import time
import struct
import serial

#Nome do arquivo de texto a ser escrito
arquivo_leitura = ''
arquivo_grafico = ''


#Abre a porta serial
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=5)

#Envia a solicitação
ser.write(b"R")

#Espera 1 segundo
time.sleep(1)

#Le os bytes recebidos
data = ser.read(122)

#Extrai o valor de batimentos e a saturação de oxigenio no sangue, logo após as amostras do gráfico
batimentos, saturacao = struct.unpack("BB", data[:2])
amostras = struct.unpack("<" + "I" * 30, data[2:])



ser.close()
