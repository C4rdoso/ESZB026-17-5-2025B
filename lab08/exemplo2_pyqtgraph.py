#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
from pyqtgraph.Qt import QtGui, QtCore
import pyqtgraph as pg
import numpy as np
import serial
import atexit
import time

coletando  = False
obterDelay = False
flushManual = False

def inicia_coleta():
    global coletando
    coletando = True
    conexaoSerial.write(b'i')

def para_coleta():
    global coletando, flushManual
    coletando = False
    conexaoSerial.write(b'p')
    flushManual = True
    
def informa_delay():
    global coletando, obterDelay

    if coletando:
        para_coleta()

    conexaoSerial.write(b'd')
    obterDelay = True
    
def incrementa_delay():
    conexaoSerial.write(b'+')

def decrementa_delay():
    conexaoSerial.write(b'-')

def saindo():
    conexaoSerial.write(b'p')
    print('Saindo')

def update():
    global data1, curve1, ptr1, conexaoSerial, x_atual, npontos, previousTime, obterDelay, flushManual
    
    trafegoSerial.setText("trafego=" + str(conexaoSerial.inWaiting()) + "bytes")

    if flushManual:
        while conexaoSerial.inWaiting() > 0:
            conexaoSerial.read()
        flushManual = False;
    
    if conexaoSerial.inWaiting() > 1:        
        if coletando:
            dado1 = conexaoSerial.read()
            dado2 = conexaoSerial.read()
            novodado = float( (ord(dado1) + ord(dado2)*256.0)*5.0/1023.0 )
            
            data1[x_atual] = novodado
            data1[(x_atual+1)%npontos] = np.nan
            x_atual = x_atual+1
            if x_atual >= npontos:
                x_atual = 0
            
            curve1.setData(data1, connect="finite")
            actualTime = time.time()*1000
            taxa = str(round(actualTime-previousTime))
            previousTime = actualTime
            texto.setText("taxa: "+taxa.zfill(3)+"ms" )
            
        if obterDelay:
            dado1 = conexaoSerial.read()
            dado2 = conexaoSerial.read()
            novodado = ord(dado1) + ord(dado2)*256.0
            textoDelay.setText("delay=" + str(novodado) + "ms")
            obterDelay = False
            inicia_coleta()

win = pg.GraphicsWindow()
win.setWindowTitle('Coletando dados do Arduino via Porta Serial')

npontos = 800
x_atual = 0
p1 = win.addPlot()
p1.setYRange(0,5,padding=0)
data1 = np.zeros(npontos)
curve1 = p1.plot(data1)
ptr1 = 0

previousTime = time.time()*1000 # pega a hora atual, em milissegundos
texto = pg.TextItem(text="", color=(255,255,0), anchor=(0,1))
textoDelay = pg.TextItem(text="delay= ", color=(200, 0, 255), anchor=(0,1))
trafegoSerial = pg.TextItem(text="trafego= ", color=(200, 0, 255), anchor=(0,1))
p1.addItem(texto)
p1.addItem(textoDelay)
p1.addItem(trafegoSerial)
texto.setPos(0,0) # adiciona o texto na posicao (0,0) do grafico
textoDelay.setPos(800, 4)
trafegoSerial.setPos(400, 4)

proxy1 = QtGui.QGraphicsProxyWidget()
botao1 = QtGui.QPushButton('Inicia')
proxy1.setWidget(botao1)
botao1.clicked.connect(inicia_coleta)

proxy2 = QtGui.QGraphicsProxyWidget()
botao2 = QtGui.QPushButton('Para')
proxy2.setWidget(botao2)
botao2.clicked.connect(para_coleta)

proxy3 = QtGui.QGraphicsProxyWidget()
botao3 = QtGui.QPushButton('Obter Delay')
proxy3.setWidget(botao3)
botao3.clicked.connect(informa_delay)

proxy4 = QtGui.QGraphicsProxyWidget()
botao4 = QtGui.QPushButton('Mais Delay')
proxy4.setWidget(botao4)
botao4.clicked.connect(incrementa_delay)

proxy5 = QtGui.QGraphicsProxyWidget()
botao5 = QtGui.QPushButton('Menos delay')
proxy5.setWidget(botao5)
botao5.clicked.connect(decrementa_delay)

p2 = win.addLayout(row=1, col=0)
p2.addItem(proxy1,row=0,col=0)
p2.addItem(proxy2,row=1,col=0)
p2.addItem(proxy3,row=2,col=0)

p3 = win.addLayout(row=2, col=0)
p3.addItem(proxy4,row=0,col=0)
p3.addItem(proxy5,row=0,col=1)

conexaoSerial = serial.Serial('/dev/ttyACM0',115200)
conexaoSerial.write(b'i')
        
# inicia timer rodando o mais rápido possível
timer = QtCore.QTimer()
timer.timeout.connect(update)
timer.start(0)

atexit.register(saindo)

## Start Qt event loop unless running in interactive mode or using pyside.
if __name__ == '__main__':
    QtGui.QApplication.instance().exec_()
