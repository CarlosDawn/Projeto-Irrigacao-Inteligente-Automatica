// Defina o pino GPIO do ESP32 que você conectou ao AOUT do sensor.
// Sugestão: GPIO34 ou GPIO35
const int pinoSensor = 34; 

// Variáveis para a calibração (ajuste estes valores)
// 0% umidade = Valor do sensor lido quando TOTALMENTE SECO (no ar).
const int leituraSeco = 4095; 
// 100% umidade = Valor do sensor lido quando SUBMERSO em água.
const int leituraMolhado = 1600; 

void setup() {
  Serial.begin(115200);
  // Configura a atenuação do ADC para 11dB (melhor faixa de 0V a 3.3V)
  analogSetAttenuation(ADC_11db); 
  // O ESP32 tem resolução de até 12 bits (0 a 4095), mas isso pode variar.
}

void loop() {
  // 1. Leitura Bruta
  int valorBruto = analogRead(pinoSensor);
  
  // 2. Conversão para Porcentagem (Mapeamento)
  // A leitura analógica é geralmente INVERSA (valor alto = seco, valor baixo = molhado).
  // A função map converte a faixa de valores brutos (Molhado a Seco)
  // para uma faixa de porcentagem de umidade (100% a 0%).
  int umidadePercentual = map(valorBruto, leituraMolhado, leituraSeco, 100, 0);

  // Garante que o valor fique entre 0 e 100
  if (umidadePercentual < 0) umidadePercentual = 0;
  if (umidadePercentual > 100) umidadePercentual = 100;
  
  // 3. Exibição
  Serial.print("Valor Bruto: ");
  Serial.print(valorBruto);
  Serial.print(" | Umidade: ");
  Serial.print(umidadePercentual);
  Serial.println(" %");

  delay(1000); // Aguarda 1 segundo
}