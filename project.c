/*
 * UART Communication using termios in Linux
 * Features:
 * - Configure UART (baud rate, data bits, parity, stop bits)
 * - Transmit test message
 * - Receive data using select() with timeout
 * - Error handling
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <sys/select.h>

//#define DEVICE "/dev/ttyUSB0"   // Change if needed
//#define DEVICE "/dev/ttyS0"
#define DEVICE "/dev/pts/2"
#define BAUDRATE B115200

int main() {
    int fd;
    struct termios options;

    // Open UART device
    fd = open(DEVICE, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd < 0) {
        perror("Error opening UART device");
        return EXIT_FAILURE;
    }

    // Get current UART settings
    if (tcgetattr(fd, &options) != 0) {
        perror("tcgetattr failed");
        close(fd);
        return EXIT_FAILURE;
    }

    // Configure UART
    cfsetispeed(&options, BAUDRATE);
    cfsetospeed(&options, BAUDRATE);

    options.c_cflag |= (CLOCAL | CREAD);   // Enable receiver
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;                // 8 data bits
    options.c_cflag &= ~PARENB;            // No parity
    options.c_cflag &= ~CSTOPB;            // 1 stop bit
    options.c_cflag &= ~CRTSCTS;           // No flow control

    options.c_lflag = 0;   // Non-canonical mode
    options.c_oflag = 0;
    options.c_iflag = 0;

    options.c_cc[VMIN]  = 0;
    options.c_cc[VTIME] = 0;

    // Apply settings
    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        perror("tcsetattr failed");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("UART configured successfully on %s\n", DEVICE);

    // Transmit test message
    const char *msg = "Hello from UART!\n";
    int bytes_written = write(fd, msg, strlen(msg));
    if (bytes_written < 0) {
        perror("UART write failed");
        close(fd);
        return EXIT_FAILURE;
    }

    printf("Sent: %s", msg);

    // Receive data using select()
    fd_set readfds;
    struct timeval timeout;
    char buffer[256];

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);

        timeout.tv_sec = 5;   // 5 sec timeout
        timeout.tv_usec = 0;

        int ret = select(fd + 1, &readfds, NULL, NULL, &timeout);

        if (ret < 0) {
            perror("select error");
            break;
        } 
        else if (ret == 0) {
            printf("Timeout: No data received\n");
        } 
        else {
            if (FD_ISSET(fd, &readfds)) {
                int n = read(fd, buffer, sizeof(buffer) - 1);
                if (n < 0) {
                    if (errno != EAGAIN) {
                        perror("read error");
                        break;
                    }
                } else if (n > 0) {
                    buffer[n] = '\0';
                    printf("Received: %s\n", buffer);
                }
            }
        }
    }

    close(fd);
    return EXIT_SUCCESS;
}
