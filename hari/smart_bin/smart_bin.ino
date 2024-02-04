#define BLYNK_TEMPLATE_ID "TMPL3kkL9n9U5"
#define BLYNK_TEMPLATE_NAME "Smart Dustbin"
#define BLYNK_AUTH_TOKEN "s51eBljN4f8q8mVArz2heaHzt4qjgVFk"
#define BLYNK_DEVICE_NAME "Smart Dustbin"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Hariharan";
char pass[] = "hariharan";

BlynkTimer timer;

#define echoPin D5
#define trigPin D6
#define greenPin D1
#define redPin D2

long duration;
int distance; 
int binLevel = 0;
WidgetLED ledr(V2);
WidgetLED ledg(V3);
void ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 4; //formula to calculate the distance for ultrasonic sensor
    binLevel = map(distance, 20, 2, 0, 100); // ADJUST BIN HEIGHT HERE
    Blynk.virtualWrite(V0,(distance-2));
    Blynk.virtualWrite(V1,binLevel);
    if (distance >= 20) {
        digitalWrite(greenPin, HIGH);
        ledg.on();
        digitalWrite(redPin, LOW);
        ledr.off();
    } 
    else if (distance <= 2) {
        digitalWrite(greenPin, LOW);
        ledg.off();
        digitalWrite(redPin, HIGH);
        ledr.on();
        Blynk.logEvent("dustbin_full");
      }
    else {
        digitalWrite(greenPin, LOW);
        ledg.off();
        digitalWrite(redPin, HIGH);
        ledr.on();
    }
}

void setup()
{
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    Blynk.begin(auth, ssid, pass);
    delay(2000);
    timer.setInterval(1000L,ultrasonic);
}

void loop() 
{
    Blynk.run();
    timer.run();
}
