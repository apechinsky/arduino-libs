#ifndef DigitalDevice_h
#define DigitalDevice_h

#include <WString.h>

/**
 * Represents digital device with single pin interface.
 *
 * Features:
 * - Allows to name device
 * - provides higher level device interface (get/set values) than digitalRead/digitalWrite
 */
class DigitalDevice {

public:

    /**
     * Constructor
     *
     * @pin pin digital pin number
     * @mode pin mode (OUTPUT, INPUT, INPUT_PULLUP)
     * @name device name
     */
    DigitalDevice(int pin, int mode, String name);

    /**
     * Creates INPUT mode deivce
     */
    static DigitalDevice input(int pin, String name);

    /**
     * Creates OUTPUT mode deivce
     */
    static DigitalDevice output(int pin, String name);

    /**
     * Returns current device value
     */
    int get();

    /**
     * Sets value
     */
    void set(int value);

    /**
     * Returns device pin number
     */
    int getPin();

    /**
     * Returns device mode
     */
    int getMode();

    /**
     * Returns device name
     */
    String getName();

private:

    int pin;

    int mode;

    String name;

};
#endif
