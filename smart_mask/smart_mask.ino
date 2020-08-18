#include <Adafruit_DotStar.h>
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define NUMPIXELS 30 // Number of LEDs in strip


Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_DotStar strip(NUMPIXELS, DOTSTAR_BRG);

void setup() {

  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin();  
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
}



void loop() {
  float temp = mlx.readObjectTempC() + 5;
  uint32_t color = 0xFF0000;
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  delay(500);
  Serial.println();

  if(temp < 38 && temp >= 31){
    normalTemp();
    } else if(temp >= 38) {
        abnormalTemp();
    }
}

void normalTemp(){
  uint32_t color = 0xFF0000;
  for(int i = 0; i < 31; i++){
      strip.setPixelColor(i, color); 
      strip.show();
    }
      delay(2000);
      turnOff();
}

void abnormalTemp(){
  uint32_t color = 0x00FF00;
  for(int i = 0; i < 31; i++){
      strip.setPixelColor(i, color); 
      strip.show();
    }
      //digitalWrite(buzzer,HIGH);
      tone(A0, 100, 500);
      delay(2000);
      //digitalWrite(buzzer,LOW);
      turnOff();
}

void turnOff(){
  uint32_t color = 0x000000;
  for(int i = 0; i < 31; i++){
      strip.setPixelColor(i, color); 
      strip.show();
    }
}
