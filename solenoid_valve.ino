#include <SPI.h>

int solenoidPin = 8;                    //SOLENOID VALVE PIN
int potentiometerPin = A0;              // POTENTOMETER PIN
float  freq= 28;                        // INITIAL FREQ
float  period = ((1/freq)*1000);        // PERIOD in ms
float  dutyCyclePerc= 50;               // Initialize Duty Cycle at 50%
char junk = ' ';
float newFreq;


void setup() {
  delay(1000);                          // 1 sec before start
  Serial.begin(9600);                   // inizializzazione porta seriale
  pinMode(solenoidPin, OUTPUT);         //Sets the pin as an output
  Serial.println("setup done");

}


void loop() {
  float value = analogRead(potentiometerPin);   // potentiometer value from 0 to 1023
  int dutyCyclePerc = map(value, 0, 1023, 0, 100); //Convert to percentage
    

  
  
    // READING FREQUENCY VALUE FROM SERIAL
    if (Serial.available())  {
      newFreq = Serial.parseFloat();        
      Serial.print("Frequency = "); 
      Serial.println(newFreq, DEC);
      while (Serial.available()>0)  // .parseFloat() can leave non-numeric characters
      { junk = Serial.read() ; }      // clear the keyboard buffer
       
      freq= newFreq;
      period = ((1/freq)*1000);        // PERIOD in ms
      newFreq=0;
    }  
    
    
      
//    if(Serial.available()){
//  while(Serial.available())
//    {
//      char inChar = (char)Serial.read(); //read the input
//      inputString += inChar;        //make a string of the characters coming on serial
//    }
//    Serial.println(inputString);
//    while (Serial.available() > 0)  
//    { junk = Serial.read() ; }      // clear the serial buffer
//    if(inputString == "a"){         //in case of 'a' turn the LED on
//      Serial.println("è stato inviato a");
//      digitalWrite(13, HIGH);  
//    }else if(inputString == "b"){   //incase of 'b' turn the LED off
//      Serial.println("è stato inviato b");
//      digitalWrite(13, LOW);
//    }
//    inputString = "";
//  }
    
    
  float dutyCycleMs = (dutyCyclePerc*period)/100;
    
  digitalWrite(solenoidPin, HIGH);              //Switch Solenoid ON
  delay(int(dutyCycleMs)); 
              

  digitalWrite(solenoidPin, LOW);  
  delay(period-int(dutyCycleMs));      //Switch Solenoid OFF
         
   

  
  Serial.println("Duty cycle %:");
  Serial.println(dutyCyclePerc);
  Serial.println("Duty cycle in ms:");
  Serial.println(int(dutyCycleMs));
}
