#include <avr/io.h>
#define F_CPU 11059200UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

#define RS 5 // нога PE0(proteus)/PD5 к RS подключена
#define RW 4 // нога PE1(proteus)/PD4 к RW подключена
#define E 6 // нога PE2(proteus)/PD6 к E подключена

#define A4  69
#define AS4 70
#define B4  71
#define C5  72
#define CS5 73
#define D5  74
#define DS5 75
#define E5  76
#define F5  77
#define FS5 78
#define G5  79
#define GS5 80
#define A5  81
#define AS5 82
#define B5  83
#define C6  84
#define CS6 85
#define D6  86
#define DS6 87
#define E6  88
#define F6  89
#define FS6 90
#define G6  91
#define GS6 92
#define A6  93
#define AS6 94
#define B6  95
#define C7  96
#define CS7 97
#define D7  98
#define DS7 99
#define E7  100

#define ZADERSHKA 500

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
static uint32_t phase96 = 0;
static uint32_t phase97 = 0;
static uint32_t phase98 = 0;
static uint32_t phase99 = 0;
static uint32_t phase100 = 0;
static uint32_t phase_step60 = (uint32_t)( ( (261.63f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step61 = (uint32_t)( ( (277.18f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step62 = (uint32_t)( ( (293.66f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step63 = (uint32_t)( ( (311.13f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step64 = (uint32_t)( ( (329.63f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step65 = (uint32_t)( ( (349.23f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step66 = (uint32_t)( ( (369.99f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step67 = (uint32_t)( ( (392.00f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step68 = (uint32_t)( ( (415.30f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step69 = (uint32_t)( ( (440.00f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step70 = (uint32_t)( ( (466.16f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step71 = (uint32_t)( ( (493.88f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step72 = (uint32_t)( ( (523.25f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step73 = (uint32_t)( ( (554.37f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step74 = (uint32_t)( ( (587.33f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step75 = (uint32_t)( ( (622.25f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step76 = (uint32_t)( ( (659.25f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step77 = (uint32_t)( ( (698.46f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step78 = (uint32_t)( ( (739.99f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step79 = (uint32_t)( ( (783.99f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step80 = (uint32_t)( ( (830.61f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step81 = (uint32_t)( ( (880.00f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step82 = (uint32_t)( ( (932.33f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step83 = (uint32_t)( ( (987.77f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step84 = (uint32_t)( ( (1046.50f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step85 = (uint32_t)( ( (1108.73f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step86 = (uint32_t)( ( (1174.66f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step87 = (uint32_t)( ( (1244.51f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step88 = (uint32_t)( ( (1318.51f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step89 = (uint32_t)( ( (1396.91f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step90 = (uint32_t)( ( (1479.98f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step91 = (uint32_t)( ( (1567.98f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step92 = (uint32_t)( ( (1661.22f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step93 = (uint32_t)( ( (1760.00f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step94 = (uint32_t)( ( (1864.66f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step95 = (uint32_t)( ( (1975.53f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step96 = (uint32_t)( ( (2093.00f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step97 = (uint32_t)( ( (2217.46f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step98 = (uint32_t)( ( (2349.32f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step99 = (uint32_t)( ( (2489.02f) * 4294967296.0f) / SAMPLE_RATE );
static uint32_t phase_step100 = (uint32_t)( ( (2637.02f) * 4294967296.0f) / SAMPLE_RATE );

uint8_t get_amplitude_note(uint8_t note)
{   
    switch (note)
    {
        // 60-71: C5 - B5 (5-я октава)
        case 60: return sine[phase60 >> 22];
        case 61: return sine[phase61 >> 22];
        case 62: return sine[phase62 >> 22];
        case 63: return sine[phase63 >> 22];
        case 64: return sine[phase64 >> 22];
        case 65: return sine[phase65 >> 22];
        case 66: return sine[phase66 >> 22];
        case 67: return sine[phase67 >> 22];
        case 68: return sine[phase68 >> 22];
        case 69: return sine[phase69 >> 22];
        case 70: return sine[phase70 >> 22];
        case 71: return sine[phase71 >> 22];
        
        // 72-83: C6 - B6 (6-я октава)
        case 72: return sine[phase72 >> 22];
        case 73: return sine[phase73 >> 22];
        case 74: return sine[phase74 >> 22];
        case 75: return sine[phase75 >> 22];
        case 76: return sine[phase76 >> 22];
        case 77: return sine[phase77 >> 22];
        case 78: return sine[phase78 >> 22];
        case 79: return sine[phase79 >> 22];
        case 80: return sine[phase80 >> 22];
        case 81: return sine[phase81 >> 22];
        case 82: return sine[phase82 >> 22];
        case 83: return sine[phase83 >> 22];
        
        // 84-95: C7 - B7 (7-я октава)
        case 84: return sine[phase84 >> 22];
        case 85: return sine[phase85 >> 22];
        case 86: return sine[phase86 >> 22];
        case 87: return sine[phase87 >> 22];
        case 88: return sine[phase88 >> 22];
        case 89: return sine[phase89 >> 22];
        case 90: return sine[phase90 >> 22];
        case 91: return sine[phase91 >> 22];
        case 92: return sine[phase92 >> 22];
        case 93: return sine[phase93 >> 22];
        case 94: return sine[phase94 >> 22];
        case 95: return sine[phase95 >> 22];
        
        // 96-100: C8 - E8 (8-я октава)
        case 96: return sine[phase96 >> 22];
        case 97: return sine[phase97 >> 22];
        case 98: return sine[phase98 >> 22];
        case 99: return sine[phase99 >> 22];
        case 100: return sine[phase100 >> 22];
            
        default:
            return 0;
    }
}


typedef struct {
    uint8_t midi_n1;
    uint8_t midi_n2;
    uint8_t midi_n3;
    uint8_t midi_n4;

    float half_beats;
} notes;

notes megalovania[] =
{
    {81, 69, 0, 0, 1}, {69, 69, 69, 69, 2}
};

uint16_t music_counter = 0; //счётчик нот
uint16_t counter_of_accords = ( sizeof(megalovania) / sizeof(notes) ); //счётчиу количества нот в песне

#define bpm 230
uint16_t ms_for_1beat = (60000.3f / bpm); //миллисекунд за бит
uint64_t dlit_ms;
uint64_t dlit_us;
uint64_t global_time_us = 0;

uint16_t global_event_counter = 0;

void duty_set(notes song[], uint16_t event_counter) {
    OCR0 = ( get_amplitude_note(song[event_counter].midi_n1) + get_amplitude_note(song[event_counter].midi_n2) + get_amplitude_note(song[event_counter].midi_n3) + get_amplitude_note(song[event_counter].midi_n4) ) >> 2;
}

static inline void inc_note(uint8_t note)
{
    switch (note) {
        case 60: phase60 += phase_step60; break;
        case 61: phase61 += phase_step61; break;
        case 62: phase62 += phase_step62; break;
        case 63: phase63 += phase_step63; break;
        case 64: phase64 += phase_step64; break;
        case 65: phase65 += phase_step65; break;
        case 66: phase66 += phase_step66; break;
        case 67: phase67 += phase_step67; break;
        case 68: phase68 += phase_step68; break;
        case 69: phase69 += phase_step69; break;
        case 70: phase70 += phase_step70; break;
        case 71: phase71 += phase_step71; break;
        case 72: phase72 += phase_step72; break;
        case 73: phase73 += phase_step73; break;
        case 74: phase74 += phase_step74; break;
        case 75: phase75 += phase_step75; break;
        case 76: phase76 += phase_step76; break;
        case 77: phase77 += phase_step77; break;
        case 78: phase78 += phase_step78; break;
        case 79: phase79 += phase_step79; break;
        case 80: phase80 += phase_step80; break;
        case 81: phase81 += phase_step81; break;
        case 82: phase82 += phase_step82; break;
        case 83: phase83 += phase_step83; break;
        case 84: phase84 += phase_step84; break;
        case 85: phase85 += phase_step85; break;
        case 86: phase86 += phase_step86; break;
        case 87: phase87 += phase_step87; break;
        case 88: phase88 += phase_step88; break;
        case 89: phase89 += phase_step89; break;
        case 90: phase90 += phase_step90; break;
        case 91: phase91 += phase_step91; break;
        case 92: phase92 += phase_step92; break;
        case 93: phase93 += phase_step93; break;
        case 94: phase94 += phase_step94; break;
        case 95: phase95 += phase_step95; break;
        case 96: phase96 += phase_step96; break;
        case 97: phase97 += phase_step97; break;
        case 98: phase98 += phase_step98; break;
        case 99: phase99 += phase_step99; break;
        case 100: phase100 += phase_step100; break;
    }
}

void phase_inc(notes song[], uint16_t event_counter)
{
    uint8_t a = song[event_counter].midi_n1;
    uint8_t b = song[event_counter].midi_n2;
    uint8_t c = song[event_counter].midi_n3;
    uint8_t d = song[event_counter].midi_n4;

    // --- Удаление дублей (самый дешёвый вариант) ---
    if (b == a) b = 0;
    if (c == a || c == b) c = 0;
    if (d == a || d == b || d == c) d = 0;

    // --- Инкременты ---
    inc_note(a);
    inc_note(b);
    inc_note(c);
    inc_note(d);
}


uint16_t timeMs = 0;

void setTimeZero(){
    TCNT1 = 0;
}

uint16_t getTimeMs(){
    return timeMs;
}

int main(void)
{
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
    //OCR0 = ( get_amplitude_note(megalovania[global_event_counter].midi_n1) + get_amplitude_note(megalovania[global_event_counter].midi_n2) + get_amplitude_note(megalovania[global_event_counter].midi_n3) + get_amplitude_note(megalovania[global_event_counter].midi_n4) ) >> 2;
    //phase_inc(megalovania, global_event_counter);
    phase69+=phase_step69;
    phase81+=phase_step81;

}

ISR(TIMER1_COMPA_vect){
    timeMs++;
}