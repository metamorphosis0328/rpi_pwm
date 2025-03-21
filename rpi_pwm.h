#ifndef __RPIPWM
#define __RPIPWM

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<string>
#include <iostream>
#include<math.h>

class RPI_PWM {
public:
    
    RPI_PWM(int channel, int frequency, float duty_cycle = 0, int chip = 2) {
	chippath = "/sys/class/pwm/pwmchip" + std::to_string(chip);
	pwmpath = chippath + "/pwm" + std::to_string(channel);
	FILE* fp;
	std::string p = chippath+"/export";
	std::cout << p << std::endl;
	fp = fopen(p.c_str(), "w");
	if (NULL == fp) {
	    fprintf(stderr,"PWM device does not exist. Make sure to add 'dtoverlay=pwm-2chan' to /boot/firmware/config.txt.\n");
	    return;
	}
	fprintf(fp, "%d", channel);
	fclose(fp);
	usleep(100000);
	per = (int)1E9 / frequency;
	setPeriod(per);
	setDutyCycle(duty_cycle);
	enable();
    }
    
    ~RPI_PWM() {
	disable();
    }

    void setDutyCycle(float v) {
	int dc = (int)round((float)per * (v / 100.0));
	setDutyCycleNS(dc);
    }

private:
    
    void setPeriod(int ns) {
	writeSYS(pwmpath+"/"+"period", ns);
    }

    void setDutyCycleNS(int ns) {
	writeSYS(pwmpath+"/"+"duty_cycle", ns);
    }

    void enable() {
	writeSYS(pwmpath+"/"+"enable", 1);
    }

    void disable() {
	writeSYS(pwmpath+"/"+"enable", 0);
    }

    int per = 0;
    
    std::string chippath;
    std::string pwmpath;
    
    void writeSYS(std::string filename, int value) {
	FILE* fp;
	fp = fopen(filename.c_str(), "w");
	if (NULL == fp) {
	    fprintf(stderr,"Cannot write to %s.",filename.c_str());
	    return;
	}
	fprintf(fp, "%d", value);
	fclose(fp);
    }
    
};

#endif
