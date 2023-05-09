#include <TFT_eSPI.h> 
#include <Tone32.h>
#include "fonts.h"
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite img = TFT_eSprite(&tft);

#define color1 TFT_WHITE
#define color2  0x8410
#define color3 TFT_ORANGE
#define color4 0x15B3
#define color5 0x00A3

#define butA 0
#define butB 35
#define butC 13 
#define butD 15 
#define anaA 12
#define togA 2
#define togB 17
#define led  27
#define BUZZER_PIN 26
#define BUZZER_CHANNEL 1

bool switches[2]={0,1};

float VALUE;
int brightness=500;
bool sound=1;
String soundL[2]={"OFF","ON"};

double rad=0.01745;
float x[360];
float y[360];

float px[360];
float py[360];

float px2[360];
float py2[360];

float lx[360];
float ly[360];

int r=132;
int sx=120;
int sy=180;

String cc[10]={"0","10","20","30","40","50","60","70","80","90"};
int start[10];
int start2[20];
int startP[60];

const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;


int dutyCycle2 = 128;

bool onOff=0;
bool debounce=0;

int angle=270;
int lastAngle=0;

void setup() {
   
    pinMode(led,OUTPUT);
    pinMode(butA,INPUT_PULLUP);
    pinMode(butB,INPUT_PULLUP);
    pinMode(butC,INPUT_PULLUP);
    pinMode(butD,INPUT_PULLUP);
    pinMode(togA,INPUT_PULLUP);
    pinMode(togB,INPUT_PULLUP);

   

    tft.init();
    tft.setRotation(1);
    tft.setSwapBytes(true);
    tft.fillScreen(TFT_BLACK);

    img.setSwapBytes(true);
    img.createSprite(240, 135);
    img.setTextDatum(4);

int b=0;
int b2=0;
int b3=0;

    for(int i=0;i<360;i++)
    {
       x[i]=(r*cos(rad*i))+sx;
       y[i]=(r*sin(rad*i))+sy;
       px[i]=((r-14)*cos(rad*i))+sx;
       py[i]=((r-14)*sin(rad*i))+sy;
       px2[i]=((r-18)*cos(rad*i))+sx;
       py2[i]=((r-18)*sin(rad*i))+sy;
       lx[i]=((r-24)*cos(rad*i))+sx;
       ly[i]=((r-24)*sin(rad*i))+sy;
       
       if(i%36==0){
       start[b]=i;
       b++; }

       if(i%18==0){
       start2[b3]=i;
       b3++;}

       if(i%6==0){
       startP[b2]=i;
       b2++;}
      }
    ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
    ledcAttachPin(4, pwmLedChannelTFT);
    ledcWrite(pwmLedChannelTFT, 500);
}


void loop() {

 angle=map(analogRead(12),0,4095,0,60);
 angle=angle*6;

 if(digitalRead(togB)==0)
 sound=0;
 else
 sound=1;

 if(digitalRead(togA)==0)
 tft.invertDisplay(false);
 else
 tft.invertDisplay(true);
 

 if(digitalRead(butB)==0)
 {
  digitalWrite(led,1);
  if(sound==1)
  tone(BUZZER_PIN, NOTE_B5, 160, BUZZER_CHANNEL);
  else delay(160);
  digitalWrite(led,0);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  switches[0]=!switches[0];
 }
 
 if(digitalRead(butA)==0)
 {
  digitalWrite(led,1);
  if(sound==1)
  tone(BUZZER_PIN, NOTE_C6, 160, BUZZER_CHANNEL);
  else delay(160);
  digitalWrite(led,0);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  switches[1]=!switches[1];
  }

   if(digitalRead(butC)==0)
 {
  digitalWrite(led,1);
  if(sound==1)
  tone(BUZZER_PIN, NOTE_G5, 160, BUZZER_CHANNEL);
  else delay(160);
  digitalWrite(led,0);
  noTone(BUZZER_PIN, BUZZER_CHANNEL);
  if(brightness<1000)
  brightness=brightness+100;
  ledcWrite(pwmLedChannelTFT, brightness);
  }

  if(digitalRead(butD)==0)
    {
    digitalWrite(led,1);
    if(sound==1)
    tone(BUZZER_PIN, NOTE_F5, 160, BUZZER_CHANNEL);
    else delay(160);
    digitalWrite(led,0);
    noTone(BUZZER_PIN, BUZZER_CHANNEL);
     if(brightness>=40)
   brightness=brightness-100;
   ledcWrite(pwmLedChannelTFT, brightness);
    }
  

  if(angle!=lastAngle)
  {
     lastAngle=angle;      
     VALUE=((angle-270)/3.60)*-1;
     if(VALUE<0)
     VALUE=VALUE+100;
  
  }
  draw();
 }

void draw()
{
 img.fillSprite(TFT_BLACK);
 img.fillCircle(sx,sy,r+9,color5);
    
    
    img.drawString("BRIGHTNESS",40,6,2);
    img.drawString("SOUND",20,45);
    img.setTextColor(color4,TFT_BLACK);
    img.drawString("CONTROL",120,4);
    img.setTextColor(color3,TFT_BLACK);
    img.setFreeFont(&Slackey_Regular_16);
    img.drawString("FAN",120,16);
    img.drawString(soundL[sound],17,58,2);
    img.setTextFont(0);
 
    img.drawRect(4,14,34,22,color2);
    img.drawString(String(brightness/10),21,25,2);

 for(int i=0;i<60;i++)
 if(startP[i]+angle<360)
 img.fillCircle(px[startP[i]+angle],py[startP[i]+angle],1,color2);
 else
 img.fillCircle(px[(startP[i]+angle)-360],py[(startP[i]+angle)-360],1,color2);
 
img.setFreeFont(&FreeSans9pt7b);

 for(int i=0;i<20;i++)
 if(start2[i]+angle<360)
 img.drawWedgeLine(px[start2[i]+angle],py[start2[i]+angle],px2[start2[i]+angle],py2[start2[i]+angle],2,2,TFT_ORANGE);
 else
 img.drawWedgeLine(px[(start2[i]+angle)-360],py[(start2[i]+angle)-360],px2[(start2[i]+angle)-360],py2[(start2[i]+angle)-360],1,1,TFT_ORANGE);
 
 img.setTextColor(TFT_WHITE,color5);
 for(int i=0;i<10;i++)
 if(start[i]+angle<360){
 img.drawString(cc[i],x[start[i]+angle],y[start[i]+angle]);
 //sprite.drawWedgeLine(x2[i*25],y2[i*25],px2[i*25],py2[i*25],1,1,0xCE59);
 img.drawWedgeLine(px[start[i]+angle],py[start[i]+angle],lx[start[i]+angle],ly[start[i]+angle],2,2,color1);
 
 }else
 {
 img.drawString(cc[i],x[(start[i]+angle)-360],y[(start[i]+angle)-360]);
 img.drawWedgeLine(px[(start[i]+angle)-360],py[(start[i]+angle)-360],lx[(start[i]+angle)-360],ly[(start[i]+angle)-360],1,1,color1);
 }

 img.setFreeFont(&DSEG7_Modern_Bold_20);
 img.drawString(String((int)VALUE),sx,122);
 img.setTextFont(0);
 img.drawString("POWER",sx,sy-76);
 img.drawString("%",sx+32,sy-54,4);

 img.setTextColor(TFT_WHITE,TFT_BLACK);
 img.drawString("SW1",182,12);
 img.drawString("SW2",182,30);



  for(int i=0;i<2;i++){
    img.drawCircle(202,11+(18*i),7,TFT_WHITE);
    img.drawCircle(222,11+(18*i),7,TFT_WHITE);
    img.drawLine(202,4+(18*i),222,4+(18*i),TFT_WHITE);
    img.drawLine(202,18+(18*i),222,18+(18*i),TFT_WHITE);
    img.fillRect(203,5+(18*i),18,13,TFT_BLACK);
    img.fillCircle(204+((int)switches[i]*16),11+(18*i),4,TFT_ORANGE); 
    }

 
 
 
 img.fillTriangle(sx,sy-100,sx-5,sy-86,sx+5,sy-86,TFT_ORANGE);
 img.pushSprite(0, 0);
}




