
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

//variable sensor ultrasonico y speaker
// libreria NEWPIN https://arduino-new-ping.googlecode.com/files/NewPing_v1.5.zip

#include <NewPing.h>
#define TRIGGER_PIN  7
#define ECHO_PIN     8
#define MAX_DISTANCE 200     
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);   //Crear el objeto de la clase NewPing
#define SPEAKERPIN 9         //pin speaker PWN


// VARIABLES RELAY

#define RELAYPIN 12            // PIN al que va conectado el relé




// Configura Arduino 
void setup() {

  // bloutooth
  bluetoothBridge.begin(9600); // inciamos comunicacion bluetooth
  Serial.println("Connection inciada bluetooth ");

  // motor 
  pinMode(DCPIN, OUTPUT); // pin motor DC output
 
 // PIR , speaker
  pinMode(PIRPIN, INPUT);     // declaramos sensor PIR  es de entrada 
  pinMode(SPEAKERPIN, OUTPUT);

  // rgb
  pinMode(REDRGB, OUTPUT);
  pinMode(GREENRGB, OUTPUT);
  pinMode(BLUERGB, OUTPUT);  
 
  //monitor serial
  Serial.begin(9600); 
  Serial.println("Prueba log:");


  pinMode(RELAYPIN, OUTPUT);  // PIN relay como salida


  // dth 11
  dht.begin();  // iniciamos sensor 

}



void loop() {

  delay(2000); // Espera dos segundos para realizar la primera medición.


  rec = bluetoothBridge.read();   // leemos la comunicacion serial de bluetooth
  switch(rec){
     case 'rgb0':
     setColor(0, 255, 255);  // ilumina led rgb con color aqua 
     Serial.println(" led encendido");
     break;

     case 'rgb1':
     setColor(0, 0, 0);  // apagamos el led 
     Serial.println(" led apagado");
     break;

     case 'relay1':
     digitalWrite(RELAYPIN, HIGH);   // bombilla ENCENDIDO
     Serial.println(" bombilla encendido");
     break; 

     case 'relay0':
      digitalWrite(relayPin, LOW);    // bombilla APAGADO
     Serial.println(" led encendido");
     break;



}


// sesor de temperatura    

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



// sensor ultrasonico y speaker


  int uS = sonar.ping_median();  // Obtener medicion de tiempo de viaje del sonido y guardar en variable uS
  long distancia= uS/US_ROUNDTRIP_CM;  // Calcular la distancia con base en una constante
  Serial.print("Distancia: ");// Imprimir la distancia medida a la consola serial
   Serial.print(distancia );
  Serial.println("cm");

  if (distancia > 2) {            // check if the input is HIGH
    playTone(300, 160);
    delay(150);
  } else { 
      playTone(0, 0);
      delay(150);    
    }
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


// tono alarma duracion en mSecs, frequencia en hertz
void playTono(long duracion, int freq) {
    duracion *= 1000;
    int periodo = (1.0 / freq) * 1000000;
    long tiempo_transcurrido = 0;
    while (tiempo_transcurrido < duracion) {
        digitalWrite(SPEAKERPIN,HIGH);
        delayMicroseconds(periodo / 2);
        digitalWrite(SPEAKERPIN, LOW);
        delayMicroseconds(periodo / 2);
        tiempo_transcurrido += (periodo);
    }
}



