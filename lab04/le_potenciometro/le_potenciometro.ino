const uint8_t analog_pin = A0;

void setup() {
  //Abre a porta serial com 115200 bps
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  //Leitura do sinal lido pelo adc
  uint16_t raw_value = analogRead(analog_pin);

  //Envia o valor lido no potênciometro para a porta serial
  Serial.println(raw_value);

  //Pequeno delay para limitar a velocidade de transmissão
  delay(10);
}
