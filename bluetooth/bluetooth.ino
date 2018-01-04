
/*
   Test af bluetooth
   af Lone Østerlund
*/

#include <SoftwareSerial.h>
int bluetoothTx = 5;
int bluetoothRx = 6;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);//Arduino RX,Tx

char msg;
int counter = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  bluetooth.begin(9600);//standard bluetooth
  sendCommand("AT");
  sendCommand("AT+LADDR");
  sendCommand("AT+NAME");
  sendCommand("AT+NAMELone");

  sendCommand("AT+NAME");
  sendCommand("AT+PASS123456");
  sendCommand("AT+PASS");

  sendCommand("AT+UUID");
  sendCommand("AT+ROLE");
  sendCommand("AT+ROLE0");
  sendCommand("AT+ROLE");
  sendCommand("AT+TYPE");
  sendCommand("AT+TYPE1"); // nem parring
  sendCommand("AT+TYPE");
  sendCommand("AT+TYPE");
  //   sendCommand("AT+RESET");
  //sendCommand("AT+START");
  sendCommand("AT+CHAR");
 // sendCommand("AT+START");
}

/*
  void loop() {
  bluetooth.listen();
  modtagFraBluetooth();
  // Serial.println(counter);
  bluetooth.println(counter);
  counter++;
  delay(1000);
  }
*/
int count = 0;
char c=' ';
boolean NL = true;

/*
void loop()
{
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (bluetooth.available())
    {
        c = bluetooth.read();
        Serial.write(c);
    }
 
 
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
 
        // do not send line end characters to the HM-10
        if (c!=10 & c!=13 ) 
        {  
             bluetooth.write(c);
        }
 
        // Echo the user input to the main window. 
        // If there is a new line print the ">" character.
        if (NL) { Serial.print("\r\n>");  NL = false; }
        Serial.write(c);
        if (c==10) { NL = true; }
    }
}
*/


void loop() {
  if (bluetooth.available())

  {
    while ( bluetooth.available() ){
   
      Serial.write(bluetooth.read());

    }
  }

   if ( Serial.available() )
    {
     delay(5);

     while ( Serial.available() ){
         c= Serial.read();
         bluetooth.write( c );
         Serial.write(c);
     }  
    }
 // bluetooth.write(count);
 // count++;
//  delay(1000);
}

void sendCommand (String command) {
  Serial.print("Command send :");
  Serial.println(command);
  bluetooth.println(command);
  //wait some time
  delay(100);
  while (bluetooth.available()) {
    Serial.write(bluetooth.read());
  }
  delay(50);
}



/*
  Denne funktion modtager på
   SoftwarerSeriel porten
   navngivet bluetooth.
   modtages 't' tændes diode på ben 13
   modtages 's' slukkes dioden
*/
void modtagFraBluetooth() {
  char msg;
  if (bluetooth.available()) {
    msg = (char)bluetooth.read();
    if (msg == 't')
      digitalWrite(13, HIGH);
    else if (msg == 's') {
      digitalWrite(13, LOW);
    }
    bluetooth.print(msg); //returner det modtagne
    Serial.println(msg);
  }
}


/*
  void sendCommand1(const char * command) {
  Serial.print("Command send :");
  Serial.println(command);
  mySerial.println(command);
  //wait some time
  delay(100);

  char reply[100];
  int i = 0;
  while (mySerial.available()) {
    reply[i] = mySerial.read();
    i += 1;
  }
  //end the string
  reply[i] = '\0';
  Serial.print(reply);
  Serial.println("Reply end");
  delay(50);
  }
*/
