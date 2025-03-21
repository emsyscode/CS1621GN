/*Begining of Auto generated code by Atmel studio */
/*
This code is not clean and also is not perfect, this is only 
a reference to extract ideas and adapte to your solution.
*/
#define LCD_in 7 // This is the pin number 7 on Arduino UNO
#define LCD_wr 8 // This is the pin number 8 on Arduino UNO
#define LCD_cs 9 // This is the pin number 9 on Arduino UNO

unsigned int symbolsHEX[16] = {0xFA,0x0A,0xD6,0x9E,0x2E,0xBC,0xFC,0x1A,0xFE,0x3E,0x7E,0xEC,0xF0,0xCE,0xF4,0x74};

//ATT: On the Uno and other ATMEGA based boards, unsigned ints (unsigned integers) are the same as ints in that they store a 2 byte value.
//Long variables are extended size variables for number storage, and store 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647.
/*
This is the format of commands:
READ..................110 A5A4A3A2A1A0 D0D1D2D3   
WRITE.................101 A5A4A3A2A1A0 D0D1D2D3   
READ- MODIFY -WRITE...101 A5A4A3A2A1A0 D0D1D2D3  
SYS DIS...............100 000-0000-X C 

SYS DIS 100 0000-0000-X C Turn off both system oscillator and LCD bias generator Yes
SYS EN 100 0000-0001-X C Turn on system oscillator LCD, OFF 100 0000-0010-X C 
Turn off LCD bias generator Yes LCD ON 100 0000-0011-X C Turn on LCD bias generator
*/
void setup() {
  pinMode(LCD_wr, OUTPUT);
  pinMode(LCD_in, OUTPUT);
  pinMode(LCD_cs, OUTPUT);
 
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  digitalWrite(LCD_cs, LOW);
  delayMicroseconds(5);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  digitalWrite(13, HIGH);
  delay(500);
  //
  initLCD(); 
  delay(100);
}
void send_char(unsigned int a){
  unsigned int data = 0; 
  unsigned int mask = 1; //our bitmask
    data=a;
    digitalWrite(LCD_cs, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
    delayMicroseconds(2);
  // I define the size of mask to send only 12 bits
    for (mask = 0b000000000001; mask<4096; mask <<= 1) { //iterate through bit mask
    // Serial.println(mask, BIN);
    digitalWrite(LCD_wr,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);
      if (data & mask){ // if bitwise AND resolves to true
        digitalWrite(LCD_in, HIGH);
      // Serial.print(1);
      }
      else{ //if bitwise and resolves to false
        digitalWrite(LCD_in, LOW);
      // Serial.print(0);
      }
      digitalWrite(LCD_wr, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
      delayMicroseconds(2);
    }
    digitalWrite(LCD_cs, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
      delayMicroseconds(2);
}
void send_cmd(unsigned int a){
  // Attention: The "cmd" use 13 bits, the send_char use only 12
  //
  unsigned int data = 0; 
  unsigned int mask = 1; //our bitmask
    data=a;
    digitalWrite(LCD_cs, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
    delayMicroseconds(2);
  // I define the size of mask to send only 12 bits
    for (mask = 0b0000000000001; mask < 8192; mask <<= 1) { //iterate through bit mask
      //Serial.println(mask, BIN);
    digitalWrite(LCD_wr,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);
      if (data & mask){ // if bitwise AND resolves to true
        digitalWrite(LCD_in, HIGH);
        //Serial.print(1);
      }
      else{ //if bitwise and resolves to false
        digitalWrite(LCD_in, LOW);
        //Serial.print(0);
      }
      digitalWrite(LCD_wr, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
      delayMicroseconds(2);
    }
    digitalWrite(LCD_cs, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
    delayMicroseconds(2);
}  
void send_cmd13(unsigned int a){
  // Attention: The "cmd" use 13 bits, the send_char use only 12
  //
  unsigned int data = 0; 
  unsigned int mask = 1; //our bitmask
    data=a;
    digitalWrite(LCD_cs, LOW); // When strobe is low, all output is enable. If high, all output will be set to low.
    delayMicroseconds(2);
  // I define the size of mask to send only 12 bits
    for (mask = 0b1000000000000; mask > 0; mask >>= 1) { //iterate through bit mask
      //Serial.println(mask, BIN);
    digitalWrite(LCD_wr,LOW);// need invert the signal to allow 8 bits is is low only send 7 bits
    delayMicroseconds(2);
      if (data & mask){ // if bitwise AND resolves to true
        digitalWrite(LCD_in, HIGH);
        //Serial.print(1);
      }
      else{ //if bitwise and resolves to false
        digitalWrite(LCD_in, LOW);
        //Serial.print(0);
      }
      digitalWrite(LCD_wr, HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
      delayMicroseconds(2);
    }
    digitalWrite(LCD_cs, HIGH); // When strobe is low, all output is enable. If high, all output will be set to low.
    delayMicroseconds(2);
}  
void initLCD(){
    //*****************************************************************//
    //  LCD OFF 10000000010X Turn off LCD outputs 
    //  LCD ON  10000000011X Turn on LCD outputs
    //
    //  BIAS & COM 1000010abXcX
    //  c=0: 1/2 bias option 
    //  c=1: 1/3 bias option 
    //  ab=00: 2 commons option 
    //  ab=01: 3 commons option 
    //  ab=10: 4 commons option
    //****************************************************************//
    //            X0Xba0100001 
    //send_char(0b000100100001); //100 0010-abX0-X BIAS 1/2 LCD 1/2 bias option ab=00: 2 commons option ab=01: 3 commons option ab=10: 4 commons option
    //send_char(0b010100100001); //100 0010-abX0-X BIAS 1/2 LCD 1/2 bias option ab=00: 2 commons option ab=01: 3 commons option ab=10: 4 commons option
    //The LCD I'm use, have 4 common pins. I let the position of "a" with "1" to select this option!
    send_char(0b000010100001); //100 0010-abX1-X BIAS 1/3 LCD 1/3 bias option ab=00: 2 commons option ab=01: 3 commons option ab=10: 4 commons option 
    send_char(0b001100000001);// TIMER EN 100 0000-0110-X  Enable time base output
    //send_char(0b000000000001); //SYS DIS Turn off both system oscillator and LCD bias generator, stay off
    //delay(2000);
    //send_char(0B100000000010); // SYS EN
    send_char(0B010000000001); // SYS EN
    //send_char(0B100000000110); // LCD ON
    send_char(0B011000000001); // LCD ON
    //send_char(0B001000000001); // LCD OFF
}
void fourBitsZero(void){
    // all the 4 first bits at left side with the value 0000, means clean LCD;
    send_cmd(0B0000000000101);
    send_cmd(0B0000100000101);
    send_cmd(0B0000010000101);
    send_cmd(0B0000110000101);
    send_cmd(0B0000001000101);
    send_cmd(0B0000101000101);
    send_cmd(0B0000011000101);
    send_cmd(0B0000111000101);
    send_cmd(0B0000000100101);
    send_cmd(0B0000100100101);
    send_cmd(0B0000010100101);
    send_cmd(0B0000110100101);
    send_cmd(0B0000001100101);
    send_cmd(0B0000101100101);
    send_cmd(0B0000011100101);
    send_cmd(0B0000111100101);
    //a0-a15 ... d0-d15
    send_cmd(0B0000000010101);
    send_cmd(0B0000100010101);
    send_cmd(0B0000010010101);
    send_cmd(0B0000110010101);
    send_cmd(0B0000001010101);
    send_cmd(0B0000101010101);
    send_cmd(0B0000011010101);
    send_cmd(0B0000111010101);
    send_cmd(0B0000000110101);
    send_cmd(0B0000100110101);
    send_cmd(0B0000010110101);
    send_cmd(0B0000110110101);
    send_cmd(0B0000001110101);
    send_cmd(0B0000101110101);
    send_cmd(0B0000011110101);
    send_cmd(0B0000111110101);
}
void numbers0123(void){
  //0xFA,0x0A,0xD6,0x9E,
    // 1/0-1/15 ... 4/0-4/15 
    send_cmd(0B1111000000101); //first digit from left seg: a,d,e,f
    send_cmd(0B1010100000101); //First digit from left seg: b,g,c

    send_cmd(0B0000010000101); //Second digit from left seg: a,d,e,f
    send_cmd(0B1010110000101); //Second digit from left seg: b,g,c,dot

    send_cmd(0B1101001000101); //Third digit from left seg: d,e,f,a,
    send_cmd(0B0110101000101); //Third digit from left seg: c,g,b,dot

    send_cmd(0B1001011000101); //Fourth digit from left seg: d,e,f,a,
    send_cmd(0B1110111000101); //Fourth digit from left seg: c,g,b,dot
}
void numbers4567(void){
  //0x2E,0xBC,0xFC,0x1A,
    // 4 
    send_cmd(0B0010000000101); //first digit from left seg: d,e,f,a
    send_cmd(0B1110100000101); //First digit from left seg: c,g,b,h
    //5
    send_cmd(0B1011010000101); //Second digit from left seg: d,e,f,a
    send_cmd(0B1100110000101); //Second digit from left seg: c,g,b,h
    //6
    send_cmd(0B1111001000101); //Third digit from left seg: d,e,f,a,
    send_cmd(0B1100101000101); //Third digit from left seg: c,g,b,h
    //7
    send_cmd(0B0001011000101); //Fourth digit from left seg: d,e,f,a,
    send_cmd(0B1010111000101); //Fourth digit from left seg: c,g,b,h
}
void numbers89AB(void){
  //0xFE,0x3E,0x7E,0xEC,
    // 8 
    send_cmd(0B1111000000101); //first digit from left seg: d,e,f,a
    send_cmd(0B1110100000101); //First digit from left seg: c,g,b,h
    //9
    send_cmd(0B0011010000101); //Second digit from left seg: d,e,f,a
    send_cmd(0B1110110000101); //Second digit from left seg: c,g,b,h
    //A
    send_cmd(0B0111001000101); //Third digit from left seg: d,e,f,a,
    send_cmd(0B1110101000101); //Third digit from left seg: c,g,b,h
    //B
    send_cmd(0B1110011000101); //Fourth digit from left seg: d,e,f,a,
    send_cmd(0B1100111000101); //Fourth digit from left seg: c,g,b,h
}
void numbersCDEF(void){
  //0xF0,0xCE,0xF4,0x74
    // C
    send_cmd(0B1111000000101); //first digit from left seg: d,e,f,a
    send_cmd(0B0000100000101); //First digit from left seg: c,g,b,h
    //D
    send_cmd(0B1100010000101); //Second digit from left seg: d,e,f,a
    send_cmd(0B1110110000101); //Second digit from left seg: c,g,b,h
    //E
    send_cmd(0B1111001000101); //Third digit from left seg: d,e,f,a,
    send_cmd(0B0100101000101); //Third digit from left seg: c,g,b,h
    //F
    send_cmd(0B0111011000101); //Fourth digit from left seg: d,e,f,a,
    send_cmd(0B0100111000101); //Fourth digit from left seg: c,g,b,h
}
void segmentTest(void){
  unsigned int common=0;
  unsigned int address=0;
  unsigned int cmd=0b101;
  unsigned int mem=0;
  unsigned int aux=0;
  unsigned int var=0;
  unsigned int data=0;
  unsigned int temp=0;
  //
    for(common=0; common<16; common++){
        temp=0;
        var=(common << 9);
        //Serial.print("var: "); Serial.print(var, BIN); Serial.print("; var=");Serial.println(var, DEC);// Only for Debug
        //
            for (mem=0; mem< 64; mem++){
              data=0;
              data=(data | cmd);
              //Serial.print("Data 1: "); Serial.println(data, BIN); // Only for Debug
              aux=mem << 3;
              //Serial.print("aux: "); Serial.print(aux, BIN); Serial.print("; mem="); Serial.println(mem, DEC); // Only for Debug
              data=(data | aux);
              //Serial.print("Data 2: "); Serial.println(data, BIN); // Only for Debug
              temp=(data | var);
              send_cmd(temp);
              //Serial.println(temp, BIN); // Only for Debug
              delay(50);
              }
    }
}
void allOn(void){
  //This is a construction of a Command: cmd with 13 bits
  //The unsigned int declaration keep 2 bytes
  //WRITE.................101 A5A4A3A2A1A0D0D1D2D3  It is design of commmand to Write, 13 bits
    unsigned int common=0;
    unsigned int address=0;
    unsigned int cmd=0b101;
    unsigned int mem=0;
    unsigned int aux=0;
    unsigned int var=0;
    unsigned int data=0;
    unsigned int temp=0;
    //
  for(common=0; common<16; common++){  //This is the four bits of DATA: D0 to D3
          temp=0;
          //var=(common << 9); //Here I create the 4 bits used as Data D0 to D3.
          var = (0x0F << 9); //Here I force the 4 bits to value "1"
            for (mem=0; mem< 64; mem++){  //This will be used to fill address A5 to A0
              data=0;
              data=(data | cmd);  //cmd is the 3 bits which define the command type
              //Serial.print("Data 1: "); Serial.println(data, BIN); // Only for Debug
              //invertBit(mem);
              aux=mem << 3; //This is normal use
              //Serial.print("aux: "); Serial.print(aux, BIN); Serial.print("; mem="); Serial.println(mem, DEC); // Only for Debug
              data=(data | aux);
              //Serial.print("Data 2: "); Serial.println(data, BIN); // Only for Debug
              temp=(data | var);
              send_cmd(temp);
              Serial.println(temp, BIN);
              delayMicroseconds(2);
            }
  }
}
void allOff(void){
  //This is a construction of a Command: cmd with 13 bits
  //The unsigned int declaration keep 2 bytes
  //WRITE.................101 A5A4A3A2A1A0D0D1D2D3  It is design of commmand to Write, 13 bits
    unsigned int common=0;
    unsigned int address=0;
    unsigned int cmd=0b101;
    unsigned int mem=0;
    unsigned int aux=0;
    unsigned int var=0;
    unsigned int data=0;
    unsigned int temp=0;
    //
  for(common=0; common<16; common++){  //This is the four bits of DATA: D0 to D3
          temp=0;
          //var=(common << 9);  //Here I create the 4 bits used as Data D0 to D3.
          var = (0x00 << 9);    //Here I force the 4 bits to value "0"
            for (mem=0; mem< 64; mem++){  //This will be used to fill address A5 to A0
              data=0;
              data=(data | cmd);  //cmd is the 3 bits which define the command type
              //Serial.print("Data 1: "); Serial.println(data, BIN); // Only for Debug
              aux=mem << 3; //This is normal use
              //Serial.print("aux: "); Serial.print(aux, BIN); Serial.print("; mem="); Serial.println(mem, DEC); // Only for Debug
              data=(data | aux);
              //Serial.print("Data 2: "); Serial.println(data, BIN); // Only for Debug
              temp=(data | var);
              send_cmd(temp);
              Serial.println(temp, BIN);
              delayMicroseconds(2);
            }
  }
}
void hexValues(void){
  //This is a construction of a Command: cmd with 13 bits
  //The unsigned int declaration keep 2 bytes
  //WRITE.................101 A5A4A3A2A1A0D0D1D2D3  It is design of commmand to Write, 13 bits
    unsigned int cmd=0b101;
    unsigned int mem=0;
    unsigned int aux=0;
    unsigned int varL=0;
    unsigned int varH=0;
    unsigned int data=0;
    unsigned int temp=0;
    unsigned int odd = 0x00;
    unsigned int pos = 0x00;
    unsigned char myChar = 0x00;
    uint8_t cL = 0;
    uint8_t cH = 0;
    
    for(pos = 0; pos < 16; pos++){
      myChar = reverse_bits(symbolsHEX[pos]);
      cL = ((myChar >> 0) & 0x0F);
      cH = ((myChar >> 4) & 0x0F);
          for(mem = 0; mem < 8; mem++){  //This is the four bits of DATA: D0 to D3
              odd = (mem % 2);
              // Serial.print("Even/Odd: "); Serial.println(odd, HEX);
              // Serial.print(cH, HEX); Serial.print("  "); Serial.println(cL, HEX);
              data = 0;
              data = cmd << 10;  //cmd is the 3 bits which define the command type and I start it by the left side!
                   if(odd == 0){  //One number is assembled by two word's of 4 bits, I use the Odd and Even to identify each is the word High or Low
                    varL = (cL << 12); //
                    Serial.print("L :"); Serial.println(varL, BIN);
                    data = ((data | mem << 4));
                    temp = (data | varL >>12);
                    send_cmd13(temp); //I use this function to send the 13 bits cmd inverted, because I construct the instruction in reverse order, only by this!
                   }
                   else{
                    varH = (cH << 12); //
                    Serial.print("H :"); Serial.println(varH, BIN);
                    data = ((data | mem << 4));
                    temp = (data | varH >>12);
                    send_cmd13(temp); //I use this function to send the 13 bits cmd inverted, because I construct the instruction in reverse order, only by this!
                    delay(700); //Only here I do the delay, because the assemblage of the digit use 2 half byte! Finish at second word of 4 bits!
                   }
              delayMicroseconds(20);     
      }
      //delay(2000);
    }
}
unsigned int reverse_bits(unsigned char b){
  //I use this function to flip the bit's of HEX construction of digits at function hexValues();
    unsigned char   r = 0;
    unsigned        byte_len = 8;

    while (byte_len--) {
        r = (r << 1) | (b & 1);
        b >>= 1;
    }
    return r;
}
void loop() {
  allOn();
  delay(1000);
  allOff();
  delay(1000);
  segmentTest();
  delay(800);

 while(1){
    allOff();
    delay(500);
    hexValues();
    delay(50);
    numbers0123();
    delay(1000);
    numbers4567();
    delay(1000);
    numbers89AB();
    delay(1000);
    numbersCDEF();
    delay(1000);
  }   
 }
