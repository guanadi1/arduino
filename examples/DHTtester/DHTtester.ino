
/* variables dht11 
#include "DHT.h"          // Libreria para Sensores Temperatura DHT
#define DHTPIN 2         // Pin del Arduino al cual esta conectado el pin 2 del sensor
#define DHTTYPE DHT11   // DHT 11  sensor DHT usado
DHT dht(DHTPIN, DHTTYPE);   // Inicializa el sensor


/* variables motor dc 
#define DCPIN 3 ; // Pin 3 que puede generar PWM
int velocidad = 255; // variable donde almacenamos la velocidad del motor 0-255





// Configura Arduino 
void setup() {
  pinMode(DCPIN, OUTPUT); // pin DC output
  Serial.begin(9600); 
  Serial.println("Prueba log:");
  dht.begin();  // iniciamos sensor 

}



void loop() {

  delay(2000); // Espera dos segundos para realizar la primera medición.

    

  float humedad = dht.readHumidity(); // Obtiene la Humedad
  float temperatura = dht.readTemperature();   // Obtiene la Temperatura en Celsius
  
  // Control de errores, valida que se obtuvieron valores para los datos medidos
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println("Fallo al leer el sensor DHT!");
    return;
  }
  Serial.print("Humedad: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperatura: "); 
  Serial.print(t);
  Serial.println(" *C ");
  
  // encendemos el motor si la temperatura sobrepasa los 25 grados Celsius
  if (temperatura > 25){
   analogWrite(DCPIN, velocidad);
  }else{
   analogWrite(DCPIN, 0);
  }

}
