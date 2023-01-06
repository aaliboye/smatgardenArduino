
#define wait 5000

void setup(){
  // Init serial port (115200 bauds)  
  Serial.begin(9600);


}

void loop() {
 // put your main code here, to run repeatedly:
 int captZone1 = analogRead(A1);  //humidité sol zone 1
 int captZone2 = analogRead(A2);  //humidité sol zone 2
 int captZone3 = analogRead(A3);  //humidité sol zone 2
 int lumiere = analogRead(A4);  //luminosité tool bi


 Serial.print("{\"CaptZone1\":");
 Serial.print(captZone1);
 Serial.print(",\"CaptZone2\":");
 Serial.print(captZone2);
 Serial.print(",\"CaptZone3\":");
 Serial.print(captZone3);
 Serial.print(",\"Luminosite\":");
 Serial.print(lumiere);

 Serial.println("}");
 delay(wait);

 if(captZone1 >1000){
    digitalWrite(11, LOW);
 }

  if(captZone3 >1000){
    digitalWrite(13, LOW);
 }


  if (Serial.available()) {  
      String data = Serial.readString();
      /*int indportArd = data.indexOf(",");
      String portArd = data.substring(0, indportArd);
      int indcmd = data.indexOf(",", indportArd+1);
      String cmd = data.substring(indportArd+1, indcmd);
      int indport = data.indexOf(",", indcmd+1);
      String portstr = data.substring(indcmd+1, indport);
      int port = portstr.toInt();*/
      
     if(data != ""){

      int tailletab=0;
      
       for (int i=0; i < data.length(); i++)
      { 
        if(data.charAt(i) == ';') 
        { 
          tailletab += 1;
        }
      }

      String sa[tailletab];
       int r=0, t=0;
      
      for (int i=0; i < data.length(); i++)
      { 
        if(data.charAt(i) == ';') 
        { 
          sa[t] = data.substring(r, i); 
          r=(i+1); 
          t++; 
        }
      }

      for(int i=0; i<tailletab; i++){
        String cmd = sa[i];
        int indportArd = cmd.indexOf(",");
        String portArd = cmd.substring(0, indportArd);
        
        int indport = cmd.indexOf(",", indportArd+1);
        String portstr = cmd.substring(indportArd+1, indport);
        int port = portstr.toInt();
        
        int indcmd = cmd.indexOf(",", indport+1);
        String cmdout = cmd.substring(indport+1, indcmd);

        Serial.print(cmdout);

        receiveData(cmdout, port);
        
      }
      
      
     }
      
      /*if (command == "ON" && captZone1 < 980) {  
         digitalWrite(11, HIGH);
      }
      else if (command == "OFF" && captZone1 > 300) { 
         digitalWrite(11, LOW);
      }
      else if (command == "ON2") { 
         digitalWrite(12, HIGH);
      }
      else if (command == "OFF2") { 
         digitalWrite(12, LOW);
      }
      else if (command == "ON3") { 
         digitalWrite(13, HIGH);
      }
      else if (command == "OFF3") { 
         digitalWrite(13, LOW);
      }*/

   }
}

void receiveData(String cmd, int port)
{
       if (cmd == "on") {  
         digitalWrite(port, HIGH);
      }
      else if (cmd == "off"){
        digitalWrite(port, LOW);
      }
}
