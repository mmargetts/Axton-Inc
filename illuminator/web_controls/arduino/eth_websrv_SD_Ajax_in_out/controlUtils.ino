String powerState       = "off";
String degree10State    = "off";
String degree30State    = "off";
String degree45State    = "off";
String degree60State    = "off";
String degree130State   = "off";
String whiteLightState  = "off";
String irLightState     = "off";


//char* modelName[] = {"AT-6ES","AT-12ES","AT-9EZ","M4","M5","M6","M7","M8"};
int powerEnable=52;
int pinInArrary[]= {31,33,35,37,39,41,43,45}; 
int pinOutArrary[]={30,32,34,36,38,40,42,44,46,48,powerEnable}; 
int degree10   = 30;
int degree30   = 32;
int degree45   = 34;
int degree60   = 36;
int degree130  = 38;
int whiteLight = 46;
int irLight    = 48;

void initPins()
{
      // set pin mode to input to read model
    for(int i=0;i<sizeof(pinInArrary)/sizeof(int);i++){
      pinMode(pinInArrary[i], INPUT_PULLUP);
    }

    // these are for illuminator control
   for(int i=0;i<sizeof(pinOutArrary)/sizeof(int);i++){
      pinMode(pinOutArrary[i], OUTPUT);
      // set default high for control lines
      digitalWrite(pinOutArrary[i], HIGH);
    }

}

void powerOff(){
  digitalWrite(powerEnable, HIGH);
  powerState="off";
}
void powerOn(){
  digitalWrite(powerEnable, LOW);
  powerState="on";
}

void turnDLOn(int _dl){
  digitalWrite(_dl, LOW);
}
void turnDLOff(int _dl){
  digitalWrite(_dl, HIGH);
}

void turnDLsOff(){
   for(int i=0;i<sizeof(pinOutArrary)/sizeof(int);i++){
      // set default high for control lines
      turnDLOff(pinOutArrary[i]);
      degree10State   ="off";
      degree30State   ="off";
      degree45State   ="off";
      degree60State   ="off";
      degree130State  ="off";
      whiteLightState ="off";
      irLightState    ="off";
    }
}

// checks if received HTTP request is switching on/off LEDs
// also saves the state of the LEDs
void SetDLs(void)
{
  Serial.println(HTTP_req);
  if (StrContains(HTTP_req, "power=0")){
    turnDLsOff();
    powerOff();
    return;
  }else if (StrContains(HTTP_req, "power=1") || powerState=="on" ) {
    powerOn();
    if (StrContains(HTTP_req      , "degree10=1")){
      turnDLsOff();  //to make DLs exclusive
      //turn 10 degree on
      turnDLOn(degree10);
      degree10State="on";
    } else if(StrContains(HTTP_req, "degree10=0")){
      turnDLOff(degree10);
      degree10State="off";
    } else if(StrContains(HTTP_req, "degree30=1")){
      turnDLsOff();  //to make DLs exclusive
      //turn 30 on
      turnDLOn(degree30);
      degree30State="on";
    }else if(StrContains(HTTP_req, "degree30=0")){
      turnDLOff(degree30);
      degree30State="off";
    }else if(StrContains(HTTP_req, "degree45=1")){
      turnDLsOff();  //to make DLs exclusive
      //turn 45 degree on
      turnDLOn(degree45);
      degree45State="on";
    } else if(StrContains(HTTP_req, "degree45=0")){
      turnDLOff(degree45);
      degree45State="off";
    } else if(StrContains(HTTP_req, "degree60=1")){
      turnDLsOff();  //to make DLs exclusive
      //turn 60 on
      turnDLOn(degree60);
      degree60State="on";
    } else if (StrContains(HTTP_req, "degree60=0")){
      turnDLOff(degree60);
      degree60State="off";
    } else if(StrContains(HTTP_req, "degree130=1")){
      turnDLsOff();  //to make DLs exclusive
      //turn 130 on
      turnDLOn(degree130);
      degree130State="on";
    } else if(StrContains(HTTP_req, "degree130=0")){
      turnDLOff(degree130);
      degree130State="off";
    } else if(StrContains(HTTP_req, "whiteLight=1")){
      turnDLsOff();  //to make DLs exclusive
      turnDLOn(whiteLight);
      whiteLightState="on";
    } else if(StrContains(HTTP_req, "whiteLight=0")){
      turnDLOff(whiteLight);
      whiteLightState="off";
    } else if(StrContains(HTTP_req, "irLight=1")){
      turnDLsOff();  //to make DLs exclusive
      turnDLOn(irLight);
      irLightState="on";
    } else if(StrContains(HTTP_req, "irLight=0")){
      turnDLOff(irLight);
      irLightState="off";
    }


  }
}

// send the XML file DATA status
void XML_response(EthernetClient cl)
{
    int modelNumber = 0;
    
    Serial.println("XML_response");
    Serial.print("powerState ");
    Serial.println(powerState);
    cl.println("<?xml version = \"1.0\" ?>");
    cl.println("<outputs>");

    cl.print("<power>");
      cl.print(powerState);
    cl.println("</power>");

    cl.print("<degree10>");
      cl.print(degree10State);
    cl.println("</degree10>");

    cl.print("<degree30>");
      cl.print(degree30State);
    cl.println("</degree30>");
 
    cl.print("<degree45>");
      cl.print(degree45State);
    cl.println("</degree45>");
 
    cl.print("<degree60>");
      cl.print(degree60State);
    cl.println("</degree60>");
    
    cl.print("<degree130>");
      cl.print(degree130State);
    cl.println("</degree130>");

    cl.print("<whiteLight>");
    Serial.print("**************white light state ");
    Serial.println(whiteLightState);
      cl.print(whiteLightState);
    cl.println("</whiteLight>");

    cl.print("<irLight>");
      cl.print(irLightState);
    cl.println("</irLight>");
    
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
