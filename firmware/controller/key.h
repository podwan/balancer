#ifndef __KEY_H
#define __KEY_H

#define L_BUTTON 6
#define R_BUTTON 19
#define POWER_KEY 10

#define KEY0_LONG_CNT 180
#define KEY1_LONG_CNT 300
#define KEY2_LONG_CNT 300
#define KEY3_LONG_CNT 1
#define KEY4_LONG_CNT 850

#define CONTINUOUS_INTEVAL 40

#define CONTINUOUS_TRIG_CNT 100

#define KEY_NUM 4


#define K1 (1 << 0)
#define K2 (1 << 1)
#define K3 (1 << 2)
#define K0 (K2 | K3)



typedef union {
  unsigned char byte;
  struct
  {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
  } bits;
} Byte;


typedef enum {
  NO_TRIG,
  TRIG_SHORT,
  TRIG_LONG,
} TrigType;

typedef enum {
  SHORT,
  LONG_WITH_SHORT,
  CONTINUOUS,
  LONG
} KeyType;

typedef struct
{
  KeyType keyType;
  int trigCnt;
  TrigType trigType;
  TrigType preKeyValue;
} KeyStruct;


typedef enum {
  NONE_KEY,
  POWER_SHORT,
  POWER_LONG,
  L_BUTTON_SHORT,
  R_BUTTON_SHORT,
  DUAL_LONG
} KeyState;

extern int keyFlags;
void getKeyState(KeyState *keyState);
void keyScan();
#endif
