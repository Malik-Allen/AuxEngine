// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_GLFW_WINDOWHANDLER_H
#define AUX_GLFW_WINDOWHANDLER_H

#include "engine/core/WindowHandler.h"

class GLFWwindow;

namespace  AuxEngine
{
    class GLFWWindowHandler : public WindowHandler
    {
        friend class GLFWInputHandler;
    public:
        GLFWWindowHandler( const GLFWWindowHandler& ) = delete;
        GLFWWindowHandler& operator=( const GLFWWindowHandler& ) = delete;
        GLFWWindowHandler( GLFWWindowHandler&& ) = delete;
        GLFWWindowHandler& operator=( GLFWWindowHandler&& ) = delete;

        GLFWWindowHandler();
        ~GLFWWindowHandler() override = default;

        virtual bool InitializeWindow( const int width, const int height, const std::string& name ) override;
        virtual bool IsWindowOpen() const override;
        virtual void ProcessEvents() const override;
        virtual void Shutdown() const override;

        GLFWwindow* GetWindow() const;

    private:
        GLFWwindow* window_;
    };
}

#endif // AUX_GLFW_WINDOWHANDLER_H