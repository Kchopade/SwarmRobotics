////////////////////////////////////////////////////////////////
                        /*REMOTE*/
////////////////////////////////////////////////////////////////



#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);

const byte rxAddr[6] = "00001";

int up = 2;
int down = 3;
int right = 4;
int left = 5;

int u=0;
int l=0;
int d=0;
int r=0;

int dir=0;

void setup()
{
  radio.begin();
  radio.setRetries(15, 15);
  radio.openWritingPipe(rxAddr);
  
  radio.stopListening();
  Serial.begin(9600);

  pinMode(up, INPUT);
  pinMode(left, INPUT);
  pinMode(down, INPUT);
  pinMode(right, INPUT);
}

void loop()
{  
  u = digitalRead(up);
  l = digitalRead(left);
  d = digitalRead(down);
  r = digitalRead(right);
  
//  Serial.println(u);
//  Serial.println(l);
//  Serial.println(d);
//  Serial.println(r);
//  Serial.println("****************");
//  delay(500);

  dir = 0;

  if(u==0)
    dir = 1;

  else if(l==0)
    dir = 2;
    
  else if(d==0)
    dir = 3;
    
  else if(r==0)
    dir = 4;

  if((l==0) && (r==0))
    dir = 5;
    
  if((u==0) && (d==0))
    dir = 6;
    
  Serial.println(dir);
  
  char x=dir+'0';
  radio.write(&x, sizeof(x));
}
