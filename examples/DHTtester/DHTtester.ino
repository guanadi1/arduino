
// libreria y variables  comunicacion serial con bbluetooth
#include <SoftwareSerial.h>
char rec; // variable que recoje valor enviado
char send // variable con valor a enviar 
SoftwareSerial bluetoothBridge(2,3);


// variables y librerias dht11 
#include "DHT.h"          // Libreria para Sensores Temperatura DHT
#define DHTPIN 2         // conectado en el pin 2 del sensor
#define DHTTYPE DHT11   // DHT 11  sensor DHT usado
DHT dht(DHTPIN, DHTTYPE);   // Inicializa el sensor


// variables motor dc 
#define DCPIN 3   // Pin 3 PWM motor 
int velocidad = 255; // variable donde almacenamos la velocidad del motor 0-255

// variables led RGB
#define REDRGB 4    // Pin 4 para el color rojo 
#define GREENRGB 5    // Pin 5 para el color verde 
#define BLUERGB 6    //Pin 6 para el color azul  
int 

// Configura Arduino 
void setup() {

  bluetoothBridge.begin(9600); // inciamos comunicacion bluetooth
  Serial.println("Connection inciada bluetooth ");

  pinMode(DCPIN, OUTPUT); // pin motor DC output

  pinMode(REDRGB, OUTPUT);
  pinMode(GREENRGB, OUTPUT);
  pinMode(BLUERGB, OUTPUT);  

  Serial.begin(9600); 
  Serial.println("Prueba log:");
  dht.begin();  // iniciamos sensor 

}



void loop() {

  delay(2000); // Espera dos segundos para realizar la primera medición.
  rec = bluetoothBridge.read();   // leemos la comunicacion serial de bluetooth
  switch(rec){
     case 'led0':
     setColor(0, 255, 255);  // ilumina led rgb con color aqua 
     Serial.println(" led encendido");
     break;

     case 'led1':
     setColor(0, 0, 0);  // apagamos el led 
     Serial.println(" led apagado");
     break;

}

    

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

// funcion que asigna el color 
void setColor(int red, int green, int blue) {
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(REDRGB, red);
  analogWrite(GREENRGB, green);
  analogWrite(BLUERGB, blue);  

/* para cambiar el color utilizar las siguientes lineas dependiendo del color y descomentar 
    setColor(255, 0, 0);  // red
    setColor(0, 255, 0);  // green
    setColor(0, 0, 255);  // blue
    setColor(255, 255, 0);  // yellow
    setColor(80, 0, 80);  // purple
*/


}

