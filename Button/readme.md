# Button library

General purpose button recognizing multiple button events.

Functions:

* press event detection
* release event detection
* click event detection
* multiple click event detection
* long press event detection
* debounce handling via Debounce library
* pull up pin support

Usage:

 ```c
Button button(pin, true);
...

void setup() {
    ...
    button.setOnPressed(onPressed);
    button.setOnReleased(onReleased);
    button.setOnClicked(onClicked);
    button.setOnMultipleClicked(onMultipleClicked);
    button.setOnLongPressed(onLongPressed);
    ...
}

void loop() {
    ...
    button.update();
    ...
}

void onPressed(int count) {
    Serial.print("pressed");
}

void onReleased(int count) {
    Serial.print("released");
}

void onClicked(int count) {
    Serial.print("clicked");
}

void onMultipleClicked(int count) {
    Serial.print("clicked multiple");
}
void onLongPressed(int duration) {
    Serial.print("long press");
}
 ```
