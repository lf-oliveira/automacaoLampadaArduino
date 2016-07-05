#include <SPI.h>
#include <Ethernet.h>

// A linha abaixo permite definir o endereço físico (MAC ADDRESS) da placa de rede. 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

byte ip[] = { 192, 168, 0, 200 };  //Define o endereço IP.
    
// Porta onde estará aberta para comunicação Internet e Arduino.
EthernetServer server(80);  
 
String readString;
int Pin = 7;  //  Pino digital onde será ligado e desligado.
 
void setup(){
 
pinMode(Pin, OUTPUT);  // Define o Pino 7 como saída.
Ethernet.begin(mac, ip);  // Chama o MAC e o endereço IP da placa Ethernet.
server.begin();  //  Inicia o servidor que esta inserido junto a placa Ethernet.
}
 
void loop(){
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
 
        if (readString.length() < 100) {
          readString += c;             
        }

        if (c == '\n') {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
    
// A partir daqui começa os códigos html.
    
client.println("<HTML>");
client.println("<HEAD>");
client.println("<meta http-equiv='Content-Type' content='text/html; charset=UTF-8'>");
client.println("<meta name='viewport' content='width=720, initial-scale=0.5' />");
client.println("<STYLE type='text/css'>");

client.println("button#on {");
client.println("border-radius: 28px;");
client.println("padding: 10px;");
client.println("background: #3498db;");
client.println("}");
client.println("button#on:hover {");
client.println("background: #3cb0fd;");
client.println("}");

client.println("button#off {");
client.println("border-radius: 28px;");
client.println("padding: 10px;");
client.println("background: #d93434;");
client.println("}");
client.println("button#off:hover {");
client.println("background: #fc3c3c;");
client.println("}");

client.println("a {");
client.println("text-decoration: none;");
client.println("font-family: Arial;");
client.println("font-size: 20px;");
client.println("color: #ffffff;");
client.println("}");

client.println("</STYLE>");
client.println("</HEAD");
client.println("<BODY>");
client.println("<H1>Automação Residencial</H1>");
client.println("<hr />");
client.println("<br />");
          
client.println
("<button id='on'><a href=\"/projetofinal/LampadaOn\"\">On</a></button>");
client.println
("<button id='off'><a href=\"/projetofinal/LampadaOff\"\">Off</a></button><br />");   
          
          client.println("</BODY>");
          client.println("</HTML>");
          
          delay(1);
          client.stop();
          
          if(readString.indexOf("projetofinal/LampadaOn") > 0)
          {
            digitalWrite(Pin, LOW);  // Liga Lampada.
          }
          else {
            if(readString.indexOf("projetofinal/LampadaOff") > 0)
            {
              digitalWrite(Pin, HIGH);  // Desliga Lampada.
            }
          }
            readString="";    
        }
      }
    }
  }
}
