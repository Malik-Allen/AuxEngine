# InputHandler – Cross-Device Input Abstraction System

## Overview

The `InputHandler` is a modular and extensible input management system for handling **keyboard**, **mouse**, and **gamepad** inputs in a unified way. It allows you to **bind input events to callback functions**, track device connections, and abstract device-specific logic behind a consistent API.

This handler supports:
- Binding keys and buttons to input actions (e.g. Pressed, Released, Clicked)
- Binding axes (e.g. left stick, scroll wheel) to movement-style callbacks
- Handling multiple gamepads (up to 16)
- Deadzone filtering for thumbsticks and triggers
- Runtime connection/disconnection of devices

`AuxEngine` comes with a `GLFW` Input Handler built in.

### Simple Example

```cpp
// Bind the A button on Gamepad1 to the jump function
Engine::Get()->GetInputHandler().BindGamepadButton(
    GamepadId::Gamepad1,
    GamepadButton::A,
    InputAction::Clicked,
    OnJump
);

// Bind the spacebar to a class method using std::bind
Engine::Get()->GetInputHandler().BindKey(
    Key::Space,
    InputAction::Clicked,
    std::bind(&MyClass::OnSpacebarPressed, this, std::placeholders::_1, std::placeholders::_2)
);

// Bind Left Stick X axis on Gamepad1 to horizontal movement
Engine::Get()->GetInputHandler().BindGamepadAxis(
    GamepadId::Gamepad1,
    GamepadAxis::LeftAxis_X,
    AxisAction::Tilted,
    std::bind(&MyClass::Move_X, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
);
```