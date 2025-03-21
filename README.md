# Raspberry PI PWM C++ class

This is a simple wrapper around the new PWM sysfs on the Raspberry PI.
It has been tested on the new Raspberry PI 5.

## Setup

Add to `/boot/firmware/config.txt`:

```
dtoverlay=pwm-2chan
```

and reboot.

Check with:

```
pinctrl -p
```

that you see:

```
12: a3    pd | lo // GPIO18 = PWM0_CHAN2
35: a3    pd | lo // GPIO19 = PWM0_CHAN3
```

which correspond to:

```
/sys/class/pwm/pwmchip2/pwm2: GPIO18 
/sys/class/pwm/pwmchip2/pwm3: GPIO19
```

## Compilation

```
cmake .
make
```

## Usage

Create a class:

```
RPI_PWM pwm(channel, frequency);
```

where channel is either 2 (GPIO18) or 3 (GPIO19). This then creates
an instance which enables the PWM at 0% duty cycle.

To set the duty cycle just write:

```
pwm.setDutyCycle(duty_cycle);
```
where `duty_cycle` is a value between 0 and 100.


## Example program

![alt tag](setup.jpg)

```
./pwm_test <channel>
```

where channel can be either 2 or 3. Default is 2.

It starts with a duty of 50%. If you press a key it changes it to 25%
and then after another key press to 75%. Then it exists after
a final key press.

## Copyright

Bernd Porr
