#include <FreeStack.h>
#include <MinimumSerial.h>
#include <SdFatConfig.h>
#include <SdFat.h>
#include <sdios.h>
#include <SysCall.h>
#include <BlockDriver.h>
#include <HubDub.h>




THEHUB mySens;
SdFatSdio sd;
File myFile;
int pinCS = 10;

//LED
int led = 13;



void setup() {
Serial.begin(57600);
delay(1000);

pinMode(led, OUTPUT);
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(4000);               // wait for a second
digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
delay(1000);


uint8_t buff;
uint8_t buff2;
uint8_t buff3;
uint8_t check;


Serial.println("Teensy ok");
mySens.beginSens();
delay(100);

Serial.print("RESET OK?:");
if (mySens.reset())
Serial.println("........ ok!");


//////  The old way
//Serial.print("Configuring the external:");
//Serial.println(mySens.extrn_conf(&buff, &check));
//Serial.print("Check:");
//Serial.println(check,HEX);


//Serial.print("Configuring the reading:");
//Serial.println(mySens.extrn_read(&check));
//Serial.print("Check:");
//Serial.println(check,HEX);



//////Passthrough way
//Serial.print("Passing through:");
//mySens.passthrough(&buff2);
//Serial.print("Who_am_I?:");
//Serial.println(buff2,HEX);
//Configure reading

//External Read
//mySens.extrn_read(&check);
//Serial.print("Just checking:");
//Serial.println(check,HEX);


//:FIFO Read

mySens.fifo_conf(&buff);
//mySens.fifodefault(&buff);
Serial.print("Is FIFO clear?:");
if(mySens.fifo_clear())
Serial.println("........ ya ma man!");
Serial.print("FIFO status:");
mySens.readRegister(ACCEL_ADDR, FIFO_STATUS2, &buff2,1);
Serial.println(buff2, HEX);
Serial.print("The checking is:");
Serial.println(buff, HEX);

 if (!sd.begin())
        {
          Serial.println("SD card Error.");
        }

digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(1000);               // wait for a second
digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
delay(1000);
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(1000);               // wait for a second
digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
delay(1000);
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
delay(1000);               // wait for a second
digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
delay(1000);
}


void loop() {

//  axis3bit16_t acceldata;
//  axis3bit16_t gyrodata;
//  axis3bit16_t magdata;
//  float temp;
  int i=0;
  uint8_t flag;
  
//  acceldata = mySens.accel_data();
//  gyrodata = mySens.gyro_data();
//  magdata = mySens.mag_data();
//  
//  
//

while((mySens.fifo_wtrm_flag()&0x80)==0){  };
myFile = sd.open("test.txt", FILE_WRITE);


while((mySens.fifo_wtrm_flag()&0x10) == 0)
{ 
  i=1;

//  while(i<=172){
  
//myFile.println("Bomb has been planted!");
         if (myFile) {

//Gyro
  myFile.print("x: ");
  myFile.print(mySens.calcGyro(mySens.fifo_read()));myFile.print(", ");
  myFile.print("y: ");
  myFile.print(mySens.calcGyro(mySens.fifo_read()));myFile.print(", ");
  myFile.print("z: ");
  myFile.print(mySens.calcGyro(mySens.fifo_read()));myFile.print(", ");
  
//Accel  
  myFile.print("x: ");
  myFile.print(mySens.calcSI(mySens.fifo_read()));myFile.print(", ");
  myFile.print("y: ");
  myFile.print(mySens.calcSI(mySens.fifo_read()));myFile.print(", ");
  myFile.print("z: ");
  myFile.print(mySens.calcSI(mySens.fifo_read()));

////Mag
  myFile.print(", ");
  myFile.print("x: ");
  myFile.print(mySens.fifo_read());myFile.print(", ");
  myFile.print("y: ");
  myFile.print(mySens.fifo_read());myFile.print(", ");
  myFile.print("z: ");
  myFile.println(mySens.fifo_read());


  
delay(10);
  
//  i++;
//    };
    
  };
}
myFile.println("Out_____________________________________________________________________________________________________________________");

 myFile.close();
 
}
