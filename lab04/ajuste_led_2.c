#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>      // open()
#include <unistd.h>     // read(), write(), close()
#include <termios.h>    // termios
#include <string.h>     // memset()

#define SERIAL_PORT "/dev/ttyACM0"  // Altere conforme sua porta serial
#define BAUDRATE B115200              // Velocidade da porta (ex: B9600)

int main() {
    int serial_fd;
    struct termios tty;

    // Abre a porta serial
    serial_fd = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd < 0) {
        perror("Erro ao abrir a porta serial");
        return 1;
    }

    // Configurações da porta
    memset(&tty, 0, sizeof(tty));
    if (tcgetattr(serial_fd, &tty) != 0) {
        perror("Erro ao obter atributos da porta");
        close(serial_fd);
        return 1;
    }

    // Configura baudrate
    cfsetospeed(&tty, BAUDRATE);
    cfsetispeed(&tty, BAUDRATE);

    // Configura: 8 bits, sem paridade, 1 stop bit
    tty.c_cflag &= ~PARENB;        // sem paridade
    tty.c_cflag &= ~CSTOPB;        // 1 stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;            // 8 bits
    tty.c_cflag |= CREAD | CLOCAL; // habilita leitura

    tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // modo raw
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // desabilita controle de fluxo
    tty.c_oflag &= ~OPOST;                          // saída raw

    // Aplica configurações
    tcsetattr(serial_fd, TCSANOW, &tty);

    // Loop infinito para leitura
    char buf[256];
    while (1) {
        int n = read(serial_fd, buf, sizeof(buf) - 1);
        if (n > 0) {
            buf[n] = '\0'; // termina a string
            printf("Recebido: %s\n", buf);
        } else {
            usleep(10000); // espera 10ms para evitar busy loop
        }
    }

    close(serial_fd);
    return 0;
}
