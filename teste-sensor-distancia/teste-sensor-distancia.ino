
#include <LiquidCrystal_I2C.h>

#include <NewPing.h>

//Configuração do LCD 16x2;
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);

const int trigPin = 4;
const int echoPin = 2;
float leitura;
NewPing sonar(trigPin, echoPin); 

void setup() {
  Serial.begin(115200);

  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Sistema de Irri-");
  LCD.setCursor(0, 1);
  LCD.print("gacao Ligada");

}

void loop() {

  leitura = sonar.ping_cm();
  Serial.print("Distância: ");
  Serial.print(leitura);
  Serial.println(" cm");

  delay(2000);

}
