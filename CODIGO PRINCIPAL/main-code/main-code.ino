
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

//Configuração do LCD 16x2;
LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);


//Configuração dos Sensores de Umidade
#define pinoSensorSolo 15 //Usado para simular o sensor de umidade do solo;
#define DHTPIN 14  //Usado apenas como senor de temperatura do ambiente
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

//Configuração do Sensor de Distância;
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
//Cofiguração de pinos do sensor de distância
const int trigPin = 4;
const int echoPin = 2;

// Variáveis para a calibração (ajuste estes valores)
// 0% umidade = Valor do sensor lido quando TOTALMENTE SECO (no ar).
const int leituraSeco = 4095; 
// 100% umidade = Valor do sensor lido quando SUBMERSO em água.
const int leituraMolhado = 1600; 

const int limiteSeco = 50; // Porcentagem mínima de umidade
const int tempoRega = 10; // Tempo de rega em segundos

int umidadeSolo = 0; // Variavel para armazenar a umidade do solo
int volumeAgua;
int temperaturaAmbiente;

// Pino da Valvula solenoide e Led de Aviso
int pinoValvula = 26;
int pinoLedAviso = 27;

int medirUmidadeSolo(){
  int valorBruto = analogRead(pinoSensorSolo);

  int umidadePercentual = map(valorBruto, leituraMolhado, leituraSeco, 100, 0);

  if (umidadePercentual < 0) umidadePercentual = 0;
  if (umidadePercentual > 100) umidadePercentual = 100;

  Serial.print("Humidade do Solo: ");
  Serial.print(umidadePercentual);
  Serial.println(" %");
  
  return umidadePercentual;
}

int medirVolumeAgua(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  float porcentagem;
  long duracao = pulseIn(echoPin, HIGH); // Mede o tempo de resposta do ECHO  
  float distancia = (duracao * 0.0343) / 2;// Calcula a distância usando a velocidade do som (aproximadamente 343 m/s)

  if (distancia == 0){
    porcentagem = 0.00;
  } else {
    porcentagem = mapFloat(distancia, 0.0, 21.0, 100.0, 0.0);
  }

  porcentagem = constrain(porcentagem, 0.0, 100.0); // Garante que a porcentagem esteja entre 0 e 100

  Serial.print("Volume de Agua: ");
  Serial.print(porcentagem);
  Serial.println(" %");

  return porcentagem;
}

int medirTemperaturaAmbiente(){
  int t = dht.readTemperature();

  Serial.print("Temperatura Ambiente: ");
  Serial.print(t);
  Serial.println(" Celsius");

  return t;
}

void setup() {
  Serial.begin(115200);

  LCD.init();
  LCD.backlight();
  LCD.setCursor(0, 0);
  LCD.print("Sistema de Irri-");
  LCD.setCursor(0, 1);
  LCD.print("gacao Ligada");

  dht.begin();
  analogSetAttenuation(ADC_11db);

  pinMode(pinoValvula, OUTPUT);

  pinMode(pinoLedAviso, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 

  delay(4000);

}

void loop() {
  umidadeSolo = medirUmidadeSolo();
  volumeAgua = medirVolumeAgua();
  temperaturaAmbiente = medirTemperaturaAmbiente();

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("H:");
  LCD.print((umidadeSolo));
  LCD.print("% ");
  LCD.print("V:");
  LCD.print((volumeAgua));
  LCD.print("%");
  LCD.setCursor(0, 1);
  LCD.print("T:");
  LCD.print((temperaturaAmbiente));
  LCD.print(" Graus");

  Serial.println(umidadeSolo);
  Serial.println(volumeAgua);
  Serial.println(temperaturaAmbiente);

  /*if (volumeAgua <= 20){
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("Baixa Capac.");
    LCD.setCursor(0, 1);
    LCD.print("De Agua - ");
    LCD.print("V:");
    LCD.print((volumeAgua));
    LCD.print("%");
  }*/

  if (umidadeSolo < limiteSeco /*&& volumeAgua > 20*/) {
    LCD.clear();
    LCD.print("REGANDO");
    digitalWrite(pinoValvula, HIGH);
    digitalWrite(pinoLedAviso, HIGH);
    delay(tempoRega*1000);
    digitalWrite(pinoValvula, LOW);
    digitalWrite(pinoLedAviso, LOW);
  }

  delay(10000);
}
