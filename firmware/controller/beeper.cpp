
#include "beeper.h"

static unsigned char peroidCnt, beepCnt, beepPeriod, beepOnTime;

static boolean beep;

void beepSet(unsigned char cnt, unsigned char onTime, unsigned char period)
{
    peroidCnt = 0;
    beepCnt = cnt;
    beepOnTime = onTime;
    beepPeriod = period;
}

void beepOnce()
{
    peroidCnt = 0;
    beepCnt = 1;
    beepOnTime = 5;
    beepPeriod = 5;
}

/*
call per 20ms
*/
void beepPolling(void)
{
    if (beepCnt > 0)
    {
        peroidCnt++;

        if (peroidCnt <= beepOnTime)
            beep = 1;
        else
            beep = 0;

        if (peroidCnt > beepPeriod)
        {
            peroidCnt = 0;

            if (--beepCnt == 0)
                beep = 0;
        }
    }

#if SIM_PWM == 0

    if (beep)
    {
        BEEP_ON;
    }
    else
    {
        BEEP_OFF;
    }

#endif
}

/*
    如果是模拟PWM驱动则在定时器中驱动蜂鸣器
*/
#if SIM_PWM
void beepDrive()
{
    if (beep)
        BEEP_ON;
    else
        BEEP_OFF;
}
#endif


boolean isBeeping()
{
    if (beepCnt > 0)
        return 1;
    else
        return 0;
}
