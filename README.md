Arduino Smart Button — FSM-Based Button Controller

A smart button controller developed for Arduino Uno, using a Finite State Machine (FSM) to detect different button press patterns and control LEDs.

The project demonstrates embedded programming concepts including GPIO control, software debouncing, state machines, and non-blocking timing using millis().

Features
Short press detection
Long press detection
Extended press detection
Double-click detection
Software button debouncing (20 ms)
Finite State Machine (FSM) implementation
Non-blocking timing without delay()
Serial debugging via UART (9600 baud)
Hardware Components
Arduino Uno
1 push button
4 LEDs (red, green, blue, yellow)
4 current-limiting resistors
Breadboard and jumper wires
Pin Configuration
Component	Arduino Pin
Push button	D3
Blue LED	D4
Red LED	D5
Green LED	D6
Yellow LED	D7

The button uses INPUT_PULLUP and is connected between D3 and GND. Each LED is connected through a current-limiting resistor.

Button Actions
Action	Press Duration	LED Response
Short press	50–299 ms	Red LED, 100 ms
Long press	301–700 ms	Green LED, 100 ms
Extended press	Over 700 ms	Blue LED, 5 seconds
Double click	Two consecutive presses	Yellow LED, 100 ms

The second click must begin within approximately 300 ms after the first release.

Press duration is evaluated after the button is released.

Software Architecture

The application uses a Finite State Machine with six states:

WAIT_PRESS — Wait for a button press.
DEBOUNCE_PRESS — Validate the press after 20 ms.
PRESSED — Wait for button release.
DEBOUNCE_RELEASE — Validate the release after 20 ms.
WAIT_SECOND_CLICK — Wait for a possible second click.
ACTION — Execute the detected action.

The implementation uses millis() instead of blocking delay() calls, allowing LED timing and button processing to run within the main loop.

How to Run
Open arduino_smart_button.ino in Arduino IDE.
Select Arduino Uno as the target board.
Connect the Arduino to your computer.
Compile and upload the sketch.
Open Serial Monitor at 9600 baud.
Press the button to test the different actions.
Technologies
Arduino / C++
GPIO
Finite State Machine (FSM)
Software Debouncing
Non-blocking Timing
UART Serial Communication
Future Improvements
Improve debounce handling for invalid transitions.
Add real-time button-hold detection.
Refactor the code for better readability and maintainability.
Add a circuit diagram and hardware demonstration.
