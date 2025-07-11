// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_GLFW_INPUTHANDLER_H
#define AUX_GLFW_INPUTHANDLER_H

#include "engine/core/InputHandler.h"
#include "engine/core/Singleton.h"

class GLFWwindow;

namespace  AuxEngine
{
    class GLFWWindowHandler;
    
    /*
    * GLFW Input Handler is responsible for handling all inputs from all gamepads, keyboards and mice.
    * Functions as singleton to support callbacks of GLFW lib, routes inputs to desired controller objects.
    */
    class GLFWInputHandler : public Singleton<GLFWInputHandler>, public InputHandler
    {
    public:
        GLFWInputHandler( const GLFWInputHandler& ) = delete;
        GLFWInputHandler& operator=( const GLFWInputHandler& ) = delete;
        GLFWInputHandler( GLFWInputHandler&& ) = delete;
        GLFWInputHandler& operator=( GLFWInputHandler&& ) = delete;

        GLFWInputHandler();
        ~GLFWInputHandler() override = default;

        virtual bool Initialize(WindowHandler* windowHandler) override;
        virtual void Update(const float deltaTime) override;
        virtual bool IsKeyDown(Key key) const override;
        virtual bool IsGamepadButtonDown(GamepadId gamepadId, GamepadButton button) const override;
        virtual bool IsGamepadConnected(GamepadId gamepadId) const override;

    protected:
        virtual void OnDeviceConnected(const int inputDeviceId, InputDevice device) override;
        virtual void OnDeviceDisconnected(const int inputDeviceId, InputDevice device) override;

    private:
        const GLFWWindowHandler* windowHandler_;

        // Detects all devices connected for input.
        void RefreshConnectedInputDevices();

        void OnKeyInput(int key, int scancode, int action, int mods);
        void OnMouseButtonInput(int button, int action, int mods);
        void OnMouseScrollInput(double xOffset, double yOffset);
        
        static void InputDeviceConnectionCallback(int inputDeviceId, int eventId);
        static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
    };
}

#endif // AUX_GLFW_INPUTHANDLER_H