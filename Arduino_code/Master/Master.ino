////////////////////////////////////////////////////////////////
                        /*MASTER*/
////////////////////////////////////////////////////////////////
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";
const byte addresses[6] = "00002";

//int x=0;
//int y=0;
int x1=0;
//int y1=0;

int direction1=0;
int manual_mode=0;
int automatic_mode=0;

int ir_sensor_right=2;
int ir_sensorstate_right=0;
int ir_sensor_left=3;
int ir_sensorstate_left=0;


//Left Motor
const int Left_Black = 6;
const int Left_Red = 5;
//Right Motor
const int Right_Black = 9;
const int Right_Red = 10;


void setup()
{
  pinMode(Left_Black, OUTPUT);
  pinMode(Left_Red, OUTPUT);
  pinMode(Right_Black, OUTPUT);
  pinMode(Right_Red, OUTPUT);  
  while (!Serial);
  Serial.begin(9600);
  
  radio.begin();
  radio.openWritingPipe(addresses); // 00002
  radio.openReadingPipe(1, rxAddr);
  radio.setPALevel(RF24_PA_MIN);
}

void loop()
{  
  x1 = direction1+4;
  char x2=x1+'0';
  //Serial.println(x2);
  delay(5);
  radio.stopListening();
  radio.write(&x2, sizeof(x2));

////////////////////////////////////////////////////////////////
  radio.startListening();
  
  for(int i=0;i<2;i++)
  {
    if (radio.available())
    {
      char dir[32] = {0};
      radio.read(&dir, sizeof(dir));
      //Serial.println(dir);
      direction1 = atoi(dir);
    }
  }

////////////////////////////////////////////////////////////////

  Serial.println(direction1);
  if (direction1==6)
  {
    automatic_mode = 0;
    manual_mode = 1;
  }
  
  if(direction1==5)
  {
    automatic_mode = 1;
    manual_mode = 0;
  }
  
  if(manual_mode==1)
  {
    Serial.println("Manual Mode");
    if(direction1==0)
      stable();
      
    if(direction1==1)
      front();
      
    if(direction1==2)
      left();
      
    if(direction1==3)
      reverse(); 
      
    if(direction1==4)
      right();
  }
  
  if(automatic_mode==1)
  {
    Serial.println("Automatic Mode");
    ir_sensorstate_right=digitalRead(ir_sensor_right);
    ir_sensorstate_left=digitalRead(ir_sensor_left);
    //Serial.println(ir_sensorstate_right);  
    //Serial.println(ir_sensorstate_left);
    //delay(1000);
    if((ir_sensorstate_right==0) && (ir_sensorstate_left==0))
    {
      front();
    }
    
    else if(ir_sensorstate_right==1)
    {
      right();
    }
    else if(ir_sensorstate_left==1)
    {
      left();
    }
    else if((ir_sensorstate_right==1) && (ir_sensorstate_left==1)) 
    {
      stable();
    }
  }
}

////////////////////////////////////////////////////////////////
                        /*FUNCTIONS*/
////////////////////////////////////////////////////////////////

void stable()
{
  direction1=0;
  analogWrite(Left_Black, LOW);
  analogWrite(Left_Red, LOW);
  analogWrite(Right_Red, LOW);
  analogWrite(Right_Black, LOW);
}
void left()
{
  direction1=2;
  analogWrite(Left_Black, 120);
  analogWrite(Left_Red, LOW);
  analogWrite(Right_Red, LOW);
  analogWrite(Right_Black, LOW);
}
void right()
{
  direction1=4;
  analogWrite(Left_Black, LOW);
  analogWrite(Left_Red, LOW);
  analogWrite(Right_Red, LOW);
  analogWrite(Right_Black, 120);
}
void front()
{
  direction1=1;
  analogWrite(Left_Black, 120);
  analogWrite(Left_Red, LOW);
  analogWrite(Right_Red, LOW);
  analogWrite(Right_Black, 120);
}
void reverse()
{
  analogWrite(Left_Black, LOW);
  analogWrite(Left_Red, 120);
  analogWrite(Right_Red, 120);
  analogWrite(Right_Black, LOW);
}
