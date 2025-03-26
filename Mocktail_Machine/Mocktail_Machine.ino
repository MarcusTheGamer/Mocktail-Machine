#include <LCDWIKI_SPI.h>
#include <lcd_spi_registers.h>
#include <mcu_spi_magic.h>

#include <LCDWIKI_GUI.h>

#include <Vector.h>

#include <Time.h>
#include <TimeLib.h>

#include <List.hpp>
#include <math.h>

#define MODEL GC9A01
#define CS   A1
#define CD   A0
#define RST  A2
#define SDA  52
#define SCK  50
#define LED  48

LCDWIKI_SPI mylcd(MODEL,CS,CD,-1,SDA,RST,SCK,LED);

#define BLACK   0x0000
#define WHITE   0xFFFF
#define YELLOW  0xFF00
#define BLUE    0x00FF
#define SYNTHYELLOW 0xRRGG
#define SYNTHPINK 0xF997

//Opsætning af pins for nemmere tilgåelse.

int pin1 = 39;
int pin2 = 41;
int pin3 = 43;
int pin4 = 45;
int pin5 = 47;
int pin6 = 49;
int pin7 = 51;
int pin8 = 53;

int pins[] = {pin1, pin2, pin3, pin4, pin5, pin6, pin7, pin8};

int btn1 = 7;
int btn2 = 2;
int btn3 = 9;

uint16_t image [73][29] = {
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFE09,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFDAA,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xFD01,0xFD01,0xE660,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFD01,0xFD01,0xE660,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xFD01,0xFB01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xE660,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xFD01,0xFB01,0xE900,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xE660,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xFD01,0xFD01,0xE900,0xFB01,0xFB01,0xFDAA,0xFD01,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xEEB5,0xE660,0xFDAA,0xE660,0xFE09,0xE309,0xE309,0xE309,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xE309,0xE309,0xE309,0xE309,0xFE09,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xE660,0xFD01,0xFD01,0xEEB5,0xEEB5,0xE660,0xE660,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFE09,0xE660,0xFE09,0xEEB5,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xE660,0xFD01,0xFD01,0xFE09,0xE660,0xFE09,0xE660,0xE660,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFDAA,0xFD01,0xFD01,0xFD01,0xE660,0xE660,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFE09,0xFD01,0xFD01,0xFE09,0xFE09,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFE09,0xFD01,0xFE09,0xFE09,0xFE09,0xFE09,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFE09,0xFD01,0xE660,0xFE09,0xFE09,0xFE09,0xE660,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xE660,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0xE660,0xFD01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFE09,0xE660,0xE660,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xE660,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFE09,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xE660,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xE660,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFD01,0xE900,0xFB01,0xFD01,0xE900,0xFB01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xE900,0xFD01,0xE900,0xFD01,0xFB01,0xFB01,0xE900,0xE900,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFD01,0xFB01,0xE900,0xFD01,0xE900,0xFB01,0xFB01,0xFB01,0xE900,0xFD01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFB01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFD01,0xFD01,0xFD01,0xE900,0xFB01,0xFB01,0xFB01,0xFD01,0xFD01,0xFB01,0xFB01,0xFB01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xE900,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFD01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFD01,0xFD01,0xFB01,0xE900,0xFB01,0xFB01,0xFB01,0xFD01,0xE900,0xFB01,0xFB01,0xFD01,0xE900,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xE900,0xFB01,0xE900,0xFB01,0xFB01,0xFB01,0xFB01,0xFD01,0xFB01,0xFD01,0xFD01,0xE900,0xFB01,0xFB01,0xE900,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFD01,0xFB01,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xFD01,0xE900,0xFB01,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xE900,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xE900,0xFB01,0xE900,0xFB01,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xFE09,0xE900,0xFB01,0xFB01,0xFB01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFB01,0xE900,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xE900,0xFD01,0xFD01,0xE900,0xFD01,0xFB01,0xFB01,0xFD01,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFB01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xE900,0xFD01,0xE900,0xFD01,0xFB01,0xFE09,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFD01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xFB01,0xFB01,0xE900,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFD01,0xE900,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFB01,0xFD01,0xFE09,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xE900,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xFD01,0xFB01,0xFB01,0xFD01,0xFD01,0xFD01,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xE900,0xFB01,0xE900,0xFD01,0xFB01,0xFB01,0xFD01,0xFB01,0xFD01,0xE900,0xFB01,0xFB01,0xFB01,0xE900,0xE900,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xE900,0xE900,0xE900,0xFD01,0xFB01,0xFB01,0xFD01,0xFD01,0xE900,0xE900,0xFD01,0xE900,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xE900,0xFB01,0x0000,0x0000},
  {0x0000,0x0000,0xE900,0xFB01,0xE900,0xFD01,0xFB01,0xFDAA,0xFD01,0xE900,0xFB01,0xFB01,0xFD01,0xFB01,0xE900,0xE900,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xFB01,0xE900,0x0000,0x0000},
  {0x0000,0x0000,0xFB01,0xFB01,0xE900,0xFB01,0xE900,0xFB01,0xFB01,0xFD01,0xFB01,0xE900,0xFB01,0xFD01,0xFB01,0xFD01,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xFB01,0xFB01,0xE900,0xE900,0xFB01,0x0000},
  {0x0000,0x0000,0xE900,0xE900,0xFD01,0xFD01,0xFB01,0xFB01,0xE900,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0x0000},
  {0x0000,0x0000,0xFB01,0xFB01,0xFB01,0xFD01,0xE900,0xFB01,0xE900,0xFD01,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xFD01,0xFB01,0xFB01,0xE900,0xFB01,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xFB01,0x0000},
  {0x0000,0x0000,0xE900,0xE900,0xFB01,0xE900,0xFB01,0xFB01,0xFB01,0xE900,0xFD01,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFD01,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0x0000},
  {0x0000,0xFB01,0xE900,0xFB01,0xE900,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xE900,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0x0000},
  {0x0000,0xF350,0xE900,0xE900,0xFB01,0xE900,0xFB01,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xE900,0xFB01,0xE900,0xE900,0xE900,0xA963,0xE900,0xE900,0x0000},
  {0x0000,0xF350,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFD01,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xFB01,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0xE900,0xE900,0xE900,0x0000},
  {0x0000,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xFB01,0xE900,0xE900,0xE900,0xE900,0xA963,0xE900,0xA963,0x0000},
  {0x0000,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFB01,0xFD01,0xE900,0xE900,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0xE900,0xE900,0xE900,0xE900,0x0000},
  {0x0000,0xFB01,0xFB01,0xE900,0xFB01,0xFB01,0xFB01,0xFB01,0xE900,0xE900,0xE900,0xE900,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0x0000},
  {0x0000,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xFB01,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0xE900,0xA963,0x0000},
  {0x0000,0xE900,0xE900,0xE900,0xE900,0xE900,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0xE900,0x0000},
  {0x0000,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0x0000},
  {0x0000,0xE900,0xFB01,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0x7141,0xA963,0xA963,0x7141,0x7141,0x0000},
  {0x0000,0x0000,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0xA963,0xA963,0xE900,0xE900,0xA963,0x0000,0x0000},
  {0x0000,0x0000,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xA963,0xA963,0xA963,0x7141,0xE900,0xA963,0xA963,0xA963,0x7141,0xA963,0xA963,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0xE900,0xA963,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xE900,0xFB01,0xA963,0xA963,0xA963,0x7141,0xA963,0x7141,0x7141,0xA963,0xA963,0xA963,0xA963,0xA963,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0xE900,0x7141,0x7141,0x7141,0x7141,0xA963,0x7141,0xA963,0xA963,0x7141,0x7141,0xA963,0xA963,0xA963,0xE309,0xA963,0xA963,0x0000,0x0000,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x7141,0x7141,0x7141,0xA963,0x7141,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000},
  {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}
};

enum Outputs
{
  Kokosmaelk,
  Limejuice,
  Danskvand,
  Grenadine,
  Appelsinjuice,
  BlaaCuracao,
  LemonSoda,
  MangoSirup
};

class Mocktail {
  public:
    String Name;
    static const int MAX_SIZE = 10;
    Outputs Ingredients[MAX_SIZE];
    int Ratios[MAX_SIZE];
    int Size;

    Mocktail(String name, const Outputs ingredients[], const int ratios[], int size) 
      : Name(name), Size(size) {

      for (int i = 0; i < size; i++) {
        Ingredients[i] = ingredients[i];
        Ratios[i] = ratios[i];
      }
    }
};

Outputs Ingredients1[] = { Kokosmaelk, Limejuice, Danskvand, Grenadine };
int Ratios1[] = { 1, 2, 3, 4 };

Outputs Ingredients2[] = { Limejuice, Danskvand };
int Ratios2[] = { 2, 3 };

Outputs Ingredients3[] = { Kokosmaelk, Grenadine };
int Ratios3[] = { 1, 4 };

Mocktail mocktails[3] = {
  Mocktail("Tropical Breeze", Ingredients1, Ratios1, 4),
  Mocktail("Citrus Fizz", Ingredients2, Ratios2, 2),
  Mocktail("Sweet Sunset", Ingredients3, Ratios3, 2)
};

int flowspeed = 50;
int cupAmount = 0;
const int cupSize = 250;

void displayMocktail()
{
  for (int y = 0; y < 73; y++)
  {
    for (int x = 0; x < 29; x++)
    {
      if (image[y][x] != 0x0000)
      {
        mylcd.Fill_Rect(x*2 + 91,y*2 + 47,2,2,image[y][x]);
      }
    }
  }
}

void displayBackground()
{

}

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);

  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);
  //Serial.begin(9600);

  //float top [3] = {255,248,117};
  //float bottom [3] = {255,89,191};
  int top [3] = {254,187,7};
  int bottom [3] = {173,2,0};
  int rgb [3];
  for (int y = 0; y < 12; y++)
  {
    for (int i = 0; i < 3; i++)
    {
      //float bottomCur = bottom[i];
      //float topCur = top[i];
      if (top[i] > bottom[i])
      {
        rgb[i] = round((top[i] - bottom[i]) / 240. * (y * 20.)) + bottom[i];
      }
      else
      {
        rgb[i] = round((bottom[i] - top[i]) / 240. * (y * 20.)) + top[i];
      }
    }
    
    uint16_t RGB = ((rgb[0] & 0xF8) << 8) | ((rgb[1] & 0xFC) << 3) | (rgb[2] >> 3);
    mylcd.Fill_Rect(0,y * 20,240,20,RGB);
  };
  displayMocktail();
}

void pour(int index, int time)
{
  
}

void pourButton(int index)
{
  Mocktail mocktail = mocktails[index];

  for (int i = 0; i < sizeof(mocktail.Ingredients) / sizeof(mocktail.Ingredients[0]); i++)
  {
    int index = 0;
    for (int j = 0; j < 8; j++)
    {
      if (mocktail.Ingredients[i] == Outputs(j))
      {
        index = j;
      }
    }

    int amount = cupSize / 100 * mocktail.Ratios[i];

    pour(index, round(amount / flowspeed * 100));
  };
}

int SelectIndex = 0;
int CurrentModule = 0;

void enableRelay(int i){
    if (i >= 0 && i < 8) {
    digitalWrite(CurrentModule, LOW);
    digitalWrite(pins[i], HIGH);
    CurrentModule = pins[i];
  }
}

int LastBtn1State = LOW;
int LastBtn2State = LOW;
int LastBtn3State = LOW;

bool compareBtnStates(int prev, int cur){
  if (prev == LOW && cur == HIGH){
    return true;
  }
  else {
    return false;
  }
}

void loop() {

  int Btn1StateNow = digitalRead(btn1);
  int Btn2StateNow = digitalRead(btn2);
  int Btn3StateNow = digitalRead(btn3);
  if (compareBtnStates(LastBtn1State, Btn1StateNow) && SelectIndex < 7 )
  {
    SelectIndex++;
    //Serial.println("↑");
  }
  else if (compareBtnStates(LastBtn3State, Btn3StateNow) && SelectIndex > 0)
  {
    SelectIndex--;
    //Serial.println("↓");
  }
  //Serial.print(testThingDeleteLater);
  if (compareBtnStates(LastBtn2State, Btn2StateNow)){
    //pourButton(testThingDeleteLater);
    enableRelay(SelectIndex);
    //Serial.println(SelectIndex);
  }
  LastBtn1State = digitalRead(btn1);
  LastBtn2State = digitalRead(btn2);
  LastBtn3State = digitalRead(btn3);
}