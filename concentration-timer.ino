#include "LedControl.h"

/*
 for MAX72XX:
 connect DataIn to pin 12  
 connect CLK to pin 11 
 connect LOAD to pin 3 
 connect VIN to 5V
 connect GND to Ground
 */
const int numDevices = 4;
bool start = false;
LedControl lc=LedControl(11,13,3,numDevices);

/*
 for button:
 connect Data to pin 9
 connect VIN to 5V
 connect GND to Ground
*/
int buttonOut = 9;

//7 seconds for each led 256 X 7 ~ 30 min
unsigned long delaytime=7000;

void setup() {
  for (int x=0; x<numDevices; x++){
    lc.shutdown(x,false);       // startup MAX72XX from power-saving mode
    lc.setIntensity(x,0);       // Brightness
    lc.clearDisplay(x);         // clear display
    }

    pinMode(buttonOut, INPUT);
}

//Write Timer and arrow to led screen
void writeTimerOnMatrix() {
  byte t[5]={B10000000,B10000000,B11111110,B10000000,B10000000};
  byte i[3]={B10000010,B11111110,B10000010};
  byte m[5]={B11111110,B01000000,B00100000,B01000000,B11111110};
  byte e[4]={B11111110,B10010010,B10010010,B10010010};
  byte r[4]={B11111110,B10011000,B10010100,B01100010};
  byte v[5]={B00001000,B00000100,B11111110,B00000100,B00001000};

  //T
  lc.setColumn(3,0,t[0]);
  lc.setColumn(3,1,t[1]);
  lc.setColumn(3,2,t[2]);
  lc.setColumn(3,3,t[3]);
  lc.setColumn(3,4,t[4]);

  //I
  lc.setColumn(3,6,i[0]);
  lc.setColumn(3,7,i[1]);
  lc.setColumn(2,0,i[2]);

  //M
  lc.setColumn(2,2,m[0]);
  lc.setColumn(2,3,m[1]);
  lc.setColumn(2,4,m[2]);
  lc.setColumn(2,5,m[3]);
  lc.setColumn(2,6,m[4]);

  //E
  lc.setColumn(1,0,e[0]);
  lc.setColumn(1,1,e[1]);
  lc.setColumn(1,2,e[2]);
  lc.setColumn(1,3,e[3]);

  //R
  lc.setColumn(1,5,r[0]);
  lc.setColumn(1,6,r[1]);
  lc.setColumn(1,7,r[2]);
  lc.setColumn(0,0,r[3]);

  //down arrow
  lc.setColumn(0,2,v[0]);
  lc.setColumn(0,3,v[1]);
  lc.setColumn(0,4,v[2]);
  lc.setColumn(0,5,v[3]);
  lc.setColumn(0,6,v[4]);
}

//Start actual timer 
void timer() {
  clearDisplay();
  for(int addr = 3; addr>=0; addr--){
  for(int col=0;col<8;col++) {
    for(int row=0;row<8;row++) {
      lc.setLed(addr,row,col,true);
      delay(delaytime);
    }
  }
}

 clearDisplay();
}

void clearDisplay(){
  for (int x=0; x<numDevices; x++){
    lc.clearDisplay(x);
    }
}

void loop() { 
  if (digitalRead(buttonOut) == HIGH) {         
      start = true;
  } 
  
  if(start){
    timer();
    start = !start;
  }
  else{
    writeTimerOnMatrix();
  }
   
}
