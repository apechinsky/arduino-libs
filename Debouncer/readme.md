# An arbitrary value debouncer

 General purpose bounce protection class.
 Unlike Debounce.cpp class this class doesn't read pin value itself so it can be used in any context.
 
 Usage:

 ```c
 if (debouncer.update(newValue)) {
    // value has changed, use it directly or obtain via debouncer.get() method
 } 
 ```
