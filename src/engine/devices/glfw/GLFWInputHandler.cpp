// MIT License, Copyright (c) 2024 Malik Allen

#include "engine/devices/glfw/GLFWInputHandler.h"
#include "engine/devices/glfw/GLFWWindowHandler.h"

#include "engine/DebugLog.h"
#include "engine/Engine.h"
#include "engine/EngineClock.h"

#include <GLFW/glfw3.h>

namespace  AuxEngine
{
    std::string input_device_to_string(InputDevice device) {
        switch (device) {
        case InputDevice::Keyboard:   return "Keyboard";
        case InputDevice::Mouse:    return "Mouse";
        case InputDevice::Gamepad:  return "Gamepad";
        case InputDevice::Other:    return "Other";
        default:           return "Unknown";
        }
    }

    void GLFWInputHandler::InputDeviceConnectionCallback(int inputDeviceId, int eventId)
    {
        if (eventId == GLFW_CONNECTED)
        {
            GLFWInputHandler::Get().DeviceConnected(inputDeviceId, InputDevice::Gamepad);
        }
        else
        {
            GLFWInputHandler::Get().DeviceDisconnected(inputDeviceId, InputDevice::Gamepad);
        }
    }

    void GLFWInputHandler::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        GLFWInputHandler::Get().OnKeyInput(key, scancode, action, mods);
    }

    void GLFWInputHandler::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        GLFWInputHandler::Get().OnMouseButtonInput(button, action, mods);
    }

    void GLFWInputHandler::MouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    {
        GLFWInputHandler::Get().OnMouseScrollInput(xOffset, yOffset);
    }

    GLFWInputHandler::GLFWInputHandler() :
        windowHandler_( nullptr )
    {}

    bool GLFWInputHandler::Initialize( WindowHandler* windowHandler )
    {
        windowHandler_ = static_cast<GLFWWindowHandler*>( windowHandler );
        if (!windowHandler_)
        {
            DEBUG_LOG(LOG::ERRORLOG, "Failed to init GLFW Input Handler! GLFW Window handler is NULL!");
            return false;
        }

        glfwSetKeyCallback(windowHandler_->window_, KeyboardCallback);
        glfwSetMouseButtonCallback(windowHandler_->window_, MouseButtonCallback);
        glfwSetScrollCallback(windowHandler_->window_, MouseScrollCallback);
        glfwSetJoystickCallback(InputDeviceConnectionCallback);

        RefreshConnectedInputDevices();

        return windowHandler_ != nullptr;
    }

    void GLFWInputHandler::Update(const float deltaTime)
    {
        glfwPollEvents();

        const int currTimestamp = Engine::Get().GetClock().GetCurrentTicks();

        for (int i = 0; i < GetMaxGamepadCount(); ++i)
        {
            if (IsGamepadConnected(static_cast<GamepadId>(i)))
            {
                GLFWgamepadstate state;
                if (glfwGetGamepadState(i, &state))
                {
                    for (int n = 0; n < static_cast<int>(GamepadButton::MAX); ++n)
                    {
                        InputHandler::ProcessGamepadButtonInput(static_cast<GamepadId>(i), InputEvent(n, state.buttons[n], 0.0f, currTimestamp));
                    }

                    for (int n = 0; n < static_cast<int>(GamepadAxis::MAX); ++n)
                    {
                        InputHandler::ProcessGamepadAxisInput(static_cast<GamepadId>(i), InputEvent(n, static_cast<int>(AxisAction::Tilted), state.axes[n], currTimestamp));
                    }
                }
            }
        }

        ExecuteInputBindings();
    }

    bool GLFWInputHandler::IsKeyDown(Key key) const
    {
        return windowHandler_ != nullptr && glfwGetKey(windowHandler_->window_, static_cast<int>(key)) == GLFW_PRESS;
    }

    bool GLFWInputHandler::IsGamepadButtonDown(GamepadId gamepadId, GamepadButton button) const
    {
        if (IsGamepadConnected(gamepadId))
        {
            GLFWgamepadstate state;
            if (glfwGetGamepadState(static_cast<int>(gamepadId), &state))
            {
                return state.buttons[static_cast<int>(button)] == GLFW_PRESS;
            }
        }
        return false;
    }

    bool GLFWInputHandler::IsGamepadConnected(GamepadId gamepadId) const
    {
        if (!InputHandler::IsGamepadConnected(gamepadId))
        {
            return false;
        }

        return glfwJoystickPresent(static_cast<int>(gamepadId)) && glfwJoystickIsGamepad(static_cast<int>(gamepadId));
    }

    void GLFWInputHandler::OnDeviceConnected(const int inputDeviceId, InputDevice device)
    {
        DEBUG_LOG(LOG::INFO, "{} Connected Id = {} ", input_device_to_string(device), inputDeviceId);
    }

    void GLFWInputHandler::OnDeviceDisconnected(const int inputDeviceId, InputDevice device)
    {
        DEBUG_LOG(LOG::INFO, "{} Disconnected Id = {} ", input_device_to_string(device), inputDeviceId);
    }

    void GLFWInputHandler::RefreshConnectedInputDevices()
    {
        for (int i = 0; i < GetMaxGamepadCount(); ++i)
        {
            if (glfwJoystickPresent(i) && glfwJoystickIsGamepad(i))
            {
                DeviceConnected(i, InputDevice::Gamepad);
            }
        }
    }

    void GLFWInputHandler::OnKeyInput(int key, int scancode, int action, int mods)
    {
        const int currTimestamp = Engine::Get().GetClock().GetCurrentTicks();
        InputHandler::ProcessKeyboardInput(InputEvent(key, action, 0.0f, currTimestamp));
    }

    void GLFWInputHandler::OnMouseButtonInput(int button, int action, int mods)
    {
        const int currTimestamp = Engine::Get().GetClock().GetCurrentTicks();
        InputHandler::ProcessMouseButtonInput(InputEvent(button, action, 0.0f, currTimestamp));
    }

    void GLFWInputHandler::OnMouseScrollInput(double xOffset, double yOffset)
    {
        const int currTimestamp = Engine::Get().GetClock().GetCurrentTicks();

        InputHandler::ProcessMouseScrollAxisInput(InputEvent(
            static_cast<int>(MouseScrollAxis::X), static_cast<int>(AxisAction::Tilted), static_cast<float>(xOffset), currTimestamp));

        InputHandler::ProcessMouseScrollAxisInput(InputEvent(
            static_cast<int>(MouseScrollAxis::Y), static_cast<int>(AxisAction::Tilted), static_cast<float>(yOffset), currTimestamp));
    }
}