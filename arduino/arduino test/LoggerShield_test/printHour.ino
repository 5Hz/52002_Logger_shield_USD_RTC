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

byte bcd2Dec(byte bcdVal)
{
  return bcdVal / 16 * 10 + bcdVal % 16;
}
