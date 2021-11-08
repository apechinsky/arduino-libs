#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifdef DESKTOP
#include <iostream>
#include <cstring>

using namespace std;
#endif

#include "CircularBuffer.h"

CircularBuffer::CircularBuffer(int maxSize) {
#ifdef DESKTOP
    if (maxSize < 1) {
        throw "CurcularBuffer size must be > 0";
    }
#endif

    this->bufferSize = maxSize;
    this->head = 0;
    this->tail = -1;

    this->buffer = new char[bufferSize];
    this->buffer[head] = 0;
    clear();
}

CircularBuffer::~CircularBuffer() {
    delete[] buffer;
}

int CircularBuffer::indexOf(const char *string) {
    long stringSize = strlen(string);

    int foundStringIndex = -1;
    int bufferIndex = head;
    int stringIndex = 0;

    for (int i = 0; i < size() && stringIndex < stringSize; i++) {

        if (string[stringIndex] == buffer[bufferIndex]) {
            if (stringIndex == 0) {
                foundStringIndex = bufferIndex;
            }

            stringIndex++;
        }
        else {
            stringIndex = 0;
            foundStringIndex = -1;
        }

        bufferIndex = roll(bufferIndex);
    }

    return stringIndex == stringSize ? foundStringIndex : -1;
}

bool CircularBuffer::contains(const char *string) {
    return indexOf(string) != -1;
}

bool CircularBuffer::contains(const String &string) {
    return contains(string.c_str());
}

String CircularBuffer::getBetween(const char *start, const char *end) {
    int startIndex = indexOf(start);

    if (startIndex == -1) {
        return "error1";
    }

    int startLength = strlen(start);
    startIndex += startLength;

    int endIndex = indexOf(end);

    if (startIndex != -1 && endIndex != -1 && startIndex <= endIndex) {
        char* temp = new char[size()];
        memset(temp, 0, size());

        for (int i = 0; startIndex < endIndex; i++) {
            temp[i] = buffer[startIndex++];
        }
        return String(temp);
    }
    return "error2";
}

void CircularBuffer::add(char c) {

    if (isEmpty()) {
        tail = head;
    }
    else {
        tail = roll(tail);
        if (head == tail) {
            head = roll(head);
        }
    }

    buffer[tail] = c;

}

int CircularBuffer::roll(int value) {
    return (value + 1) % bufferSize;
}

int CircularBuffer::size() {
    return isEmpty()
        ? 0
        : tail >= head
           ? tail - head + 1
           : bufferSize - head + tail + 1;
}

void CircularBuffer::clear() {
    for (int i = 0; i < bufferSize; i++) {
        buffer[i] = 0;
    }
}

void CircularBuffer::empty() {
    tail = -1;
}

bool CircularBuffer::isEmpty() {
    return tail == -1;
}

void CircularBuffer::print() {
    for (int i = 0; i < size(); i++) {
        int index = (head + i) % bufferSize;
        Serial.print(buffer[index]);
    }
    Serial.println();
}

void CircularBuffer::printState() {

#ifdef ARDUINO
    Serial.print(F("Buffer ["));
    Serial.print(F("bufferSize: "));
    Serial.print(bufferSize);
    Serial.print(F(" size: "));
    Serial.print(size());
    Serial.print(F(" head: "));
    Serial.print(head);
    Serial.print(F(" tail: "));
    Serial.print(tail);

    Serial.print(F(" contents: "));
    for (int i = 0; i < size(); i++) {
        int index = (head + i) % bufferSize;
        Serial.print(buffer[index]);
    }

    Serial.print(F(" raw: "));
    for (int i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] == 0 ? '.' : buffer[i]);
    }
    Serial.print(F("]"));
    Serial.println();
#endif
#ifdef DESKTOP
    cout << "Buffer [ "
        << "bufferSize: " << bufferSize
        << " size: "
        << size()
        << " head: "
        << head
        << " tail: "
        << tail;

    cout << " contents: ";
    for (int i = 0; i < size(); i++) {
        int index = (head + i) % bufferSize;
        cout << buffer[index];
    }

    cout << " raw: ";
    for (int i = 0; i < bufferSize; i++) {
        cout << (buffer[i] == 0 ? '.' : buffer[i]);
    }
    cout << "]" << endl;

#endif
}

void CircularBuffer::print(char c) {
    if (c == 0) {
        Serial.print(".");
    }
    else if (c == '\r') {
        Serial.print("CR");
    }
    else if (c == '\n') {
        Serial.print("LF");
    }
    else {
        Serial.print(c);
    }

}

