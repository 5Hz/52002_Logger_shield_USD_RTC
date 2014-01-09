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
  
  FilePrintHour();
}

void FilePrintHour()
{
  String dataString = printHour(STR);
  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.print("Se escribio en la SD: ");
    Serial.println(dataString);
  }  
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  } 
}
