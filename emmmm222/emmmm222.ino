#include <Servo.h>

// GF --- Smart Robot Car ---
// Playlist: https://www.youtube.com/playlist?list=PLRFnGJH1nJiJxoO0woBW6vl_8URTQPhfL
// Smart Robot Car: Part 4 - DC Motors & L298N Dual Motor Controller 
// Wiring & Video Demo: https://www.youtube.com/watch?v=0RLAivgppBM

// connect motor controller pins to Arduino digital pins
// motor one
int enA = 10;
int in1 = 9;
int in2 = 8;
// motor two
int enB = 5;
int in3 = 7;
int in4 = 6;
int estado;
//gcardenas@fcdperu.com


//#define PIN_TRIG 11
//#define PIN_ECO  12

Servo servo1;

int flag = 1;
long duracion, distancia;  // Variables

void setup()
{
  // set all the motor control pins to outputs
  Serial.begin (9600);
  servo1.attach(13, 600, 1500);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //pinMode(PIN_TRIG, OUTPUT);
  //pinMode(PIN_ECO, INPUT);
}


void adelante(){
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}
void atras(){
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
void izquierda(){
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
}

void derecha(){
    analogWrite(enA, 255);
    analogWrite(enB, 255);
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
}
void parar(){
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
} 

void demoOne()
{
  // this function will run the motors in both directions at a fixed speed
  // turn on motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 200);

  // turn on motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enB, 200);

  delay(2000);

  // now change motor directions
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 

  delay(2000);

  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void demoTwo()
{
  // this function will run the motors across the range of possible speeds
  // note that maximum speed is determined by the motor itself and the operating voltage
  // the PWM values sent by analogWrite() are fractions of the maximum speed possible 
  // by your hardware
  // turn on motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 

  // accelerate from zero to maximum speed
  for (int i = 0; i < 256; i++)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  } 

  // decelerate from maximum speed to zero
  for (int i = 255; i >= 0; --i)
  {
    analogWrite(enA, i);
    analogWrite(enB, i);
    delay(20);
  }

  // now turn off motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);  
}
int disparar() {
  //* Hacer el disparo 
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG, HIGH);  // Flanco ascendente
  delayMicroseconds(10);        // Duracion del pulso
  digitalWrite(PIN_TRIG, LOW);  // Flanco descendente
  
  // Recepcion del eco de respuesta 
  duracion = pulseIn(PIN_ECO, HIGH);
  
  //* Calculo de la distancia efectiva 
  distancia = (duracion/2) / 29;

/* Imprimir resultados a la terminal serial */
  if (distancia >= 500 || distancia <= 0){
    //Serial.print(duracion);
    //Serial.println("Fuera de rango");
    return 0;
  }
  else {
    Serial.print(distancia);
    Serial.println(" cm");
    if (distancia <= 30) {
      return 1;
    }
  }
  return 0;
}
int verificarIzquierda() {
  int obstaculo = 0;
  for (int pos = 90; pos >= 1; pos--) {
    servo1.write(pos);
    int dis = disparar();
    obstaculo += dis;
    delay(30);
  }
  return obstaculo;
}
int verificarDerecha() {
  int obstaculo = 0;
  servo1.write(90);
  delay(15);
  for (int pos = 90; pos < 180; pos++) {
    servo1.write(pos);
    int dis = disparar();
    obstaculo += dis;
    delay(30);
  }
  return obstaculo;
}

void loop()
{
  if (flag == 1){
     adelante();
     flag = 0;
  }
  //demoOne();
  //delay(1000);
  //demoTwo();
  //delay(1000);
  if (Serial.available ()>0){
    estado = Serial.read();
    if (estado != -1){
      switch(estado){
   
          case 'a':
          adelante(); 
          break;
          case 'b':
          atras(); 
          break;
          case 'c':
          izquierda(); 
          break;
          case 'd':
          derecha(); 
          break;
          case 'e':
          parar(); 
          break;
          case 't':
          servo1.write(180);
          delay(15);
          break;
          case 'y':
          servo1.write(0);
          delay(15);
          break;
          case 'u':
          servo1.write(90);
          break;
          
      }
    }
  }
  servo1.write(90);
  /*
  for (int pos = 0; pos < 180; pos++) {
    servo1.write(pos);
    delay(15);
  }
  for (int pos = 180; pos >= 1; pos--) {
    servo1.write(pos);
    delay(15);
  }*/
  
  /* Hacer el disparo */
  digitalWrite(PIN_TRIG, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG, HIGH);  // Flanco ascendente
  delayMicroseconds(10);        // Duracion del pulso
  digitalWrite(PIN_TRIG, LOW);  // Flanco descendente
  
  /* Recepcion del eco de respuesta */
  duracion = pulseIn(PIN_ECO, HIGH);
  
  /* Calculo de la distancia efectiva */
  distancia = (duracion/2) / 29;

/* Imprimir resultados a la terminal serial */
  if (distancia >= 500 || distancia <= 0){
    //Serial.print(duracion);
    //Serial.println("Fuera de rango");
  }
  else {
    Serial.print(distancia);
    Serial.println(" cm");
    if (distancia <= 30) {
      
      parar();
      int izq = verificarIzquierda();
      int der = verificarDerecha();
      if (izq > 0 && der > 0) {
        atras();
        delay(1500);
        derecha();
        delay(1500);
        parar();
        delay(50);
        adelante();
      }
      else if (izq > 0) {
        derecha();
        delay(1300);
        parar();
        delay(50);
        adelante();
      }
      else if (der > 0) {
        izquierda();
        delay(1300);
        parar();
        delay(50);
        adelante();
      }
      else {
        atras();
        delay(1500);
        derecha();
        delay(1500);
        parar();
        delay(50);
        adelante();
      }
    }
  }
  //delay(500);
}

