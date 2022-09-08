#include <HUB.h>



THEHUB mySens;
//MAG3110 mymag;


void setup() {
Serial.begin(57600);
delay(1000);


uint8_t buff;
uint8_t buff2;
uint8_t buff3;
uint8_t check;

//uint8_t tempread;
//uint8_t whoamI;

Serial.println("Teensy ok");
mySens.beginSens();

Serial.print("RESET OK?:");
Serial.println(mySens.reset());


////  The old way
//Serial.print("Configuring the external:");
//Serial.println(mySens.extrn_conf(&buff, &check));
//Serial.print("Check:");
//Serial.println(check,HEX);

//////Passthrough way
Serial.print("Passing through:");
Serial.println(mySens.passthrough(&buff2));
//Serial.print("Who_am_I?:");
//Serial.println(buff2,HEX);
//Configure reading
//Serial.print("Configuring Reading Setup:");
Serial.println(mySens.extrn_read(&buff3));
mySens.fifo_watermark(&buff, 720);
mySens.fifo_mode(&buff);
mySens.fifo_odr(&buff);
mySens.fifodec_accel(&buff);
mySens.fifodec_gyro(&buff);
mySens.fifodec_mag(&buff);
if(mySens.fifo_clear())
Serial.println("fifo clear");
}


void loop() {
  axis3bit16_t acceldata;
  axis3bit16_t gyrodata;
  axis3bit16_t magdata;
  float temp;
  uint8_t flag;
//  acceldata = mySens.accel_data();
//  gyrodata = mySens.gyro_data();
//  magdata = mySens.mag_data();
//  
//  
//  Serial.print("x: ");
//  Serial.print(mySens.calcSI(acceldata.i16bit[0]));Serial.print(", ");
//  Serial.print("y: ");
//  Serial.print(mySens.calcSI(acceldata.i16bit[1]));Serial.print(", ");
//  Serial.print("z: ");
//  Serial.print(mySens.calcSI(acceldata.i16bit[2]));Serial.print(", ");
//
//
//  Serial.print("x: ");
//  Serial.print(mySens.calcGyro(gyrodata.i16bit[0]));Serial.print(", ");
//  Serial.print("y: ");
//  Serial.print(mySens.calcGyro(gyrodata.i16bit[1]));Serial.print(", ");
//  Serial.print("z: ");
//  Serial.print(mySens.calcGyro(gyrodata.i16bit[2]));Serial.print(", ");
//  
//  Serial.print("x: ");
//  Serial.print(magdata.i16bit[0]);Serial.print(", ");
//  Serial.print("y: ");
//  Serial.print(magdata.i16bit[1]);Serial.print(", ");
//  Serial.print("z: ");
//  Serial.println(magdata.i16bit[2]);

mySens.fifo_wtrm_flag(&flag);
while(flag&0x80==0){};
while(flag&0x80==1)
{
  
    Serial.print("x: ");
  Serial.print(mySens.calcSI(mySens.fifo_read()));Serial.print(", ");
  Serial.print("y: ");
  Serial.print(mySens.calcSI(mySens.fifo_read()));Serial.print(", ");
  Serial.print("z: ");
  Serial.print(mySens.calcSI(mySens.fifo_read()));Serial.print(", ");


  Serial.print("x: ");
  Serial.print(mySens.calcGyro(mySens.fifo_read()));Serial.print(", ");
  Serial.print("y: ");
  Serial.print(mySens.calcGyro(mySens.fifo_read()));Serial.print(", ");
  Serial.print("z: ");
  Serial.print(mySens.calcGyro(mySens.fifo_read()));Serial.print(", ");
  
  Serial.print("x: ");
  Serial.print(mySens.fifo_read());Serial.print(", ");
  Serial.print("y: ");
  Serial.print(mySens.fifo_read());Serial.print(", ");
  Serial.print("z: ");
  Serial.println(mySens.fifo_read());

  
  
  
  };


}
