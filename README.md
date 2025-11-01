# Projeto-Irrigação-Inteligente-Automática
Sistema de Irrigação em miniatura demonstrando como funcionaria uma irrigação de uma plantação com microcrontroladores.

Componentes Utilizados:
  ESP32;
  Mini Válvula Solenoide;
  Sensor de Umidade do Solo;
  Sensor sonoro/distância (para verificar a quantidade de água no reservatório);
  Sensor de temperatura;
  Relé (acionado pelo "pinoValvula" no código);
  Protoboard;

Funcionamento do sistema:
  A ideia é ter um sistema que saiba quando é necessário realizar a irrigação de plantações de grande até pequeno porte, através da umidade do solo. É estabelecido um limite de umidade baixa para a plantação no código, assim quando é atingido a baixa umidade do solo, o sistema irá distribuir a água do reservatório para a plantação. Ainda é verificado pelo sistema se a quantidade de água no reservatório é suficiente, tal limite pode ser estabelecido no código. O sensor de temperatura é utilizado apenas para demonstração da utilização de componentes que ajudam na análise do ambiente de plantação.
  A Mini válvula solenoide esta conctada a um relé. Esta válvula ao ser energizada fecha a passagem de água, e quando o sistema decide fazer a irrigação de água, a válvula não é energizada por um tempo previamente estabelecido, dependendo da área de irrigação, assim liberando a passagems de água. O relé ao receber o sinal do ESP32, fecha a passagem da porta 3,3 V para a válvula, libreando a passagem de água.


Versão do sistema feito no Wokwi: https://wokwi.com/projects/440668704348163073


