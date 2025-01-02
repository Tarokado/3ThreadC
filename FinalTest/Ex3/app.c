#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>

#define LED_BLINK_START _IO('q', 1)
#define LED_BLINK_STOP _IO('q', 2)

int main() {
    int fd;
    char *dev = "/dev/led_driver";

    fd = open(dev, O_RDWR);
    if (fd < 0) {
        perror("Failed to open the device");
        return errno;
    }

    // Start LED blinking
    if (ioctl(fd, LED_BLINK_START) < 0) {
        perror("Failed to start blinking");
    } else {
        printf("LED blinking started.\n");
    }

    sleep(5); // Let it blink for 5 seconds

    // Stop LED blinking
    if (ioctl(fd, LED_BLINK_STOP) < 0) {
        perror("Failed to stop blinking");
    } else {
        printf("LED blinking stopped.\n");
    }

    close(fd);
    return 0;
}
