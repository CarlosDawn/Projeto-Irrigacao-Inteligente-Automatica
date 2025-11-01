# Projeto-Irrigação-Inteligente-Automática
Sistema de Irrigação em miniatura demonstrando como funcionaria uma irrigação de uma plantação com microcrontroladores.

<strong>Componentes Utilizados:</strong>
<ul>
  <li>ESP32;</li>
  <li>Mini Válvula Solenoide;</li>
  <li>Sensor de Umidade do Solo;</li>
  <li>Sensor sonoro/distância (para verificar a quantidade de água no reservatório);</li>
  <li>Sensor de temperatura;</li>
  <li>Relé (acionado pelo "pinoValvula" no código);</li>
  <li>Protoboard;</li>
</ul>

<strong>Funcionamento do sistema:</strong>
  <p>A ideia é ter um sistema que saiba quando é necessário realizar a irrigação de plantações de grande até pequeno porte, através da umidade do solo. É estabelecido um limite de umidade baixa para a plantação no código, assim quando é atingido a baixa umidade do solo, o sistema irá distribuir a água do reservatório para a plantação. Ainda é verificado pelo sistema se a quantidade de água no reservatório é suficiente, tal limite pode ser estabelecido no código. O sensor de temperatura é utilizado apenas para demonstração da utilização de componentes que ajudam na análise do ambiente de plantação.</p>
  <p></p>A Mini válvula solenoide esta conctada a um relé. Esta válvula ao ser energizada fecha a passagem de água, e quando o sistema decide fazer a irrigação de água, a válvula não é energizada por um tempo previamente estabelecido, dependendo da área de irrigação, assim liberando a passagems de água. O relé ao receber o sinal do ESP32, fecha a passagem da porta 3,3 V para a válvula, libreando a passagem de água.</p>


Versão do sistema feito no Wokwi, <a href="https://wokwi.com/projects/440668704348163073" target="_blank">Link</a>


