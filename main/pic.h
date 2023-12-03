#ifndef __PIC_H__
#define __PIC_H__

const unsigned char gImage_boom[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,
0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0X00,0X00,0X00,0X00,0X00,
0X00,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0X00,0X00,0X00,0X00,0X00,0X00,0XD6,0XCD,0XC8,
0XD6,0XCD,0XC8,0X00,0X00,0X00,0X00,0X00,0X00,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0X00,
0X00,0X00,0X00,0X00,0X00,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,
0XC8,0X00,0X00,0X00,0X00,0X00,0X00,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,
0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,
0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0X00,0X00,0X00,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0X00,
0X00,0X00,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,
0XC8,0XD6,0XCD,0XC8,0XD6,0XCD,0XC8,0XFF,0X00,0X00,0X00,0XFF,0X00,0X00,0X00,0XFF,
};


const unsigned char gImage_sun[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,
0X8A,0X2A,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XEB,0X8A,0X2A,0XEB,0X8A,
0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0X00,0X00,0X00,
0X00,0X00,0X00,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0X9C,
0X5B,0X1C,0X9C,0X5B,0X1C,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XEB,0X8A,
0X2A,0XEB,0X8A,0X2A,0X9C,0X5B,0X1C,0X9C,0X5B,0X1C,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X9C,0X5B,0X1C,0X9C,0X5B,0X1C,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_sun2cloudy[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,
0X8A,0X2A,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XEB,0X8A,0X2A,0XEB,0X8A,
0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0X00,0X00,0X00,
0X00,0X00,0X00,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XEB,0X8A,0X2A,0XC4,
0XD1,0XDE,0XC4,0XD1,0XDE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XEB,0X8A,
0X2A,0XEB,0X8A,0X2A,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XAD,0XB9,0XC4,0XAD,0XB9,0XC4,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XAD,
0XB9,0XC4,0XAD,0XB9,0XC4,0XAD,0XB9,0XC4,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_rain_s[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,
0XD1,0XDE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,
0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XA3,0XAF,0XB9,0XA3,0XAF,0XB9,0X00,0X00,0X00,
0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XA3,0XAF,0XB9,0XA3,
0XAF,0XB9,0XA3,0XAF,0XB9,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0X98,
0XE5,0X00,0X00,0X00,0X00,0X00,0X00,0X19,0X7B,0XB9,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_rain_m[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,
0XD1,0XDE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,
0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XA3,0XAF,0XB9,0XA3,0XAF,0XB9,0X00,0X00,0X00,
0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XA3,0XAF,0XB9,0XA3,
0XAF,0XB9,0XA3,0XAF,0XB9,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0X98,
0XE5,0X00,0X00,0X00,0X00,0X00,0X00,0X19,0X7B,0XB9,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X19,0X7B,0XB9,0X00,0X00,0X00,0X00,0X00,0X00,0X19,0X7B,0XB9,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_rain_l[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,
0XD1,0XDE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,
0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XA3,0XAF,0XB9,0XA3,0XAF,0XB9,0X00,0X00,0X00,
0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XA3,0XAF,0XB9,0XA3,
0XAF,0XB9,0XA3,0XAF,0XB9,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0X99,
0XE6,0X19,0X7B,0XB9,0X00,0X00,0X00,0X14,0X63,0X94,0X14,0X63,0X94,0X00,0X00,0X00,
0X00,0X00,0X00,0X1F,0X99,0XE6,0X19,0X7B,0XB9,0X00,0X00,0X00,0X14,0X63,0X94,0X14,
0X63,0X94,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_rain_flash[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,
0XD1,0XDE,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,
0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XA3,0XAF,0XB9,0XA3,0XAF,0XB9,0X00,0X00,0X00,
0X00,0X00,0X00,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XC4,0XD1,0XDE,0XA3,0XAF,0XB9,0XA3,
0XAF,0XB9,0XA3,0XAF,0XB9,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X1F,0X99,
0XE6,0X00,0X00,0X00,0XE9,0XD0,0X26,0X00,0X00,0X00,0X14,0X63,0X94,0X00,0X00,0X00,
0X00,0X00,0X00,0X1F,0X99,0XE6,0X00,0X00,0X00,0XE9,0XD0,0X26,0X00,0X00,0X00,0X14,
0X63,0X94,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_zy1[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,
0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0X00,0X00,0X00,0XFF,0XFF,0XFF,0X6E,0XA1,0XA9,0X00,0X00,0X00,0XFF,
0XFF,0XFF,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X6E,0XA1,0XA9,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,
0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,
0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,
0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,
0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_zy2[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,
0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0XFF,0XFF,
0XFF,0X6E,0XA1,0XA9,0X00,0X00,0X00,0XFF,0XFF,0XFF,0X6E,0XA1,0XA9,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,
0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,
0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,
0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,
0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_zy3[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,
0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0X00,0X00,
0X00,0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,
0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,
0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,
0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,
0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,
};

const unsigned char gImage_zy4[192] = { /* 0X00,0X18,0X08,0X00,0X08,0X00,0X00,0X1B, */
0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,
0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0X00,0X00,0X00,0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0X00,
0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0X6E,0XA1,0XA9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X6E,0XA1,0XA9,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,
0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,
0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,
0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,0XA1,0XA9,0X6E,
0XA1,0XA9,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,
0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X6E,0XA1,0XA9,0X00,0X00,0X00,0X00,0X00,0X00,
};


#endif /*__PIC_H__*/