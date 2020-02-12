String inputString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete
String signal = "$GPGLL";
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period=1;
int magnetsense=0;
int laststate=1;

int sensPin=2;
int counter=0;

float vecichlespeed;
float radius=0.2;
float pi=3.14;
float circumference=2*radius*pi;



void setup() {
    // initialize serial:
    Serial.begin(9600);
    // reserve 200 bytes for the inputString:
    inputString.reserve(200);
startMillis=millis();
 pinMode(sensPin, INPUT);
}

void loop() {
    // print the string when a newline arrives:
    if (stringComplete) {
        String BB = inputString.substring(0, 6);
        if (BB == signal) {
            String LAT = inputString.substring(7, 17);
            int LATperiod = LAT.indexOf('.');
            int LATzero = LAT.indexOf('0');
            if (LATzero == 0) {
                LAT = LAT.substring(1);
            }

            String LON = inputString.substring(20, 31);
            int LONperiod = LON.indexOf('.');
            int LONTzero = LON.indexOf('0');
            if (LONTzero == 0) {
                LON = LON.substring(1);
            }

            Serial.println(LAT);
            Serial.println(LON);
           

        }

        // Serial.println(inputString);
        // clear the string:
        inputString = "";
        stringComplete = false;
    }
    currentMillis=millis();
magnetsense=digitalRead(sensPin);
 
  if(magnetsense==0 && laststate==1){
       laststate=0;
       
    if(currentMillis-startMillis>=period && laststate==0){
    vecichlespeed=circumference/(currentMillis-startMillis)*1000;
    startMillis=currentMillis;
 counter++;
   Serial.println(String(vecichlespeed)+"m/s");
                                                         }
                                    }


else{
  if(currentMillis-startMillis>=period && laststate==0){
    startMillis=currentMillis;
  laststate=1;
                                                       } 
    }
    
}

/*
SerialEvent occurs whenever a new data comes in the
hardware serial RX. This routine is run between each
time loop() runs, so using delay inside loop can delay
response. Multiple bytes of data may be available.
*/
void serialEvent() {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char) Serial.read();
        // add it to the inputString:
        inputString += inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n') {
            stringComplete = true;
        }
    }
    
}
