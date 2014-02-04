String powerStatus1       = "off";
String powerStatus2       = "off";
String powerStatus3       = "off";
String lowBeamStatus1     = "off";
String lowBeamStatus2     = "off";
String lowBeamStatus3     = "off";
String highBeamStatus1    = "off";
String highBeamStatus2    = "off";
String highBeamStatus3    = "off";
String dayNightStatus1    = "off";
String dayNightStatus2    = "off";
String dayNightStatus3    = "off";
String manualOff1         = "on";
String manualOff2         = "on";
String manualOff3         = "on";


int io_jumper_illuminator1=32;
int io_power1             =45;
int io_in21               =49;
int io_in11               =51;
int io_day_night1         =47;

int io_jumper_illuminator2=28;
int io_power2             =35;
int io_in22               =39;
int io_in12               =41;
int io_day_night2         =37;

int io_jumper_illuminator3=24;
int io_power3             =25;
int io_in13               =31;
int io_in23               =29;
int io_day_night3         =27;


int pinInArrary[]= {io_jumper_illuminator1,io_jumper_illuminator2,io_jumper_illuminator3,io_power1,io_power2,io_power3}; 
int pinOutArrary[]={io_in21,io_in11,io_in22,io_in12,io_in13,io_in23}; 

void initPins()
{
      // set default pin modes
    for(int i=0;i<sizeof(pinInArrary)/sizeof(int);i++){
      pinMode(pinInArrary[i], INPUT_PULLUP);
    }

   for(int i=0;i<sizeof(pinOutArrary)/sizeof(int);i++){
      pinMode(pinOutArrary[i], OUTPUT);
      digitalWrite(pinOutArrary[i], HIGH);
    }
    pinMode(io_day_night1, OUTPUT);
    pinMode(io_day_night2, OUTPUT);
    pinMode(io_day_night3, OUTPUT);
    digitalWrite(io_day_night1,LOW);
    digitalWrite(io_day_night2,LOW);
    digitalWrite(io_day_night3,LOW);


}

void turnDLOn(int _dl){
  digitalWrite(_dl, LOW);
}
void turnDLOff(int _dl){
  digitalWrite(_dl, HIGH);
}

void setManualOff1(){
  digitalWrite(io_in11,HIGH);
  digitalWrite(io_in21,HIGH);
  manualOff1      = "on";
  lowBeamStatus1  = "off";
  highBeamStatus1 = "off";
}
void setManualOff2(){
  digitalWrite(io_in12,HIGH);
  digitalWrite(io_in22,HIGH);
  manualOff2      = "on";
  lowBeamStatus2  = "off";
  highBeamStatus2 = "off";
}
void setManualOff3(){
  digitalWrite(io_in13,HIGH);
  digitalWrite(io_in23,HIGH);
  manualOff3      = "on";
  lowBeamStatus3  = "off";
  highBeamStatus3 = "off";
}


void setLowBeam1(){
  digitalWrite(io_in11,LOW);
  digitalWrite(io_in21,HIGH);
  manualOff1      = "off";
  lowBeamStatus1  = "on";
  highBeamStatus1 = "off";
}
void setLowBeam2(){
  digitalWrite(io_in12,LOW);
  digitalWrite(io_in22,HIGH);
  manualOff2 = "off";
  lowBeamStatus2  = "on";
  highBeamStatus2 = "off";
}
void setLowBeam3(){
  digitalWrite(io_in13,LOW);
  digitalWrite(io_in23,HIGH);
  manualOff3 = "off";
  lowBeamStatus3  = "on";
  highBeamStatus3 = "off";
}

void setHighBeam1(){
  digitalWrite(io_in11,LOW);
  digitalWrite(io_in21,LOW);
  manualOff1      = "off";
  lowBeamStatus1 = "off";
  highBeamStatus1 = "on";
}
void setHighBeam2(){
  digitalWrite(io_in12,LOW);
  digitalWrite(io_in22,LOW);
  manualOff2      = "off";
  lowBeamStatus2  = "off";
  highBeamStatus2 = "on";
}
void setHighBeam3(){
  digitalWrite(io_in13,LOW);
  digitalWrite(io_in23,LOW);
  manualOff3      = "off";
  lowBeamStatus3  = "off";
  highBeamStatus3 = "on";
}



// checks if received HTTP request is switching on/off LEDs
// also saves the state of the LEDs
void SetDLs(void)
{
  Serial.println(HTTP_req);
  
  if (digitalRead(io_power1)){
    powerStatus1="off";
  }else{powerStatus1="on";}

  if (StrContains(HTTP_req, "manualOff1=1")){
    setManualOff1();
  }else if (StrContains(HTTP_req, "lowBeam1=1")){
    setLowBeam1();
  }else if (StrContains(HTTP_req, "highBeam1=1")){
    setHighBeam1();
  }else if (StrContains(HTTP_req, "dayNight1=1")){
    digitalWrite(io_day_night1,HIGH);
    dayNightStatus1 = "on";
  }else if (StrContains(HTTP_req, "dayNight1=0")){
    digitalWrite(io_day_night1,LOW);
    dayNightStatus1 = "off";
  }
  
  
  if (digitalRead(io_power2)){
    powerStatus2="off";
  }else{powerStatus2="on";}
  
  if (StrContains(HTTP_req, "manualOff2=1")){
    setManualOff2();
  }else if (StrContains(HTTP_req, "lowBeam2=1")){
    setLowBeam2();
  }else if (StrContains(HTTP_req, "highBeam2=1")){
    setHighBeam2();
  }else if (StrContains(HTTP_req, "dayNight2=1")){
    digitalWrite(io_day_night2,HIGH);
    dayNightStatus2 = "on";
  }else if (StrContains(HTTP_req, "dayNight2=0")){
    digitalWrite(io_day_night2,LOW);
    dayNightStatus2 = "off";
  }
  

  if (digitalRead(io_power3)){
    powerStatus3="off";
  }else{powerStatus3="on";}
  
  if (StrContains(HTTP_req, "manualOff3=1")){
    setManualOff3();
  }else if (StrContains(HTTP_req, "lowBeam3=1")){
    setLowBeam3();
  }else if (StrContains(HTTP_req, "highBeam3=1")){
    setHighBeam3();
  }else if (StrContains(HTTP_req, "dayNight3=1")){
    digitalWrite(io_day_night3,HIGH);
    dayNightStatus3 = "on";
  }else if (StrContains(HTTP_req, "dayNight3=0")){
    digitalWrite(io_day_night3,LOW);
    dayNightStatus3 = "off";
  }
  
}

// send the XML file DATA status
void XML_response(EthernetClient cl)
{
    cl.println("<?xml version = \"1.0\" ?>");
    cl.println("<outputs>");

    cl.print("<manualOff>");
      cl.print(manualOff1);
    cl.println("</manualOff>");
    cl.print("<manualOff>");
      cl.print(manualOff2);
    cl.println("</manualOff>");
    cl.print("<manualOff>");
      cl.print(manualOff3);
    cl.println("</manualOff>");
cl.println(" ");
    cl.print("<powerStatus>");
      cl.print(powerStatus1);
    cl.println("</powerStatus>");
    cl.print("<powerStatus>");
      cl.print(powerStatus2);
    cl.println("</powerStatus>");
    cl.print("<powerStatus>");
      cl.print(powerStatus3);
    cl.println("</powerStatus>");
cl.println(" ");
    cl.print("<lowBeamStatus>");
      cl.print(lowBeamStatus1);
    cl.println("</lowBeamStatus>");
    cl.print("<lowBeamStatus>");
      cl.print(lowBeamStatus2);
    cl.println("</lowBeamStatus>");
    cl.print("<lowBeamStatus>");
      cl.print(lowBeamStatus3);
    cl.println("</lowBeamStatus>");
cl.println(" ");
    cl.print("<highBeamStatus>");
      cl.print(highBeamStatus1);
    cl.println("</highBeamStatus>");
    cl.print("<highBeamStatus>");
      cl.print(highBeamStatus2);
    cl.println("</highBeamStatus>");
    cl.print("<highBeamStatus>");
      cl.print(highBeamStatus3);
    cl.println("</highBeamStatus>");
cl.println(" ");
    cl.print("<dayNightStatus>");
      cl.print(dayNightStatus1);
    cl.println("</dayNightStatus>");
    cl.print("<dayNightStatus>");
      cl.print(dayNightStatus2);
    cl.println("</dayNightStatus>");
    cl.print("<dayNightStatus>");
      cl.print(dayNightStatus3);
    cl.println("</dayNightStatus>");
    
    cl.println("</outputs>");
}

// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++) {
        str[i] = 0;
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }

    return 0;
}
