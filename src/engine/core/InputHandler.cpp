// MIT License, Copyright (c) 2024 Malik Allen


#include "InputHandler.h"
#include "HighResTimer.h"


namespace  AuxEngine
{
	InputHandler::InputHandler()
	{
		trackedInputDevices_.fill(0);

		// By default the keyboard and mouse devices are assumed to be connected.
		trackedInputDevices_[KEYBOARD_INDEX] = 1;	
		trackedInputDevices_[MOUSE_INDEX] = 1;
	}

	bool InputHandler::IsGamepadConnected(GamepadId gamepadId) const
	{
		return trackedInputDevices_[static_cast<int>(gamepadId)] != 0;
	}

	void InputHandler::DeviceConnected(const int inputDeviceId, InputDevice device)
	{
		trackedInputDevices_[inputDeviceId] = 1;
		OnDeviceConnected(inputDeviceId, device);
	}

	void InputHandler::DeviceDisconnected(const int inputDeviceId, InputDevice device)
	{
		trackedInputDevices_[inputDeviceId] = 0;
		OnDeviceDisconnected(inputDeviceId, device);
	}

	void InputHandler::BindKey(Key key, InputAction action, InputCallback inputCallback)
	{
		if (key != Key::MAX && action != InputAction::Unknown)
		{
			trackedInputCallbacks_[KEYBOARD_INDEX][static_cast<int>(key)] = InputCallbackBinding(inputCallback, static_cast<int>(action));
		}
	}

	void InputHandler::BindMouseButton(MouseButton button, InputAction action, InputCallback inputCallback)
	{
		if (button != MouseButton::MAX && action != InputAction::Unknown)
		{
			trackedInputCallbacks_[MOUSE_INDEX][static_cast<int>(button)] = InputCallbackBinding(inputCallback, static_cast<int>(action));
		}
	}

	void InputHandler::BindMouseScrollWheel(MouseScrollAxis axis, AxisAction action, AxisCallback axisCallback)
	{
		if (axis != MouseScrollAxis::MAX && action != AxisAction::Unknown)
		{
			trackedAxisCallbacks_[MOUSE_INDEX][static_cast<int>(axis)] = AxisCallbackBinding(axisCallback, static_cast<int>(action));
		}
	}

	void InputHandler::BindGamepadButton(GamepadId gamepadId, GamepadButton button, InputAction action, InputCallback inputCallback)
	{
		if (gamepadId != GamepadId::MAX && button != GamepadButton::MAX && action != InputAction::Unknown)
		{
			trackedInputCallbacks_[static_cast<int>(gamepadId)][static_cast<int>(button)] = InputCallbackBinding(inputCallback, static_cast<int>(action));
		}
	}

	void InputHandler::BindGamepadAxis(GamepadId gamepadId, GamepadAxis axis, AxisAction action, AxisCallback axisCallback)
	{
		if (gamepadId != GamepadId::MAX && axis != GamepadAxis::MAX && action != AxisAction::Unknown)
		{
			trackedAxisCallbacks_[static_cast<int>(gamepadId)][static_cast<int>(axis)] = AxisCallbackBinding(axisCallback, static_cast<int>(action));
		}
	}

	void InputHandler::ClearKeyBinding(Key key)
	{
		trackedInputCallbacks_[KEYBOARD_INDEX].erase(static_cast<int>(key));
	}

	void InputHandler::ClearMouseButtonBinding(MouseButton button)
	{
		trackedInputCallbacks_[MOUSE_INDEX].erase(static_cast<int>(button));
	}

	void InputHandler::ClearMouseScrollAxisBinding(MouseScrollAxis axis)
	{
		trackedAxisCallbacks_[MOUSE_INDEX].erase(static_cast<int>(axis));
	}

	void InputHandler::ClearGamepadButtonBinding(GamepadId gamepadId, GamepadButton button)
	{
		if (gamepadId != GamepadId::MAX)
		{
			trackedInputCallbacks_[static_cast<int>(gamepadId)].erase(static_cast<int>(button));
		}
	}

	void InputHandler::ClearGamepadAxisBinding(GamepadId gamepadId, GamepadAxis axis)
	{
		if (gamepadId != GamepadId::MAX)
		{
			trackedAxisCallbacks_[static_cast<int>(gamepadId)].erase(static_cast<int>(axis));
		}
	}

	void InputHandler::ProcessKeyboardInput(const InputEvent& inputEvent)
	{
		if (inputEvent.button < static_cast<int>(Key::MAX))
		{
			ProcessButtonInput(KEYBOARD_INDEX, inputEvent);
		}
	}

	void InputHandler::ProcessMouseButtonInput(const InputEvent& inputEvent)
	{
		if (inputEvent.button < static_cast<int>(MouseButton::MAX))
		{
			ProcessButtonInput(MOUSE_INDEX, inputEvent);
		}
	}

	void InputHandler::ProcessMouseScrollAxisInput(const InputEvent& inputEvent)
	{
		if (inputEvent.button < static_cast<int>(MouseScrollAxis::MAX))
		{
			ProcessAxisInput(MOUSE_INDEX, inputEvent);
		}
	}

	void InputHandler::ProcessGamepadButtonInput(GamepadId gamepadId, const InputEvent& inputEvent)
	{
		if (inputEvent.button < static_cast<int>(GamepadButton::MAX) && gamepadId != GamepadId::MAX)
		{
			ProcessButtonInput(static_cast<int>(gamepadId), inputEvent);
		}
	}

	void InputHandler::ProcessGamepadAxisInput(GamepadId gamepadId, const InputEvent& inputEvent)
	{
		if (inputEvent.button < static_cast<int>(GamepadAxis::MAX) && gamepadId != GamepadId::MAX)
		{
			ProcessAxisInput(static_cast<int>(gamepadId), inputEvent);
		}
	}

	void InputHandler::ExecuteInputBindings()
	{
		for (int i = 0; i < MAX_INPUT_DEVICE_COUNT; ++i)
		{
			for (const auto& [buttonId, inputCallbackBinding] : trackedInputCallbacks_[i])
			{
				InputInstance inputInstance = trackedInputs_[i][buttonId];
				if (inputCallbackBinding.action != -1 
					&& inputInstance.bIsConsumed == false
					&& static_cast<int>(inputInstance.cachedAction) == inputCallbackBinding.action)
				{
					inputCallbackBinding.inputCallback(buttonId, inputCallbackBinding.action);
					inputInstance.bIsConsumed = true;
					trackedInputs_[i][buttonId] = inputInstance;
				}
			}

			for (const auto& [axisId, axisCallbackBinding] : trackedAxisCallbacks_[i])
			{
				InputInstance inputInstance = trackedAxes_[i][axisId];
				if (axisCallbackBinding.axisAction != -1
					&& inputInstance.bIsConsumed == false
					&& static_cast<int>(inputInstance.cachedAxisAction) == axisCallbackBinding.axisAction)
				{
					axisCallbackBinding.axisCallback(axisId, axisCallbackBinding.axisAction, inputInstance.currInputEvent.value);
					inputInstance.bIsConsumed = true;
					trackedAxes_[i][axisId] = inputInstance;
				}
			}
		}
	}

	void InputHandler::ProcessButtonInput(const unsigned int inputDeviceId, const InputEvent& inputEvent)
	{
		if (inputEvent.button < 0)
		{
			return;
		}

		InputInstance inputInstance = trackedInputs_[inputDeviceId][inputEvent.button];

		// Updating Input Events if the incoming action is different than the last action.
		if (inputInstance.currInputEvent.action != inputEvent.action)
		{
			inputInstance.bIsConsumed = false;
			inputInstance.prevInputEvent = inputInstance.currInputEvent;
			inputInstance.currInputEvent = inputEvent;
		}

		const InputAction prevAction = static_cast<InputAction>(inputInstance.prevInputEvent.action);
		const InputAction currAction = static_cast<InputAction>(inputInstance.currInputEvent.action);

		if (prevAction == InputAction::Pressed
			&& currAction == InputAction::Released)
		{
			const int TimeBetweenCurrentAndPreviousInput = inputInstance.currInputEvent.timestamp - inputInstance.prevInputEvent.timestamp;
			if ((TimeBetweenCurrentAndPreviousInput) <= CLICK_TIME)
			{
				inputInstance.cachedAction = InputAction::Clicked;
			}
			else
			{
				inputInstance.cachedAction = InputAction::Released;
			}
		}
		else
		{
			inputInstance.cachedAction = currAction;
		}

		trackedInputs_[inputDeviceId][inputEvent.button] = inputInstance;
	}

	void InputHandler::ProcessAxisInput(const unsigned int inputDeviceId, const InputEvent& inputEvent)
	{
		if (inputEvent.button < 0)
		{
			return;
		}

		InputInstance inputInstance = trackedAxes_[inputDeviceId][inputEvent.button];

		const bool bIsTriggerAxis = IsTriggerAxis(static_cast<GamepadAxis>(inputEvent.button));

		const float Deadzone = bIsTriggerAxis ? DEADZONE_TRIGGER : DEADZONE_THUMBSTICK;

		bool bIsAlive = false;
		if (bIsTriggerAxis)
		{
			bIsAlive = inputEvent.value >= Deadzone;
		}
		else
		{
			bIsAlive = inputEvent.value >= Deadzone || inputEvent.value <= -Deadzone;
		}

		// When the axis is alive we update the current input, with the new value.
		if (bIsAlive)
		{
			inputInstance.bIsConsumed = false;
			inputInstance.prevInputEvent = inputInstance.currInputEvent;
			inputInstance.currInputEvent = inputEvent;

			inputInstance.cachedAxisAction = AxisAction::Tilted;

			const InputAction prevAction = static_cast<InputAction>(inputInstance.prevInputEvent.action);
			const InputAction currAction = static_cast<InputAction>(inputInstance.currInputEvent.action);
		}
		else
		{
			inputInstance.cachedAxisAction = AxisAction::Unknown;
		}

		trackedAxes_[inputDeviceId][inputEvent.button] = inputInstance;
	}

	bool InputHandler::IsTriggerAxis(GamepadAxis axis) const
	{
		return axis == GamepadAxis::LeftTrigger || axis == GamepadAxis::RightTrigger;
	}
}