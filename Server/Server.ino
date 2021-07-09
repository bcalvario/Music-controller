#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "*****";  // Enter your SSID here
const char* password = "****";  //Enter your Password here

WebServer server(80);  // Object of WebServer(HTTP port, 80 is defult)

void setup() {
  Serial.begin(115200);
  Serial.println("Try Connecting to ");
  Serial.println(ssid);

  // Connect to your wi-fi modem
  WiFi.begin(ssid, password);

  // Check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Got IP: ");
  Serial.println(WiFi.localIP());  //Show ESP32 IP on serial

  server.on("/", handle_root);

  server.begin();
  Serial.println("HTTP server started");
  delay(100); 
}

void loop() {
  server.handleClient();
}

// HTML & CSS contents which display on web server
String HTML = "<!DOCTYPE html>\
<html lang='en'>\
  <head>\
    <meta charset='UTF-8' />\
    <meta http-equiv='X-UA-Compatible' content='IE=edge' />\
    <meta name='viewport' content='width=device-width, initial-scale=1.0' />\
    <title>Reproductor de musica</title>\
    <style type='text/css'>\
      BODY {\
        display: flex;\
        margin-top: 2rem;\
        flex-direction: column;\
        justify-content: center;\
        align-items: center;\
      }\
      .botton {\
        background-color: #ffffff;\
        cursor: pointer;\
        justify-content: center;\
        align-items: center;\
        position: relative;\
      }\
      .botton:hover {\
        background-color: #a9c3db;\
      }\
      .reproduction,\
      .volume {\
        margin: 1rem;\
        justify-content: center;\
        align-items: center;\
        position: relative;\
      }\
      .message {\
        margin: 1rem;\
        padding: 0.5rem;\
        border: 1px solid black;\
        border-radius: 0.5rem;\
        justify-content: center;\
        align-items: center;\
        position: relative;\
      }\
      .tittle {\
        color: #387ac9;\
      }\
    </style>\
  </head>\
  <body>\
    <link\
      href='https://fonts.googleapis.com/icon?family=Material+Icons'\
      rel='stylesheet'\
    />\
    <h2 class='tittle'>Música cosultorios 629</h2>\
    <div class='reproduction'>\
      <button class='botton'>\
        <span class='material-icons' alt='Next'>skip_previous</span>\
      </button>\
      <button class='botton'>\
        <span class='material-icons' alt='Pause'>pause</span>\
      </button>\
      <button class='botton'>\
        <span class='material-icons' alt='Play'>play_arrow</span>\
      </button>\
      <button class='botton'>\
        <span class='material-icons' alt='Next'>skip_next</span>\
      </button>\
    </div>\
    <div class='volume'>\
      <button class='botton'>\
        <span class='material-icons' alt='Volume Down'>volume_down</span>\
      </button>\
      <button class='botton'>\
        <span class='material-icons' alt='Volume Up'>volume_up</span>\
      </button>\
    </div>\
    <div class='message'>mensajes: reproduciendo, en pausa...</div>\
  </body>\
</html>";

// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", HTML);
}
