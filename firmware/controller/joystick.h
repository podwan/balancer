#ifndef __JOY_STICK_H
#define __JOY_STICK_H



int map_normal(int val, int lower, int middle, int upper, bool reverse);
void read_joydata();
void eeprom_init();
void zero_test();

extern int LX_read, LY_read, RX_read, RY_read;

#endif