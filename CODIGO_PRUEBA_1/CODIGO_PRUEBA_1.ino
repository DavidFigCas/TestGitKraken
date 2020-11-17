int motor_ena = 11;
int motor_in1 = 12;
int motor_in2 = 13;

int motor_enb = 5;
int motor_in4 = 4;
int motor_in3 = 3;

int trigger_fre = A0;
int echo_fre = A1;

int trigger_izq = A2;
int echo_izq = A3;

int trigger_der = A4;
int echo_der = A5;


void setup() 
{
  pinMode(motor_in1, OUTPUT);         //MOTORES IZQUIERDA ADELANTE
  pinMode(motor_in2, OUTPUT);         //MOTORES IZQUIERDA ATRAS
  pinMode(motor_ena, OUTPUT);         //CONTROL PWM

  pinMode(motor_in3, OUTPUT);         //MOTORES DERECHA ADELANTE
  pinMode(motor_in4, OUTPUT);         //MOTORES DERECHA ATRAS
  pinMode(motor_enb, OUTPUT);         //CONTROL PWM

  pinMode(trigger_fre,OUTPUT);
  pinMode(echo_fre, INPUT);

  pinMode(trigger_izq,OUTPUT);
  pinMode(echo_izq, INPUT);

  pinMode(trigger_der,OUTPUT);
  pinMode(echo_der, INPUT);

  analogWrite(motor_ena, 88);
  analogWrite(motor_enb, 88);
}

void loop()
{
  Serial.begin(9600);
  long duracion_fre, distancia_fre, duracion_izq, distancia_izq, duracion_der, distancia_der;

  //Calcular distancia con ultrasonicos

  digitalWrite(trigger_fre, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_fre, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_fre, LOW);
  duracion_fre = pulseIn(echo_fre, HIGH);
  distancia_fre = duracion_fre*0.034/2;

  digitalWrite(trigger_izq, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_izq, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_izq, LOW);
  duracion_izq = pulseIn(echo_izq, HIGH);
  distancia_izq = duracion_izq*0.034/2;
  
  digitalWrite(trigger_der, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_der, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_der, LOW);
  duracion_der = pulseIn(echo_der, HIGH);
  distancia_der = duracion_der*0.034/2;

  Serial.print("Frente = ");
  Serial.println(distancia_fre);
  Serial.print("Izquierda = ");
  Serial.println(distancia_izq);
  Serial.print("Derecha = ");
  Serial.println(distancia_der);
  delay(50);

  if (distancia_fre >30)                                    //SI LA DISTANCIA DEL SENSOR DE ENFRENTE ES MAYOR A 20 EL CARRO AVANZA
  {
    adelante();

    if(distancia_izq >10 && distancia_izq <30)              //SI LA DISTANCIA DEL SENSOR IZQUIERDA ES MAYOR A 10 Y LA DISTANCIA DEL SENSOR IZQUIERDA ES MENOR A 20 EL CARRO AVANZA
    {
      adelante();
    }
      if(distancia_izq >=30)                                //SI LA DISTANCIA DEL SENSOR IZQUIERDA ES MAYOR O IGUAL A 20 EL CARRO GIRA A LA IZQUIERDA Y AVANZA
      {
        izquierda();
        delay(30);
        adelante();
      }
        if(distancia_izq <10 && distancia_izq >0)           //SI LA DISTANCIA DEL SENSOR IZQUIERDA ES MENOR A 10 Y LA DISTANCIA DEL SENSOR IZQUIERDA ES MAYOR A 0 EL CARRO GIRA A LA DERECHA Y AVANZA
        {
          derecho();
          delay(30);
          adelante();
        }
  }
           if(distancia_fre <=30 && distancia_der >30)      //SI LA DISTANCIA DEL SENSOR DE ENFRENTE ES MENOR O IGUAL A 20 Y LA DISTANCIA DEL SENSOR DERECHA ES MAYOR A 20 EL CARRO PARA Y GIRA A LA DERECHA
           {
            alto();
            delay(1000);
            derecho();
            //delay(400);
           }
             if(distancia_fre <=30 && distancia_der <30)    //SI LA DISTANCIA DEL SENSOR DE ENFRENTE ES MENOR O IGUAL A 20 Y LA DISTANCIA DEL SENSOR DERECHA ES MENOR A 20 EL CARRO PARA Y GIRA A LA DERECHA
             {
              alto();
              delay(1000);
              derecho();
              //delay(800);
             }

}


void adelante()                 //ACTIVAR MOTORES PARA QUE AVANCE
{
  digitalWrite(motor_in1,1);
  digitalWrite(motor_in2,0);
  digitalWrite(motor_in3,1);
  digitalWrite(motor_in4,0);
  delay(1000);
}

void derecho()                  //ACTIVAR GIRO A LA DERECHA
{
  digitalWrite(motor_in1,HIGH);
  digitalWrite(motor_in2,LOW);
  digitalWrite(motor_in3,HIGH);
  digitalWrite(motor_in4,LOW);
  delay(10);
}

void izquierda()                //ACTIVAR GIRO A LA IZQUIERDA
{
  digitalWrite(motor_in1,LOW);
  digitalWrite(motor_in2,HIGH);
  digitalWrite(motor_in3,HIGH);
  digitalWrite(motor_in4,LOW);
  delay(1000);
}

void alto()                     //DETENER GIRO DE MOTORES 
{
  digitalWrite(motor_in1,LOW);
  digitalWrite(motor_in2,LOW);
  digitalWrite(motor_in3,LOW);
  digitalWrite(motor_in4,LOW);
  delay(3000);
}
