// MIT License, Copyright (c) 2024 Malik Allen

#include "engine/devices/glfw/GLFWWindowHandler.h"

#include <GLFW/glfw3.h>

namespace  AuxEngine
{
    GLFWWindowHandler::GLFWWindowHandler() :
        window_( nullptr )
    {}

    bool GLFWWindowHandler::InitializeWindow( const int width, const int height, const std::string& name )
    {
        if( !glfwInit() )
        {
            return false;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window_ = glfwCreateWindow( width, height, name.c_str(), nullptr, nullptr );
        return window_ != nullptr;
    }

    bool GLFWWindowHandler::IsWindowOpen() const
    {
        return window_ != nullptr && !glfwWindowShouldClose( window_ );
    }

    void GLFWWindowHandler::ProcessEvents() const
    {
        if( window_ )
        {
            glfwPollEvents();
            if( glfwWindowShouldClose( window_ ) )
            {
                glfwDestroyWindow( window_ );
                glfwTerminate();
            }
        }
    }

    void GLFWWindowHandler::Shutdown() const
    {
        if( window_ )
        {
            glfwSetWindowShouldClose( window_, GLFW_TRUE );
            glfwDestroyWindow( window_ );
        }
        glfwTerminate();
    }

    GLFWwindow* GLFWWindowHandler::GetWindow() const
    {
        return window_;
    }
}