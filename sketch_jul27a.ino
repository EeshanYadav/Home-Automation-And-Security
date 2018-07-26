int trig = 7;
int echo = 8;
int b = 13;
void setup() {
  Serial.begin(9600);
  pinMode(b, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);// put your setup code here, to run once:
#include <GSM.h>

#define PINNUMBER ""

// initialize the library instance
GSM gsmAccess;
GSM_SMS sms;

void setup(){
  // initialize serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("SMS Messages Sender");

  // connection state
  boolean notConnected = true;

  // Start GSM shield
  // If your SIM has PIN, pass it as a parameter of begin() in quotes
  while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
}
}

void loop() {
  long duration, distance;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration*0.034/2;
  Serial.println(distance);
  if(distance > 15)
  {
    digitalWrite(b, LOW);
    }
    else if(distance < 15)
    {
      digitalWrite(b, HIGH);
      }
  delay(100);
  // put your main code here, to run repeatedly:
  Serial.print("Enter a mobile number: ");
  char remoteNum[20];  // telephone number to send sms
  readSerial(remoteNum);
  Serial.println(remoteNum);

  // sms text
  Serial.print("Now, enter the Message: ");
  char txtMsg[200];
  txtMsg = "Your house has been compromosied with theft!"
  readSerial(txtMsg);
  Serial.println("SENDING");
  Serial.println();
  Serial.println("Message:");
  Serial.println(txtMsg);

  // send the message
  sms.beginSMS(remoteNum);
  sms.print(txtMsg);
  sms.endSMS();
  Serial.println("\nCOMPLETE!\n");
}
int readSerial(char result[]) {
  int i = 0;
  while (1) {
    while (Serial.available() > 0) {
      char inChar = Serial.read();
      if (inChar == '\n') {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r') {
        result[i] = inChar;
        i++;
      }
    }
  }
}
