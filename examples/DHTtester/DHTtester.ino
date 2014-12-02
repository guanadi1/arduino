

#include "DHT.h"          // Libreria para Sensores DHT
#define DHTPIN 2         // Pin del Arduino al cual esta conectado el pin 2 del sensor
#define DHTTYPE DHT11   // DHT 11  sensor DHT usado

DHT dht(DHTPIN, DHTTYPE);   // Inicializa el sensor

// Configura Arduino 
void setup() {
  Serial.begin(9600); 
  Serial.println("Prueba log:");
  dht.begin();  // iniciamos sensor 
}



void loop() {

  delay(2000); // Espera dos segundos para realizar la primera medición.

  float h = dht.readHumidity(); // Obtiene la Humedad
  float t = dht.readTemperature();   // Obtiene la Temperatura en Celsius
  
  // Control de errores, valida que se obtuvieron valores para los datos medidos
  if (isnan(h) || isnan(t)) {
    Serial.println("Fallo al leer el sensor DHT!");
    return;
  }

  Serial.print("Humedad: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: "); 
  Serial.print(t);
  Serial.println(" *C ");
}
