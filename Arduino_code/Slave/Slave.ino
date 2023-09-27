////////////////////////////////////////////////////////////////
                        /*SLAVE*/
////////////////////////////////////////////////////////////////

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte addresses[6] = "00002";

//int x=0;
//int y=0;
//int z=0;

//Left Motor
const int Left_Black = 5;
const int Left_Red = 6;
//Right Motor
const int Right_Black = 10;
const int Right_Red = 9;

int digits = 0;
int direction2 = 0;

void setup()
{
  pinMode(Left_Black, OUTPUT);
  pinMode(Left_Red, OUTPUT);
  pinMode(Right_Black, OUTPUT);
  pinMode(Right_Red, OUTPUT);  
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, addresses); 
  
  radio.startListening();
}

void loop()
{
  for(int i=0;i<2;i++)
  {
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    digits = atoi(text);
    direction2=digits-4;
    //Serial.println(text);
  }
  }
  //Serial.println(direction2);
  
  if(direction2==0)
    stable();
    
  if(direction2==1)
    front();
    
  if(direction2==2)
    right();
    
  if(direction2==3)
    reverse(); 
    
  if(direction2==4)
    left();
}





////////////////////////////////////////////////////////////////
                        /*FUNCTIONS*/
////////////////////////////////////////////////////////////////

void stable()
{
  analogWrite(Left_Black, LOW);
  analogWrite(Left_Red, LOW);
  analogWrite(Right_Red, LOW);
  analogWrite(Right_Black, LOW);
}
void left()
{
  analogWrite(Left_Black, 90);
  analogWrite(Left_Red, LOW);
  analogWrite(Right_Red, LOW);
  analogWrite(Right_Black, LOW);
}
void right()
{
  analogWrite(Left_Black, LOW);
  analogWrite(Left_Red, LOW);
  analogWrite(Right_Red, LOW);
  analogWrite(Right_Black, 90);
}
void front()
{
  analogWrite(Left_Black, 90);
  analogWrite(Left_Red, LOW);
  analogWrite(Right_Red, LOW);
  analogWrite(Right_Black, 90);
}
void reverse()
{
  analogWrite(Left_Black, LOW);
  analogWrite(Left_Red, 90);
  analogWrite(Right_Red, 90);
  analogWrite(Right_Black, LOW);
}
