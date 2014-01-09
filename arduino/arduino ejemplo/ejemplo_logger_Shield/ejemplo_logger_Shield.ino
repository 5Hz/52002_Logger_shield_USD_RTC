/******************************************************************
** Código creado en Electrónica 5Hz                              **
** www.5hz-electronica.com                                       **
** Por: Rafael Almaguer                                          **
**                                                               **
** Descripción del código:                                       **
**                                                               **
** Ejemplo para el Logger Shield:                                **
** Este programa lee la hora actual del RTC y la almacena en     **
** la memoria uSD cada vez que se corre el programa, tambien     **
** imprime la hora guardada en el puerto Serial.                 **
** (Se guarda en un archivo llamado LOGTEST.txt, si no existe    **
** primero lo crea y despues escribe en el).                     **
**                                                               **
*******************************************************************
Conexiones:
UNO   Logger Shield

10    Chip Select (memoria uSD)
11    MOSI (master Out - Slave In)
12    MISO (master In - Slave Out)
13    SCK (serial Clock)
A4    SDA         (RTC)
A5    SCL         (RTC)
*/

#include <SD.h> //requerido para escribir en la memoria SD
#include <Wire.h> //requerido para comunicarse con RTC

//Definiciones de registros del RTC
#define DS1307      0xD0 >> 1
#define R_SECS      0
#define R_MINS      1
#define R_HRS       2
#define R_WKDAY     3
#define R_DATE      4
#define R_MONTH     5
#define R_YEAR      6
#define R_SQW       7

//definiciones de configuracion de funcion printHour()
#define SER 0 //imprime en puerto Serial
#define STR 1 //guarda en String y regresa el valor al programa principal

int entrada;
int opcion = 0;

byte second = 0x00;    // default a 01 JAN 2007, midnight
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
  Wire.begin(); //inicializa comunicacion I2C
  Serial.begin(9600); //Inicializa comunicacion serial
  
  // asegurarse que el pin chip select esté configurado 
  // como salida, aunque no se utilice:
  pinMode(10, OUTPUT);
  
  // checa si hay una tarjeta y si puede inicializarse:
  if (!SD.begin(chipSelect)) {
    Serial.println("Error en SD");
    return;
  }
  Serial.println("SD inicializada");
  getClock(); //lee la hora del RTC
  FilePrintHour(); //Escribe la hora en la memoria uSD
}

void loop(){} //No se hace nada en el loop

//*************************************************************************************

void getClock()
{
  Wire.beginTransmission(DS1307);
  Wire.write(R_SECS);
  Wire.endTransmission();
  Wire.requestFrom(DS1307, 8);
  do{}while(Wire.available()<8);
  second = Wire.read();
  minute = Wire.read();
  hour   = Wire.read();
  wkDay  = Wire.read();
  day    = Wire.read();
  month  = Wire.read();
  year   = Wire.read();
  ctrl   = Wire.read();
  
}

//*************************************************************************************

void FilePrintHour()
{
  String dataString = printHour(STR);
  File dataFile = SD.open("LogTest.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.print("Se escribio en la SD: ");
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error abriendo LogTest.txt");
  } 
}

//*************************************************************************************

String printHour(int sink)
{
  String hora = "";
  if(sink == SER)
  {
    printHex2(hour, SER);
    Serial.print(":");
    printHex2(minute, SER);
    Serial.print(":");
    printHex2(second, SER);
  
    Serial.print("  ");
    printDayName(bcd2Dec(wkDay), SER);
    Serial.print("  ");
  
    printHex2(day, SER);
    Serial.print(" ");
    printMonthName(bcd2Dec(month), SER);
    Serial.print(" 20");
    printHex2(year, SER);
    Serial.println();
  }
  else if(sink == STR)
  {
    hora += printHex2(hour, STR);
    hora += ":";
    hora += printHex2(minute, STR);
    hora += ":";
    hora += printHex2(second, STR);
  
    hora += "  ";
    hora += printDayName(bcd2Dec(wkDay), STR);
    hora += "  ";
  
    hora += printHex2(day, STR);
    hora += "  ";
    hora += printMonthName(bcd2Dec(month), STR);
    hora += " 20";
    hora += printHex2(year, STR);
  }
    return hora;
}

//*************************************************************************************

String printHex2(byte hexVal, int sink)
{
  String hexString = "";
  if(sink == SER)
  {
    if (hexVal < 0x10)
      Serial.print("0");
    Serial.print(hexVal, HEX);
  }
  else if(sink == STR)
  {
    if (hexVal < 0x10)
      hexString += '0';
    hexString += String(hexVal, HEX);
  }
  return hexString;
}

//*************************************************************************************

String printMonthName(byte m, int sink)
{
  String mes = "";
  switch (m) {
  case 1:
    mes = "JAN";
    break;
  case 2:
    mes = "FEB";
    break;
  case 3:
    mes = "MAR";
    break;
  case 4:
    mes = "APR";
    break;
  case 5:
    mes = "MAY";
    break;
  case 6:
    mes = "JUN";
    break;
  case 7:
    mes = "JUL";
    break;
  case 8:
    mes = "AUG";
    break;
  case 9:
    mes = "SEP";
    break;
  case 10:
    mes = "OCT";
    break;
  case 11:
    mes = "NOV";
    break;
  case 12:
    mes = "DEC";
    break;
  default:
    mes = "???";
  }
  if(sink == SER)
    Serial.print(mes);
  return mes;
}

//*************************************************************************************

String printDayName(byte d, int sink)
{
  String dia = "";
  switch (d) {
  case 1:
    dia = "SUN";
    break;
  case 2:
    dia = "MON";
    break;
  case 3:
    dia = "TUE";
    break;
  case 4:
    dia = "WED";
    break;
  case 5:
    dia = "THU";
    break;
  case 6:
    dia = "FRI";
    break;
  case 7:
    dia = "SAT";
    break;
  default:
    dia = "???";
  }
  if(sink == SER)
    Serial.print(dia);
  return dia;
}

//*************************************************************************************

byte bcd2Dec(byte bcdVal)
{
  return bcdVal / 16 * 10 + bcdVal % 16;
}

//*************************************************************************************
