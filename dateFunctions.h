




//prin("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
//prin("numberRele", numberRele);
//prin("numberDataTime", numberDataTime);
//prin("dataAndTime[numberRele].data_datamiliseconds[numberDataTime]", dataAndTime[numberRele].data_datamiliseconds[numberDataTime]);
//prin("getDate.epochTime", getDate.epochTime);
//prin("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");

//boolean controlRangeDate(byte numberRele, byte numberDataTime) {
//  if(dataAndTime[numberRele].data_datamiliseconds[numberDataTime] <= (getDate.epochTime) && dataAndTime[numberRele].data_datamiliseconds[numberDataTime + 1] >= (getDate.epochTime)){
//    return true; 
//  }  else {
//    return false;
//  }
//}
//******************************************************************************


//void deleteAndMovingSection(byte numberRele) {
//  for (byte x = 0; x < 9; x += 2) {
//    if (dataAndTime[numberRele].data_datamiliseconds[x + 1] < (getDate.epochTime)) { //Якщо  елемент з датою  простроченo
//      deleteOldDate(numberRele, x);//Видаляємо прострочену секцію
//      for (byte startSection = x + 2; startSection < 9; startSection += 2 ) {
//        //        Serial.print("data_datamiliseconds:<><><><><><><> ");
//        //        Serial.println(startSection);
//        //        Serial.println(startSection - 2);
//        movingSection(numberRele,  startSection,  startSection - 2);
//      }
//      deleteOldDate(numberRele, 8);//Видаляємо останню секцію
//      EEPROM.put(START_SECTION_EEPROM_TIMERDATE + (sizeof(timerDate)*numberRele), dataAndTime[numberRele]); //write objeck to EEPROM
//      Eeprom::comitEprom();
//      x -= 2; //Повторно перевіряємо ту саму мекцію адже на її місце приїхали нові дані
//      //      client.publish(nameUser+"_out-web-rele-data-time", objectToJsonDate(numberRele));
//    }
//  }
//}

//void deleteOldDate(byte numberRele, byte numberDataTime) {
//  //  Serial.print("delete the old date:");
//  dataAndTime[numberRele].data_datamiliseconds[numberDataTime] = 4294967295;
//  dataAndTime[numberRele].data_datamiliseconds[numberDataTime + 1] = 4294967295;
//  dataAndTime[numberRele].data_rik[numberDataTime] = 65535;
//  dataAndTime[numberRele].data_rik[numberDataTime + 1] = 65535;
//  dataAndTime[numberRele].data_months[numberDataTime] = 99;
//  dataAndTime[numberRele].data_months[numberDataTime + 1] = 99;
//  dataAndTime[numberRele].data_dey[numberDataTime] = 99;
//  dataAndTime[numberRele].data_dey[numberDataTime + 1] = 99;
//  dataAndTime[numberRele].data_godyna[numberDataTime] = 99;
//  dataAndTime[numberRele].data_godyna[numberDataTime + 1] = 99;
//  dataAndTime[numberRele].data_minut[numberDataTime] = 99;
//  dataAndTime[numberRele].data_minut[numberDataTime + 1] = 99;
//  dataAndTime[numberRele].data_daywikend[numberDataTime] = 99;
//  dataAndTime[numberRele].data_daywikend[numberDataTime + 1] = 99;
//
//  for (byte i = 0; i < 10; i++ ) {
//    dataAndTime[numberRele].godyna[numberDataTime * 5 + i] = 99;
//    dataAndTime[numberRele].minut[numberDataTime * 5 + i] = 99;
//    if (i < 7)dataAndTime[numberRele].dey[numberDataTime * 5 + i] = 0;
//  }
//}

//void movingSection(byte numberRele, byte numberSectionStart, byte numberSectionEnd) {
//  //  Serial.println("movingSection:");
//  dataAndTime[numberRele].data_datamiliseconds[numberSectionEnd] = dataAndTime[numberRele].data_datamiliseconds[numberSectionStart];
//  dataAndTime[numberRele].data_datamiliseconds[numberSectionEnd + 1] = dataAndTime[numberRele].data_datamiliseconds[numberSectionStart + 1];
//  dataAndTime[numberRele].data_rik[numberSectionEnd] =  dataAndTime[numberRele].data_rik[numberSectionStart];
//  dataAndTime[numberRele].data_rik[numberSectionEnd + 1] = dataAndTime[numberRele].data_rik[numberSectionStart + 1];
//  dataAndTime[numberRele].data_months[numberSectionEnd] = dataAndTime[numberRele].data_months[numberSectionStart];
//  dataAndTime[numberRele].data_months[numberSectionEnd + 1] = dataAndTime[numberRele].data_months[numberSectionStart + 1];
//  dataAndTime[numberRele].data_dey[numberSectionEnd] = dataAndTime[numberRele].data_dey[numberSectionStart];
//  dataAndTime[numberRele].data_dey[numberSectionEnd + 1] = dataAndTime[numberRele].data_dey[numberSectionStart + 1];
//  dataAndTime[numberRele].data_godyna[numberSectionEnd] = dataAndTime[numberRele].data_godyna[numberSectionStart];
//  dataAndTime[numberRele].data_godyna[numberSectionEnd + 1] = dataAndTime[numberRele].data_godyna[numberSectionStart + 1];
//  dataAndTime[numberRele].data_minut[numberSectionEnd] = dataAndTime[numberRele].data_minut[numberSectionStart] ;
//  dataAndTime[numberRele].data_minut[numberSectionEnd + 1] = dataAndTime[numberRele].data_minut[numberSectionStart + 1];
//  dataAndTime[numberRele].data_daywikend[numberSectionEnd] = dataAndTime[numberRele].data_daywikend[numberSectionStart];
//  dataAndTime[numberRele].data_daywikend[numberSectionEnd + 1] = dataAndTime[numberRele].data_daywikend[numberSectionStart + 1];
//
//  for (byte i = 0; i < 10; i++ ) {
//    dataAndTime[numberRele].godyna[numberSectionEnd * 5 + i] = dataAndTime[numberRele].godyna[numberSectionStart * 5 + i];
//    dataAndTime[numberRele].minut[numberSectionEnd * 5 + i] = dataAndTime[numberRele].minut[numberSectionStart * 5 + i];
//    if (i < 7)dataAndTime[numberRele].dey[numberSectionEnd * 5 + i] = dataAndTime[numberRele].dey[numberSectionStart * 5 + i];
//  }
//}
