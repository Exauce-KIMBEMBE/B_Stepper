# B_Stepper Library

This is a C++ library for controlling stepper motors using an Arduino. The library provides a convenient interface to control the motor's movement and speed.

## Author

- Exaucé KIMBEMBE
- Email: openprogramming23@gmail.com
- Date: 21/10/2023
- https://www.youtube.com/@OpenProgramming

## Installation

To use this library in your Arduino project, follow these steps:

1. Download the B_Stepper library.
2. Extract the library to your Arduino libraries folder.
3. Include the library in your Arduino sketch.
4. Create an instance of the B_Stepper class and start controlling your stepper motor.

## Public Methods

The following are the public methods that you can use with the B_Stepper library:

### Constructors

- `B_Stepper(uint8_t rpm=DEFAULT_RPM)`: Initialize a stepper motor with a default or custom RPM setting.
- `B_Stepper(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)`: Initialize a stepper motor with custom input pins.

### Setting Parameters

- `void setSteps(int steps)`: Set the number of steps in a movement.
- `void setPins(uint8_t in1, uint8_t in2, uint8_t in3, uint8_t in4)`: Set the input pins for the motor.
- `void setRpm(uint8_t rpm)`: Set the RPM (rotations per minute) for the motor.

### Getting Parameters

- `int getRpm()`: Get the current RPM setting.
- `int getDelay()`: Get the current delay in microseconds between steps.
- `int getTotalSteps()`: Get the total number of steps in a movement.
- `int getStepsLeft()`: Get the number of steps left in the current movement.
- `int getStep()`: Get the current miniStep position.

### Movement Control

- `void move(bool sens=true)`: Start moving the motor in a specified direction (default is clockwise).
- `void newMove(int numSteps=N_STEP)`: Initiate a new movement with a specified number of steps.
- `void newMoveDeg(int Deg=360)`: Initiate a new movement with a specified number of degrees.
- `void stop()`: Stop the motor's movement.

## License

This library is open source, and no specific license is attached. You are free to use, modify, and distribute this library as you see fit. Please respect open-source principles and provide proper attribution when appropriate.

---

Feel free to reach out to the author, Exaucé KIMBEMBE, at openprogramming23@gmail.com if you have any questions or need support.

Happy coding!