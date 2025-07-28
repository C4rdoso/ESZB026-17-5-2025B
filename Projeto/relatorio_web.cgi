#!/bin/bash

echo "Content-type: text/html"
echo ""
echo '<HTML><HEAD><meta charset="UTF-8">'
echo '<TITLE>Relatório Web</TITLE></HEAD>'
echo '<BODY style="background-color:#FFFFE0"><H1>Coletando dados de batidas do coração por minuto e oximetria</H1>'
echo 'Dados coletados na porta x do Arduino a n amostras / segundo.<br>'
echo '<br>'
echo 'SPO2 = 95% (saturação de oxigênio)'
echo '78 bpm (batidas por minuto)'
echo 'Gráfico de bpm x tempo:'
#echo 'Rodando programa y. Saída apresentada:<br>'
#/usr/local/bin/le_pot_spi
echo '<br>'
echo '<h2>IMAGEM:</h2>'
#echo '<img src="imagem_spi.cgi">'
echo '<br>'
echo '</HTML>'

