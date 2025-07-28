#!/bin/sh
ARQUIVODADOS=/home/pi/ESZB026-17-5-2025B/lab07/gnuplot/dados3.txt
ARQUIVOSAIDA=/home/pi/ESZB026-17-5-2025B/lab07/gnuplot/dados3.png

gnuplot << EOF
set title "Título"
set ylabel "Eixo Y"
set xlabel "Eixo X"
set terminal png
set output "$ARQUIVOSAIDA"
plot "$ARQUIVODADOS" \
     linecolor rgb '#000000' \
     linetype 1 \
     linewidth 2 \
     pointtype 3 \
     pointsize 2.0 \
     title "meus dados" \
     with linespoints
EOF

