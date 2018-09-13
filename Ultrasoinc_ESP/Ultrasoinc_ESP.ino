#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#define trigPin D3
#define echoPin D4
float duration,distance ; 


ESP8266WebServer server(80); // 80 is the port number

const char* ssid="Harsh";
const char* password="9bb992e97a34";

String Website,data,XML,Javascript;
void javascriptContent(){
    Javascript ="<SCRIPT>\n";
    Javascript+="var xmlHttp=createXmlHttpObject();\n";
    Javascript+="function createXmlHttpObject(){\n";
    Javascript+="if(window.XMLHttpRequest){\n";
    Javascript+="xmlHttp=new XMLHttpRequest();\n";
    Javascript+="}else{\n";
    Javascript+="xmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n";
    Javascript+="}\n";
    Javascript+="return xmlHttp;\n";
    Javascript+="}\n";
    Javascript+="\n";
    Javascript+="function response(){\n";
    Javascript+="xmlResponse=xmlHttp.responseXML;\n";
    Javascript+="xmldoc = xmlResponse.getElementsByTagName('data');\n";
    Javascript+="message = xmldoc[0].firstChild.nodeValue;\n";
    Javascript+="document.getElementById('div1').innerHTML=message;\n";
    Javascript+="}\n";

    Javascript+="function process(){\n";
    Javascript+="xmlHttp.open('PUT','xml',true);\n";
    Javascript+="xmlHttp.onreadystatechange=response;\n";
    Javascript+="xmlHttp.send(null);\n";
    Javascript+="setTimeout('process()',200);\n";
    Javascript+="}\n";
    
    Javascript+="</SCRIPT>\n";
    
  
  }

void WebsiteContent(){
    javascriptContent();
    
    Website="<html>\n"; 
    Website+="<style>\n";
    Website+="#div1{\n";
    Website+="width:400px;\n";
    Website+="margin:0 auto;\n";
    Website+="margin-top:130px;\n";
    Website+="font-size:900%;\n";
    Website+="color:red;\n";
    Website+="}\n";
    Website+="</style>\n";
    Website+="<body onload='process()'>";
    Website+="<div id='div1'>"+data+"</div></body>";
    Website+=Javascript;
    Website+="</html>";
    server.send(200,"text/html",Website);
  }
void XMLcontent(){

  XML ="<?xml version='1.0'?>";
  XML+="<data>";
  XML+=data;
  XML+="</data>";

  server.send(200,"text/xml",XML);
  
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  WiFi.mode(WIFI_STA);
  Serial.print(WiFi.localIP());
  server.on("/",WebsiteContent);
  server.on("/xml",XMLcontent);
  server.begin();


}
void loop() {
  
  
  digitalWrite (trigPin,LOW);
  delayMicroseconds(2); // put your main code here, to run repeatedly:
  digitalWrite (trigPin,HIGH);
  delayMicroseconds (10);
  digitalWrite (trigPin,LOW);
  
  duration = pulseIn(echoPin,HIGH);
  distance= (duration / 2)*0.0343;
  Serial.print("Distance= ");
 

  if(distance>=400 || distance<=2)
  {
 
   Serial.println("Out of range"); 
    data = "Distance : "+(String)distance+" cm" ;

    }
  else
  {

   Serial.print(distance);
    data = "Distance : "+(String)distance+" cm";
   
    } 
   


  server.handleClient();

  Serial.println("");
  
  }
