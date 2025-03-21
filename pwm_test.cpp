#include "rpi_pwm.h"

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    RPI_PWM pwm(2, 50);
    printf("Duty cycle at 50%%\n");
    pwm.setDutyCycle(50);
    getchar();
    printf("Duty cycle at 25%%\n");
    pwm.setDutyCycle(25);
    getchar();
    printf("Duty cycle at 25%%\n");
    pwm.setDutyCycle(75);
    getchar();
}
