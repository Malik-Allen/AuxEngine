// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_INPUTHANDLER_H
#define AUX_INPUTHANDLER_H

#include <unordered_map>
#include <functional>
#include <array>

namespace  AuxEngine
{
    class IWindowHandler;

    enum class GamepadId : int
    {
        Gamepad1 = 0,
        Gamepad2 = 1,
        Gamepad3 = 2,
        Gamepad4 = 3,
        Gamepad5 = 4,
        Gamepad6 = 5,
        Gamepad7 = 6,
        Gamepad8 = 7,
        Gamepad9 = 8,
        Gamepad10 = 9,
        Gamepad11 = 10,
        Gamepad12 = 11,
        Gamepad13 = 12,
        Gamepad14 = 13,
        Gamepad15 = 14,
        Gamepad16 = 15,
        MAX = 16
    };

    enum class GamepadButton
    {
        Unknown = -1,
        A = 0,
        B = 1,
        X = 2,
        Y = 3,
        LeftBumper = 4,
        RightBumper = 5,
        Back = 6,
        Start = 7,
        Guide = 8,
        LeftThumb = 9,
        RightThumb = 10,
        DpadUp = 11,
        DpadRight = 12,
        DpadDown = 13,
        DpadLeft = 14,
        MAX = 15,

        // Aliases for clarity and convenience
        Cross = 0,
        Circle = 1,
        Square = 2,
        Triangle = 3
    };

    enum class GamepadAxis
    {
        Unknown = -1,
        LeftAxis_X = 0,
        LeftAxis_Y = 1,
        RightAxis_X = 2,
        RightAxis_Y = 3,
        LeftTrigger = 4,
        RightTrigger = 5,
        MAX = 6
    };

    enum class Key
    {
        Unknown = -1,
        Space = 32,
        Apostrophe = 39,
        Comma = 44,
        Minus = 45,
        Period = 46,
        Slash = 47,
        _0 = 48,
        _1 = 49,
        _2 = 50,
        _3 = 51,
        _4 = 52,
        _5 = 53,
        _6 = 54,
        _7 = 55,
        _8 = 56,
        _9 = 57,
        Semicolon = 59,
        Equal = 61,
        A = 65,
        B = 66,
        C = 67,
        D = 68,
        E = 69,
        F = 70,
        G = 71,
        H = 72,
        I = 73,
        J = 74,
        K = 75,
        L = 76,
        M = 77,
        N = 78,
        O = 79,
        P = 80,
        Q = 81,
        R = 82,
        S = 83,
        T = 84,
        U = 85,
        V = 86,
        W = 87,
        X = 88,
        Y = 89,
        Z = 90,
        LeftBracket = 91,
        Backslash = 92,
        RightBracket = 93,
        GraveAccent = 96,
        World1 = 161,
        World2 = 162,
        Escape = 256,
        Enter = 257,
        Tab = 258,
        Backspace = 259,
        Insert = 260,
        Delete = 261,
        Right = 262,
        Left = 263,
        Down = 264,
        Up = 265,
        PageUp = 266,
        PageDown = 267,
        Home = 268,
        End = 269,
        CapsLock = 280,
        ScrollLock = 281,
        NumLock = 282,
        PrintScreen = 283,
        Pause = 284,
        F1 = 290,
        F2 = 291,
        F3 = 292,
        F4 = 293,
        F5 = 294,
        F6 = 295,
        F7 = 296,
        F8 = 297,
        F9 = 298,
        F10 = 299,
        F11 = 300,
        F12 = 301,
        F13 = 302,
        F14 = 303,
        F15 = 304,
        F16 = 305,
        F17 = 306,
        F18 = 307,
        F19 = 308,
        F20 = 309,
        F21 = 310,
        F22 = 311,
        F23 = 312,
        F24 = 313,
        F25 = 314,
        Numpad0 = 320,
        Numpad1 = 321,
        Numpad2 = 322,
        Numpad3 = 323,
        Numpad4 = 324,
        Numpad5 = 325,
        Numpad6 = 326,
        Numpad7 = 327,
        Numpad8 = 328,
        Numpad9 = 329,
        NumpadDecimal = 330,
        NumpadDivide = 331,
        NumpadMultiply = 332,
        NumpadSubtract = 333,
        NumpadAdd = 334,
        NumpadEnter = 335,
        NumpadEqual = 336,
        ShiftLeft = 340,
        ControlLeft = 341,
        AltLeft = 342,
        SuperLeft = 343,
        ShiftRight = 344,
        ControlRight = 345,
        AltRight = 346,
        SuperRight = 347,
        Menu = 348,
        MAX = 349
    };

    enum class MouseButton
    {
        Unknown = -1,
        Button1 = 0,  // Usually Left
        Button2 = 1,  // Usually Right
        Button3 = 2,  // Usually Middle
        Button4 = 3,  // Typically side button 1
        Button5 = 4,  // Typically side button 2
        Button6 = 5,
        Button7 = 6,
        Button8 = 7,
        MAX = 8
    };

    enum class MouseScrollAxis
    {
        X = 0,
        Y = 1,
        MAX = 2
    };

    // The physical action done by the user.
    enum class InputAction
    {
        Unknown = -1,
        Released = 0,
        Pressed = 1,
        Clicked = 2,
    };

    enum class AxisAction
    {
        Unknown = -1,
        Tilted = 0,
        Flicked = 1
    };

    struct InputEvent
    {
        int button = -1;  // Can be a Key, Mouse Button, or Gamepad Button. Also used to represent Axis Id, when input is coming from an Axis.
        int action = 0;  
        float value = 0.0f; // Used store the axis value from -1.0f to 1.0f inclusive
        unsigned int timestamp = 0;
    };

    struct InputInstance
    {
        InputEvent prevInputEvent;
        InputEvent currInputEvent;

        // The cached action used to determine when an input binding is triggered.
        InputAction cachedAction = InputAction::Unknown;

        // The cached axis action used to determine when an axis binding is triggered.
        AxisAction cachedAxisAction = AxisAction::Unknown;

        bool bIsConsumed = false;

        unsigned int AccumulatedHoldTime = 0;
    };

    enum class InputDevice
    {
        Keyboard = 0,
        Mouse,
        Gamepad,
        Other
    };

    class InputHandler
    {
        // Time window between press and release state of an input to be considered clicked.
        static constexpr unsigned int CLICK_TIME{ 350 };

        // Max Number of Gamepads supported by this input handler.
        static constexpr unsigned int MAX_GAMEPAD_COUNT{ 16 };

        // Up to 16 gamepads + 1 keyboard + 1 mouse.
        static constexpr unsigned int MAX_INPUT_DEVICE_COUNT{ 18 };
        static constexpr unsigned int KEYBOARD_INDEX{ 16 };
        static constexpr unsigned int MOUSE_INDEX{ 17 };

        static constexpr float DEADZONE_THUMBSTICK{ 0.25f };
        // Neutral Trigger values start at -1.0f
        static constexpr float DEADZONE_TRIGGER{ -0.95f };

        using TrackedInputMap = std::unordered_map<int /*Button Id*/, InputInstance>;

        // ~~~ Button Input Bindings Type Definitions ~~~
        
        using InputCallback = std::function<void(int button, int action)>;
        struct InputCallbackBinding
        {
            InputCallback inputCallback;
            int action = -1;
        };
        using InputCallbackMap = std::unordered_map<int, InputCallbackBinding>;


        // ~~~ Axis Bindings Type Definitions ~~~

        using AxisCallback = std::function<void(int axis, int action, float value)>;
        struct AxisCallbackBinding
        {
            AxisCallback axisCallback;
            int axisAction = -1;
        };
        using AxisCallbackMap = std::unordered_map<int, AxisCallbackBinding>;


    public:
        InputHandler( const InputHandler& ) = delete;
        InputHandler& operator=( const InputHandler& ) = delete;
        InputHandler( InputHandler&& ) = delete;
        InputHandler& operator=( InputHandler&& ) = delete;

        InputHandler();
        virtual ~InputHandler() = default;

        virtual bool Initialize(IWindowHandler* windowHandler) = 0;
        virtual void Update(const float deltaTime) = 0;
        virtual bool IsKeyDown(Key key) const = 0;
        virtual bool IsGamepadButtonDown(GamepadId gamepadId, GamepadButton button) const = 0;

        virtual bool IsGamepadConnected(GamepadId gamepadId) const;
        int GetMaxGamepadCount() const { return MAX_GAMEPAD_COUNT; }
        int GetKeyboardDeviceId() const { return KEYBOARD_INDEX; }
        int GetMouseDeviceId() const { return MOUSE_INDEX; }

    protected:
        void DeviceConnected(const int inputDeviceId, InputDevice device);
        void DeviceDisconnected(const int inputDeviceId, InputDevice device);

        virtual void OnDeviceConnected(const int inputDeviceId, InputDevice device) = 0;
        virtual void OnDeviceDisconnected(const int inputDeviceId, InputDevice device) = 0;

    public:
        // TODO: Find out how I can remove the need to add the placeholder params on std::bind(...) for input and axis bindings.

        void BindKey(Key key, InputAction action, InputCallback inputCallback);
        void BindMouseButton(MouseButton button, InputAction action, InputCallback inputCallback);
        void BindMouseScrollWheel(MouseScrollAxis axis, AxisAction action, AxisCallback axisCallback);
        void BindGamepadButton(GamepadId gamepadId, GamepadButton button, InputAction action, InputCallback inputCallback);
        void BindGamepadAxis(GamepadId gamepadId, GamepadAxis axis, AxisAction action, AxisCallback axisCallback);

        // TODO: Add cursor position bindings. Consider on mouse button click obtains the mouse position as well.

        void ClearKeyBinding(Key key);
        void ClearMouseButtonBinding(MouseButton button);
        void ClearMouseScrollAxisBinding(MouseScrollAxis axis);
        void ClearGamepadButtonBinding(GamepadId gamepadId, GamepadButton button);
        void ClearGamepadAxisBinding(GamepadId gamepadId, GamepadAxis axis);

        // TODO: Add support for unique input binding. At the moment a single function can be bound to inputs. Requiring clearing of all bindings at input if you would like to bind something else to the input.

    protected:
        void ProcessKeyboardInput(const InputEvent& inputEvent);
        void ProcessMouseButtonInput(const InputEvent& inputEvent);
        void ProcessMouseScrollAxisInput(const InputEvent& inputEvent);
        void ProcessGamepadButtonInput(GamepadId gamepadId, const InputEvent& inputEvent);
        void ProcessGamepadAxisInput(GamepadId gamepadId, const InputEvent& inputEvent);

        void ExecuteInputBindings();

    private:
        // Value of 1 at the given device index, means device is connected. Value of 0 means the device at the given index is not connected.
        std::array<int, MAX_INPUT_DEVICE_COUNT> m_trackedInputDevices = {};
        std::unordered_map<int /*Device Input Id*/, TrackedInputMap> m_trackedInputs;
        std::unordered_map<int /*Device Input Id*/, InputCallbackMap> m_trackedInputCallbacks;

        std::unordered_map<int /*Device Input Id*/, TrackedInputMap> m_trackedAxes;
        std::unordered_map<int /*Device Input Id*/, AxisCallbackMap> m_trackedAxisCallbacks;

        void ProcessButtonInput(const unsigned int inputDeviceId, const InputEvent& inputEvent);
        void ProcessAxisInput(const unsigned int inputDeviceId, const InputEvent& inputEvent);

        bool IsTriggerAxis(GamepadAxis axis) const;
    };
}

#endif // INPUTHANDLER_H
