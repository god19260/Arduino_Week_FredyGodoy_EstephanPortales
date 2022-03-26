// Competencia Semana Arduino
// Estephan Portales - 19826
// Fredy Godoy - 19260

#include <WiFi.h>
#include <WebServer.h>

/* Put your SSID & Password */
const char* ssid = "ESP32";  // Enter SSID here
const char* password = "ESP32-Estephan";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

// Pine para motores
uint8_t Motor_1D= 13;
uint8_t  Motor_1I= 12;
uint8_t  Motor_2D= 14;
uint8_t  Motor_2I= 27;

bool Adelante = LOW;
bool Atras = LOW;
bool Derecha = LOW;
bool Izquierda = LOW;
bool Freno = LOW;


void setup() {
  Serial.begin(115200);
  pinMode(Motor_1D, OUTPUT);
  pinMode(Motor_1I, OUTPUT);
  pinMode(Motor_2D, OUTPUT);
  pinMode(Motor_2I, OUTPUT);
  

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/AdelanteOn", handle_adelanteOn);
  server.on("/AdelanteOff", handle_adelanteOff);
  server.on("/AtrasOn", handle_atrasOn);
  server.on("/AtrasOff", handle_atrasOff);
  server.on("/IzquierdaOn", handle_izquierdaOn);
  server.on("/IzquierdaOff", handle_izquierdaOff);
  server.on("/DerechaOn", handle_derechaOn);
  server.on("/DerechaOff", handle_derechaOff);
  server.on("/FrenoOn", handle_frenoOn);
  server.on("/FrenoOff", handle_frenoOff);
  server.onNotFound(handle_NotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  if(Adelante){
    digitalWrite(Motor_1D, HIGH);
    digitalWrite(Motor_1I, LOW);
    digitalWrite(Motor_2D, HIGH);
    digitalWrite(Motor_2I, LOW);
  } 
  if(Atras){
    digitalWrite(Motor_1D, LOW);
    digitalWrite(Motor_1I, HIGH);
    digitalWrite(Motor_2D, LOW);
    digitalWrite(Motor_2I, HIGH);
  }
  if(Derecha){
    digitalWrite(Motor_1D, HIGH);
    digitalWrite(Motor_1I, LOW);
    digitalWrite(Motor_2D, LOW);
    digitalWrite(Motor_2I, HIGH);
  }
  if(Izquierda){
    digitalWrite(Motor_1D, LOW);
    digitalWrite(Motor_1I, HIGH);
    digitalWrite(Motor_2D, HIGH);
    digitalWrite(Motor_2I, LOW);
  }   
  if(Freno){
    digitalWrite(Motor_1D, LOW);
    digitalWrite(Motor_1I, LOW);
    digitalWrite(Motor_2D, LOW);
    digitalWrite(Motor_2I, LOW);
  }
  if(!Adelante and !Atras and !Derecha and !Izquierda ){
    digitalWrite(Motor_1D, LOW);
    digitalWrite(Motor_1I, LOW);
    digitalWrite(Motor_2D, LOW);
    digitalWrite(Motor_2I, LOW);
  }
}

void handle_OnConnect() {
  Adelante = LOW;
  Atras = LOW;
  Derecha = LOW;
  Izquierda = LOW;
  Freno = LOW;
  Serial.println("Sin movimiento");
  server.send(200, "text/html", SendHTML(Adelante, Atras, Derecha, Izquierda,Freno)); 
}

void handle_adelanteOn() {
  Adelante = HIGH;
  Atras = LOW;
  Derecha = LOW;
  Izquierda = LOW;
  Freno = LOW;
  Serial.println("Adelante ON");
  server.send(200, "text/html", SendHTML(true,Atras, Derecha, Izquierda,Freno)); 
}

void handle_adelanteOff() {
  Adelante = LOW;
  Atras = LOW;
  Derecha = LOW;
  Izquierda = LOW;
  Freno = LOW;
  Serial.println("Adelante OFF");
  server.send(200, "text/html", SendHTML(false, Atras, Derecha, Atras,Freno)); 
}

void handle_atrasOn() {
  Adelante = LOW;
  Atras = HIGH;
  Derecha = LOW;
  Izquierda = LOW;  
  Freno = LOW;
  Serial.println("Atras ON");
  server.send(200, "text/html", SendHTML(Adelante,true, Derecha, Izquierda,Freno)); 
}

void handle_atrasOff() {
  Atras = LOW;
  Adelante = LOW;
  Atras = LOW;
  Derecha = LOW;
  Izquierda = LOW;
  Freno = LOW;
  Serial.println("Atras OFF");
  server.send(200, "text/html", SendHTML(Adelante, false, Derecha, Izquierda,Freno)); 
}
void handle_derechaOn() {
  Adelante = LOW;
  Atras = LOW;
  Derecha = HIGH;
  Izquierda = LOW;
  Freno = LOW;
  Serial.println("Derecha ON");
  server.send(200, "text/html", SendHTML(Adelante,Atras, true, Izquierda,Freno)); 
}

void handle_derechaOff() {
  Adelante = LOW;
  Atras = LOW;
  Derecha = LOW;
  Izquierda = LOW;
  Freno = LOW;
  Serial.println("Derecha OFF");
  server.send(200, "text/html", SendHTML(Adelante,Atras, false, Izquierda,Freno)); 
}
void handle_izquierdaOn() {
  Adelante = LOW;
  Atras = LOW;
  Derecha = LOW;
  Izquierda = HIGH;
  Freno = LOW;
  Serial.println("Izquieda ON");
  server.send(200, "text/html", SendHTML(Adelante,Atras, Derecha, true,Freno)); 
}

void handle_izquierdaOff() {
  Adelante = LOW;
  Atras = LOW;
  Derecha = LOW;
  Izquierda = LOW;
  Freno = LOW;
  Serial.println("Izquierda OFF");
  server.send(200, "text/html", SendHTML(Adelante, Atras, Derecha, false,Freno)); 
}
void handle_frenoOn() {
  Adelante = LOW;
  Atras = LOW;
  Derecha = LOW;
  Izquierda = LOW;
  Freno = HIGH;
  Serial.println("Freno ON");
  server.send(200, "text/html", SendHTML(Adelante,Atras, Derecha, Izquierda,true)); 
}
void handle_frenoOff() {
  Freno = LOW;
  Serial.println("Freno Off");
  server.send(200, "text/html", SendHTML(Adelante,Atras, Derecha, Izquierda,false)); 
}


void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t Adelante,uint8_t Atras, uint8_t Derecha, uint8_t Izquierda,uint8_t Freno){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  //ptr +="<META http-equiv=refresh content = 1>\n";
  ptr +="<title>Competencia Arduino Week</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  //ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  // Boton derecha
  ptr +=".Derecha_button {display: block; position: fixed; top:220px;left: 120px; width: 40px;background-color: #3498db;border: none;color: white;padding:10px 25px 10px 25px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 30px;}\n";
  ptr +=".Derecha_button-on {background-color: #53F510;}\n";
  ptr +=".Derecha_button-on:active {background-color: #53F510;}\n";
  ptr +=".Derecha_button-off {background-color: #EF0000;}\n";
  ptr +=".Derecha_button-off:active {background-color: #EF0000;}\n";
  // boton izquierda
  ptr +=".Izquierda_button {display: block; position: fixed;top:220px; left: 20px; width: 40px;background-color: #3498db;border: none;color: white;padding:10px 25px 10px 25px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 30px;}\n";
  ptr +=".Izquierda_button-on {background-color: #53F510;}\n";
  ptr +=".Izquierda_button-on:active {background-color: #53F510;}\n";
  ptr +=".Izquierda_button-off {background-color: #EF0000;}\n";
  ptr +=".Izquierda_button-off:active {background-color: #EF0000;}\n";
  // Boton Adelante
  ptr +=".Adelante_button {display: block; position: fixed; top:180px;left: 250px; width: 40px;background-color: #3498db;border: none;color: white;padding:10px 25px 10px 25px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 30px;}\n";
  ptr +=".Adelante_button-on {background-color: #53F510;}\n";
  ptr +=".Adelante_button-on:active {background-color: #53F510;}\n";
  ptr +=".Adelante_button-off {background-color: #EF0000;}\n";
  ptr +=".Adelante_button-off:active {background-color: #EF0000;}\n";
  // boton Atras
  ptr +=".Atras_button {display: block; position: fixed;top:260px; left: 250px; width: 40px;background-color: #3498db;border: none;color: white;padding:10px 25px 10px 25px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 30px;}\n";
  ptr +=".Atras_button-on {background-color: #53F510;}\n";
  ptr +=".Atras_button-on:active {background-color: #53F510;}\n";
  ptr +=".Atras_button-off {background-color: #EF0000;}\n";
  ptr +=".Atras_button-off:active {background-color: #EF0000;}\n";
  // boton Freno
  ptr +=".Freno_button {display: block; position: fixed;top:345px; left: 40px; width: 140px;background-color: #3498db;border: none;color: white;padding:10px 70px 10px 70px;text-decoration: none;font-size: 25px;cursor: pointer;border-radius: 30px;}\n";
  ptr +=".Freno_button-on {background-color: #53F510;}\n";
  ptr +=".Freno_button-on:active {background-color: #53F510;}\n";
  ptr +=".Freno_button-off {background-color: #EF0000;}\n";
  ptr +=".Freno_button-off:active {background-color: #EF0000;}\n";

  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Competencia Arduino Week</h1>\n";
  ptr +="<h3>Fredy Godoy - Estephan Portales</h3>\n";

   if(Adelante)
  {ptr +="<p></p><a class=\"Adelante_button Adelante_button-off \" href=\"/AdelanteOff\">OFF</a>\n";}
  else
  {ptr +="<p></p><a class=\"Adelante_button Adelante_button-on\" href=\"/AdelanteOn\">ON</a>\n";}

  if(Atras)
  {ptr +="<p></p><a class=\"Atras_button Atras_button-off\" href=\"/AtrasOff\">OFF</a>\n";}
  else
  {ptr +="<p></p><a class=\"Atras_button Atras_button-on\" href=\"/AtrasOn\">ON</a>\n";}
  
   if(Derecha)
  {ptr +="<p></p><a class=\"Derecha_button Derecha_button-off \" href=\"/DerechaOff\">OFF</a>\n";}
  else
  {ptr +="<p></p><a class=\"Derecha_button Derecha_button-on\" href=\"/DerechaOn\">ON</a>\n";}

  if(Izquierda)
  {ptr +="<p></p><a class=\"Izquierda_button Izquierda_button-off\" href=\"/IzquierdaOff\">OFF</a>\n";}
  else
  {ptr +="<p></p><a class=\"Izquierda_button Izquierda_button-on\" href=\"/IzquierdaOn\">ON</a>\n";}

  if(Freno)
  {ptr +="<p></p><a class=\"Freno_button Freno_button-off\" href=\"/FrenoOff\">FRENO:OFF</a>\n";}
  else
  {ptr +="<p></p><a class=\"Freno_button Freno_button-on\" href=\"/FrenoOn\">FRENO:ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
