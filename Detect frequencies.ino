#include <Wire.h>                                     //I2C library for the OLED
#include <Adafruit_SSD1306.h>                         //OLED driver
#include <FreqCount.h>                                //FreqCount library for you know...counting frequencies
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>                                                      //find it here: https://github.com/PaulStoffregen/FreqCount
 
#define OLED_RESET 4                                  //it's a thing
//Sensor warna
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Variables for Color Pulse Width Measurements

int redPW = 0;
int greenPW = 0;
int bluePW = 0;
//Sensor warna 
 
 
 
Adafruit_SSD1306 display(OLED_RESET);                 //create instance of the SSD1306 called display

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2); 
 
 
void setup()   {                
 // Set S0 - S3 as outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Set Sensor output as input
  pinMode(sensorOut, INPUT);
  
  // Set Pulse Width scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Setup Serial Monitor
  Serial.begin(9600);


  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);          //begin the OLED @ hex addy )x3C
  display.display();                                  //show the buffer
  delay(2000);                                        //bask in the glory of LadyAda
  display.clearDisplay();                             //enough basking
  FreqCount.begin(1000);                              //start counting 1,2,3,4...

 // Robojax code for LCD with I2C
  // initialize the LCD, 
  lcd.begin();
 
  // Turn on the blacklight and print a message.
  lcd.backlight();
  // Robojax code for LCD with I2C

}
 
 
void loop() {
 
 
  if (FreqCount.available()) {                        //if the code if working
    float count = FreqCount.read();                   //create float var called count and populate it with current frequency count
    float period = (1/count);                         //create float var called period and populate it with the inverse of the frequency
  display.clearDisplay();                             //always clear the display first
  display.setTextSize(1);                             //smallest text size
  display.setTextColor(WHITE);                        //my only choice, really
  display.setCursor(0,0);                             //cursor to upper left
             //print heading to buffer
  display.println("------- ----- -------");           //print some pretty line to buffer
  display.println("");                                //skip a line
  display.print("Freq:   ");                          //print the name of the function to buffer
  display.print(count);                               //print the actual counted frequency to buffer
  display.println("Hz");                              //print units to buffer & drop down 1 line
                        //print the period of signal in milliseconds to buffer
                                //print the units to buffer
  display.display();                                  //SHOW ME THE BUFFER!!!!
  


}}
