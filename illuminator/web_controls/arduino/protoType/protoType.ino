/*--------------------------------------------------------------
 
--------------------------------------------------------------*/
#include <SPI.h>
#include <Ethernet.h>
#define REQ_BUF_SZ   100

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xC6, 0xFC };  //  No POE----But assigned to poe unit at axton 
//byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x77, 0x0B };  // POE MAC
//byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0x77, 0x27 };  // POE MAC



IPAddress ip(192, 168, 1, 103); // IP address at home
//IPAddress ip(10, 1, 1, 125); // IP address at home
//IPAddress gateway(10,1,1,254);


EthernetServer server(3000);  // create a server at port 80
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer


void setup()
{
  
    while (!Serial);
    Serial.begin(9600);       // for debugging
    
    initPins(); 

  Serial.println("Starting w5100");
  if(!Ethernet.begin(mac)) {
    Serial.println("DHCP fail");
    Serial.println("Using default IP 192.168.1.103");
    Ethernet.begin(mac,ip);
  }else Serial.println(Ethernet.localIP());
  
//    Serial.println("init ethernet");
//    Ethernet.begin(mac);  // initialize Ethernet device
    server.begin();           // start to listen for clients
//    Serial.print("server is at ");
//    Serial.println(Ethernet.localIP());
}


void loop()
{
    EthernetClient client = server.available();  // try to get client
    

    if (client) {  // got client?
        Serial.println("got client");
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
                        client.println("Access-Control-Allow-Origin: http://axtontech.com");
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
                        client.println("Access-Control-Allow-Origin: http://axtontech.com");
                        client.println();
                        // send web page
                        Serial.println("send web page");
                        //printWebPage(client);
                        ui_v1(client);
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
        delay(7);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
}


