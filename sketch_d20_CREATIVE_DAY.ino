#include "Arduino.h"
#include <TM1637Display.h>
#include <Keypad.h>

const byte DISPLAY_CLK = 6;
const byte DISPLAY_DIO = 5;
const byte DELAY = 500;

const byte XXXX[] = {
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
};
const byte XXXL[] = {
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  SEG_D | SEG_E | SEG_F,
};
const byte XXLO[] = {
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
};
const byte XLOS[] = {
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
};
const byte LOST[] = {
  SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C,
};
const byte OST[] = {
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C,
  SEG_A,
};
const byte ST_[] = {
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C,
  SEG_A,
  0b00000000 |  0b00000000 |  0b00000000 |  SEG_D |  0b00000000 |  0b00000000 |  0b00000000,  
};
const byte T_I[] = {
  SEG_A | SEG_B | SEG_C,
  SEG_A,
  0b00000000 |  0b00000000 |  0b00000000 |  SEG_D |  0b00000000 |  0b00000000 |  0b00000000,  
  SEG_B | SEG_C,
};
const byte T_IN[] = {
  SEG_A,
  0b00000000 |  0b00000000 |  0b00000000 |  SEG_D |  0b00000000 |  0b00000000 |  0b00000000,  
  SEG_B | SEG_C,
  SEG_C | SEG_E | SEG_G
};
const byte _IN_[] = {
  0b00000000 |  0b00000000 |  0b00000000 |  SEG_D |  0b00000000 |  0b00000000 |  0b00000000,  
  SEG_B | SEG_C,
  SEG_C | SEG_E | SEG_G,
  0b00000000 |  0b00000000 |  0b00000000 |  SEG_D |  0b00000000 |  0b00000000 |  0b00000000,
};
const byte IN_S[] = {
  SEG_B | SEG_C,
  SEG_C | SEG_E | SEG_G,
  0b00000000 |  0b00000000 |  0b00000000 |  SEG_D |  0b00000000 |  0b00000000 |  0b00000000,
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
};
const byte N_SP[] = {
  SEG_C | SEG_E | SEG_G,
  0b00000000 |  0b00000000 |  0b00000000 |  SEG_D |  0b00000000 |  0b00000000 |  0b00000000,
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
};
const byte _SPA[] = {
  0b00000000 |  0b00000000 |  0b00000000 |  SEG_D |  0b00000000 |  0b00000000 |  0b00000000,
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
};
const byte SPAC[] = {
  SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_D | SEG_E | SEG_F, SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
};
const byte PACE[] = {
  SEG_A | SEG_B | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_D | SEG_E | SEG_F, 
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
};
const byte ACEX[] = {
  SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
  SEG_A | SEG_D | SEG_E | SEG_F, 
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
};
const byte CEXX[] = {
  SEG_A | SEG_D | SEG_E | SEG_F, 
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
};
const byte EXXX[] = {
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
};
const byte XXT[] = {
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000 |  0b00000000,
  SEG_A ,
  SEG_A | SEG_E | SEG_F,
 
};

TM1637Display display_panel = TM1637Display(DISPLAY_CLK, DISPLAY_DIO);

void setup() {
  // put your setup code here, to run once:
  display_panel.setBrightness(7);
}

void loop() {
  // put your main code here, to run repeatedly:
  display_panel.setSegments(XXXX);
  delay(DELAY);
  display_panel.setSegments(XXXL);
  delay(DELAY);
  display_panel.setSegments(XXLO);
  delay(DELAY);
  display_panel.setSegments(XLOS);
  delay(DELAY);
  display_panel.setSegments(LOST);
  delay(DELAY);
  display_panel.setSegments(OST);
  delay(DELAY);
  display_panel.setSegments(ST_);
  delay(DELAY);
  display_panel.setSegments(T_I);
  delay(DELAY);
  display_panel.setSegments(T_IN);
  delay(DELAY);
  display_panel.setSegments(_IN_);
  delay(DELAY);
  display_panel.setSegments(IN_S);
  delay(DELAY);
  display_panel.setSegments(N_SP);
  delay(DELAY);
  display_panel.setSegments(_SPA);
  delay(DELAY);
  display_panel.setSegments(SPAC);
  delay(DELAY);
  display_panel.setSegments(PACE);
  delay(DELAY);
  display_panel.setSegments(ACEX);
  delay(DELAY);
  display_panel.setSegments(CEXX);
  delay(DELAY);
  display_panel.setSegments(EXXX);
  delay(DELAY);
  display_panel.setSegments(XXXX);
  delay(2000);
}
