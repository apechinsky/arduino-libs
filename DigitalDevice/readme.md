# DigitalDevice library

Encapsulates digital pin number, operation mode and underlying device name in a single object.

Without DigitalDevice
```
#DEFINE LAMP_PIN 7

void setup() {

pinMode(LAMP_PIN, OUTPUT);

}

void loop() {

    digitalWrite(LAMP_PIN, HIGH)
}

```

With DigitalDevice
```
DigitalDevice lamp(7, "Lamp");

void loop() {

    lamp.set(HIGH);
}

```
