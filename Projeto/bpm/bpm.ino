// Leitura de batimentos cardíacos utilizando Arduino Uno
// Programa baseado no Exemplo 5:HeartRate da biblioteca MAX30105
// Modificado por Lucas Jácome e Erick León, 2022.

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

const byte RATE_SIZE = 4; // Número de medidas usadas na média
byte rates[RATE_SIZE];    // Vetor de medidas de frequência
byte rateSpot = 0;        // guarda a posição atual do vetor
long lastBeat = 0;        // Instante em que ocorreu a última batida cardíaca
float beatsPerMinute;     // frequência (batidas por minuto)
int beatAvg;              // média da frequência

long ultimoenvio=0;
// esta função só roda uma vez, no início
void setup()
{
    // Inicializa o display
    Serial.begin(115200);
    //lcd.begin(16, 2); // usando um display LCD de 16x2 caracteres
    //lcd.clear();
    //lcd.setCursor(0, 0);

    // Initializa o sensor, usando a porta I2C padrão, velocidade de 400kHz
    if (!particleSensor.begin(Wire, I2C_SPEED_FAST))
    {
        //lcd.print("Sensor nao encontrado ");
        //Serial.println("Sensor nao encontrado ");
        while (1); // Se não encontra o sensor, fica parado aqui em um loop infinito
    }

    //lcd.print("Coloque seu dedo");
    //Serial.println("Coloque seu dedo");
    delay(1000);

    // Configura o sensor
    particleSensor.setup();
    // Liga o LED vermelho para indicar que o sensor está ligado
    particleSensor.setPulseAmplitudeRed(0x0A);
    // desliga o LED verde
    particleSensor.setPulseAmplitudeGreen(0);
}

// esta função se repete indefinidamente
void loop()
{
    long irValue = particleSensor.getIR();
    
    if (checkForBeat(irValue) == true) // verifica se ocorreu uma batida
    {
        // A batida ocorreu
        long delta = millis() - lastBeat; // mede o intervalo desde a última batida
        lastBeat = millis(); // guarda o instante desta batida
      
        beatsPerMinute = 60 / (delta / 1000.0); // calcula a frequência em batidas por minuto
      
        if (beatsPerMinute < 255 && beatsPerMinute > 20) // se o valor for válido...
        {
            rates[rateSpot++] = (byte)beatsPerMinute; // Armazena a leitura no vetor
            rateSpot %= RATE_SIZE; // muda a posição da medida no vetor
        
            // Calcula a média das leituras
            beatAvg = 0;
            for (byte x = 0 ; x < RATE_SIZE ; x++)
                beatAvg += rates[x];
            beatAvg /= RATE_SIZE;
        }
    }

  long deltaenvio = millis() - ultimoenvio;
  if (deltaenvio>=1000){
    ultimoenvio = millis();
    // Mostra as informações no LCD
    //lcd.clear();
    //lcd.setCursor(0, 0);
    //lcd.print("IR= ");
    //Serial.print("IR= ");
    //lcd.print(irValue);
    //Serial.println(irValue);
    //lcd.setCursor(0, 1);
    if (irValue < 50000){
        //lcd.print("SEM DEDO? ");
        //Serial.println("SEM DEDO? ");
    } else{
        //lcd.print("BPM=");
        Serial.print("BPM ");
        //lcd.print(beatsPerMinute);
        Serial.println(beatsPerMinute);
    }
  }
    //delay(10);
}
