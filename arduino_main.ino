#include <virtuabotixRTC.h>

virtuabotixRTC myRTC(6, 7, 8);

int RELAYPIN   = 4;
int RESETPIN   = 13;
int state = 0;

//variable to tell if we are watering at the moment
bool isWatering = false;

//set the time to water plants
// String wateringTime = "540,960, ";
int wateringTime[2] = {540, 1409};
int WATER_DURATION = 10;

void setup() {
  Serial.begin(9600);
  // Set the current date, and time in the following format:
 // seconds, minutes, hours, day of the week, day of the month, month, year
 myRTC.setDS1302Time(15, 59, 8, 7, 8, 59, 2022); //Here you write your actual time/date as shown above 
 //but remember to "comment/remove" this function once you're done
 //The setup is done only one time and the module will continue counting it automatically

// Set the relay
 pinMode(RELAYPIN, OUTPUT);
 pinMode(RESETPIN, INPUT);
}

void loop() {
  myRTC.updateTime();
 
  // Start printing elements as individuals
  Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth); //You can switch between day and month if you're using American system
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print(" ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);

  if((isWatering == false) && isTimetoWater())
  {
    // Time to start watering
    state = 1;
    isWatering = true;
  }
  else if((isWatering) && !isTimetoWater())
  {
      state = 0;
      isWatering = false;
  }
  // else
  // {
  //   state = 0;
  //   //TODO: Optimize the sleep based on when to wake up next
  //   //delay(1000);
  // }
 
  if(0 == state)
  {
    
    digitalWrite(RELAYPIN, LOW);
  }
  else if(1 == state)
  {
    Serial.println("WATERING");
    digitalWrite(RELAYPIN, HIGH);
  }
  // Delay so the program doesn't print non-stop
  delay(10000);

}
bool isTimetoWater(void)
{
  bool switchOn = false;
  int curr_time = myRTC.hours * 60 + myRTC.minutes;
  int onTime = 0;
  for( int i = 0; i < 2; i++)
  {
    onTime = wateringTime[i];
    Serial.print("|Debug| onTime ");
    Serial.println(onTime);
    switchOn = (curr_time >= onTime) && (curr_time < onTime+WATER_DURATION);
    if(switchOn)
    {
      Serial.print("|Debug| SwitchOn: ");
      Serial.println(switchOn);
      break;
    }
  }
  return(switchOn); 
}
// bool isTimetoWater(void)
// {
//   bool switchOn = false;
//   int curr_time = myRTC.hours * 60 + myRTC.minutes;
//   char* token;
//   token = strtok((char *)wateringTime.c_str(), ',');
//   Serial.println(token);
//   while(token!= NULL)
//   {
//     token = strtok(NULL, ',');
//     Serial.println(token);
//     int onTime = atoi(token);
//     Serial.print("|Debug| onTime ");
//     Serial.println(onTime);
//     switchOn = (curr_time > onTime) && (curr_time < onTime+WATER_DURATION);
//     if(switchOn)
//     {
//       Serial.print("|Debug| SwitchOn: ");
//       Serial.println(switchOn);
//       break;
//     }

    
//   }
//   return(switchOn); 
// }
