/*--------------------------------------------------------------
 
--------------------------------------------------------------*/
#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>
#define REQ_BUF_SZ   100

File logoImage;
// MAC address from Ethernet shield sticker under board
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xC6, 0xFC };  //  no POE 
//byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x77, 0x0B };  // POE MAC

IPAddress ip(192, 168, 1, 144); // IP address at home
IPAddress gateway(192, 168, 1, 100);
//IPAddress ip(10, 1, 1, 125); // IP address at home
//IPAddress gateway(10,1,1,254);


EthernetServer server(80);  // create a server at port 80
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer

String powerState       = "off";
String degree10State    = "off";
String degree30State    = "off";
String degree45State    = "off";
String degree60State    = "off";
String degree130State   = "off";


char* modelName[] = {"AT-6ES","AT-12ES","AT-9EZ","M4","M5","M6","M7","M8"};

int pinInArrary[]= {}; 
int pinOutArrary[]={30,32,34,36,38,40,42,44}; 
int degree10  = 30;
int degree30  = 32;
int degree45  = 34;
int degree60  = 36;
int degree130 = 38;




void setup()
{
  
    while (!Serial);
    Serial.begin(9600);       // for debugging
    
    initPins(); 
  
    Serial.println("init ethernet");
    Ethernet.begin(mac,ip,gateway);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
}

void initPins()
{
      // set pin mode to input to read model
    for(int i=0;i<sizeof(pinInArrary)/sizeof(int);i++){
      //pinMode(pinInArrary[i], INPUT_PULLUP);
      pinMode(pinInArrary[i], INPUT);
    }

    // these are for illuminator control
   for(int i=0;i<sizeof(pinOutArrary)/sizeof(int);i++){
      pinMode(pinOutArrary[i], OUTPUT);
      // set default high for control lines
      digitalWrite(pinOutArrary[i], HIGH);
    }

}

void powerOff(){
  powerState="off";
}
void powerOn(){
  powerState="on";
}

void turnDLOn(int _dl){
  digitalWrite(_dl, HIGH);
}
void turnDLOff(int _dl){
  digitalWrite(_dl, LOW);
}

void turnDLsOff(){
   for(int i=0;i<sizeof(pinOutArrary)/sizeof(int);i++){
      // set default high for control lines
      //digitalWrite(pinOutArrary[i], HIGH);
      turnDLOff(pinOutArrary[i]);
      degree10State ="off";
      degree30State ="off";
      degree45State ="off";
      degree60State ="off";
      degree130State="off";
    }
}




void loop()
{
    EthernetClient client = server.available();  // try to get client
    //Serial.println(" try to get client");
    

    if (client) {  // got client?
        //debugOut("got client");
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                // limit the size of the stored received HTTP request
                // buffer first part of HTTP request in HTTP_req array (string)
                // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
                if (req_index < (REQ_BUF_SZ - 1)) {
                    HTTP_req[req_index] = c;          // save HTTP request character
                    req_index++;
                }
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    // remainder of header follows below, depending on if
                    // web page or XML page is requested
                    // Ajax request - send XML file
                    if (StrContains(HTTP_req, "ajax_inputs")) {
                        // send rest of HTTP header
                        client.println("Content-Type: text/xml");
                        client.println("Connection: keep-alive");
                        client.println();
                        SetDLs();
                        // send XML file containing input states
                        Serial.println("calling xml response");
                        XML_response(client);
                    }
                    else {  // web page request
                        // send rest of HTTP header
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();
                        // send web page
                        Serial.println("send web page");
                        printWebPage(client);
                    }
                    // display received HTTP request on serial port
                    Serial.print(HTTP_req);
                    // reset buffer index and all buffer elements to 0
                    req_index = 0;
                    StrClear(HTTP_req, REQ_BUF_SZ);
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(20);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
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
