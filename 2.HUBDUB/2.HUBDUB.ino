#include <HubDub.h>




THEHUB mySens;

void setup() {
Serial.begin(57600);
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

while((mySens.fifo_wtrm_flag()&0x10) == 0)
{ 
  i=1;

//  while(i<=172){
  
//Serial.println("Bomb has been planted!");

//Gyro
  Serial.print("x: ");
  Serial.print(mySens.calcGyro(mySens.fifo_read()));Serial.print(", ");
  Serial.print("y: ");
  Serial.print(mySens.calcGyro(mySens.fifo_read()));Serial.print(", ");
  Serial.print("z: ");
  Serial.print(mySens.calcGyro(mySens.fifo_read()));Serial.print(", ");
  
//Accel  
  Serial.print("x: ");
  Serial.print(mySens.calcSI(mySens.fifo_read()));Serial.print(", ");
  Serial.print("y: ");
  Serial.print(mySens.calcSI(mySens.fifo_read()));Serial.print(", ");
  Serial.print("z: ");
  Serial.print(mySens.calcSI(mySens.fifo_read()));

////Mag
  Serial.print(", ");
  Serial.print("x: ");
  Serial.print(mySens.fifo_read());Serial.print(", ");
  Serial.print("y: ");
  Serial.print(mySens.fifo_read());Serial.print(", ");
  Serial.print("z: ");
  Serial.println(mySens.fifo_read());


  
delay(10);
  
//  i++;
//    };
    
  };
Serial.println("Out_____________________________________________________________________________________________________________________");


}
