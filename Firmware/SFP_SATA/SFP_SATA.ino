    /*  
     *  How I2C Communication Protocol Works - Example01
     *  
     *   by Dejan Nedelkovski, www.HowToMechatronics.com 
     *   for a in 0 1 2 ; do
  i2cset -y ${a} 0x56 0x1b 0x8490 w
  i2cset -y ${a} 0x56 0x09 0x000f w
  i2cset -y ${a} 0x56 0x00 0x0081 w
  i2cset -y ${a} 0x56 0x04 0xe10d w
  i2cset -y ${a} 0x56 0x00 0x0091 w
done
     *   
     */
    #include <Wire.h>
    int SFP_Address = 0x56; // Device address in which is also included the 8th bit for selecting the mode, read in this case.

    void write16B(int addr, int value)
    {
    Wire.beginTransmission(SFP_Address);
    Wire.write(addr); 

    Wire.write(0xff & (value>>8));
    Wire.write(0xff & value);
    Wire.endTransmission();
    delay(10);
    }
    
   unsigned int  read16B(int addr)
    {

    Wire.beginTransmission(SFP_Address);
    Wire.write(addr);   
    Wire.endTransmission();
    Wire.requestFrom(SFP_Address, 2, 1); 
    unsigned int value = Wire.read()<<8;
    value |= Wire.read();
   delay(10);
    return value;
    }

    
    void setup() {
      Wire.begin(); // Initiate the Wire library
     Serial.begin(9600);
      delay(100);

    if (read16B(02) == 0x141) 

    {
     Serial.print("detected 88E1111 chip\n");
     //Serial.print(read16B(27)& 0x0F );
       if ((read16B(27)& 0x0F )!=0x8) 
       {
       Serial.print("88E1111 chip works in SGMII mode, updating\n");
//      // Enable measurement
      write16B(22, 0x00); //page0
      write16B(0, 0x140); 
      write16B(1, 0x149); 
      write16B(4, 0xC01);
      write16B(7, 0x2001);
      write16B(9, 0xE00);
      write16B(16, 0x78);
      write16B(17, 0x8140);
      write16B(19, 0x50);  
      write16B(26, 0xA);       
      write16B(27, 0x9088);
      
      write16B(22, 0x01); //page1
      write16B(0, 0x1140); 
      write16B(1, 0x149); 
      write16B(4, 0x0);
      write16B(7, 0x2001);
      write16B(9, 0xE00);
      write16B(16, 0x78);
      write16B(17, 0x8010);
      write16B(19, 0x0);  
      write16B(26, 0xA);       
      write16B(27, 0x9088);
   
      write16B(0x00, 0x8000 | (0x0F & read16B(00)));
      write16B(0x00,  (0x0F & read16B(00)));
  Serial.print("88E1111 updated, works in 1000Base-x mode now");
 
       }
       else 
       {
        Serial.print("88E1111  works in 1000Base-x mode, no update needed");
       }
       
       
    
     
    }



      
     Serial.print("  \n");
     Serial.print("ADDR  DAT page0 page1");
     Serial.print("  \n");
      for (int a=0; a<32; a++) 
     {
         Serial.print(a);
         Serial.print(" ");
          write16B(22, 0x00); //page0
          delay(10);
         Serial.print(read16B((a)),HEX);
          write16B(22, 0x01); //page1
         Serial.print(" ");
          delay(10);
         Serial.print(read16B((a)),HEX);
         Serial.print("  \n");
          delay(10);
     }


      
    }
    void loop() {

  Serial.print("  \n");
     Serial.print("ADDR  DAT page0 page1");
     Serial.print("  \n");
      for (int a=0; a<32; a++) 
     {
         Serial.print(a);
         Serial.print(" ");
          write16B(22, 0x00); //page0
          delay(10);
         Serial.print(read16B((a)),HEX);
          write16B(22, 0x01); //page1
         Serial.print(" ");
          delay(10);
         Serial.print(read16B((a)),HEX);
         Serial.print("  \n");
          delay(10);
     }

     delay(1000);
     
      }
      
      
 
