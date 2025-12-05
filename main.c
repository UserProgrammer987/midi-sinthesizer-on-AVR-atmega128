#include <avr/io.h>
#define F_CPU 11059200UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#define RS 5 // нога PE0(proteus)/PD5 к RS подключена
#define RW 4 // нога PE1(proteus)/PD4 к RW подключена
#define E 6 // нога PE2(proteus)/PD6 к E подключена

#define REST  0
#define A0    21
#define AS0   22
#define B0    23
#define C1    24
#define CS1   25
#define D1    26
#define DS1   27
#define E1    28
#define F1    29
#define FS1   30
#define G1    31
#define GS1   32
#define A1    33
#define AS1   34
#define B1    35
#define C2    36
#define CS2   37
#define D2    38
#define DS2   39
#define E2    40
#define F2    41
#define FS2   42
#define G2    43
#define GS2   44
#define A2    45
#define AS2   46
#define B2    47
#define C3    48
#define CS3   49
#define D3    50
#define DS3   51
#define E3    52
#define F3    53
#define FS3   54
#define G3    55
#define GS3   56
#define A3    57
#define AS3   58
#define B3    59
#define C4    60
#define CS4   61
#define D4    62
#define DS4   63
#define E4    64
#define F4    65
#define FS4   66
#define G4    67
#define GS4   68
#define A4    69
#define AS4   70
#define B4    71
#define C5    72
#define CS5   73
#define D5    74
#define DS5   75
#define E5    76
#define F5    77
#define FS5   78
#define G5    79
#define GS5   80
#define A5    81
#define AS5   82
#define B5    83
#define C6    84
#define CS6   85
#define D6    86
#define DS6   87
#define E6    88
#define F6    89
#define FS6   90
#define G6    91
#define GS6   92
#define A6    93
#define AS6   94
#define B6    95
#define C7    96
#define CS7   97
#define D7    98
#define DS7   99
#define E7    100

#define ZADERSHKA 125

uint16_t timeMs = 0;

void setTimeZero(){
    TCNT1 = 0;
    timeMs = 0;
}

uint16_t getTimeMs(){
    return timeMs;
}

const uint8_t sine[1024] = {
    127, 128, 129, 129, 130, 131, 132, 132, 133, 134, 135, 136, 136, 137, 138, 139,
    139, 140, 141, 142, 143, 143, 144, 145, 146, 146, 147, 148, 149, 150, 150, 151,
    152, 153, 153, 154, 155, 156, 156, 157, 158, 159, 159, 160, 161, 162, 163, 163,
    164, 165, 166, 166, 167, 168, 168, 169, 170, 171, 171, 172, 173, 174, 174, 175,
    176, 177, 177, 178, 179, 179, 180, 181, 182, 182, 183, 184, 184, 185, 186, 186,
    187, 188, 188, 189, 190, 191, 191, 192, 193, 193, 194, 195, 195, 196, 197, 197,
    198, 198, 199, 200, 200, 201, 202, 202, 203, 204, 204, 205, 205, 206, 207, 207,
    208, 208, 209, 210, 210, 211, 211, 212, 213, 213, 214, 214, 215, 215, 216, 217,
    217, 218, 218, 219, 219, 220, 220, 221, 221, 222, 223, 223, 224, 224, 225, 225,
    226, 226, 227, 227, 228, 228, 228, 229, 229, 230, 230, 231, 231, 232, 232, 233,
    233, 233, 234, 234, 235, 235, 236, 236, 236, 237, 237, 238, 238, 238, 239, 239,
    239, 240, 240, 241, 241, 241, 242, 242, 242, 243, 243, 243, 244, 244, 244, 244,
    245, 245, 245, 246, 246, 246, 247, 247, 247, 247, 248, 248, 248, 248, 249, 249,
    249, 249, 249, 250, 250, 250, 250, 250, 251, 251, 251, 251, 251, 252, 252, 252,
    252, 252, 252, 252, 253, 253, 253, 253, 253, 253, 253, 253, 254, 254, 254, 254,
    254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254,
    255, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254,
    254, 254, 254, 254, 254, 253, 253, 253, 253, 253, 253, 253, 253, 252, 252, 252,
    252, 252, 252, 252, 251, 251, 251, 251, 251, 250, 250, 250, 250, 250, 249, 249,
    249, 249, 249, 248, 248, 248, 248, 247, 247, 247, 247, 246, 246, 246, 245, 245,
    245, 244, 244, 244, 244, 243, 243, 243, 242, 242, 242, 241, 241, 241, 240, 240,
    239, 239, 239, 238, 238, 238, 237, 237, 236, 236, 236, 235, 235, 234, 234, 233,
    233, 233, 232, 232, 231, 231, 230, 230, 229, 229, 228, 228, 228, 227, 227, 226,
    226, 225, 225, 224, 224, 223, 223, 222, 221, 221, 220, 220, 219, 219, 218, 218,
    217, 217, 216, 215, 215, 214, 214, 213, 213, 212, 211, 211, 210, 210, 209, 208,
    208, 207, 207, 206, 205, 205, 204, 204, 203, 202, 202, 201, 200, 200, 199, 198,
    198, 197, 197, 196, 195, 195, 194, 193, 193, 192, 191, 191, 190, 189, 188, 188,
    187, 186, 186, 185, 184, 184, 183, 182, 182, 181, 180, 179, 179, 178, 177, 177,
    176, 175, 174, 174, 173, 172, 171, 171, 170, 169, 168, 168, 167, 166, 166, 165,
    164, 163, 163, 162, 161, 160, 159, 159, 158, 157, 156, 156, 155, 154, 153, 153,
    152, 151, 150, 150, 149, 148, 147, 146, 146, 145, 144, 143, 143, 142, 141, 140,
    139, 139, 138, 137, 136, 136, 135, 134, 133, 132, 132, 131, 130, 129, 129, 128,
    127, 126, 125, 125, 124, 123, 122, 122, 121, 120, 119, 118, 118, 117, 116, 115,
    115, 114, 113, 112, 111, 111, 110, 109, 108, 108, 107, 106, 105, 104, 104, 103,
    102, 101, 101, 100,  99,  98,  98,  97,  96,  95,  95,  94,  93,  92,  91,  91,
     90,  89,  88,  88,  87,  86,  86,  85,  84,  83,  83,  82,  81,  80,  80,  79,
     78,  77,  77,  76,  75,  75,  74,  73,  72,  72,  71,  70,  70,  69,  68,  68,
     67,  66,  66,  65,  64,  63,  63,  62,  61,  61,  60,  59,  59,  58,  57,  57,
     56,  56,  55,  54,  54,  53,  52,  52,  51,  50,  50,  49,  49,  48,  47,  47,
     46,  46,  45,  44,  44,  43,  43,  42,  41,  41,  40,  40,  39,  39,  38,  37,
     37,  36,  36,  35,  35,  34,  34,  33,  33,  32,  31,  31,  30,  30,  29,  29,
     28,  28,  27,  27,  26,  26,  26,  25,  25,  24,  24,  23,  23,  22,  22,  21,
     21,  21,  20,  20,  19,  19,  18,  18,  18,  17,  17,  16,  16,  16,  15,  15,
     15,  14,  14,  13,  13,  13,  12,  12,  12,  11,  11,  11,  10,  10,  10,  10,
      9,   9,   9,   8,   8,   8,   7,   7,   7,   7,   6,   6,   6,   6,   5,   5,
      5,   5,   5,   4,   4,   4,   4,   4,   3,   3,   3,   3,   3,   2,   2,   2,
      2,   2,   2,   2,   1,   1,   1,   1,   1,   1,   1,   1,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   1,   1,   1,   1,   1,   1,   1,   1,   2,   2,   2,
      2,   2,   2,   2,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   5,   5,
      5,   5,   5,   6,   6,   6,   6,   7,   7,   7,   7,   8,   8,   8,   9,   9,
      9,  10,  10,  10,  10,  11,  11,  11,  12,  12,  12,  13,  13,  13,  14,  14,
     15,  15,  15,  16,  16,  16,  17,  17,  18,  18,  18,  19,  19,  20,  20,  21,
     21,  21,  22,  22,  23,  23,  24,  24,  25,  25,  26,  26,  26,  27,  27,  28,
     28,  29,  29,  30,  30,  31,  31,  32,  33,  33,  34,  34,  35,  35,  36,  36,
     37,  37,  38,  39,  39,  40,  40,  41,  41,  42,  43,  43,  44,  44,  45,  46,
     46,  47,  47,  48,  49,  49,  50,  50,  51,  52,  52,  53,  54,  54,  55,  56,
     56,  57,  57,  58,  59,  59,  60,  61,  61,  62,  63,  63,  64,  65,  66,  66,
     67,  68,  68,  69,  70,  70,  71,  72,  72,  73,  74,  75,  75,  76,  77,  77,
     78,  79,  80,  80,  81,  82,  83,  83,  84,  85,  86,  86,  87,  88,  88,  89,
     90,  91,  91,  92,  93,  94,  95,  95,  96,  97,  98,  98,  99, 100, 101, 101,
    102, 103, 104, 104, 105, 106, 107, 108, 108, 109, 110, 111, 111, 112, 113, 114,
    115, 115, 116, 117, 118, 118, 119, 120, 121, 122, 122, 123, 124, 125, 125, 126,
};

#define TABLE_SIZE 1024
#define TABLE_BITS 10
#define SAMPLE_RATE 15935

// Объявления phase переменных для нот 21-35 (A0 - B1)
static uint32_t phase21 = 0;
static uint32_t phase22 = 0;
static uint32_t phase23 = 0;
static uint32_t phase24 = 0;
static uint32_t phase25 = 0;
static uint32_t phase26 = 0;
static uint32_t phase27 = 0;
static uint32_t phase28 = 0;
static uint32_t phase29 = 0;
static uint32_t phase30 = 0;
static uint32_t phase31 = 0;
static uint32_t phase32 = 0;
static uint32_t phase33 = 0;
static uint32_t phase34 = 0;
static uint32_t phase35 = 0;

// Объявления phase переменных для нот 36-47 (C2 - B2)
static uint32_t phase36 = 0;
static uint32_t phase37 = 0;
static uint32_t phase38 = 0;
static uint32_t phase39 = 0;
static uint32_t phase40 = 0;
static uint32_t phase41 = 0;
static uint32_t phase42 = 0;
static uint32_t phase43 = 0;
static uint32_t phase44 = 0;
static uint32_t phase45 = 0;
static uint32_t phase46 = 0;
static uint32_t phase47 = 0;

// Объявления phase переменных для нот 48-59 (C3 - B3)
static uint32_t phase48 = 0;
static uint32_t phase49 = 0;
static uint32_t phase50 = 0;
static uint32_t phase51 = 0;
static uint32_t phase52 = 0;
static uint32_t phase53 = 0;
static uint32_t phase54 = 0;
static uint32_t phase55 = 0;
static uint32_t phase56 = 0;
static uint32_t phase57 = 0;
static uint32_t phase58 = 0;
static uint32_t phase59 = 0;

// Объявления phase переменных для нот 60-71 (C4 - B4)
static uint32_t phase60 = 0;
static uint32_t phase61 = 0;
static uint32_t phase62 = 0;
static uint32_t phase63 = 0;
static uint32_t phase64 = 0;
static uint32_t phase65 = 0;
static uint32_t phase66 = 0;
static uint32_t phase67 = 0;
static uint32_t phase68 = 0;
static uint32_t phase69 = 0;
static uint32_t phase70 = 0;
static uint32_t phase71 = 0;

// Объявления phase переменных для нот 72-83 (C5 - B5)
static uint32_t phase72 = 0;
static uint32_t phase73 = 0;
static uint32_t phase74 = 0;
static uint32_t phase75 = 0;
static uint32_t phase76 = 0;
static uint32_t phase77 = 0;
static uint32_t phase78 = 0;
static uint32_t phase79 = 0;
static uint32_t phase80 = 0;
static uint32_t phase81 = 0;
static uint32_t phase82 = 0;
static uint32_t phase83 = 0;

// Объявления phase переменных для нот 84-95 (C6 - B6)
static uint32_t phase84 = 0;
static uint32_t phase85 = 0;
static uint32_t phase86 = 0;
static uint32_t phase87 = 0;
static uint32_t phase88 = 0;
static uint32_t phase89 = 0;
static uint32_t phase90 = 0;
static uint32_t phase91 = 0;
static uint32_t phase92 = 0;
static uint32_t phase93 = 0;
static uint32_t phase94 = 0;
static uint32_t phase95 = 0;

// Объявления phase переменных для нот 96-100 (C7 - E7)
static uint32_t phase96 = 0;
static uint32_t phase97 = 0;
static uint32_t phase98 = 0;
static uint32_t phase99 = 0;
static uint32_t phase100 = 0;
static uint32_t phase_step21 = (uint32_t)( ( (27.50f) * 4294967296.0f) / SAMPLE_RATE );   // A0
static uint32_t phase_step22 = (uint32_t)( ( (29.14f) * 4294967296.0f) / SAMPLE_RATE );   // A#0/Bb0
static uint32_t phase_step23 = (uint32_t)( ( (30.87f) * 4294967296.0f) / SAMPLE_RATE );   // B0
static uint32_t phase_step24 = (uint32_t)( ( (32.70f) * 4294967296.0f) / SAMPLE_RATE );   // C1
static uint32_t phase_step25 = (uint32_t)( ( (34.65f) * 4294967296.0f) / SAMPLE_RATE );   // C#1/Db1
static uint32_t phase_step26 = (uint32_t)( ( (36.71f) * 4294967296.0f) / SAMPLE_RATE );   // D1
static uint32_t phase_step27 = (uint32_t)( ( (38.89f) * 4294967296.0f) / SAMPLE_RATE );   // D#1/Eb1
static uint32_t phase_step28 = (uint32_t)( ( (41.20f) * 4294967296.0f) / SAMPLE_RATE );   // E1
static uint32_t phase_step29 = (uint32_t)( ( (43.65f) * 4294967296.0f) / SAMPLE_RATE );   // F1
static uint32_t phase_step30 = (uint32_t)( ( (46.25f) * 4294967296.0f) / SAMPLE_RATE );   // F#1/Gb1
static uint32_t phase_step31 = (uint32_t)( ( (49.00f) * 4294967296.0f) / SAMPLE_RATE );   // G1
static uint32_t phase_step32 = (uint32_t)( ( (51.91f) * 4294967296.0f) / SAMPLE_RATE );   // G#1/Ab1
static uint32_t phase_step33 = (uint32_t)( ( (55.00f) * 4294967296.0f) / SAMPLE_RATE );   // A1
static uint32_t phase_step34 = (uint32_t)( ( (58.27f) * 4294967296.0f) / SAMPLE_RATE );   // A#1/Bb1
static uint32_t phase_step35 = (uint32_t)( ( (61.74f) * 4294967296.0f) / SAMPLE_RATE );   // B1

// phase steps для нот 36-47 (C2 - B2)
static uint32_t phase_step36 = (uint32_t)( ( (65.41f) * 4294967296.0f) / SAMPLE_RATE );   // C2
static uint32_t phase_step37 = (uint32_t)( ( (69.30f) * 4294967296.0f) / SAMPLE_RATE );   // C#2/Db2
static uint32_t phase_step38 = (uint32_t)( ( (73.42f) * 4294967296.0f) / SAMPLE_RATE );   // D2
static uint32_t phase_step39 = (uint32_t)( ( (77.78f) * 4294967296.0f) / SAMPLE_RATE );   // D#2/Eb2
static uint32_t phase_step40 = (uint32_t)( ( (82.41f) * 4294967296.0f) / SAMPLE_RATE );   // E2
static uint32_t phase_step41 = (uint32_t)( ( (87.31f) * 4294967296.0f) / SAMPLE_RATE );   // F2
static uint32_t phase_step42 = (uint32_t)( ( (92.50f) * 4294967296.0f) / SAMPLE_RATE );   // F#2/Gb2
static uint32_t phase_step43 = (uint32_t)( ( (98.00f) * 4294967296.0f) / SAMPLE_RATE );   // G2
static uint32_t phase_step44 = (uint32_t)( ( (103.83f) * 4294967296.0f) / SAMPLE_RATE );  // G#2/Ab2
static uint32_t phase_step45 = (uint32_t)( ( (110.00f) * 4294967296.0f) / SAMPLE_RATE );  // A2
static uint32_t phase_step46 = (uint32_t)( ( (116.54f) * 4294967296.0f) / SAMPLE_RATE );  // A#2/Bb2
static uint32_t phase_step47 = (uint32_t)( ( (123.47f) * 4294967296.0f) / SAMPLE_RATE );  // B2

// phase steps для нот 48-59 (C3 - B3)
static uint32_t phase_step48 = (uint32_t)( ( (130.81f) * 4294967296.0f) / SAMPLE_RATE );  // C3
static uint32_t phase_step49 = (uint32_t)( ( (138.59f) * 4294967296.0f) / SAMPLE_RATE );  // C#3/Db3
static uint32_t phase_step50 = (uint32_t)( ( (146.83f) * 4294967296.0f) / SAMPLE_RATE );  // D3
static uint32_t phase_step51 = (uint32_t)( ( (155.56f) * 4294967296.0f) / SAMPLE_RATE );  // D#3/Eb3
static uint32_t phase_step52 = (uint32_t)( ( (164.81f) * 4294967296.0f) / SAMPLE_RATE );  // E3
static uint32_t phase_step53 = (uint32_t)( ( (174.61f) * 4294967296.0f) / SAMPLE_RATE );  // F3
static uint32_t phase_step54 = (uint32_t)( ( (185.00f) * 4294967296.0f) / SAMPLE_RATE );  // F#3/Gb3
static uint32_t phase_step55 = (uint32_t)( ( (196.00f) * 4294967296.0f) / SAMPLE_RATE );  // G3
static uint32_t phase_step56 = (uint32_t)( ( (207.65f) * 4294967296.0f) / SAMPLE_RATE );  // G#3/Ab3
static uint32_t phase_step57 = (uint32_t)( ( (220.00f) * 4294967296.0f) / SAMPLE_RATE );  // A3
static uint32_t phase_step58 = (uint32_t)( ( (233.08f) * 4294967296.0f) / SAMPLE_RATE );  // A#3/Bb3
static uint32_t phase_step59 = (uint32_t)( ( (246.94f) * 4294967296.0f) / SAMPLE_RATE );  // B3

// phase steps для нот 60-71 (C4 - B4) - уже есть у вас
static uint32_t phase_step60 = (uint32_t)( ( (261.63f) * 4294967296.0f) / SAMPLE_RATE );  // C4
static uint32_t phase_step61 = (uint32_t)( ( (277.18f) * 4294967296.0f) / SAMPLE_RATE );  // C#4/Db4
static uint32_t phase_step62 = (uint32_t)( ( (293.66f) * 4294967296.0f) / SAMPLE_RATE );  // D4
static uint32_t phase_step63 = (uint32_t)( ( (311.13f) * 4294967296.0f) / SAMPLE_RATE );  // D#4/Eb4
static uint32_t phase_step64 = (uint32_t)( ( (329.63f) * 4294967296.0f) / SAMPLE_RATE );  // E4
static uint32_t phase_step65 = (uint32_t)( ( (349.23f) * 4294967296.0f) / SAMPLE_RATE );  // F4
static uint32_t phase_step66 = (uint32_t)( ( (369.99f) * 4294967296.0f) / SAMPLE_RATE );  // F#4/Gb4
static uint32_t phase_step67 = (uint32_t)( ( (392.00f) * 4294967296.0f) / SAMPLE_RATE );  // G4
static uint32_t phase_step68 = (uint32_t)( ( (415.30f) * 4294967296.0f) / SAMPLE_RATE );  // G#4/Ab4
static uint32_t phase_step69 = (uint32_t)( ( (440.00f) * 4294967296.0f) / SAMPLE_RATE );  // A4
static uint32_t phase_step70 = (uint32_t)( ( (466.16f) * 4294967296.0f) / SAMPLE_RATE );  // A#4/Bb4
static uint32_t phase_step71 = (uint32_t)( ( (493.88f) * 4294967296.0f) / SAMPLE_RATE );  // B4

// phase steps для нот 72-83 (C5 - B5)
static uint32_t phase_step72 = (uint32_t)( ( (523.25f) * 4294967296.0f) / SAMPLE_RATE );  // C5
static uint32_t phase_step73 = (uint32_t)( ( (554.37f) * 4294967296.0f) / SAMPLE_RATE );  // C#5/Db5
static uint32_t phase_step74 = (uint32_t)( ( (587.33f) * 4294967296.0f) / SAMPLE_RATE );  // D5
static uint32_t phase_step75 = (uint32_t)( ( (622.25f) * 4294967296.0f) / SAMPLE_RATE );  // D#5/Eb5
static uint32_t phase_step76 = (uint32_t)( ( (659.25f) * 4294967296.0f) / SAMPLE_RATE );  // E5
static uint32_t phase_step77 = (uint32_t)( ( (698.46f) * 4294967296.0f) / SAMPLE_RATE );  // F5
static uint32_t phase_step78 = (uint32_t)( ( (739.99f) * 4294967296.0f) / SAMPLE_RATE );  // F#5/Gb5
static uint32_t phase_step79 = (uint32_t)( ( (783.99f) * 4294967296.0f) / SAMPLE_RATE );  // G5
static uint32_t phase_step80 = (uint32_t)( ( (830.61f) * 4294967296.0f) / SAMPLE_RATE );  // G#5/Ab5
static uint32_t phase_step81 = (uint32_t)( ( (880.00f) * 4294967296.0f) / SAMPLE_RATE );  // A5
static uint32_t phase_step82 = (uint32_t)( ( (932.33f) * 4294967296.0f) / SAMPLE_RATE );  // A#5/Bb5
static uint32_t phase_step83 = (uint32_t)( ( (987.77f) * 4294967296.0f) / SAMPLE_RATE );  // B5

// phase steps для нот 84-95 (C6 - B6)
static uint32_t phase_step84 = (uint32_t)( ( (1046.50f) * 4294967296.0f) / SAMPLE_RATE ); // C6
static uint32_t phase_step85 = (uint32_t)( ( (1108.73f) * 4294967296.0f) / SAMPLE_RATE ); // C#6/Db6
static uint32_t phase_step86 = (uint32_t)( ( (1174.66f) * 4294967296.0f) / SAMPLE_RATE ); // D6
static uint32_t phase_step87 = (uint32_t)( ( (1244.51f) * 4294967296.0f) / SAMPLE_RATE ); // D#6/Eb6
static uint32_t phase_step88 = (uint32_t)( ( (1318.51f) * 4294967296.0f) / SAMPLE_RATE ); // E6
static uint32_t phase_step89 = (uint32_t)( ( (1396.91f) * 4294967296.0f) / SAMPLE_RATE ); // F6
static uint32_t phase_step90 = (uint32_t)( ( (1479.98f) * 4294967296.0f) / SAMPLE_RATE ); // F#6/Gb6
static uint32_t phase_step91 = (uint32_t)( ( (1567.98f) * 4294967296.0f) / SAMPLE_RATE ); // G6
static uint32_t phase_step92 = (uint32_t)( ( (1661.22f) * 4294967296.0f) / SAMPLE_RATE ); // G#6/Ab6
static uint32_t phase_step93 = (uint32_t)( ( (1760.00f) * 4294967296.0f) / SAMPLE_RATE ); // A6
static uint32_t phase_step94 = (uint32_t)( ( (1864.66f) * 4294967296.0f) / SAMPLE_RATE ); // A#6/Bb6
static uint32_t phase_step95 = (uint32_t)( ( (1975.53f) * 4294967296.0f) / SAMPLE_RATE ); // B6

// phase steps для нот 96-100 (C7 - E7)
static uint32_t phase_step96 = (uint32_t)( ( (2093.00f) * 4294967296.0f) / SAMPLE_RATE ); // C7
static uint32_t phase_step97 = (uint32_t)( ( (2217.46f) * 4294967296.0f) / SAMPLE_RATE ); // C#7/Db7
static uint32_t phase_step98 = (uint32_t)( ( (2349.32f) * 4294967296.0f) / SAMPLE_RATE ); // D7
static uint32_t phase_step99 = (uint32_t)( ( (2489.02f) * 4294967296.0f) / SAMPLE_RATE ); // D#7/Eb7
static uint32_t phase_step100 = (uint32_t)( ( (2637.02f) * 4294967296.0f) / SAMPLE_RATE ); // E7

uint8_t get_amplitude_note(uint8_t note)
{   
    switch (note)
    {
        case 0: return 0;  // REST - пауза
        
        // 21-35: A0 - B1 (0-1 октавы)
        case 21: phase21 += phase_step21; return sine[phase21 >> 22];
        case 22: phase22 += phase_step22; return sine[phase22 >> 22];
        case 23: phase23 += phase_step23; return sine[phase23 >> 22];
        case 24: phase24 += phase_step24; return sine[phase24 >> 22];
        case 25: phase25 += phase_step25; return sine[phase25 >> 22];
        case 26: phase26 += phase_step26; return sine[phase26 >> 22];
        case 27: phase27 += phase_step27; return sine[phase27 >> 22];
        case 28: phase28 += phase_step28; return sine[phase28 >> 22];
        case 29: phase29 += phase_step29; return sine[phase29 >> 22];
        case 30: phase30 += phase_step30; return sine[phase30 >> 22];
        case 31: phase31 += phase_step31; return sine[phase31 >> 22];
        case 32: phase32 += phase_step32; return sine[phase32 >> 22];
        case 33: phase33 += phase_step33; return sine[phase33 >> 22];
        case 34: phase34 += phase_step34; return sine[phase34 >> 22];
        case 35: phase35 += phase_step35; return sine[phase35 >> 22];
        
        // 36-47: C2 - B2 (2-я октава)
        case 36: phase36 += phase_step36; return sine[phase36 >> 22];
        case 37: phase37 += phase_step37; return sine[phase37 >> 22];
        case 38: phase38 += phase_step38; return sine[phase38 >> 22];
        case 39: phase39 += phase_step39; return sine[phase39 >> 22];
        case 40: phase40 += phase_step40; return sine[phase40 >> 22];
        case 41: phase41 += phase_step41; return sine[phase41 >> 22];
        case 42: phase42 += phase_step42; return sine[phase42 >> 22];
        case 43: phase43 += phase_step43; return sine[phase43 >> 22];
        case 44: phase44 += phase_step44; return sine[phase44 >> 22];
        case 45: phase45 += phase_step45; return sine[phase45 >> 22];
        case 46: phase46 += phase_step46; return sine[phase46 >> 22];
        case 47: phase47 += phase_step47; return sine[phase47 >> 22];
        
        // 48-59: C3 - B3 (3-я октава)
        case 48: phase48 += phase_step48; return sine[phase48 >> 22];
        case 49: phase49 += phase_step49; return sine[phase49 >> 22];
        case 50: phase50 += phase_step50; return sine[phase50 >> 22];
        case 51: phase51 += phase_step51; return sine[phase51 >> 22];
        case 52: phase52 += phase_step52; return sine[phase52 >> 22];
        case 53: phase53 += phase_step53; return sine[phase53 >> 22];
        case 54: phase54 += phase_step54; return sine[phase54 >> 22];
        case 55: phase55 += phase_step55; return sine[phase55 >> 22];
        case 56: phase56 += phase_step56; return sine[phase56 >> 22];
        case 57: phase57 += phase_step57; return sine[phase57 >> 22];
        case 58: phase58 += phase_step58; return sine[phase58 >> 22];
        case 59: phase59 += phase_step59; return sine[phase59 >> 22];
        
        // 60-71: C4 - B4 (4-я октава)
        case 60: phase60 += phase_step60; return sine[phase60 >> 22];
        case 61: phase61 += phase_step61; return sine[phase61 >> 22];
        case 62: phase62 += phase_step62; return sine[phase62 >> 22];
        case 63: phase63 += phase_step63; return sine[phase63 >> 22];
        case 64: phase64 += phase_step64; return sine[phase64 >> 22];
        case 65: phase65 += phase_step65; return sine[phase65 >> 22];
        case 66: phase66 += phase_step66; return sine[phase66 >> 22];
        case 67: phase67 += phase_step67; return sine[phase67 >> 22];
        case 68: phase68 += phase_step68; return sine[phase68 >> 22];
        case 69: phase69 += phase_step69; return sine[phase69 >> 22];
        case 70: phase70 += phase_step70; return sine[phase70 >> 22];
        case 71: phase71 += phase_step71; return sine[phase71 >> 22];
        
        // 72-83: C5 - B5 (5-я октава)
        case 72: phase72 += phase_step72; return sine[phase72 >> 22];
        case 73: phase73 += phase_step73; return sine[phase73 >> 22];
        case 74: phase74 += phase_step74; return sine[phase74 >> 22];
        case 75: phase75 += phase_step75; return sine[phase75 >> 22];
        case 76: phase76 += phase_step76; return sine[phase76 >> 22];
        case 77: phase77 += phase_step77; return sine[phase77 >> 22];
        case 78: phase78 += phase_step78; return sine[phase78 >> 22];
        case 79: phase79 += phase_step79; return sine[phase79 >> 22];
        case 80: phase80 += phase_step80; return sine[phase80 >> 22];
        case 81: phase81 += phase_step81; return sine[phase81 >> 22];
        case 82: phase82 += phase_step82; return sine[phase82 >> 22];
        case 83: phase83 += phase_step83; return sine[phase83 >> 22];
        
        // 84-95: C6 - B6 (6-я октава)
        case 84: phase84 += phase_step84; return sine[phase84 >> 22];
        case 85: phase85 += phase_step85; return sine[phase85 >> 22];
        case 86: phase86 += phase_step86; return sine[phase86 >> 22];
        case 87: phase87 += phase_step87; return sine[phase87 >> 22];
        case 88: phase88 += phase_step88; return sine[phase88 >> 22];
        case 89: phase89 += phase_step89; return sine[phase89 >> 22];
        case 90: phase90 += phase_step90; return sine[phase90 >> 22];
        case 91: phase91 += phase_step91; return sine[phase91 >> 22];
        case 92: phase92 += phase_step92; return sine[phase92 >> 22];
        case 93: phase93 += phase_step93; return sine[phase93 >> 22];
        case 94: phase94 += phase_step94; return sine[phase94 >> 22];
        case 95: phase95 += phase_step95; return sine[phase95 >> 22];
        
        // 96-100: C7 - E7 (7-я октава, первые 5 нот)
        case 96: phase96 += phase_step96; return sine[phase96 >> 22];
        case 97: phase97 += phase_step97; return sine[phase97 >> 22];
        case 98: phase98 += phase_step98; return sine[phase98 >> 22];
        case 99: phase99 += phase_step99; return sine[phase99 >> 22];
        case 100: phase100 += phase_step100; return sine[phase100 >> 22];
            
        default:
            return 0;
    }
}


typedef struct {
    uint8_t midi_n1;
    uint8_t midi_n2;
    uint8_t midi_n3;
    uint8_t midi_n4;

    uint8_t half_beats;
} notes;

static const notes megalovania[] =
{
{D4, 0, 0, 0, 1}, {D4, 0, 0, 0, 1}, {D5, 0, 0, 0, 2}, {A4, 0, 0, 0, 3}, {GS4, 0, 0, 0, 2}, {G4, 0, 0, 0, 2}, {F4, 0, 0, 0, 2}, {D4, 0, 0, 0, 1},
{F4, 0, 0, 0, 1}, {G4, 0, 0, 0, 1}, {C4, 0, 0, 0, 1}, {C4, 0, 0, 0, 1}, {D5, 0, 0, 0, 2}, {A4, 0, 0, 0, 3}, {GS4, 0, 0, 0, 2}, {G4, 0, 0, 0, 2},
{F4, 0, 0, 0, 2}, {D4, 0, 0, 0, 1}, {F4, 0, 0, 0, 1}, {G4, 0, 0, 0, 1}, {B3, 0, 0, 0, 1}, {B3, 0, 0, 0, 1}, {D5, 0, 0, 0, 2}, {A4, 0, 0, 0, 3},
{GS4, 0, 0, 0, 2}, {G4, 0, 0, 0, 2}, {F4, 0, 0, 0, 2}, {D4, 0, 0, 0, 1}, {F4, 0, 0, 0, 1}, {G4, 0, 0, 0, 1}, {AS3, 0, 0, 0, 1}, {AS3, 0, 0, 0, 1},
{D5, 0, 0, 0, 2}, {A4, 0, 0, 0, 3}, {GS4, 0, 0, 0, 2}, {G4, 0, 0, 0, 2}, {F4, 0, 0, 0, 2}, {D4, 0, 0, 0, 1}, {F4, 0, 0, 0, 1}, {G4, 0, 0, 0, 1},
{D3, D4, 0, 0, 1}, {D3, D4, 0, 0, 1}, {D3, D5, 0, 0, 2}, {D3, A4, 0, 0, 1}, {D3, A4, 0, 0, 2}, {D3, GS4, 0, 0, 2}, {D3, G4, 0, 0, 2}, {D3, F4, 0, 0, 2},
{D3, D4, 0, 0, 1}, {D3, F4, 0, 0, 1}, {D3, G4, 0, 0, 1}, {C3, C4, 0, 0, 1}, {C3, C4, 0, 0, 1}, {C3, D5, 0, 0, 2}, {C3, A4, 0, 0, 1}, {C3, A4, 0, 0, 2},
{C3, GS4, 0, 0, 2}, {C3, G4, 0, 0, 2}, {C3, F4, 0, 0, 2}, {C3, D4, 0, 0, 1}, {C3, F4, 0, 0, 1}, {C3, G4, 0, 0, 1}, {B2, B3, 0, 0, 1}, {B2, B3, 0, 0, 1},
{B2, D5, 0, 0, 2}, {B2, A4, 0, 0, 1}, {B2, A4, 0, 0, 2}, {B2, GS4, 0, 0, 2}, {B2, G4, 0, 0, 2}, {B2, F4, 0, 0, 2}, {B2, D4, 0, 0, 1}, {B2, F4, 0, 0, 1},
{B2, G4, 0, 0, 1}, {AS2, AS3, 0, 0, 1}, {AS2, AS3, 0, 0, 1}, {AS2, D5, 0, 0, 2}, {AS2, A4, 0, 0, 1}, {AS2, A4, 0, 0, 2}, {C3, GS4, 0, 0, 1}, {C3, G3, GS4, 0, 1},
{C3, G4, 0, 0, 1}, {C3, G3, G4, 0, 1}, {C3, F4, 0, 0, 1}, {C3, G3, F4, 0, 1}, {C3, D4, 0, 0, 1}, {C3, G3, F4, 0, 1}, {C3, G4, 0, 0, 1}, {C2, D2, AS2, D3, 1},
// {D2, D3, D5, 0, 1}, {D2, E2, AS2, D3, 1}, {D2, D3, D6, 0, 1}, {C2, D2, AS2, D3, 1}, {D2, D3, A5, 0, 1}, {D2, E2, AS2, D3, 1}, {C2, D2, D3, GS5, 1}, {D2, AS2, D3, GS5, 1},
// {C2, D2, D3, G5, 1}, {D2, E2, AS2, D3, 1}, {C2, D2, D3, F5, 1}, {C2, D2, AS2, D3, 1}, {D2, D3, D5, 0, 1}, {C2, D2, E2, AS2, 1}, {D2, D3, G5, 0, 1}, {C2, AS2, C3, C5, 1},
// {C3, C5, 0, 0, 1}, {C2, E2, AS2, C3, 1}, {C2, C3, D6, 0, 1}, {C2, AS2, C3, A5, 1}, {C2, C3, A5, 0, 1}, {C2, E2, AS2, C3, 1}, {C2, C3, GS5, 0, 1}, {AS2, C3, GS5, 0, 1},
// {C2, C3, G5, 0, 1}, {E2, AS2, C3, G5, 1}, {C2, C3, F5, 0, 1}, {C2, AS2, C3, F5, 1}, {C2, C3, D5, 0, 1}, {C2, E2, AS2, C3, 1}, {C3, G5, 0, 0, 1}, {B1, AS2, B2, B4, 1},
// {B1, B2, B4, 0, 1}, {B1, E2, AS2, B2, 1}, {B1, B2, D6, 0, 1}, {B1, C2, AS2, B2, 1}, {B1, B2, A5, 0, 1}, {B1, E2, AS2, B2, 1}, {B1, C2, B2, GS5, 1}, {B1, AS2, B2, GS5, 1},
// {B1, C2, B2, G5, 1}, {B1, E2, AS2, B2, 1}, {B1, C2, B2, F5, 1}, {B1, C2, AS2, B2, 1}, {B1, B2, D5, 0, 1}, {B1, C2, E2, AS2, 1}, {B1, B2, G5, 0, 1}, {AS1, C2, AS2, AS4, 1},
// {AS1, AS4, 0, 0, 1}, {AS1, E2, AS2, D6, 1}, {AS1, D6, 0, 0, 1}, {AS1, C2, AS2, A5, 1}, {AS1, E2, AS2, A5, 1}, {AS1, AS2, A5, 0, 1}, {C2, E2, C3, GS5, 1}, {AS2, C3, GS5, 0, 1},
// {C2, C3, G5, 0, 1}, {E2, AS2, C3, G5, 1}, {C2, C3, F5, 0, 1}, {C2, E2, AS2, C3, 1}, {C2, C3, D5, 0, 1}, {C2, E2, AS2, C3, 1}, {C3, G5, 0, 0, 1}, {D2, AS2, D3, A3, 1},
// {D2, D3, D5, 0, 1}, {D2, E2, AS2, D3, 1}, {D2, D3, D6, 0, 1}, {C2, D2, AS2, D3, 1}, {D2, D3, A5, 0, 1}, {D2, E2, AS2, D3, 1}, {C2, D2, D3, GS5, 1}, {D2, AS2, D3, GS5, 1},
// {C2, D2, D3, G5, 1}, {D2, E2, AS2, D3, 1}, {C2, D2, D3, F5, 1}, {C2, D2, AS2, D3, 1}, {D2, D3, D5, 0, 1}, {C2, D2, E2, AS2, 1}, {D2, D3, G5, 0, 1}, {C2, AS2, C3, C5, 1},
// {C3, C5, 0, 0, 1}, {C2, E2, AS2, C3, 1}, {C2, C3, D6, 0, 1}, {C2, AS2, C3, A5, 1}, {C2, C3, A5, 0, 1}, {C2, E2, AS2, C3, 1}, {C2, C3, GS5, 0, 1}, {AS2, C3, GS5, 0, 1},
// {C2, C3, G5, 0, 1}, {E2, AS2, C3, G5, 1}, {C2, C3, F5, 0, 1}, {C2, AS2, C3, F5, 1}, {C2, C3, D5, 0, 1}, {C2, E2, AS2, C3, 1}, {C3, G5, 0, 0, 1}, {B1, AS2, B2, B4, 1},
// {B1, B2, B4, 0, 1}, {B1, E2, AS2, B2, 1}, {B1, B2, D6, 0, 1}, {B1, C2, AS2, B2, 1}, {B1, B2, A5, 0, 1}, {B1, E2, AS2, B2, 1}, {B1, C2, B2, GS5, 1}, {B1, AS2, B2, GS5, 1},
// {B1, C2, B2, G5, 1}, {B1, E2, AS2, B2, 1}, {B1, C2, B2, F5, 1}, {B1, C2, AS2, B2, 1}, {B1, B2, D5, 0, 1}, {B1, C2, E2, AS2, 1}, {B1, B2, G5, 0, 1}, {AS1, C2, AS2, AS4, 1},
// {AS1, AS4, 0, 0, 1}, {AS1, E2, AS2, D6, 1}, {AS1, D6, 0, 0, 1}, {AS1, C2, AS2, A5, 1}, {AS1, E2, AS2, A5, 1}, {AS1, AS2, A5, 0, 1}, {C2, E2, C3, GS5, 1}, {AS2, C3, GS5, 0, 1},
// {C2, C3, G5, 0, 1}, {E2, AS2, C3, G5, 1}, {C2, C3, F5, 0, 1}, {C2, E2, AS2, C3, 1}, {C2, C3, D5, 0, 1}, {C2, E2, AS2, C3, 1}, {C3, G5, 0, 0, 1}, {GS2, D3, A3, F5, 1},
// {GS2, D3, 0, 0, 1}, {E2, D3, A3, F5, 1}, {GS2, D3, A3, F5, 1}, {C2, GS2, D3, A3, 1}, {GS2, D3, A3, F5, 1}, {E2, D3, A3, F5, 1}, {C2, D3, A3, F5, 1}, {GS2, D3, A3, F5, 1},
// {C2, GS2, D3, A3, 1}, {E2, D3, A3, D5, 1}, {C2, GS2, D3, A3, 1}, {C2, GS2, D3, A3, 1}, {GS2, D3, A3, D5, 1}, {C2, E2, D3, A3, 1}, {D3, A3, D5, 0, 1}, {C2, GS2, C3, G3, 1},
// {GS2, C3, G3, F5, 1}, {E2, C3, G3, F5, 1}, {GS2, C3, G3, F5, 1}, {C2, GS2, C3, G3, 1}, {GS2, C3, G3, G5, 1}, {E2, C3, G3, G5, 1}, {C2, C3, G3, GS5, 1}, {GS2, C3, G3, GS5, 1},
// {C2, GS2, C3, G3, 1}, {E2, C3, G3, F5, 1}, {C2, GS2, C3, G3, 1}, {C2, GS2, C3, G3, 1}, {GS2, C3, G3, G5, 1}, {C2, E2, C3, G3, 1}, {C3, G3, G5, 0, 1}, {C2, GS2, B2, G3, 1},
// {GS2, B2, G3, 0, 1}, {E2, B2, G3, F5, 1}, {GS2, B2, G3, F5, 1}, {C2, GS2, B2, G3, 1}, {GS2, B2, G3, G5, 1}, {E2, B2, G3, G5, 1}, {C2, B2, G3, GS5, 1}, {GS2, B2, G3, GS5, 1},
// {C2, GS2, B2, G3, 1}, {E2, B2, G3, A5, 1}, {C2, GS2, B2, G3, 1}, {C2, GS2, B2, G3, 1}, {GS2, B2, G3, A5, 1}, {C2, E2, B2, G3, 1}, {B2, G3, A5, 0, 1}, {C2, GS2, AS2, F3, 1},
// {GS2, AS2, F3, D6, 1}, {E2, AS2, F3, D6, 1}, {GS2, AS2, F3, D6, 1}, {C2, GS2, AS2, F3, 1}, {E2, GS2, AS2, F3, 1}, {AS2, F3, D6, 0, 1}, {C2, E2, C3, G3, 1}, {GS2, C3, G3, C6, 1},
// {C2, GS2, C3, G3, 1}, {E2, C3, G3, C6, 1}, {C2, C3, CS3, G3, 1}, {C2, E2, GS2, C3, 1}, {GS2, C3, G3, A3, 1}, {C2, E2, GS2, C3, 1}, {C3, G3, C6, 0, 1}, {C2, AS2, D3, A3, 1},
// {D3, 0, 0, 0, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, F5, A5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, F5, A5, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, F5, 1}, {AS2, D3, A3, F5, 1},
// {C2, D3, A3, D5, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, D5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, D5, G5, 1}, {C2, E2, AS2, D3, 1}, {D3, A3, D5, G5, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, 0, 0, 1}, {E2, AS2, C3, G3, 1}, {C3, G3, F5, A5, 1}, {C2, AS2, C3, G3, 1}, {C3, G3, F5, A5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, D5, 1}, {AS2, C3, G3, D5, 1},
// {C2, C3, G3, F5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, A5, 1}, {C2, AS2, C3, G3, 1}, {C3, G3, F5, A5, 1}, {C2, E2, AS2, C3, 1}, {C3, G3, D5, G5, 1}, {C2, AS2, B2, G3, 1},
// {B2, G3, F5, D6, 1}, {E2, AS2, B2, G3, 1}, {B2, G3, F5, A5, 1}, {C2, AS2, B2, G3, 1}, {B2, G3, D5, G5, 1}, {E2, AS2, B2, G3, 1}, {C2, B2, G3, D5, 1}, {AS2, B2, G3, F5, 1},
// {C2, B2, G3, F5, 1}, {E2, AS2, B2, G3, 1}, {C2, B2, G3, F5, 1}, {C2, AS2, B2, G3, 1}, {B2, G3, D5, F5, 1}, {C2, E2, AS2, B2, 1}, {B2, G3, D5, E5, 1}, {C2, AS2, F3, AS4, 1},
// {F3, AS4, 0, 0, 1}, {E2, AS2, F3, C5, 1}, {F3, D5, 0, 0, 1}, {C2, AS2, F3, 0, 1}, {E2, AS2, F3, AS4, 1}, {AS2, F3, AS4, F5, 1}, {C2, E2, C3, G3, 1}, {AS2, C3, G3, C5, 1},
// {C2, C3, G3, A3, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, CS3, G3, 1}, {C2, E2, AS2, C3, 1}, {C3, G3, A3, C5, 1}, {C2, E2, AS2, C3, 1}, {C3, G3, C5, E5, 1}, {C2, AS2, F3, A3, 1},
// {F3, 0, 0, 0, 1}, {E2, AS2, F3, 0, 1}, {F3, 0, 0, 0, 1}, {C2, AS2, F3, 0, 1}, {AS2, F3, 0, 0, 1}, {E2, AS2, F3, 0, 1}, {C2, AS2, F3, 0, 1}, {AS2, F3, F5, 0, 1},
// {C2, AS2, F3, D5, 1}, {E2, AS2, F3, F5, 1}, {C2, AS2, F3, G5, 1}, {C2, AS2, F3, GS5, 1}, {AS2, F3, G5, 0, 1}, {C2, E2, AS2, F3, 1}, {F3, D5, 0, 0, 1}, {C2, C3, G3, GS5, 0},
// {C2, C3, G3, G5, 0}, {C3, G3, F5, 0, 0}, {C3, G3, D5, 0, 0}, {E2, AS2, C3, G3, 1}, {C3, G3, 0, 0, 1}, {C2, AS2, C3, G3, 1}, {C3, G3, C5, G5, 1}, {E2, AS2, C3, G3, 1},
// {C2, C3, G3, C5, 1}, {AS2, C3, G3, C5, 1}, {C2, C3, G3, C5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, C5, 1}, {C2, AS2, C3, G3, 1}, {C3, G3, GS5, 0, 1}, {C2, E2, AS2, C3, 1},
// {C3, G3, A5, 0, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, 0, 0, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, GS5, 0, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, F5, 0, 1}, {E2, AS2, D3, A3, 1},
// {C2, D3, A3, E5, 1}, {AS2, D3, A3, F5, 1}, {C2, D3, A3, F5, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, G5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, A5, 0, 1}, {C2, E2, AS2, D3, 1},
// {D3, A3, C6, 0, 1}, {C2, AS2, CS3, GS3, 1}, {CS3, GS3, CS5, CS6, 1}, {E2, AS2, CS3, GS3, 1}, {CS3, GS3, GS5, 0, 1}, {C2, AS2, CS3, GS3, 1}, {E2, CS3, GS3, G5, 1}, {AS2, CS3, GS3, F5, 1},
// {C2, E2, DS3, AS3, 1}, {AS2, DS3, AS3, DS5, 1}, {C2, DS3, A3, AS3, 1}, {E2, AS2, DS3, AS3, 1}, {C2, E2, CS3, DS3, 1}, {C2, AS2, DS3, AS3, 1}, {E2, DS3, A3, AS3, 1}, {C2, E2, AS2, DS3, 1},
// {DS3, AS3, DS5, G5, 1}, {C2, AS2, F3, A3, 1}, {F3, F4, 0, 0, 1}, {E2, AS2, F3, G4, 1}, {F3, G4, 0, 0, 1}, {C2, AS2, F3, F4, 1}, {AS2, F3, F4, A4, 1}, {E2, AS2, F3, F5, 1},
// {C2, AS2, F3, F5, 1}, {AS2, F3, C5, E5, 1}, {C2, AS2, F3, C5, 1}, {E2, AS2, F3, C5, 1}, {C2, AS2, F3, C5, 1}, {C2, AS2, F3, A4, 1}, {AS2, F3, A4, D5, 1}, {C2, E2, AS2, F3, 1},
// {F3, A4, D5, 0, 1}, {C2, C3, G3, G4, 1}, {C3, G3, G4, E5, 1}, {E2, AS2, C3, G3, 1}, {C3, G3, G4, E5, 1}, {C2, AS2, C3, G3, 1}, {C3, G3, A4, F5, 1}, {E2, AS2, C3, G3, 1},
// {C2, C3, G3, A4, 1}, {AS2, C3, G3, C5, 1}, {C2, C3, G3, C5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, C5, 1}, {C2, AS2, C3, G3, 1}, {C3, G3, A4, E5, 1}, {C2, E2, AS2, C3, 1},
// {C3, G3, A4, E5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, D5, A5, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, D5, A5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, D5, A5, 1}, {E2, AS2, D3, A3, 1},
// {C2, D3, A3, D5, 1}, {AS2, D3, A3, A5, 1}, {C2, D3, A3, GS5, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, FS5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, E5, 0, 1}, {C2, E2, AS2, D3, 1},
// {D3, A3, D5, 0, 1}, {C2, AS2, CS3, GS3, 1}, {CS3, GS3, GS4, CS5, 1}, {E2, AS2, CS3, GS3, 1}, {CS3, GS3, GS4, CS5, 1}, {C2, AS2, CS3, GS3, 1}, {E2, CS3, GS3, GS4, 1}, {AS2, CS3, GS3, GS4, 1},
// {C2, E2, DS3, AS3, 1}, {AS2, DS3, AS3, AS4, 1}, {C2, DS3, A3, AS3, 1}, {E2, AS2, DS3, AS3, 1}, {C2, E2, CS3, DS3, 1}, {C2, AS2, DS3, AS3, 1}, {E2, DS3, A3, AS3, 1}, {C2, E2, AS2, DS3, 1},
// {DS3, AS3, AS4, DS5, 1}, {C2, AS2, F3, A3, 1}, {F3, 0, 0, 0, 1}, {E2, AS2, F3, 0, 1}, {F3, 0, 0, 0, 1}, {C2, AS2, F3, 0, 1}, {AS2, F3, 0, 0, 1}, {E2, AS2, F3, 0, 1},
// {C2, AS2, F3, 0, 1}, {AS2, F3, F5, 0, 1}, {C2, AS2, F3, D5, 1}, {E2, AS2, F3, F5, 1}, {C2, AS2, F3, G5, 1}, {C2, AS2, F3, GS5, 1}, {AS2, F3, G5, 0, 1}, {C2, E2, AS2, F3, 1},
// {F3, D5, 0, 0, 1}, {C2, C3, G3, GS5, 0}, {C2, C3, G3, G5, 0}, {C3, G3, F5, 0, 0}, {C3, G3, D5, 0, 0}, {E2, AS2, C3, G3, 1}, {C3, G3, 0, 0, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, C5, G5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, C5, 1}, {AS2, C3, G3, C5, 1}, {C2, C3, G3, C5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, C5, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, GS5, 0, 1}, {C2, E2, AS2, C3, 1}, {C3, G3, A5, 0, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, 0, 0, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, GS5, 0, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, F5, 0, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, E5, 1}, {AS2, D3, A3, F5, 1}, {C2, D3, A3, F5, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, G5, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, A5, 0, 1}, {C2, E2, AS2, D3, 1}, {D3, A3, C6, 0, 1}, {C2, AS2, CS3, GS3, 1}, {CS3, GS3, CS5, CS6, 1}, {E2, AS2, CS3, GS3, 1}, {CS3, GS3, GS5, 0, 1}, {C2, AS2, CS3, GS3, 1},
// {E2, CS3, GS3, G5, 1}, {AS2, CS3, GS3, F5, 1}, {C2, E2, DS3, AS3, 1}, {AS2, DS3, AS3, DS5, 1}, {C2, DS3, A3, AS3, 1}, {E2, AS2, DS3, AS3, 1}, {C2, E2, CS3, DS3, 1}, {C2, AS2, DS3, AS3, 1},
// {E2, DS3, A3, AS3, 1}, {C2, E2, AS2, DS3, 1}, {DS3, AS3, DS5, G5, 1}, {C2, AS2, F3, A3, 1}, {F3, F4, 0, 0, 1}, {E2, AS2, F3, G4, 1}, {F3, G4, 0, 0, 1}, {C2, AS2, F3, F4, 1},
// {AS2, F3, F4, A4, 1}, {E2, AS2, F3, F5, 1}, {C2, AS2, F3, F5, 1}, {AS2, F3, C5, E5, 1}, {C2, AS2, F3, C5, 1}, {E2, AS2, F3, C5, 1}, {C2, AS2, F3, C5, 1}, {C2, AS2, F3, A4, 1},
// {AS2, F3, A4, D5, 1}, {C2, E2, AS2, F3, 1}, {F3, A4, D5, 0, 1}, {C2, C3, G3, G4, 1}, {C3, G3, G4, E5, 1}, {E2, AS2, C3, G3, 1}, {C3, G3, G4, E5, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, A4, F5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, A4, 1}, {AS2, C3, G3, C5, 1}, {C2, C3, G3, C5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, C5, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, A4, E5, 1}, {C2, E2, AS2, C3, 1}, {C3, G3, A4, E5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, D5, A5, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, D5, A5, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, D5, A5, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, D5, 1}, {AS2, D3, A3, A5, 1}, {C2, D3, A3, GS5, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, FS5, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, E5, 0, 1}, {C2, E2, AS2, D3, 1}, {D3, A3, D5, 0, 1}, {C2, AS2, CS3, GS3, 1}, {CS3, GS3, GS4, CS5, 1}, {E2, AS2, CS3, GS3, 1}, {CS3, GS3, GS4, CS5, 1}, {C2, AS2, CS3, GS3, 1},
// {E2, CS3, GS3, GS4, 1}, {AS2, CS3, GS3, GS4, 1}, {C2, E2, DS3, AS3, 1}, {AS2, DS3, AS3, AS4, 1}, {C2, DS3, A3, AS3, 1}, {E2, AS2, DS3, AS3, 1}, {C2, E2, CS3, DS3, 1}, {C2, AS2, DS3, AS3, 1},
// {E2, DS3, A3, AS3, 1}, {C2, E2, AS2, DS3, 1}, {DS3, AS3, AS4, DS5, 1}, {C2, GS2, AS2, F3, 1}, {AS2, F3, 0, 0, 1}, {GS2, AS2, F3, 0, 1}, {AS2, F3, 0, 0, 1}, {E2, GS2, AS2, F3, 1},
// {AS2, F3, 0, 0, 1}, {GS2, AS2, F3, 0, 1}, {C2, AS2, F3, 0, 1}, {GS2, AS2, F3, 0, 1}, {C2, AS2, F3, 0, 1}, {GS2, AS2, F3, 0, 1}, {C2, AS2, F3, 0, 1}, {C2, E2, GS2, AS2, 1},
// {AS2, F3, F4, 0, 1}, {GS2, AS2, F3, F4, 1}, {E2, AS2, F3, F4, 1}, {C2, GS2, C3, G3, 1}, {C3, G3, E4, 0, 1}, {GS2, C3, G3, E4, 1}, {C3, G3, E4, 0, 1}, {E2, GS2, C3, G3, 1},
// {C3, G3, E4, 0, 1}, {GS2, C3, G3, E4, 1}, {C2, C3, G3, E4, 1}, {GS2, C3, G3, D4, 1}, {C2, C3, G3, D4, 1}, {GS2, C3, G3, D4, 1}, {C2, C3, G3, D4, 1}, {C2, E2, GS2, C3, 1},
// {C3, G3, D4, 0, 1}, {GS2, C3, G3, D4, 1}, {E2, C3, G3, D4, 1}, {C2, GS2, B2, G3, 1}, {B2, G3, F4, 0, 1}, {GS2, B2, G3, F4, 1}, {B2, G3, F4, 0, 1}, {E2, GS2, B2, G3, 1},
// {B2, G3, F4, 0, 1}, {GS2, B2, G3, F4, 1}, {C2, B2, G3, F4, 1}, {GS2, B2, G3, F4, 1}, {C2, B2, G3, F4, 1}, {GS2, B2, G3, F4, 1}, {C2, B2, G3, F4, 1}, {C2, E2, GS2, B2, 1},
// {B2, G3, F4, 0, 1}, {GS2, B2, G3, F4, 1}, {E2, B2, G3, F4, 1}, {C2, GS2, B2, G3, 1}, {B2, G3, 0, 0, 1}, {GS2, B2, G3, 0, 1}, {B2, G3, 0, 0, 1}, {E2, GS2, B2, G3, 1},
// {B2, G3, 0, 0, 1}, {GS2, B2, G3, 0, 1}, {C2, B2, G3, 0, 1}, {GS2, B2, G3, 0, 1}, {C2, B2, G3, 0, 1}, {GS2, B2, G3, 0, 1}, {C2, B2, G3, 0, 1}, {C2, E2, GS2, B2, 1},
// {B2, G3, 0, 0, 1}, {GS2, B2, G3, 0, 1}, {E2, B2, G3, 0, 1}, {C2, GS2, AS2, F3, 1}, {AS2, F3, AS3, 0, 1}, {GS2, AS2, F3, AS3, 1}, {AS2, F3, AS3, 0, 1}, {E2, GS2, AS2, F3, 1},
// {AS2, F3, AS3, 0, 1}, {GS2, AS2, F3, AS3, 1}, {C2, AS2, F3, AS3, 1}, {GS2, AS2, F3, AS3, 1}, {C2, AS2, F3, AS3, 1}, {GS2, AS2, F3, AS3, 1}, {C2, AS2, F3, AS3, 1}, {C2, E2, GS2, AS2, 1},
// {AS2, F3, F4, 0, 1}, {GS2, AS2, F3, F4, 1}, {E2, AS2, F3, F4, 1}, {C2, GS2, C3, G3, 1}, {C3, G3, E4, 0, 1}, {GS2, C3, G3, E4, 1}, {C3, G3, E4, 0, 1}, {E2, GS2, C3, G3, 1},
// {C3, G3, E4, 0, 1}, {GS2, C3, G3, E4, 1}, {C2, C3, G3, E4, 1}, {GS2, C3, G3, D4, 1}, {C2, C3, G3, D4, 1}, {GS2, C3, G3, D4, 1}, {C2, C3, G3, D4, 1}, {C2, E2, GS2, C3, 1},
// {C3, G3, D4, 0, 1}, {GS2, C3, G3, D4, 1}, {E2, C3, G3, D4, 1}, {C2, GS2, D3, A3, 1}, {D3, A3, D4, 0, 1}, {GS2, D3, A3, D4, 1}, {D3, A3, D4, 0, 1}, {E2, GS2, D3, A3, 1},
// {D3, A3, D4, 0, 1}, {GS2, D3, A3, D4, 1}, {C2, D3, A3, D4, 1}, {GS2, D3, A3, D4, 1}, {C2, D3, A3, D4, 1}, {GS2, D3, A3, D4, 1}, {C2, D3, A3, D4, 1}, {C2, E2, GS2, D3, 1},
// {D3, A3, D4, 0, 1}, {GS2, D3, A3, D4, 1}, {E2, D3, A3, D4, 1}, {C2, GS2, D3, A3, 1}, {D3, A3, 0, 0, 1}, {GS2, D3, A3, 0, 1}, {D3, A3, 0, 0, 1}, {E2, GS2, D3, A3, 1},
// {D3, A3, 0, 0, 1}, {GS2, D3, A3, 0, 1}, {C2, D3, A3, 0, 1}, {GS2, D3, A3, 0, 1}, {C2, D3, A3, 0, 1}, {GS2, D3, A3, 0, 1}, {C2, D3, A3, 0, 1}, {C2, E2, GS2, D3, 1},
// {D3, A3, 0, 0, 1}, {GS2, D3, A3, 0, 1}, {E2, D3, A3, 0, 1}, {C2, GS2, AS2, F3, 1}, {AS2, F3, D4, 0, 1}, {GS2, AS2, F3, D5, 1}, {AS2, F3, D5, 0, 1}, {E2, GS2, AS2, F3, 1},
// {AS2, F3, A4, 0, 1}, {GS2, AS2, F3, A4, 1}, {C2, AS2, F3, GS4, 1}, {GS2, AS2, F3, GS4, 1}, {C2, AS2, F3, G4, 1}, {GS2, AS2, F3, G4, 1}, {C2, AS2, F3, F4, 1}, {C2, E2, GS2, AS2, 1},
// {AS2, F3, D4, 0, 1}, {GS2, AS2, F3, F4, 1}, {E2, AS2, F3, G4, 1}, {C2, GS2, C3, G3, 1}, {C3, G3, C4, 0, 1}, {GS2, C3, G3, D5, 1}, {C3, G3, D5, 0, 1}, {E2, GS2, C3, G3, 1},
// {C3, G3, A4, 0, 1}, {GS2, C3, G3, A4, 1}, {C2, C3, G3, GS4, 1}, {GS2, C3, G3, GS4, 1}, {C2, C3, G3, G4, 1}, {GS2, C3, G3, G4, 1}, {C2, C3, G3, F4, 1}, {C2, E2, GS2, C3, 1},
// {C3, G3, D4, 0, 1}, {GS2, C3, G3, F4, 1}, {E2, C3, G3, G4, 1}, {C2, GS2, B2, G3, 1}, {B2, G3, B3, 0, 1}, {GS2, B2, G3, D5, 1}, {B2, G3, D5, 0, 1}, {E2, GS2, B2, G3, 1},
// {B2, G3, A4, 0, 1}, {GS2, B2, G3, A4, 1}, {C2, B2, G3, GS4, 1}, {GS2, B2, G3, GS4, 1}, {C2, B2, G3, G4, 1}, {GS2, B2, G3, G4, 1}, {C2, B2, G3, F4, 1}, {C2, E2, GS2, B2, 1},
// {B2, G3, D4, 0, 1}, {GS2, B2, G3, F4, 1}, {E2, B2, G3, G4, 1}, {C2, GS2, B2, G3, 1}, {B2, G3, B3, 0, 1}, {GS2, B2, G3, D5, 1}, {B2, G3, D5, 0, 1}, {E2, GS2, B2, G3, 1},
// {B2, G3, A4, 0, 1}, {GS2, B2, G3, A4, 1}, {C2, B2, G3, GS4, 1}, {GS2, B2, G3, GS4, 1}, {C2, B2, G3, G4, 1}, {GS2, B2, G3, G4, 1}, {C2, B2, G3, F4, 1}, {C2, E2, GS2, B2, 1},
// {B2, G3, D4, 0, 1}, {GS2, B2, G3, F4, 1}, {E2, B2, G3, G4, 1}, {C2, GS2, AS2, F3, 1}, {AS2, F3, D4, 0, 1}, {GS2, AS2, F3, D5, 1}, {AS2, F3, D5, 0, 1}, {E2, GS2, AS2, F3, 1},
// {AS2, F3, A4, 0, 1}, {GS2, AS2, F3, A4, 1}, {C2, AS2, F3, GS4, 1}, {GS2, AS2, F3, GS4, 1}, {C2, AS2, F3, G4, 1}, {GS2, AS2, F3, G4, 1}, {C2, AS2, F3, F4, 1}, {C2, E2, GS2, AS2, 1},
// {AS2, F3, D4, 0, 1}, {GS2, AS2, F3, F4, 1}, {E2, AS2, F3, G4, 1}, {C2, GS2, C3, G3, 1}, {C3, G3, C4, 0, 1}, {GS2, C3, G3, D5, 1}, {C3, G3, D5, 0, 1}, {E2, GS2, C3, G3, 1},
// {C3, G3, A4, 0, 1}, {GS2, C3, G3, A4, 1}, {C2, C3, G3, GS4, 1}, {GS2, C3, G3, GS4, 1}, {C2, C3, G3, G4, 1}, {GS2, C3, G3, G4, 1}, {C2, C3, G3, F4, 1}, {C2, E2, GS2, C3, 1},
// {C3, G3, D4, 0, 1}, {GS2, C3, G3, F4, 1}, {E2, C3, G3, G4, 1}, {D3, A3, D4, 0, 1}, {D3, A3, D4, 0, 1}, {D5, F5, 0, 0, 2}, {F5, 0, 0, 0, 0}, {A4, E5, 0, 0, 1},
// {GS4, C5, 0, 0, 2}, {G4, E5, 0, 0, 1}, {F4, D5, 0, 0, 2}, {C4, A4, 0, 0, 1}, {E4, C5, 0, 0, 1}, {F4, D5, 0, 0, 1}, {D3, A3, D4, 0, 1}, {D3, A3, D4, 0, 1},
// {D5, F5, 0, 0, 2}, {F5, 0, 0, 0, 0}, {A4, E5, 0, 0, 1}, {GS4, C5, 0, 0, 2}, {D3, A3, G4, E5, 1}, {D3, 0, 0, 0, 1}, {CS3, D3, A3, F4, 1}, {D3, A3, F4, D5, 1},
// {D3, A3, C4, A4, 1}, {D3, A3, E4, C5, 1}, {D3, F4, D5, 0, 1}, {C2, AS2, F3, F4, 1}, {F3, F4, AS4, 0, 1}, {E2, AS2, F3, F4, 1}, {F3, F4, AS4, 0, 1}, {C2, AS2, F3, F4, 1},
// {AS2, F3, F4, AS4, 1}, {E2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1}, {AS2, F3, F4, AS4, 1}, {C2, AS2, F3, F4, 1}, {E2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1},
// {AS2, F3, F4, AS4, 1}, {C2, E2, AS2, F3, 1}, {F3, F4, AS4, 0, 1}, {C2, C3, G3, G4, 1}, {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, G4, 1}, {AS2, C3, G3, G4, 1}, {C2, C3, G3, G4, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, G4, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, G4, C5, 1}, {C2, E2, AS2, C3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, A4, D5, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, A4, D5, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, A4, D5, 1}, {E2, AS2, D3, A3, 1}, {C2, CS3, GS3, GS4, 1}, {AS2, CS3, GS3, GS4, 1}, {C2, CS3, GS3, GS4, 1}, {E2, AS2, CS3, GS3, 1}, {C2, CS3, GS3, GS4, 1}, {C2, AS2, CS3, GS3, 1},
// {CS3, GS3, GS4, CS5, 1}, {C2, E2, AS2, CS3, 1}, {CS3, GS3, GS4, CS5, 1}, {C2, AS2, C3, G3, 1}, {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, C3, G3, 1},
// {E2, C3, G3, G4, 1}, {AS2, C3, G3, G4, 1}, {C2, E2, B2, G3, 1}, {AS2, B2, G3, G4, 1}, {C2, B2, G3, A3, 1}, {E2, AS2, B2, G3, 1}, {C2, B2, CS3, G3, 1}, {C2, E2, AS2, B2, 1},
// {B2, G3, A3, G4, 1}, {C2, E2, AS2, B2, 1}, {B2, G3, G4, B4, 1}, {C2, AS2, F3, A3, 1}, {F3, F4, AS4, 0, 1}, {E2, AS2, F3, F4, 1}, {F3, F4, AS4, 0, 1}, {C2, AS2, F3, F4, 1},
// {AS2, F3, F4, AS4, 1}, {E2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1}, {AS2, F3, F4, AS4, 1}, {C2, AS2, F3, F4, 1}, {E2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1},
// {AS2, F3, F4, AS4, 1}, {C2, E2, AS2, F3, 1}, {F3, F4, AS4, 0, 1}, {C2, C3, G3, G4, 1}, {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, G4, 1}, {AS2, C3, G3, G4, 1}, {C2, C3, G3, G4, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, G4, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, G4, C5, 1}, {C2, E2, AS2, C3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, A4, D5, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, A4, D5, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, A4, D5, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, A4, 1}, {AS2, D3, A3, A4, 1}, {C2, D3, A3, A4, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, A4, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, A4, D5, 1}, {C2, E2, AS2, D3, 1}, {D3, A3, A4, D5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, A4, D5, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, A4, D5, 1}, {C2, AS2, D3, A3, 1},
// {E2, D3, A3, A4, 1}, {AS2, D3, A3, A4, 1}, {C2, E2, D3, A3, 1}, {AS2, D3, A3, A4, 1}, {C2, D3, A3, A4, 1}, {E2, AS2, D3, A4, 1}, {C2, E2, CS3, D3, 1}, {C2, AS2, D3, A3, 1},
// {E2, D3, A3, A4, 1}, {C2, E2, AS2, D3, 1}, {D3, A4, D5, 0, 1}, {C2, AS2, F3, F4, 1}, {F3, F4, AS4, 0, 1}, {E2, AS2, F3, F4, 1}, {F3, F4, AS4, 0, 1}, {C2, AS2, F3, F4, 1},
// {AS2, F3, F4, AS4, 1}, {E2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1}, {AS2, F3, F4, AS4, 1}, {C2, AS2, F3, F4, 1}, {E2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1},
// {AS2, F3, F4, AS4, 1}, {C2, E2, AS2, F3, 1}, {F3, F4, AS4, 0, 1}, {C2, C3, G3, G4, 1}, {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, G4, 1}, {AS2, C3, G3, G4, 1}, {C2, C3, G3, G4, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, G4, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, G4, C5, 1}, {C2, E2, AS2, C3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, A4, D5, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, A4, D5, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, A4, D5, 1}, {E2, AS2, D3, A3, 1}, {C2, CS3, GS3, GS4, 1}, {AS2, CS3, GS3, GS4, 1}, {C2, CS3, GS3, GS4, 1}, {E2, AS2, CS3, GS3, 1}, {C2, CS3, GS3, GS4, 1}, {C2, AS2, CS3, GS3, 1},
// {CS3, GS3, GS4, CS5, 1}, {C2, E2, AS2, CS3, 1}, {CS3, GS3, GS4, CS5, 1}, {C2, AS2, C3, G3, 1}, {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, C3, G3, 1},
// {E2, C3, G3, G4, 1}, {AS2, C3, G3, G4, 1}, {C2, E2, B2, G3, 1}, {AS2, B2, G3, G4, 1}, {C2, B2, G3, A3, 1}, {E2, AS2, B2, G3, 1}, {C2, B2, CS3, G3, 1}, {C2, E2, AS2, B2, 1},
// {B2, G3, A3, G4, 1}, {C2, E2, AS2, B2, 1}, {B2, G3, G4, B4, 1}, {C2, AS2, F3, A3, 1}, {F3, F4, AS4, 0, 1}, {E2, AS2, F3, F4, 1}, {F3, F4, AS4, 0, 1}, {C2, AS2, F3, F4, 1},
// {AS2, F3, F4, AS4, 1}, {E2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1}, {AS2, F3, F4, AS4, 1}, {C2, AS2, F3, F4, 1}, {E2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1}, {C2, AS2, F3, F4, 1},
// {AS2, F3, F4, AS4, 1}, {C2, E2, AS2, F3, 1}, {F3, F4, AS4, 0, 1}, {C2, C3, G3, G4, 1}, {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, G4, C5, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, G4, 1}, {AS2, C3, G3, G4, 1}, {C2, C3, G3, G4, 1}, {E2, AS2, C3, G3, 1}, {C2, C3, G3, G4, 1}, {C2, AS2, C3, G3, 1},
// {C3, G3, G4, C5, 1}, {C2, E2, AS2, C3, 1}, {C3, G3, G4, C5, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, D4, 0, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, D5, 0, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, A4, 0, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, GS4, 1}, {AS2, D3, A3, GS4, 1}, {C2, D3, A3, G4, 1}, {E2, AS2, D3, A3, 1}, {C2, D3, A3, F4, 1}, {C2, AS2, D3, A3, 1},
// {D3, A3, D4, 0, 1}, {C2, E2, AS2, D3, 1}, {D3, A3, G4, 0, 1}, {C2, AS2, D3, A3, 1}, {D3, A3, D4, 0, 1}, {E2, AS2, D3, A3, 1}, {D3, A3, D5, 0, 1}, {C2, AS2, D3, A3, 1},
// {E2, D3, A3, A4, 1}, {AS2, D3, A3, A4, 1}, {C2, E2, D3, A3, 1}, {AS2, D3, A3, GS4, 1}, {C2, D3, A3, G4, 1}, {E2, AS2, D3, G4, 1}, {C2, E2, CS3, D3, 1}, {C2, AS2, D3, A3, 1},
// {E2, D3, A3, D4, 1}, {C2, E2, AS2, D3, 1}, {D3, G4, 0, 0, 1}, {AS3, 0, 0, 0, 1}, {AS3, 0, 0, 0, 1}, {D5, 0, 0, 0, 2}, {A4, 0, 0, 0, 3}, {GS4, 0, 0, 0, 2},
// {G4, 0, 0, 0, 2}, {F4, 0, 0, 0, 2}, {D4, 0, 0, 0, 1}, {F4, 0, 0, 0, 1}, {G4, 0, 0, 0, 1}, {C4, 0, 0, 0, 1}, {C4, 0, 0, 0, 1}, {D5, 0, 0, 0, 2},
// {A4, 0, 0, 0, 3}, {GS4, 0, 0, 0, 2}, {G4, 0, 0, 0, 2}, {F4, 0, 0, 0, 2}, {D4, 0, 0, 0, 1}, {F4, 0, 0, 0, 1}, {G4, 0, 0, 0, 1}, {D4, 0, 0, 0, 1},
// {D4, 0, 0, 0, 1}, {D5, 0, 0, 0, 2}, {A4, 0, 0, 0, 3}, {GS4, 0, 0, 0, 2}, {G4, 0, 0, 0, 2}, {F4, 0, 0, 0, 2}, {D4, 0, 0, 0, 1}, {F4, 0, 0, 0, 1},
// {G4, 0, 0, 0, 1}, {D4, 0, 0, 0, 1}, {D4, 0, 0, 0, 1}, {D5, 0, 0, 0, 2}, {A4, 0, 0, 0, 3}, {GS4, 0, 0, 0, 2}, {G4, 0, 0, 0, 2}, {F4, 0, 0, 0, 2},
// {D4, 0, 0, 0, 1}, {F4, 0, 0, 0, 1}, {G4, 0, 0, 0, 1}
};

uint64_t music_counter = 0; //счётчик нот
uint64_t counter_of_accords = ( sizeof(megalovania) / sizeof(notes) ); //счётчик количества аккордов в песне

#define bpm 230
static uint16_t ms_for_1beat = (60000.3f / bpm); //миллисекунд за бит
uint16_t dlit_ms[];

void count_all_dlit_ms(notes song[]){
    for (uint8_t i = 0; i < counter_of_accords; i++){
        dlit_ms[i] = ms_for_1beat * (song[i].half_beats / 2.0f);
    }
}


uint64_t global_event_counter = 0;

typedef struct {
    uint8_t attack;
    uint8_t decay;
    //uint8_t sustain;
    uint8_t release;
} adsr;

adsr adsr_variables[] = {{1, 10, 10}};

uint8_t adsr_factor(uint16_t time_ms)
{
    // return 1; //Если треуется убрать ADSR
    uint16_t attack  = adsr_variables[0].attack;
    uint16_t decay   = adsr_variables[0].decay;      // порог sustain
    uint16_t release = adsr_variables[0].release;    // длительность release
    uint16_t end_time = dlit_ms[global_event_counter]; // длительность звучания ноты

    uint16_t release_start = end_time - release;

    // // --- 1. ATTACK (0 → 10)
    // if (time_ms < attack) {
    //     return (uint8_t)((time_ms * 10) / attack);
    // }

    // // --- 2. DECAY (10 → 6)
    // if (time_ms < decay) {
    //     uint16_t dt = time_ms - attack;
    //     uint16_t decay_len = decay - attack;
    //     // 10 -> 6  → диапазон 4
    //     return (uint8_t)(10 - ((dt * 4) / decay_len));
    // }

    // --- 3. SUSTAIN (6)
    if (time_ms < release_start) {
        return 10;
    }

    // --- 4. RELEASE (6 → 0)
    if (time_ms < end_time) {
        uint16_t dt = time_ms - release_start;
        return (uint8_t)(6 - (dt * 6) / release);
    }
}



void duty_set(notes song[], uint16_t event_counter) {

    uint8_t a = song[event_counter].midi_n1;
    uint8_t b = song[event_counter].midi_n1;
    uint8_t c = song[event_counter].midi_n1;
    uint8_t d = song[event_counter].midi_n1;

    // // --- Удаление дублей (самый дешёвый вариант) ---
    // if (b == a) b = 0;
    // if (c == a || c == b) c = 0;
    // if (d == a || d == b || d == c) d = 0;

    uint8_t duty = ( get_amplitude_note(a) + get_amplitude_note(b) +get_amplitude_note(c) + get_amplitude_note(d) ) >> 2;

    OCR0 = ( duty * adsr_factor(getTimeMs()) ) / 10;
}

int main(void)
{

    count_all_dlit_ms(megalovania);

    DDRF = 0xFF;

    DDRB = 0xFF;

    TCCR1B = (1 << WGM12) | (1 << CS10); // 11059200/(1+11058) = 1000гц, считает миллисекунды
    OCR1A = 11058;
    TIMSK = (1 << OCIE1A); //прерывание добавляет счётчику миллисекунд 1

    TCCR0 = (1 << CS00) | (1 << COM01) | (1 << WGM01) | (1 << WGM00); // 0-таймер для ШИМ
    // 8-бит ШИМ, нет предделителя(1 в CS00), частота 11052900/256 = 43175 (в proteus измерил, проверил)

    TCCR3B = (1 << WGM32) | (1 << CS30); // 3-таймер для частоты дискретизации музыки, CTC-режим и 1-предделитель
    OCR3A = 690; // считает с частотой 11059200(частота МК)/( 1(предделитель) * (1+690(OCR3A-граница счёта)) = 15935 Гц, наша частота дискретизации
    ETIMSK = (1 << OCIE3A); //прерывание у 3-го таймера по переполнению(которое происходит 15935 раз в секунду) или раз в 63 мкс
    sei();

    while (1) 
    {   
        
    }
}




ISR(TIMER3_COMPA_vect){
    duty_set(megalovania, global_event_counter);
    if (getTimeMs() > dlit_ms[global_event_counter]){
        global_event_counter++;
        setTimeZero();
        //allPhaseNullify();
    }
    if (global_event_counter > counter_of_accords){
        global_event_counter = 0;
    }
}

ISR(TIMER1_COMPA_vect){
    timeMs++;
}