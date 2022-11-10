// Constants
#include "ControlMotor.h"

#define x 100 //Nombre de tour dans la boucle
#define freq 100 //Acquisition devra être réalisée toutes les ... en ms

 struct Motor_Data // Structure dans le Labo
 {
  float Time;
  float Vitesse;
  int Position; 
 }; 

const int SignalA = 2;
const int SignalB = 3;
const int MotorForward1 = 9;
const int MotorReverse1 = 10;

// Variables
volatile int Cpt =0;
int j=0; //Variable en globale pour stocker les données dans la fonction AcquisitionComputing
long startMillis; //Temps au debut du loop
int Position = 0; //Position du moteur
const int Power = 100; //Pour les 1er exs. Motor velocity between 0 and 255

void setup(){
  Serial.begin(9600);
  //pinMode(MotorForward1,OUTPUT); // pour les 1er exs
  //pinMode(MotorReverse1,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SignalB),Capteur,CHANGE);
  attachInterrupt(digitalPinToInterrupt(SignalA),Capteur,CHANGE);
  Init_Motor();
}

void loop(){
  struct Motor_Data tab[x]; // declaration du tableau des valeurs pour le tableau Excel
    startMillis = millis(); //Stock le temps actuel
    
    for(j=0;j<x;j++){
      AcquisitionComputing(tab);
      Control_Motor();
    }
    for(j=0;j<x;j++){
      Serial.print(tab[j].Time);
      Serial.print(",");
      Serial.print(tab[j].Vitesse);
      Serial.print(",");
      Serial.println(tab[j].Position);
    }
    delay(20000);
}

void AcquisitionComputing(struct Motor_Data* tab)
{
  long CurrentMillis = millis();  
  int calcul = freq*j+1000; //define du freq + 1sec de "delay"
  
  while( CurrentMillis - startMillis < calcul ){
    CurrentMillis = millis();
  }
  tab[j].Vitesse = Cpt*60000.0/freq/360;// tour(360)/minute(60000ms)
  Position = (Position + Cpt)%360;
  tab[j].Position = Position;
  tab[j].Time = CurrentMillis;
  Cpt=0;
}

void Capteur()
{
  Cpt++;
}
/////////////////////////////////////////////////:
void Sens_Continu()
{
  analogWrite(MotorForward1,Power);
  delay(2000);
  analogWrite(MotorForward1,0);
}

void Rampe_Acc()
{
  for(int i=0;i<255;i++)
  {
    analogWrite(MotorForward1,i);
    delay(100);
    Serial.println(Cpt);
    
  }   
}

void Rampe_Dec()
{
  for(int i=255;i>0;i--)
  {
    analogWrite(MotorForward1,i);
    delay(100);
  }   
}

void Acc_Dec()
{
  Rampe_Acc();
  Rampe_Dec();
}
