#include <SoftwareSerial.h>
#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>
#include <SD.h>
#include <SPI.h>

#define CS 4
TMRpcm aud;

SoftwareSerial mySerial(2,3);
int n=0,i=0;
File root;
String songs[20];
int choice;

void setup() {
  pinMode(5,OUTPUT);
  
  aud.speakerPin=9;
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  
  Serial.print("Initializing SD card...");

  if (!SD.begin(CS)) {
Serial.println("initialization failed!");
    return;

  }
  
  Serial.println("initialization done.");
  mySerial.begin(9600);
  root = SD.open("/");

  printDirectory(root);
  
  Serial.println("done!");
  Serial.println("The wav files in the SD card are : \n");

  
 for(int k=0;k<i;k++)
 {
    Serial.println(songs[k]);
    
  } 

playsong(n);

}

void loop() 
{
  

  digitalWrite(5,HIGH);
  if (mySerial.available()) {
    choice=mySerial.read();
    if(choice>100)
    choice=0;
    Serial.println(choice);
  }

  
  switch(choice)
  {
    case 1:
          choice=0;
          if(aud.isPlaying())
          aud.pause();
          else
          playsong(n);
          break;
    case 2:
          aud.stopPlayback();
          break;
    case 3:
          choice=0;
          n++;
          if(n>=i)
          n=0;
          playsong(n);
          break;
    case 4:
          choice=0;
          n--;
          if(n<=0)
          n=i-1;
          playsong(n);
          break;
     case 5:
          choice=0;
          aud.volume(1);
          break;
     case 6:
          choice=0;
          aud.volume(0);
          break;
     case 7:
          choice=0;
          aud.setVolume(0);
          break;
     }
}
 




void playsong (int sno)
{
  char sname[20];
  songs[sno].toCharArray(sname,20);
  aud.play(sname);
  
  
}




void printDirectory(File dir) {
  while (true) {

    File entry =  dir.openNextFile();
    
    if (! entry) {
     
      break;
    }
    if (entry.isDirectory()) {
      
      printDirectory(entry);
    } 
 
    Serial.println(entry.name());
    String entryname=entry.name();
  if(entryname.endsWith(".WAV"))
  {
    songs[i]=entryname;
    i++;
  }
    entry.close();
  }
}
