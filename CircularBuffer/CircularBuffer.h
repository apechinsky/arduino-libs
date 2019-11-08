#ifndef CircularBuffer_h
#define CircularBuffer_h

/**
 * Circular buffer.
 *
 */
class CircularBuffer {

public:

    /**
     * Constructor.
     *
     * @param maxSize max buffer size (must be > 0)
     */
    CircularBuffer(int maxSize);

    ~CircularBuffer();

    /**
     * Checks if buffer contains specified char array.
     */
    bool contains(const char *string);

    /**
     * Checks if buffer contains specified string.
     */
    bool contains(const String &string);

    /**
     * Adds char to buffer.
     *
     * Removes oldest item if buffer is full.
     */
    void add(char c);

    /**
     * Returns number of characters in buffer.
     */
    int size();

    /**
     * Clear internal buffer.
     */
    void clear();

    /**
     * Empties the buffer.
     */
    void empty();

    /**
     * Checks if buffer is empty.
     */
    bool isEmpty();

    /**
     * Print buffer state.
     */
    void print();

    /**
     * Print char.
     */
    void print(char c);


private:

    char *buffer;

    int bufferSize;

    /**
     * Buffer head. Points to first item.
     */
    int head;

    /**
     * Buffer tail. Points to the last buffer item.
     *
     * For empty buffer value is -1.
     *
     * head == tail if buffer contains single item.
     */
    int tail;

    /**
     * Returns cyclically incremented value.
     */
    int roll(int value);


};

#endif
