

class GetDate {
  public:
    //Week Days
    String weekDays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    //Month names
    String months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    time_t epochTime;
    String formattedTime;
    int currentHour;
    int currentMinute;
    int currentSecond;
    int weekDayNumber;
    String weekDay;
    int monthDay;
    int currentMonth;
    String currentMonthName;
    int currentYear;
    String currentDate;


    static  void getDateTime(GetDate getDate) {
      timeClient.update();
      //
      //  Serial.println();
      //  Serial.println("------------------------------");

      getDate.epochTime = timeClient.getEpochTime() - 7196;
      getDate.formattedTime = timeClient.getFormattedTime();
      getDate.currentHour = timeClient.getHours();
      getDate.currentMinute = timeClient.getMinutes();
      getDate.currentSecond = timeClient.getSeconds();
      getDate.weekDayNumber = timeClient.getDay();
      getDate.weekDay = getDate.weekDays[getDate.weekDayNumber];
      //Get a time structure
      struct tm *ptm = gmtime ((time_t *)&getDate.epochTime);
      getDate.monthDay = ptm->tm_mday;
      getDate.currentMonth = ptm->tm_mon + 1;
      getDate.currentMonthName = getDate.months[getDate.currentMonth - 1];
      getDate.currentYear = ptm->tm_year + 1900;
      //Print complete date:
      getDate.currentDate = String(getDate.currentYear) + "-" + String(getDate.currentMonth) + "-" + String(getDate.monthDay);

      //    Serial.print("Epoch Time: ");
      //    Serial.println(getDate.epochTime);
      //    Serial.print("Formatted Time: ");
      //    Serial.println(getDate.formattedTime);
      //    Serial.print("Hour: ");
      //    Serial.println(getDate.currentHour);
      //    Serial.print("Minutes: ");
      //    Serial.println(getDate.currentMinute);
      //    Serial.print("Seconds: ");
      //    Serial.println(getDate.currentSecond);
      //    Serial.print("Week Day Number: ");
      //    Serial.println(getDate.weekDayNumber);
      //    Serial.print("Week Day: ");
      //    Serial.println(getDate.weekDay);
      //    Serial.print("Month day: ");
      //    Serial.println(getDate.monthDay);
      //    Serial.print("Month: ");
      //    Serial.println(getDate.currentMonth);
      //    Serial.print("Month name: ");
      //    Serial.println(getDate.currentMonthName);
      //    Serial.print("Year: ");
      //    Serial.println(getDate.currentYear);
      //    Serial.print("Current date: ");
      //    Serial.println(getDate.currentDate);

      //    Serial.println("------------------------------");
      //    Serial.println();
    }
//*****************************************************************************


//******************************************************************************
static byte controlRangeHour(GetDate getDate, byte numberRele, byte numberDataTime) {

  boolean  SubTimersFlagSections[5];//флаги для годин в секції
  for (byte numberTime = 0; numberTime < 9; numberTime += 2  ) { //numberTime 0 2 4 6 8) {//провіряємо в секії всі години і для кожної ставимо флаг
    word tempGod_0 = dataAndTime[numberRele].godyna[numberTime + numberDataTime * 5];
    word tempGod_1 = dataAndTime[numberRele].godyna[numberTime + numberDataTime * 5 + 1];
    word tempMinute_0 = dataAndTime[numberRele].minut[numberTime + numberDataTime * 5];
    word tempMinute_1 = dataAndTime[numberRele].minut[numberTime + numberDataTime * 5 + 1];
    word tempGodStart = tempGod_0 * 60 + tempMinute_0;
    word tempGodStop = tempGod_1 * 60 + tempMinute_1;
    word tempCurentGod = getDate.currentHour * 60 + getDate.currentMinute;

    if (tempGodStart <= tempCurentGod  &&  tempGodStop > tempCurentGod)
    {
      digitalWrite(releControl[numberRele].numberPin, ChangeLow);
      SubTimersFlagSections[numberTime / 2] = true;
    } else {
      digitalWrite(releControl[numberRele].numberPin, ChangeHIGH);
      SubTimersFlagSections[numberTime / 2] = false;
    }
  }

  //   0 2 4 6 8   0-6   7-13   14-20    21-27   28 - 34
  //   0 1 2 3 4
  //   1 2 3 4 5
  //getDate.weekDay
  //dataAndTime[numberRele].dey[]
  boolean flagDey;
  int tempweekDayNumber = getDate.weekDayNumber - 1;

  if (tempweekDayNumber == -1)tempweekDayNumber = 6;

  if (dataAndTime[numberRele].dey[tempweekDayNumber + numberDataTime / 2 * 7] == 1) {
    flagDey = true;
//    Serial.println("flagDey --true");
  } else {
    flagDey = false;
  }

  //Провіряємо флаги всіх годин даної секції і якщо хощаб одина дорівнює true то  timersFlagSections = true
  if ((SubTimersFlagSections[0] || SubTimersFlagSections[1] || SubTimersFlagSections[2] || SubTimersFlagSections[3] || SubTimersFlagSections[4]) && flagDey ) {
    return  1;
  } else {
    return  0;
  }
}




//*****************************************************************************
};

GetDate getDate;
