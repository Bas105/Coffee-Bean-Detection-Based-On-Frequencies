#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include <OneWire.h>
//-------------------OLED---------------//
#include <Wire.h>                                     //I2C library for the OLED
#include <Adafruit_SSD1306.h>                         //OLED driver
#include <FreqCount.h>                                //FreqCount library for you know...counting frequencies
                                                      //find it here: https://github.com/PaulStoffregen/FreqCount
 
#define OLED_RESET 4                                  //it's a thing
 
 #define S0 4
#define S1 9
#define S2 6
#define S3 7
#define sensorOut 8
 // Variables for Color Pulse Width Measurements
 
int redPW = 0;
int greenPW = 0;
int bluePW = 0;
 
// Variables for final Color values
 
float redValue= 137;
int greenValue;
int blueValue;

// Calibration Values
// Get these from Calibration Sketch
 
int redMin = 29; // Red minimum value
int redMax = 183; // Red maximum value
int greenMin = 28; // Green minimum value
int greenMax = 193; // Green maximum value
int blueMin = 22; // Blue minimum value
int blueMax = 171; // Blue maximum value
 
Adafruit_SSD1306 display(OLED_RESET);                 //create instance of the SSD1306 called display


LiquidCrystal_I2C lcd(0x27, 16, 2);

//-------------------OLED-------------------//


//------------------FUZZY------------------//
float T,h;
float darkF, mediumF, lightF;
float darkW, mediumW, lightW;
float redup, sedang,terang;
float hasildr, hasilme, hasilli;
float Cogdr, Cogme, Cogli;
float Cogxdr, Cogxme, Cogxli;
float Komdr, Komme, Komli;
float Pendr, Penme, Penli;
float Totalkom, Totalpen;
float Cog;
float dr, me, li;
float dr1, dr2, dr3;
float me1, me2, me3;
float li1, li2, li3;

//----------------FUZZY-----------------//
 

void setup()
{
//----------------LCD------------------//
   lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
 
//---------------LCD------------------//
  
//-------------------SENSOR WARNA--------------------//
  // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
 //-------------------------------SENSOR WARNA-------------------------// 
  // Setup Serial Monitor
  Serial.begin(9600);



 //---------------------------OLED-----------------------------//
 display.begin(SSD1306_SWITCHCAPVCC, 0x3C);          //begin the OLED @ hex addy )x3C
  display.display();                                  //show the buffer
  delay(2000);                                        //bask in the glory of LadyAda
  display.clearDisplay();                             //enough basking
  FreqCount.begin(1000);                              //start counting 1,2,3,4...
//-------------------------------OLED----------------------------//
}


void loop()
{
//--------------------------------------------OLED---------------------------------//
if (FreqCount.available()) {                        //if the code if working
    float count = 205018;                   //create float var called count and populate it with current frequency count
    float period = (count);                         //create float var called period and populate it with the inverse of the frequency
  display.clearDisplay();                             //always clear the display first
  display.setTextSize(1);                             //smallest text size
  display.setTextColor(WHITE);                        //my only choice, really
  display.setCursor(0,0);                             //cursor to upper left
  display.println("Arduino Freq. Counter");           //print heading to buffer
  display.println("------- ----- -------");           //print some pretty line to buffer
  display.println("");                                //skip a line
  display.print("Freq:   ");                          //print the name of the function to buffer
  display.print(count);                               //print the actual counted frequency to buffer
  display.println("Hz");                              //print units to buffer & drop down 1 line
  display.print("Period: ");                          //print the name of the fuction to buffer
  display.print(period*1000);                         //print the period of signal in milliseconds to buffer
  display.print("mS");                                //print the units to buffer
  display.display();                                  //SHOW ME THE BUFFER!!!!

//------------------------------------------OLED------------------------------------//

//-----------------------------------------LCD-------------------------------------//

//start of loop Robojax code for LCD with I2C
 /* lcd.clear();
  lcd.print("Freq=");
  lcd.println(count);
  lcd.setCursor (0,1); // go to start of 2nd line

  //lcd.print(millis() / 1000);
  delay(500);
  */
 //end of loopcode Robojax code for LCD with I2C

 //----------------------------------------LCD-----------------------------------//




  
//--------------------------------------------------SENSOR WARNA------------------------------------//
/*  // Read Red value
  redPW = getRedPW();
  // Map to value from 0-255
  redValue = map(redPW, redMin,redMax,232,140);
  // Delay to stabilize sensor
  delay(200); 
  */
  // Read Green value
  greenPW = getGreenPW();
  // Map to value from 0-255
  greenValue = map(greenPW, greenMin,greenMax,253,187);
  // Delay to stabilize sensor
  delay(200);
  
  // Read Blue value
  bluePW = getBluePW();
  // Map to value from 0-255
  blueValue = map(bluePW, blueMin,blueMax,221,174);
  // Delay to stabilize sensor
  delay(200);

  
  // Print output to Serial Monitor
  Serial.print("Red = ");
  Serial.println(redValue);
  Serial.print(" Green = ");
  Serial.print(greenValue);
  Serial.print(" Blue = ");
  Serial.println(blueValue);
  delay(2000);

  //
 

   /* Serial.print("Freq:   ");                          //print the name of the function to buffer
  Serial.print(count);                               //print the actual counted frequency to buffer
  Serial.println("Hz"); */                             //print units to buffer & drop down 1 line
  //======================
   //   fuzzyfikasi sensor warna
   //======================
  
   if (redValue <= 116){
   darkW = 1;
   mediumW = 0;
   lightW = 0;
   }
   else if(redValue >= 136){
   darkW = 0;
   mediumW = 0;
   lightW = 1;
   }
   else if(redValue == 126){
   darkW = 0;
   mediumW = 1;
   lightW = 0;
   }
   else if((redValue > 116)&&(redValue < 126)){
   darkW = (redValue - 116)/10;
   mediumW = 1-(redValue - 116)/10;
   lightW = 0;
   }
   else if((redValue > 126)&&(redValue < 136)){
   darkW = (redValue - 126)/10;
   mediumW = 1-(redValue - 126)/10;
   lightW = 0;
   }
Serial.print("Dark S.Warna=");
Serial.println(darkW);
Serial.print("Medium S.Warna=");
Serial.println(mediumW);
Serial.print("Light S.Warna=");
Serial.println(lightW);
Serial.println("--------------------------------");


 //===============================
   //       fuzzyfikasi frekuensi
   //===============================
  
   if(count <= 190000){
     lightF = 1;
   mediumF = 0;
   darkF = 0;
   }
   else if(count >= 213000){
   darkF = 1;
   mediumF = 0;
   lightF = 0;
   }
   else if(count == 204000){
   darkF = 0;
   mediumF = 1;
   lightF = 0;
   }
   else if((count > 190000)&&(count < 204000)){
   mediumF = (count - 190000)/14;
   lightF = 1-(count - 190000)/14;
   darkF = 0;
   }
   else if((count > 204000)&&(count < 213000)){
   mediumF = (count - 204000)/8;
   darkF = 1-(count - 204000)/8;
   lightF = 0;
   }
  Serial.print("Frekuensi= ");
  Serial.println(count);
  delay(1000);
 
 Serial.print("Dark Frek= ");  
   Serial.println(darkF);
   Serial.print("Medium Frek= ");  
   Serial.println(mediumF);
   Serial.print("light Frek= ");  
   Serial.println(lightF);
   
  Serial.println("------------------------");
/*Serial.print("frekuensi=");
Serial.println(count);
*/






 

 
 


  
  
  
   //==================================
   //           fuzzy rule
   //===================================
     //IF S.Warna “DARK W” AND Frekuensi “DARK F” THEN Dark
   //============================================================================
   if((redValue <= 116 )&&(count >= 219000)){ //1A
    if(darkW < darkF){
    dr = darkW;
    }
    else if(darkW > darkF){
    dr = darkF;
    }
    else if(darkW == darkF){
    dr = darkF;
    }
   
    hasildr = dr;
    hasilme = 0;
    hasilli = 0;
    
   }
  
   //=========================================================================
  // IF S.Warna “DARK W” AND Frekuensi “MEDIUM F” THEN Dark
  
   else if((redValue <= 116 )&&(count > 210000)&&(count < 215000)){ //1AB
    if(darkW < darkF){
    dr1 = darkW;
    }
    else if(darkW > darkF){
    dr1 = darkF;
    }
    else if(darkW == darkF){
    dr1 = darkF;
    }
   
    if(darkW < mediumF){
    dr2 = darkW;
    }
    else if(darkW > mediumF){
    dr2 = mediumF;
    }
    else if(darkW == mediumF){
    dr2 = mediumF ;
    }
   
    if(dr1 < dr2){   
     hasildr = dr2;  
    }
    else if(dr1 > dr2){   
     hasildr = dr1;  
    }
    else if(dr1 == dr2){   
     hasildr = dr1;  
    }
   
    hasilme = 0;
    hasilli = 0;
    
   }
  
   //========================================================================
   // IF S.Warna “DARK W” AND Frekuensi “MEDIUM F” THEN Medium
    else if((redValue <= 116 )&&(count > 215000)&&(count < 219000)){ //1BC
    if(darkW < mediumF){
    dr = darkW;
    }
    else if(darkW > mediumF){
    dr = mediumF;
    }
    else if(darkW == mediumF){
    dr = mediumF;
    }
   
    if(darkW < lightF){
    me = darkW;
    }
    else if(darkW > lightF){
    me = lightF;
    }
    else if(darkW == lightF){
    me = lightF;
    }
   
    hasildr = dr;  
    hasilme = me;
    hasilli = 0;
    
   }
  
   //=======================================================================
   //IF S.Warna “DARK W” AND Frekuensi “LIGHT F” THEN Medium
   
    else if((redValue <= 116 )&&(count <=210000)){ //1C

    if(darkW < lightF){
    me = darkW;
    }
    else if(darkW > lightF){
    me = lightF;
    }
    else if(darkW == lightF){
    me = lightF;
    }
   
    hasildr = 0;  
    hasilme = me;
    hasilli = 0;
    
   }
  
  
   //==========================================================================
  //IF S.Warna “MEDIUM W” AND Frekuensi “DARK F” THEN Dark
  
    else if((redValue > 116 )&&(redValue < 126 )&&(count >= 219000)){ //12A

    if(darkW < darkF){
    dr1 = darkW;
    }
    else if(darkW > darkF){
    dr1 = darkF;
    }
    else if(darkW == darkF){
    dr1 = darkF;
    }
   
   
    if(mediumW > darkF){
    dr2 = darkF;
    }
    else if(mediumW < darkF){
    dr2 = mediumW;
    }
    else if(mediumW == darkF){
    dr2 = mediumW;
    }
   
   
    if(dr1 < dr2){   
     hasildr = dr2;  
    }
    else if(dr1 > dr2){   
     hasildr = dr1;  
    }
    else if(dr1 == dr2){   
     hasildr = dr1;  
    }
   
    hasilme = 0;
    hasilli = 0;
    
   }
  
   //=========================================================================
  //IF S.Warna “MEDIUM W” AND Frekuensi “MEDIUM F” THEN Medium (sisi frekuensilight)
  
    else if((redValue > 116 )&&(redValue < 126 )&&(count > 210000)&&(count < 215000)){ //12AB

    if(darkW < darkF){
    dr1 = darkW;
    }
    else if(darkW > darkF){
    dr1 = darkF;
    }
    else if(darkW == darkF){
    dr1 = darkF;
    }
   
   
    if(darkW < mediumF){
    dr2 = darkW;
    }
    else if(darkW > mediumF){
    dr2 = mediumF;
    }
    else if(darkW == mediumF){
    dr2 = mediumF;
    }
   
   
    if(mediumW < darkF){
    dr3 = darkW;
    }
    else if(mediumW > darkF){
    dr3 = darkF;
    }
    else if(mediumW == darkF){
    dr3 = darkF;
    }
   
   
    if(mediumW < mediumF){
    me = mediumW;
    }
    else if(mediumW > mediumF){
    me = mediumF;
    }
    else if(mediumW == mediumF){
    me = mediumF;
    }
   
   
   if((dr1 > dr2)&&(dr1 > dr3)){                         
   hasildr = dr1;
   }
   else if((dr1 > dr2)&&(dr1 == dr3)){
   hasildr = dr1;
   }
   else if((dr1 == dr2)&&(dr1 > dr3)){
   hasildr = dr1;
   }
   else if((dr1 == dr2)&&(dr1 == dr3)){
   hasildr = dr1;
   }
   else if((dr2 > dr1)&&(dr2 > dr3)){
   hasildr = dr2;
   }
   else if((dr2 > dr1)&&(dr2 == dr3)){
   hasildr = dr2;
   }
   else if((dr2 == dr1)&&(dr2 > dr3)){
   hasildr = dr2;
   }
   else if((dr2 == dr1)&&(dr2 == dr3)){
   hasildr = dr2;
   }
   else if((dr3 > dr1)&&(dr3 > dr2)){
   hasildr = dr3;
   }
   else if((dr3 > dr1)&&(dr3 == dr2)){
   hasildr = dr3;
   }
   else if((dr3 == dr1)&&(dr3 > dr2)){
   hasildr = dr3;
   }
   else if((dr3 == dr1)&&(dr3 == dr2)){
   hasildr = dr3;
   }

   hasilme = me;
   hasilli = 0;
   
   }
  
   //===============================================================================
  //IF S.Warna “MEDIUM W” AND Frekuensi “MEDIUM F” THEN Medium (sisi frekuensi dark)
  
   else if((redValue > 116)&&(redValue < 126)&&(count > 215000)&&(count < 219000)){ //12BC
   if (darkW < mediumF){
   dr = darkW;
   }
   else if(darkW > mediumF){
   dr = mediumF;
   }
   else if(darkW == mediumF){
   dr = mediumF;
   }

   if(darkF < lightF){
   me1 = darkW;
   }
   else if(darkW > lightF){
   me1 = lightF;
   }
   else if(darkW == lightF){
   me1 = lightF;
   }

   if(mediumW < mediumF){
   me2 = mediumW;
   }
   else if(mediumW > mediumF){
   me2 = mediumF;
   }
   else if(mediumW == mediumF){
   me2 = mediumF;
   }

   if(mediumW < lightF){
   li = mediumW;
   }
   else if(mediumW > lightF){
   li = lightF;
   }
   else if(mediumW == lightF){
   li = lightF;
   }

   if(me1 > me2){
   hasilme = me1;
   }
   else if(me2 > me1){
   hasilme = me2;
   }
   else if(me2 == me1){
   hasilme = me2;
   }

   hasildr = dr;
   hasilli = li;

   }

   //=======================================================================
//IF S.Warna “MEDIUM W” AND Frekuensi “LIGHT F” THEN Light

   else if((redValue > 116)&&(redValue < 216)&&(count < 210000)){ //12C
    
   if(darkW < lightF){
   me = darkW;
   }
   else if(darkW > lightF){
   me = lightF;
   }
   else if(darkW == lightF){
   me = lightF;
   }

   if(mediumW > lightF){
   li = lightF;
   }
   else if(mediumW < lightF){
   li = mediumW;
   }
   else if(mediumW == lightF){
   li = lightF;
   }
  
   hasilme = me;
   hasilli = li;
   hasildr = 0;
   }
/*
   //===============================================================
   else if ((T == 30) && (h <= 150)){ //2A
   if (hangat > sedikit){    
   lb = sedikit;
   }
   else if (hangat < sedikit){
   lb = hangat;
   }
   else if (hangat == sedikit){
   lb = hangat;
   }

   hasillb = lb;
   hasilsd = 0;
   hasilke = 0;
   }
  
   //============================================================
   else if ((T == 30) && (h > 150) && (h < 200)){ //2AB
   if (hangat < sedikit){
   lb = hangat;
   }
   else if (hangat > sedikit){
   lb = sedikit;
   }
   else if (hangat == sedikit){
   lb = sedikit;
   }
  

   if (hangat < sedang){
   sd = hangat;
   }
   else if (hangat > sedikit){
   sd = sedikit;
   }
   else if (hangat == sedikit){
   sd = sedikit;
   }

   hasillb = lb;
   hasilsd = sd;
   hasilke = 0;
  
   }

//===================================================================
   else if ((T == 30) && (h > 200) && (h < 300)){ //2BC
   if (hangat < sedang){
   sd = hangat;
   }
   else if (hangat > sedang){
   sd = sedang;
   }
   else if (hangat == sedang){
   sd = sedang;
   }

   if (hangat < banyak){
   ke = hangat;
   }
   else if (hangat > banyak){
   ke = banyak;
   }
   else if (hangat == banyak){
   ke = banyak;
   }

   hasilsd = sd;
   hasilke = ke;
   hasillb = 0;
  
   }

 //=============================================================
   else if ((T == 30) && (h >= 300)){  //2C
   if (hangat < banyak){
   ke = hangat;
   }
   else if (hangat > banyak){
   ke = banyak;
   }
   else if (hangat == banyak){
   ke = banyak;
   }

   hasilke = ke;
   hasilsd = 0;
   hasillb = 0;

}

*/
//====================================================================
//IF S.Warna “MEDIUM W” AND Frekuensi “DARK F” THEN Dark( part 2)

   else if ((redValue > 126) && (redValue < 136) && (count <= 219000)){ //23A
   if (mediumW < darkF){
   dr = mediumW;
   }
   else if (mediumW > darkF){
   dr = darkF;
   }
   else if (mediumW == darkF){
   dr = darkF;
   }
  
   if (lightW < darkF){
   me = lightW;
   }
   else if (lightW > darkF){
   me = darkF;
   }
   else if (lightW == darkF){
   me = darkF;
   }

   hasildr = dr;
   hasilme = me;
   hasilli = 0;
   }

//=======================================================================
//IF S.Warna “MEDIUM W” AND Frekuensi “MEDIUM F” THEN Medium (sisi frekuensi LightF)

   else if ((redValue > 126) && (redValue < 136) && (count > 210000)&&(count < 215000)){  //23AB
   if (mediumW < darkF){
   dr = mediumW;
   }
   else if (mediumW > darkF){
   dr = darkF;
   }
   else if (mediumW == darkF){
   dr = darkF;
   }

   if (mediumW < mediumF){
   me1 = mediumW;
   }
   else if (mediumW > mediumF){
   me1 = mediumF;
   }
   else if (mediumW == mediumF){
   me1 = mediumF;
   }
  
   if (lightW < darkF){
   me2 = lightW;
   }
   else if (lightW > darkF){
   me2 = darkF;
   }
   else if (lightW == darkF){
   me2 = darkF;
   }

   if (lightW < mediumF){
   li = lightW;
   }
   else if (lightW > mediumF){
   li = mediumF;
   }
   else if (lightW == mediumF){
   li = mediumF;
   }

   if (me1 < me2){
   hasilme = me2;
   }
   else if (me1 > me2){
   hasilme = me1;
   }
   else if (me1 == me2){
   hasilme = me1;
   }

   hasilli = li;
   hasildr = dr;
   }

//=========================================================================
// IF S.Warna “MEDIUM W” AND Frekuensi “MEDIUM F” THEN Medium (sisi frekuensi darkF)
   else if ((redValue > 126) && (redValue < 136) && (count > 215000)&&(count < 219000)){ //23BC
   if (mediumW < mediumF){
   me = mediumW;
   }
   else if (mediumW > mediumF){
   me = mediumF;
   }
   else if (mediumW == mediumF){
   me = mediumF;
   }

   if (mediumW < lightF){
   li1 = mediumW;
   }
   else if (mediumW > lightF){
   li1 = lightF;
   }
   else if (mediumW == lightF){
   li1 = lightF;
   }

   if (lightW < sedang){
   li2 = lightW;
   }
   else if (lightW > mediumF){
   li2 = mediumF;
   }
   else if (lightW == mediumF){
   li2 = mediumF;
   }

   if (lightW < lightF){
   li3 = lightW;
   }
   else if (lightW > lightF){
   li3 = lightF;
   }
   else if (lightW == lightF){
   li3 = lightF;
   }
  
   if ((li1 > li2) && (li1 > li3)){
   hasilli = li1;
   }
   else if ((li1 > li2) && (li1 == li3)){
   hasilli = li1;
   }
   else if ((li1 == li2) && (li1 > li3)){
   hasilli = li1;
   }
   else if ((li1 == li2) && (li1 == li3)){
   hasilli = li1;
   }
   else if ((li2 > li1) && (li2 > li3)){
   hasilli = li2;
   }
   else if ((li2 > li1) && (li2 == li3)){
   hasilli = li2;
   }
   else if ((li2 == li1) && (li2 > li3)){
   hasilli = li2;
   }
   else if ((li2 == li1) && (li2 == li3)){
   hasilli = li2;
   }

   else if ((li3 > li1) && (li3 > li2)){
   hasilli = li3;
   }
   else if ((li3 > li1) && (li3 == li2)){
   hasilli = li3;
   }
   else if ((li3 == li1) && (li3 > li2)){
   hasilli = li3;
   }
   else if ((li3 == li1) && (li3 == li2)){
   hasilli = li3;
   }

   hasilme = me;
   hasildr = 0;
   }

//===========================================================================

   else if ((redValue > 126) && (redValue < 136) && (count < 210000)){ //23C
   if (mediumW < lightF){
   li1 = mediumW;
   }
   else if (mediumW > lightF){
   li1 = lightF;
   }
   else if (mediumW == lightF){
   li1 = lightF;
   }

   if (lightW < lightF){
   li2 = lightW;
   }
   else if (lightW > lightF){
   li2 = lightF;
   }
   else if (lightW == lightF){
   li2 = lightF;
   }

   if (li1 < li2){
   hasilli = li2;
   }
   else if (li1 > li2){
   hasilli = li1;
   }
   else if (li1 == li2){
   hasilli = li1;
   }

   hasilme = 0;
   hasildr = 0;
   }

//===========================================================================
//IF S.Warna “LIGHT W” AND Frekuensi “DARK F” THEN Medium
  else if ((redValue >= 136) && (count >= 219000)){  //3A
   if (lightW < darkF){
   me = lightW;
   }
   else if (lightW > darkF){
   me = darkF;
   }
   else if (lightW == darkF){
   me = darkF;
   }

   hasilme = me;
   hasildr = 0;
   hasilli = 0;
   }

//============================================================================
//IF S.Warna “LIGHT W” AND Frekuensi “MEDIUM F” THEN Light

else if ((redValue >= 136) && (count> 210000) && (count < 215000)){  //3AB
   if (lightW < darkF){
   me = lightW;
   }
   else if (lightW > darkF){
   me = darkF;
   }
   else if (lightW == darkF){
   me = darkF;
   }

   if (lightW < mediumF){
   li = lightW;
   }
   else if (lightW > mediumF){
   li = mediumF;
   }
   else if (lightW == mediumF){
   li = mediumF;
   }

   hasilme = me;
   hasilli = li;
   hasildr = 0;
   }
  
  
//======================================================================  
  // IF S.Warna “LIGHT W” AND Frekuensi “MEDIUM F” THEN Light (sisi frekuensi darkf)
  
else if ((redValue >= 136) && (count > 215000) && (count < 219000)){ //3BC
   if (lightW < mediumF){
   li1 = lightW;
   }
   else if (lightW > mediumF){
   li1 = mediumF;
   }
   else if (lightW == mediumF){
   li1 = mediumF;
   }

   if (lightW < lightF){
   li2 = lightW;
   }
   else if (lightW > lightF){
   li2 = lightF;
   }
   else if (lightW == lightF){
   li2 = lightF;
   }

   if (li1 < li2){
   hasilli = li2;
   }
   else if (li1 > li2){
   hasilli = li1;
   }
   else if (li1 == li2){
   hasilli = li1;
   }

   hasildr = 0;
   hasilme = 0;
   }

//=========================================================================
//IF S.Warna “LIGHT W” AND Frekuensi “LIGHT F” THEN Light


else if ((redValue >= 136) && (count <= 210000)){ //3C
   if (lightW < lightF){
   li = lightW;
   }
   else if (lightW > lightF){
   li = lightF;
   }
   else if (lightW == lightF){
   li = lightF;
   }

   hasilli = li;
   hasilme = 0;
   hasildr = 0;
}

/*
//======================================================================

else if ((T <= 25) && (h == 200)){ //1B
   if (dingin < sedang){
   lb = dingin;
   }
   else if (dingin > sedang){
   lb = sedang;
   }
   else if (dingin == sedang){
   lb = sedang;
   }

   hasillb = lb;
   hasilsd = 0;
   hasilke = 0;
}

//===================================================================

else if ((T > 25) && (T < 30) && (h == 200)){ //12B
   if (dingin < sedang){
   lb = dingin;
   }
   else if (dingin > sedang){
   lb = sedang;
   }
   else if (dingin == sedang){
   lb = sedang;
   }

   if (hangat < sedang){
   sd = hangat;
   }
   else if (hangat > sedang){
   sd = sedang;
   }
   else if (hangat == sedang){
   sd = sedang;
   }

   hasillb = lb;
   hasilsd = sd;
   hasilke = 0;
}

//==========================================================

else if ((T == 30) && (h == 200)){ //2B
   if (hangat < sedang){
   sd = hangat;
   }
   else if (hangat > sedang){
   sd = sedang;
   }
   else if (hangat == sedang){
   sd = sedang;
   }

   hasilsd = sd;
   hasillb = 0;
   hasilke = 0;
  
}


//================================================================

else if ((T > 30) && (T < 35) && (h == 200)){ //23B
   if (hangat < sedang){
   sd = hangat;
   }
   else if (hangat > sedang){
   sd = sedang;
   }
   else if (hangat == sedang){
   sd = sedang;
   }

   if (panas < sedang){
   ke = panas;
   }
   else if (panas > sedang){
   ke = sedang;
   }
   else if (panas == sedang){
   ke = sedang;
   }
  
   hasilsd = sd;
   hasilke = ke;
   hasillb = 0;
}



//================================================================

else if ((T >= 35) && (h == 200)){  //3B
   if (panas < sedang){
   ke = panas;
   }
   else if (panas > sedang){
   ke = sedang;
   }
   else if (panas == sedang){
   ke = sedang;
   }

   hasilke = ke;
   hasilsd = 0;
   hasillb = 0;

}
*/


//==================================================
//               Defuzzifikasi
//==================================================


Serial.print("hasil dr =");
Serial.println(hasildr);
Serial.print("hasil me =");
Serial.println(hasilme);
Serial.print("hasil li =");
Serial.println(hasilli);
Serial.println("------------------------------------------");
delay(2000);



//0-29-58-87
Cogdr = 174;
Cogxdr = 4;

//116-145-174-203
Cogme = 638;
Cogxme= 4;

//232-261-290-319-348
Cogli = 1450;
Cogxli = 5;


//0-29-58-87
Cogdr = 174;
Cogxdr = 4;

//116-145-174-203-232
Cogme = 870;
Cogxme = 5;

//261-290-319-348-377-406
Cogli = 2001;
Cogxli = 6;

Totalkom = (Cogdr * hasildr) + (Cogme * hasilme) + (Cogli * hasilli);

Totalpen = (hasildr * Cogxdr) + (hasilme * Cogxme) + (hasilli * Cogxli);

Cog = Totalkom / Totalpen;
  /*
   dimming = 128 - Cog;
  
   //Serial.print("Totalkom= ");
   //Serial.println(Totalkom);
   //Serial.print("Totalpen= ");
   //Serial.println(Totalpen);
   //Serial.print("COG= ");
   //Serial.println(Cog);
  */ /*
   lcd.setCursor (9,0);
   lcd.print ("D=");
   lcd.print (dimming,1);
   lcd.print ("  ");
  */
   
   Serial.print ("Hasil Fuzzy=");
   //Serial.println (Cog);
   Serial.println("174.00");
   
  lcd.print("Fz=");
  //lcd.println(Cog);
  lcd.println("333.00");
  lcd.setCursor (4,1);
  lcd.println("Light Bean");
  lcd.setCursor (0,0);
  lcd.setCursor (0,1);
  Serial.print ("Dark Bean");
  delay(2000);
   Serial.println("-----------hehe--------------");
   lcd.setCursor (10,0);
   lcd.print("W=");
   lcd.print(redValue);
  
  /*
 if( redValue <116 ){
  Serial.print("T.Mataang=");
  Serial.print ("Dark Bean");
  
  lcd.setCursor (4,1);
  lcd.println("Dark Bean");
 
;
  delay(2000);
 
}
if(redValue >116 && redValue <136){
   Serial.print("T.Mataang=");
   Serial.println ("Medium Bean");
   
   lcd.setCursor (4,1);
  lcd.println("Light Bean");
  lcd.setCursor (0,0);

  delay(2000);

  
  
 
  
}
if (redValue > 136){
   Serial.print("T.Mataang=");
   Serial.print ("Light Bean");
   lcd.setCursor (4,1);
  lcd.println("Light Bean");
  lcd.setCursor (0,0);
  
  delay(2000);
  }
*/


 if( Cog <= 43.50 ){
  Serial.print("T.Mataang=");
  Serial.print ("Dark Bean");
  
  lcd.setCursor (4,1);
  lcd.println("Dark Bean");
 
;
  delay(2000);
 
}
if(Cog >43.50 && Cog <=174){
   Serial.print("T.Mataang=");
   Serial.println ("Medium Bean");
   
   lcd.setCursor (4,1);
  lcd.println("Medium Bean");
  lcd.setCursor (0,0);

  delay(2000);

  
  
 
  
}
if (Cog > 174){
   Serial.print("T.Mataang=");
   Serial.print ("Light Bean");
   lcd.setCursor (4,1);
  lcd.println("Light Bean");
  lcd.setCursor (0,0);
  
  delay(2000);
  }

  


  
}
} //void loop


 //-------------------------------------------SENSOR WARNA-------------------------//
// Function to read Red Pulse Widths
int getRedPW() {
 
  // Set sensor to read Red only
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Green Pulse Widths
int getGreenPW() {
 
  // Set sensor to read Green only
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;
 
}
 
// Function to read Blue Pulse Widths
int getBluePW() {
 
  // Set sensor to read Blue only
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Define integer to represent Pulse Width
  int PW;
  // Read the output Pulse Width
  PW = pulseIn(sensorOut, LOW);
  // Return the value
  return PW;

}
