# Design Of Capacitance Sensor And Utilization Of Color Sensor As a Roasting Level Detection For Kawi’s Coffee Bean Using The Value of Frequencies And Color Sensor As a Base Value For Fuzzy Logic Based On Arduino

### firstly i'm curious about how roastery machine work. Most of it using temperatures and time to setting up the roasting level. When we talk about the essence of coffee it really important to consider every deatails on it process such as planting, harvesting, grinding, water content, the size of the beans, the colours etc. I want to dive deep into the beans after roasting process.

### Every Roasting level has different water content inside the bean that can affect the taste of coffee. From this perspective i want to increase the accuracy of roaster machine , i can put another variable to consider when we roast the beans. the capacitance, frequencies and the value of colour sensor of the beans can be fun to try.

### Pictures

![Capacitance Sensor] (https://www.facebook.com/photo?fbid=4441504129212703&set=pcb.4441504869212629)

![RC Oscillator] (https://www.facebook.com/photo?fbid=4441503979212718&set=pcb.4441504869212629)
(https://www.facebook.com/photo?fbid=4441503975879385&set=pcb.4441504869212629)

![System] (https://www.facebook.com/photo?fbid=4441503975879385&set=pcb.4441504869212629)
(https://www.facebook.com/photo?fbid=4441503995879383&set=pcb.4441504869212629)

### \***_ I'm using OLED to read the frequencies from RC Oscillator_**

```c++

if (FreqCount.available()) {                        //if the code if working
    float count = 213998;                   //create float var called count and populate it with current frequency count
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
```
