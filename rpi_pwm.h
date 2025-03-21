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
	fprintf(fp, "%d", channel);
	fclose(fp);
	per = (int)1E9 / frequency;
	setPeriod(per);
	setDutyCycle(duty_cycle);
    }
    
    ~RPI_PWM() {
	disable();
    }

    void setPeriod(int ns) {
	writeSYS(pwmpath+"/"+"period", ns);
    }

    void setDutyCycleNS(int ns) {
	writeSYS(pwmpath+"/"+"duty_cycle", ns);
    }

    void setDutyCycle(float v) {
	int dc = round((float)per * (v / 100.0));
	setDutyCycleNS(dc);
    }

    void enable() {
	writeSYS(pwmpath+"/"+"enable", 1);
    }

    void disable() {
	writeSYS(pwmpath+"/"+"enable", 0);
    }

private:
    
    int per = 0;
    
    std::string chippath;
    std::string pwmpath;
    
    void writeSYS(std::string filename, int value) {
	FILE* fp;
	fp = fopen(filename.c_str(), "w");
	fprintf(fp, "%d", value);
	fclose(fp);
    }
    
};

#endif
