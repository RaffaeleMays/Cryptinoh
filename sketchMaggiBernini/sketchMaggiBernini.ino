#include <Servo.h>

// Settings
int servoPin = 7;
Servo myServo;
int molt = 7;
int giro = 0;
int inc = 0;
bool crypt = true;

// Carattere
char car;
int ascii;
int newCar = 0;

void setup() {
  Serial.begin(9600, SERIAL_8N1);
  myServo.attach(servoPin);
  myServo.write(180);
}

void loop() { 
  
  if(Serial.available() > 0){
    // C'è qualcosa da leggere
    car = Serial.read();
    ascii = (int)(car);
    
    if(car != '\n'){
      // Carattere diverso da line field
      if(ascii == 43){
        // carattere = +
        delay(5);
        inc = (((int)Serial.read()) - 48) * 10;
        inc += (((int)Serial.read()) - 48);
        crypt = true;
      }
      else if(ascii == 45){
        // carattere = -
        delay(5);
        inc = (((int)Serial.read()) - 48) * 10;
        inc += (((int)Serial.read()) - 48);
        crypt = false;
      }
      else if((int)car == 32){
          Serial.print(car);
          delay(2000);
      }
      else {
        
        if(crypt == false){
          newCar = ascii - inc;
          if(newCar < 65)
            newCar += 26;
            
          newCar -= 65;
        }
        else{
          newCar = ascii + inc;   
          if(newCar > 90){
            newCar -= 91;
          }
          else
            newCar -= 65;
        }
        // Scrittura del nuovo carattere
        car = (char) (newCar + 65);
        Serial.print(car);
        giro = 180 - (newCar * molt);

        // Aggiustamento angolazioni lettere
        if(newCar >= 1 && newCar <= 2)
          giro -= 2;
          
        if(newCar >= 3 && newCar <= 5)
          giro -= 4;

          if((newCar >= 6 && newCar <= 11) || newCar == 24)
          giro -= 6;

          if(newCar == 12 || (newCar >= 21 && newCar <= 23))
          giro -= 8;

          if((newCar >= 13 && newCar <= 14)||(newCar >= 19 && newCar <= 20))
          giro -= 9;

          if(newCar >= 15 && newCar <= 18)
          giro -= 10;

          if(newCar == 25)
          giro = 0;
                    
        myServo.write(giro);        
        delay(1000);
        
    }    
  } 
  }
}
