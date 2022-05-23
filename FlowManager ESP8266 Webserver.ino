#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h> 
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WifiMultiW;      //Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'
ESP8266WebServer ServerS(80);     //Create a webserver object that listens for HTTP request on port 80
WiFiClient client;                //Initialize the client library

String HTMLindex;
String HTTPsendStr;
String HTTPresponseStr;
String PrinterURL = "http://192.168.8.124";
int PrinterPort = 80;
int NewDataRdy = 0;

//Serial Read
String ESPreadStr;
char ESPreadChar[32];

//Float Parsing For 6 Digits of Acccuracy
float ESPreadNum;
String FloatFrontStr;
float FloatFrontF;
String FloatEndStr;
float FloatEndF;

//Function HTTP handlers
void handleRoot();
void handleNotFound();

//Misc variables
int A;
int B;
int C;

///////////Setup///////////
void setup(void)
     {
      //Establish serial settings
      //Serial.begin(115200);
      Serial.begin(34000);
      Serial.print("RX TX Serial Established at 34000...");
      Serial.setTimeout(500);
      Serial.println('\n');
      delay(10);

      //Add access point
      WifiMultiW.addAP("WiFiRouterSSID", "Password");  //Add Wi-Fi network
      
      Serial.println("Connecting ...");
      while(WifiMultiW.run() != WL_CONNECTED) //Wait for Wi-Fi connect
           {
            delay(250);
            Serial.print('.');
           }

      //Print connection status
      Serial.println('\n');
      Serial.print("Connected to ");
      Serial.println(WiFi.SSID());              //Print connected network SSID
      Serial.print("IP address:\t");
      Serial.println(WiFi.localIP());           //Print IP address of ESP8266
      
      ServerS.on("/", handleRoot);              //Client requests handleRoot function URI "/"
      ServerS.onNotFound(handleNotFound);       //Client requests unknown URI
      
      ServerS.begin();                          //Start the server

      WiFiClient client;
     }

///////////Loop///////////
void loop(void)
     {
      RecieveDataV();
      ServerS.handleClient();
     }
    
///////////Parse Serial data into float///////////
void RecieveDataV()
     {
      if(NewDataRdy)
        {
         if(Serial.available() && (Serial.read() == '\a'))
           {
            ESPreadStr = Serial.readStringUntil('\n');
            A = ESPreadStr.length();
            
            //Capture BEFORE decimal and convert to int with float
            FloatFrontStr = Serial.readStringUntil('.');
            B = FloatFrontStr.length();
            FloatFrontStr = ESPreadStr.substring(0, (B-1));
            FloatFrontF = 0.0000001 + FloatFrontStr.toInt();
            
            //Capture AFTER decimal and convert to int with float
            FloatEndStr = ESPreadStr.substring(B, A); //Six digits
            FloatEndF = 0.0000001 + FloatEndStr.toInt(); 
            for(int ZZ = 0; ZZ <= 5; ZZ++) {FloatEndF = FloatEndF / 10;} //Move decimal over six places
            
            //Combine to create float
            ESPreadNum = FloatFrontF + FloatEndF;

            NewDataRdy = 0;
           }
        }
     }

///////////Output Webpage///////////
void handleRoot() 
     {
      HTMLindex  += "<html><head><title>Filament Flow Manager</title></head>";
      HTMLindex  += "<body>";
      
      HTMLindex  += "<h1>Filament Flow Manager</h1>";
      HTMLindex  += "<BR>";
      
      HTMLindex  += "<h2>";
      HTMLindex  += "Measured Filament Size: ";
      HTMLindex  += String(ESPreadNum, 6);
      HTMLindex  += "<BR>";
      HTMLindex  += "<BR>";
      
      HTMLindex  += "<h3>";
      HTMLindex  += "H3 text";
      HTMLindex  += "</h3>";
      HTMLindex  += "<BR>";
      
      HTMLindex  += "<h4>";
      HTMLindex  += "<p1>Input text below</p>";
      HTMLindex  += "<textarea name=\"TextBox1\" cols=\"50\" rows=\"5\">This is a textbox</textarea>";
      HTMLindex  += "</h4>";
      HTMLindex  += "<BR>";
      
      HTMLindex  += "<h5>";
      HTMLindex  += "<form action=\"/get\"> input1: <input type=\"text\" name=\"input1\">";
      HTMLindex  += "<input type=\"submit\" value=\"Submit\">";
      HTMLindex  += "</form>";
      HTMLindex  += "</h5>";
      HTMLindex  += "<BR><BR>";
      
      HTTPClient http;
      HTTPsendStr = "http://192.168.8.124/set?code=G28";
      http.begin(HTTPsendStr);
      //http.addHeader("Content-Type", "text/plain");
      HTTPresponseStr = http.GET();
      http.end();
      
      HTMLindex  += "PRINTER SEND STRING: ";
      HTMLindex  += HTTPsendStr;
      HTMLindex  += "<BR><BR>";
      HTMLindex  += "PRINTER RESPONSE: ";
      HTMLindex  += HTTPresponseStr;
      
      HTMLindex  += "<BR><BR><BR>";
      
      C++; //Page views
      HTMLindex  += "Page Views: ";
      HTMLindex  += C;
      
      //Send webpage
      ServerS.send(200, "text/html", HTMLindex);   //Http status 200 (Ok)
      
      HTMLindex = "";
      NewDataRdy = 1;
     }

//Ouput Webpage 404 error
void handleNotFound()
    {
     ServerS.send(404, "text/plain", "404: Not found");
    }


/////////////////////////////////Debug stuff/////////////////////////////////

/*
      HTMLindex  += "ESPreadStr: ";       
      HTMLindex  += ESPreadStr;
      HTMLindex  += "<BR>";
      HTMLindex  += "FloatFrontStr: ";
      HTMLindex  += FloatFrontStr;
      HTMLindex  += "<BR>";
      HTMLindex  += "FloatFrontF: ";       
      HTMLindex  += String(FloatFrontF, 6);
      HTMLindex  += "<BR>";
      HTMLindex  += "FloatEndStr: ";
      HTMLindex  += FloatEndStr;
      HTMLindex  += "<BR>";
      HTMLindex  += "FloatEndF: ";
      HTMLindex  += String(FloatEndF, 6);
      HTMLindex  += "</h2>";
      HTMLindex  += "<BR>";
*/

/*
      HTMLindex  += "CONNECTION STATUS: ";       
      //Connect to printer if not already
      if(!client.connected()) client.connect(PrinterURL, PrinterPort);
      
      if(client.connected()) 
        {
         HTMLindex += "!CONNECTED TO PRINTER!";
         client.println("/set?code=G28");
        }
      
      if(!client.connected())
        {
         HTMLindex += "Not connected to printer";
        }
*/
