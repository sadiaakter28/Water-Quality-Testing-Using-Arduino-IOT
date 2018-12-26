#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h> 
#define ONE_WIRE_BUS 12
#define TURB_SENSOR A0

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

// turbidity
float voltage,turbidity;

// temp
float Celsius = 0;
float Fahrenheit = 0;

void setup() {
  sensors.begin();
  pinMode(TURB_SENSOR,INPUT);
  Serial.begin(9600);
  Serial.print("Turbdity and Temperature test");
}

void loop() {
  // Temperature test start
  sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);

  Serial.print(Celsius);
  Serial.print(" C  ");
  Serial.print(Fahrenheit);
  Serial.println(" F");

  delay(2000);

  // Turbidity test start
  voltage=0.004888*analogRead(TURB_SENSOR);  //in V
  turbidity=-1120.4*voltage*voltage+5742.3*voltage-4352.9;  //in NTU
  if((voltage>=1.5)&(turbidity>=0))
  {
    Serial.println("Voltage="+String(voltage)+" V Turbidity="+String(turbidity)+" NTU");  
    delay(2000);
  }
}
