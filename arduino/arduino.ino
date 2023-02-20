#include "DHT.h"
#define DHTPIN A0
#define DHTTYPE DHT11   // DHT 11

int L1 = 9;
int L2 = 8;
int L3 = 7;
int L4 = 6;

int L5 = 5;
int L6 = 4;
int L7 = 3;
int L8 = 2;

bool AutoFan = false;

DHT dht(DHTPIN, DHTTYPE);
unsigned long startTime;

void setup()
{
  Serial.begin(9600);
  dht.begin();
//################## Modulo Relay 1 ##################
  pinMode(L1,OUTPUT);     //Lampara 1
  digitalWrite(L1, HIGH);
  pinMode(L2,OUTPUT);     //Lampara 2
  digitalWrite(L2, HIGH);
  pinMode(L3,OUTPUT);     //Lampara 3
  digitalWrite(L3, HIGH);
  pinMode(L4,OUTPUT);     //Lampara 4
  digitalWrite(L4, HIGH);
//################## Modulo Relay 2 ##################
  pinMode(L5,OUTPUT);     //Enchufe 1
  digitalWrite(L5, HIGH);
  pinMode(L6,OUTPUT);     //Enchufe 2
  digitalWrite(L6, HIGH);
  pinMode(L7,OUTPUT);     //Ventilador 1
  digitalWrite(L7, HIGH);
  pinMode(L8,OUTPUT);     //Ventilador 2
  digitalWrite(L8, HIGH);
  Serial.println("Ahora esta funcionando");
}

void loop()
{
  delay(250);
  EncenderApagar();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer el sensor");
    return;
  }
  controlarVentilador(t);
  ImprimirValores();
}

void controlarVentilador(float t) {
  if (AutoFan == true){
    if (t > 23) {
      digitalWrite(L8, LOW);
      digitalWrite(L7, LOW);
    }
    else if (t < 23) {
      digitalWrite(L8, HIGH);
      digitalWrite(L7, HIGH);
  }      
  }
}

void ImprimirValores(){
  Serial.print(dht.readHumidity());
  Serial.print(",");
  Serial.print(dht.readTemperature());
  Serial.print(",");
  Serial.print(dht.computeHeatIndex(dht.readTemperature(), dht.readHumidity(), false));
  Serial.print(",");
  Serial.print(AutoFan);
  Serial.print(",");
  Serial.print(getElapsedTime());
  Serial.println();
}

String getElapsedTime() {
  unsigned long elapsedTime = (millis() - startTime) / 1000;
  int hours = elapsedTime / 3600;
  int minutes = (elapsedTime % 3600) / 60;
  int seconds = elapsedTime % 60;

  String time = "";
  if (hours < 10) time += "0";
  time += String(hours) + ":";

  if (minutes < 10) time += "0";
  time += String(minutes) + ":";

  if (seconds < 10) time += "0";
  time += String(seconds);

  return time;
}


int EncenderApagar() {
  int valor;
  if (Serial.available()) { // Si hay datos disponibles en el puerto serie
    valor = Serial.parseInt(); // Leer la cadena recibida
    
    if (valor == 1) { // Prender Lampara 1
      digitalWrite(L1, LOW);
      return 0;
    } 
    else if (valor == 2) { // Apagar Lampara 1
      digitalWrite(L1, HIGH);
      return 0;
    } 
    
    else if (valor == 3) { // Prender Lampara 2
      digitalWrite(L2, LOW);
      return 0;
    } 
    else if (valor == 4) { // Apagar Lampara 2
      digitalWrite(L2, HIGH);
      return 0;
    }
    
    else if (valor == 5) { // Prender Lampara 3
      digitalWrite(L3, LOW);
      return 0;
    } 
    else if (valor == 6) { // Apagar Lampara 3
      digitalWrite(L3, HIGH);
      return 0;
    }
    
    else if (valor == 7) { // Prender Lampara 4
      digitalWrite(L4, LOW);
      return 0;
    } 
    else if (valor == 8) { // Apagar Lampara 4
      digitalWrite(L4, HIGH);
      return 0;
    }
    
    else if (valor == 9) { // Prender Enchufe 1
      digitalWrite(L5, LOW);
      return 0;
    } 
    else if (valor == 10) { // Apagar Enchufe 1
      digitalWrite(L5, HIGH);
      return 0;
    }
    
    else if (valor == 11) { // Prender Enchufe 2
      digitalWrite(L6, LOW);
      return 0;
    } 
    else if (valor == 12) { // Apagar Enchufe 2
      digitalWrite(L6, HIGH);
      return 0;
    }
    
    else if (valor == 13) { // Prender Ventilador 1
      digitalWrite(L7, LOW);
      return 0;
    } 
    else if (valor == 14) { // Apagar Ventilador 1
      digitalWrite(L7, HIGH);
      return 0;
    }
    
    else if (valor == 15) { // Prender Ventilador 2
      digitalWrite(L8, LOW);
      return 0;
    } 
    else if (valor == 16) { // Apagar Ventilador 2
      digitalWrite(L8, HIGH);
      return 0;
    }
    
    else if (valor == 20) { // Cambiar el valor del AutoFan
      AutoFan = false;
      return 0;
    } 
    else if (valor == 21) { // Cambiar el valor del AutoFan
      AutoFan = true;
      return 0;
    }
    else {
      return 0;
    }
  }
}
