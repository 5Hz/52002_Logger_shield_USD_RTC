#include <SD.h>
#include <Wire.h>
#include <avr/pgmspace.h>
extern "C" { 
#include "utility/twi.h"  // from Wire library, so we can do bus scanning
}

#define DS1307      0xD0 >> 1
#define R_SECS      0
#define R_MINS      1
#define R_HRS       2
#define R_WKDAY     3
#define R_DATE      4
#define R_MONTH     5
#define R_YEAR      6
#define R_SQW       7

#define SER 0
#define STR 1

int entrada;
int opcion = 0;

byte second = 0x00;                             // default to 01 JAN 2007, midnight
byte minute = 0x06;
byte hour =   0x12;
byte wkDay =  0x06;
byte day =    0x27;
byte month =  0x01;
byte year =   0x12;
byte ctrl =   0x10;

const int chipSelect = 10;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; // espera que se conecte el puerto serial. Se necesita sólo para el arduino Leonardo.
   }
   
//  Serial.print("memoria: ");
//  Serial.println(availableMemory());
  // asegurarse que el pin chip select esté configurado 
  // como salida, aunque no se utilice:
  pinMode(10, OUTPUT);
  
  // checa si hay una tarjeta y si puede inicializarse:
  if (!SD.begin(chipSelect)) {
    Serial.println("Error en SD");
    return;
  }
  Serial.println("SD inicializada");
  menu();
}

void loop()
{
  delay(1000);
    if (opcion == 2)  // indica que se seleccionó una opción válida
      getClock();
  else
    menu();
  if (Serial.available()){
    entrada=Serial.read();
    if(entrada=='*'){
      menu();
    }    
  }
}

void menu(){
  int entradaMenu;
  Serial.println("MENU PRINCIPAL:");
  Serial.println("1-Escanear I2C");
  Serial.println("2-Get clock (Serial + SD)");
  Serial.println("3-Set clock");
  
  do{
  }while(Serial.available()==0);
      entradaMenu=Serial.read();
    switch(entradaMenu){
   
    case '1':
      Serial.println("");
      Serial.println("I2C Scan");
      delay(1000);
      StartScan();
      opcion = 1;
      break;
      
    case '2':
      Serial.println("");
      Serial.println("Get Clock");
      getClock();
      delay(1000);
      opcion = 2;
      break;

    case '3':
      Serial.println("");
      Serial.println("Set Clock");
      setClock();
      getClock();
      opcion = 3;
      break;

    default:
      Serial.println("opcion no existe...");
      opcion = 0;
      break;
    }
    
    if (opcion == 1)
    Serial.println("presiona * para ir al menu");

}

//int availableMemory() {
//  int size = 2048; // Use 2048 with ATmega328
//  byte *buf;
//
//  while ((buf = (byte *) malloc(--size)) == NULL);
//
//  free(buf);
//
//  return size;
//}

