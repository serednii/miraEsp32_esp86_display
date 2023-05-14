 




//*************************************************************************************************************************************************

  //*************************************************************************************************************************************************










  //{"NUMPACKAGE":1,"NUM":0, "DELAYSECONDSTART":0, "DATATIME":["2023-05-13T14:36", "2023-05-18T14:36", "65535-99-99T99:99", "65535-99-99T99:99", "65535-99-99T99:99", "65535-99-99T99:99", "65535-99-99T99:99", "65535-99-99T99:99", "65535-99-99T99:99", "65535-99-99T99:99"]}
  //{"NUMPACKAGE":1,"NUM":0,"DELAYSECONDSTART":"0","DATATIME":["2023-5-13T14:36","2023-5-18T14:36","65535-99-99T99:99","65535-99-99T99:99","65535-99-99T99:99","65535-99-99T99:99","65535-99-99T99:99","65535-99-99T99:99","65535-99-99T99:99","65535-99-99T99:99"]}
 


  //
  //String objectToJsonDate(byte num, byte numberPackege) {
  //  String output;
  //
  //  output = "{";
  //  output += "\"NUMPACKAGE\":";
  //  output += String(numberPackege);
  //  output +=  ", ";
  //  const word NumberElementDate = 10;
  //
  //  if (numberPackege == 1) {
  //    output += "\"NUM\":";
  //    output += String(num);
  //    output +=  ", ";
  //    output +=   "\"DELAYSECONDSTART\":";
  //    output += String(dataAndTime[num].delaySecondStart);
  //    output +=  ", ";
  //    output +=   "\"DATATIME\":";
  //    output +=  "[";
  //    for (int k = 0; k < NumberElementDate; k++) {
  //      output += "\"";
  //      output += String(dataAndTime[num].data_rik[k]);
  //      output += "-";
  //      if (dataAndTime[num].data_months[k] > 9)output += String(dataAndTime[num].data_months[k]);
  //      else {
  //        output += "0";
  //        output += String(dataAndTime[num].data_months[k]);
  //      }
  //      output += "-";
  //      if (dataAndTime[num].data_dey[k] > 9)output += String(dataAndTime[num].data_dey[k]);
  //      else {
  //        output += "0";
  //        output += String(dataAndTime[num].data_dey[k]);
  //      }
  //      output += "T";
  //      if (dataAndTime[num].data_godyna[k] > 9)output += String(dataAndTime[num].data_godyna[k]);
  //      else {
  //        output += "0";
  //        output += String(dataAndTime[num].data_godyna[k]);
  //      }
  //      output += ":";
  //      if (dataAndTime[num].data_minut[k] > 9)output += String(dataAndTime[num].data_minut[k]);
  //      else {
  //        output += "0";
  //        output += String(dataAndTime[num].data_minut[k]);
  //      }
  //      output += "\"";
  //      if (k < NumberElementDate - 1)output +=  ", ";
  //    }
  //    output +=  "]";
  //    //"data_":"2022-5-16 12:30",
  //
  //    //  output +=  ", ";
  //  }
  //
  //  if (numberPackege == 2) {
  //    output +=   "\"TIME\":";
  //    output +=  "[";
  //    const word NumberElementTime = 25;
  //    for (int k = 0; k < NumberElementTime; k++) {
  //      output += "\"";
  //      if (dataAndTime[num].godyna[k] > 9)output += String(dataAndTime[num].godyna[k]);
  //      else {
  //        output += "0";
  //        output += String(dataAndTime[num].godyna[k]);
  //      }
  //      output += ":";
  //      if (dataAndTime[num].minut[k] > 9)output += String(dataAndTime[num].minut[k]);
  //      else {
  //        output += "0";
  //        output += String(dataAndTime[num].minut[k]);
  //      }
  //      output += "\"";
  //      if (k < NumberElementTime - 1)output +=  ", ";
  //    }
  //    output +=  "]";
  //    //  output +=  ", ";
  //  }
  //
  //  if (numberPackege == 3) {
  //    output +=   "\"TIME\":";
  //    output +=  "[";
  //    const word NumberElementTime = 50;
  //    for (int k = 25; k < NumberElementTime; k++) {
  //      output += "\"";
  //      if (dataAndTime[num].godyna[k] > 9)output += String(dataAndTime[num].godyna[k]);
  //      else {
  //        output += "0";
  //        output += String(dataAndTime[num].godyna[k]);
  //      }
  //      output += ":";
  //      if (dataAndTime[num].minut[k] > 9)output += String(dataAndTime[num].minut[k]);
  //      else {
  //        output += "0";
  //        output += String(dataAndTime[num].minut[k]);
  //      }
  //      output += "\"";
  //      if (k < NumberElementTime - 1)output +=  ", ";
  //    }
  //    output +=  "]";
  //    //  output +=  ", ";
  //  }
  //
  //  if (numberPackege == 4) {
  //    output +=   "\"DEY\":";
  //    output +=  "[";
  //    const word NumberElementDay = 35;
  //    for (int k = 0; k < NumberElementDay; k++) {
  //      output += String(dataAndTime[num].dey[k]);
  //      if (k < NumberElementDay - 1)output +=  ", ";
  //    }
  //    output +=  "]";
  //  }
  //
  //  output += "}";
  //
  //  prin("OUTPUT LENGTH", output.length());
  //  prin("OUTPUT LENGTH", output);
  //  return output;
  //}

  //*************************************************************************************************************************************************
