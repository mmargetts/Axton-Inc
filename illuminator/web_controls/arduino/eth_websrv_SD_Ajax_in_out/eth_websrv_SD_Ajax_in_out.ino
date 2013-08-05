/*--------------------------------------------------------------
  Program:      eth_websrv_SD_Ajax_in_out

  Description:  Arduino web server that displays 4 analog inputs,
                the state of 3 switches and controls 4 outputs,
                2 using checkboxes and 2 using buttons.
                The web page is stored on the micro SD card.
  
  Hardware:     Arduino Uno and official Arduino Ethernet
                shield. Should work with other Arduinos and
                compatible Ethernet shields.
                2Gb micro SD card formatted FAT16.
                A2 to A4 analog inputs, pins 2, 3 and 5 for
                the switches, pins 6 to 9 as outputs (LEDs).
                
  Software:     Developed using Arduino 1.0.5 software
                Should be compatible with Arduino 1.0 +
                SD card contains web page called index.htm
  
  References:   - WebServer example by David A. Mellis and 
                  modified by Tom Igoe
                - SD card examples by David A. Mellis and
                  Tom Igoe
                - Ethernet library documentation:
                  http://arduino.cc/en/Reference/Ethernet
                - SD Card library documentation:
                  http://arduino.cc/en/Reference/SD

  Date:         4 April 2013
  Modified:     19 June 2013
                - removed use of the String class
 
  Author:       W.A. Smith, http://startingelectronics.com
--------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
// size of buffer used to capture HTTP requests
#define REQ_BUF_SZ   100

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xC6, 0xFC };  // old MAC no POE 
//byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x77, 0x0B };  // POE MAC

//IPAddress ip(192, 168, 0, 155); // IP address for axton
IPAddress ip(192, 168, 1, 155); // IP address at home

EthernetServer server(80);  // create a server at port 80
File webFile;               // the web page file on the SD card
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer

boolean dataLineState[8] = {0};
char* dataLineNames[] = {"DATA46=1","DATA46=0","DATA47=1","DATA47=0","DATA48=1","DATA48=0","DATA49=1","DATA49=0","DATA50=1","DATA50=0","DATA51=1","DATA51=0","DATA52=1","DATA52=0","DATA53=1","DATA53=0"};
char* modelName[] = {"AT-6ES","AT-12ES","AT-9EZ","M4","M5","M6","M7","M8"};
int pinInArrary[]= {22,23,24,25,26,27,28,29};
int pinOutArrary[]={46,47,48,49,50,51,52,53};

void setup()
{
  
    while (!Serial);
    Serial.begin(9600);       // for debugging
    
    Serial.println(sizeof(char));
    Serial.println(sizeof(dataLineNames)/sizeof(char));
    // initialize SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERROR - SD card initialization failed!");
        return;    // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
    if (!SD.exists("index.htm")) {
        Serial.println("ERROR - Can't find index.htm file!");
        return;  // can't find index file
    }
    Serial.println("SUCCESS - Found index.htm file.");
  
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
    
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
    Serial.print("server is at ");
    Serial.println(Ethernet.localIP());
}

void loop()
{
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
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
                        XML_response(client);
                    }
                    else {  // web page request
                        // send rest of HTTP header
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();
                        // send web page
                        webFile = SD.open("index.htm");        // open web page file
                        if (webFile) {
                            while(webFile.available()) {
                                client.write(webFile.read()); // send web page to client
                            }
                            webFile.close();
                        }
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
        delay(1);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}

// checks if received HTTP request is switching on/off LEDs
// also saves the state of the LEDs
void SetDLs(void)
{
  
  for (int i=0;i<sizeof(pinOutArrary)/sizeof(int);i++){
      if (StrContains(HTTP_req, char(pinOutArrary[i]))) {
          dataLineState[i] = 1;  // save LED state
          digitalWrite(pinOutArrary[i], LOW);
            Serial.print("digital linename ");
            Serial.print(" pin val ");
            Serial.println(pinOutArrary[i]);
      }
      else if (StrContains(HTTP_req, "DATA"+ pinOutArrary[i] + "=0")) {
          dataLineState[i] = 0;  // save LED state
          digitalWrite(pinOutArrary[i], HIGH);
            Serial.print("digital linename ");
            Serial.print(" pin val ");
            Serial.println(pinOutArrary[i]);
      }
    }
  
  
/*
      if (StrContains(HTTP_req, "DATA7=1")) {
          dataLineState[0] = 1;  // save DL state
          digitalWrite(7, LOW);
      }
      else if (StrContains(HTTP_req, "DATA7=0")) {
          dataLineState[0] = 0;  // save DL state
          digitalWrite(7, HIGH);
      }
  
      if (StrContains(HTTP_req, "DATA8=1")) {
          dataLineState[1] = 1;  // save DL state
          digitalWrite(8, LOW);
      }
      else if (StrContains(HTTP_req, "DATA8=0")) {
          dataLineState[1] = 0;  
          digitalWrite(8, HIGH);
      }
      if (StrContains(HTTP_req, "DATA9=1")) {
          dataLineState[2] = 1;  
          digitalWrite(9, LOW);
      }
      else if (StrContains(HTTP_req, "DATA9=0")) {
          dataLineState[2] = 0; 
          digitalWrite(9, HIGH);
      }
  */
}

// send the XML file DATA status
void XML_response(EthernetClient cl)
{
    int modelNumber = 0;
    cl.print("<?xml version = \"1.0\" ?>");
    cl.print("<inputs>");

    // read inputs
    for (int i = 0; i < sizeof(pinInArrary); i++) {
        cl.print("<jumpers>");
        if (digitalRead(pinInArrary[i])) {
            cl.print("ON");
        }
        else {
            cl.print("OFF");
        }
        cl.println("</jumpers>");
    }

    cl.print("<model>");
    for (int i = 0; i < sizeof(pinInArrary); i++) {
        if (digitalRead(pinInArrary[i])) {
          modelNumber = modelNumber + 1;
        }
    }
    cl.print(modelName[modelNumber]);
    Serial.println(modelName[modelNumber]);
    Serial.println(modelNumber);
    
    cl.println("</model>");

    // checkbox DATA states
    for (int i = 0; i < sizeof(dataLineState); i++){
        cl.print("<DATA>");
        if (dataLineState[i]) {
            cl.print("checked");
        }
        else {
            cl.print("unchecked");
        }
        cl.println("</DATA>");
    }
    cl.print("</inputs>");
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
