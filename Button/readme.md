# Button library

General purpose button with debounce handler.

Usage:

 ```c
Button button(pin, true);
...

void setup() {
    ...
    button.setOnClicked(onButtonClick);
    button.setOnMultipleClicking(onButtonClicking);
    button.setOnMultipleClicked(onButtonClicked);
    button.setOnLongPressed(onButtonLongPressed);
    ...
}

void loop() {
    ...
    button.update();
    ...
}

void onButtonClick() {
    Serial.println("button click");
}

void onButtonClicking(int count) {
    Serial.print("button clicking ");
    Serial.println(count);
}

void onButtonClicked(int count) {
    Serial.print("button clicked ");
    Serial.println(count);
}

void onButtonLongPressed(int duration) {
    Serial.print("button clicked ");
    Serial.println(count);
}
 ```
