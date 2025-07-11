// MIT License, Copyright (c) 2024 Malik Allen

#include "engine/devices/glfw/GLFWWindowHandler.h"
#include "engine/core/DebugLog.h"

#include <GLFW/glfw3.h>

namespace  AuxEngine
{
    GLFWWindowHandler::GLFWWindowHandler() :
        window_( nullptr )
    {}

    bool GLFWWindowHandler::InitializeWindow( const int width, const int height, const std::string& name )
    {
        if(!glfwInit())
        {
            DEBUG_LOG(LOG::ERRORLOG, "Failed to initialize GLFW!");
            return false;
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window_ = glfwCreateWindow( width, height, name.c_str(), nullptr, nullptr );
        if (!window_)
        {
            DEBUG_LOG(LOG::ERRORLOG, "Failed to GLFW Window! Window properties: width:{} height:{} name:{}", width, height, name);
            return false;
        }
        return true;
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