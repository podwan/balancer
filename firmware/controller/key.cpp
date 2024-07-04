#include "key.h"
#include <arduino.h>

static KeyStruct keyStruct[KEY_NUM];
    int keyFlags;
int getKeyFlags()
{

    static int keyFlagsBak; // back up keyflags for filtering
    static char filterCnt;
    static Byte flags;      // real time key flags with bits operation
    static int keyFlagsBuf; // return key flags after filtering

    flags.byte = 0;

    // when IO been multiplexed
    if (digitalRead(POWER_KEY) == 0)
    {
        flags.bits.b0 = 1; // SW1
    }

    if (digitalRead(L_BUTTON) == 0)
    {
        flags.bits.b1 = 1; // SW1
    }
    if (digitalRead(R_BUTTON) == 0)
    {
        flags.bits.b2 = 1; // SW1
    }

    if (flags.byte == keyFlagsBak)
    {
        if (filterCnt < 10)
            filterCnt++;
        else
        {
            if (flags.bits.b0)
                keyFlagsBuf |= 1;
            else
                keyFlagsBuf &= ~1;

            if (flags.bits.b1)
                keyFlagsBuf |= 1 << 1;
            else
                keyFlagsBuf &= ~(1 << 1);

            if (flags.bits.b2)
                keyFlagsBuf |= 1 << 2;
            else
                keyFlagsBuf &= ~(1 << 2);
        }
    }
    else
    {
        filterCnt = 0;
        keyFlagsBak = flags.byte;
    }
#if DEBUG_KEY
    // displayStuff = keyFlagsBuf;
#endif

    return keyFlagsBuf;
}

void keyScan()
{
    static bool keyInited;


    if (keyInited == 0)
    {
        char i;
        keyInited = 1;
        keyStruct[0].keyType = LONG;
        keyStruct[1].keyType = LONG_WITH_SHORT;
        keyStruct[2].keyType = SHORT;
        keyStruct[3].keyType = SHORT;
        for (i = 0; i < KEY_NUM; i++)
        {
            keyStruct[i].trigCnt = 0;
            keyStruct[i].preKeyValue = NO_TRIG;
        }
    }

    keyFlags = getKeyFlags();

    if (keyFlags == 0)
    {
        char i;
        for (i = 0; i < KEY_NUM; i++)
        {
            if (keyStruct[i].keyType == LONG_WITH_SHORT && keyStruct[i].trigCnt > 0)
            {
                keyStruct[i].trigType = TRIG_SHORT;
            }
            keyStruct[i].trigCnt = 0;
            keyStruct[i].preKeyValue = NO_TRIG;
        }
    }

    if (keyStruct[0].preKeyValue == NO_TRIG)
    {
        if (keyFlags == K0)
        {
            if (keyStruct[0].preKeyValue == NO_TRIG)
            {
                if (keyStruct[0].keyType == SHORT || keyStruct[0].keyType == CONTINUOUS)
                {
                    keyStruct[0].trigType = TRIG_SHORT;
                    keyStruct[0].preKeyValue = TRIG_SHORT;
                }
                else if (keyStruct[0].keyType == LONG_WITH_SHORT || keyStruct[0].keyType == LONG)
                {
                    if (++keyStruct[0].trigCnt >= KEY0_LONG_CNT)
                    {
                        keyStruct[0].trigCnt = 0;
                        keyStruct[0].trigType = TRIG_LONG;
                        keyStruct[0].preKeyValue = TRIG_LONG;
                    }
                }
            }
        }
    }
    else if (keyStruct[0].keyType == CONTINUOUS)
    {
        if (keyStruct[0].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[0].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[0].trigCnt = 0;
                keyStruct[0].trigType = TRIG_LONG; // long
                keyStruct[0].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[0].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[0].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[0].trigCnt = 0;
                keyStruct[0].trigType = keyStruct[0].preKeyValue;
            }
        }
    }

    if (keyStruct[1].preKeyValue == NO_TRIG)
    {
        if (keyFlags == K1)
        {
            if (keyStruct[1].preKeyValue == NO_TRIG)
            {
                if (keyStruct[1].keyType == SHORT || keyStruct[1].keyType == CONTINUOUS)
                {
                    keyStruct[1].trigType = TRIG_SHORT;
                    keyStruct[1].preKeyValue = TRIG_SHORT;
                }
                else if (keyStruct[1].keyType == LONG_WITH_SHORT || keyStruct[1].keyType == LONG)
                {
                    if (++keyStruct[1].trigCnt >= KEY1_LONG_CNT)
                    {
                        keyStruct[1].trigCnt = 0;
                        keyStruct[1].trigType = TRIG_LONG;
                        keyStruct[1].preKeyValue = TRIG_LONG;
                    }
                }
            }
        }
    }
    else if (keyStruct[1].keyType == CONTINUOUS)
    {
        if (keyStruct[1].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[1].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[1].trigCnt = 0;
                keyStruct[1].trigType = TRIG_LONG; // long
                keyStruct[1].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[1].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[1].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[1].trigCnt = 0;
                keyStruct[1].trigType = keyStruct[1].preKeyValue;
            }
        }
    }

    if (keyStruct[2].preKeyValue == NO_TRIG)
    {
        if (keyFlags == K2)
        {

            if (keyStruct[2].keyType == SHORT || keyStruct[2].keyType == CONTINUOUS)
            {
                keyStruct[2].trigType = TRIG_SHORT;
                keyStruct[2].preKeyValue = TRIG_SHORT;
            }
            else if (keyStruct[2].keyType == LONG_WITH_SHORT || keyStruct[2].keyType == LONG)
            {
                if (++keyStruct[2].trigCnt >= KEY2_LONG_CNT)
                {
                    keyStruct[2].trigCnt = 0;
                    keyStruct[2].trigType = TRIG_LONG;
                    keyStruct[2].preKeyValue = TRIG_LONG;
                }
            }
        }
    }
    else if (keyStruct[2].keyType == CONTINUOUS)
    {
        if (keyStruct[2].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[2].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[2].trigCnt = 0;
                keyStruct[2].trigType = TRIG_LONG; // long
                keyStruct[2].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[2].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[2].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[2].trigCnt = 0;
                keyStruct[2].trigType = keyStruct[2].preKeyValue;
            }
        }
    }

    if (keyStruct[3].preKeyValue == NO_TRIG)
    {
        if (keyFlags == K3)
        {
            if (keyStruct[3].keyType == SHORT || keyStruct[3].keyType == CONTINUOUS)
            {
                keyStruct[3].trigType = TRIG_SHORT;
                keyStruct[3].preKeyValue = TRIG_SHORT;
            }
            else if (keyStruct[3].keyType == LONG_WITH_SHORT || keyStruct[3].keyType == LONG)
            {
                if (++keyStruct[3].trigCnt >= KEY3_LONG_CNT)
                {
                    keyStruct[3].trigCnt = 0;
                    keyStruct[3].trigType = TRIG_LONG;
                    keyStruct[3].preKeyValue = TRIG_LONG;
                }
            }
        }
    }
    else if (keyStruct[3].keyType == CONTINUOUS)
    {
        if (keyStruct[3].preKeyValue == TRIG_SHORT) // short key
        {
            if (++keyStruct[3].trigCnt >= CONTINUOUS_TRIG_CNT)
            {
                keyStruct[3].trigCnt = 0;
                keyStruct[3].trigType = TRIG_LONG; // long
                keyStruct[3].preKeyValue = TRIG_LONG;
            }
        }
        else if (keyStruct[3].preKeyValue == TRIG_LONG) // long key
        {
            if (++keyStruct[3].trigCnt >= CONTINUOUS_INTEVAL)
            {
                keyStruct[3].trigCnt = 0;
                keyStruct[3].trigType = keyStruct[3].preKeyValue;
            }
        }
    }
}

/*
将物理按键转化为逻辑按键
 */
void getKeyState(KeyState *keyState)
{
    char i;
    if (keyStruct[0].trigType == TRIG_LONG)
        *keyState = DUAL_LONG;
    else if (keyStruct[1].trigType == TRIG_SHORT)
        *keyState = POWER_SHORT;
    else if (keyStruct[1].trigType == TRIG_LONG)
        *keyState = POWER_LONG;
    else if (keyStruct[2].trigType == TRIG_SHORT)
        *keyState = L_BUTTON_SHORT;
    else if (keyStruct[3].trigType == TRIG_SHORT)
        *keyState = R_BUTTON_SHORT;
    else
        *keyState = NONE_KEY;

    for (i = 0; i < KEY_NUM; i++)
    {
        keyStruct[i].trigType = NO_TRIG;
    }
}
