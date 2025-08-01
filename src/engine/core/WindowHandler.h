﻿// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_WINDOWHANDLER_H
#define AUX_WINDOWHANDLER_H

#include <string>

namespace  AuxEngine
{
    class WindowHandler
    {
    public:
        WindowHandler( const WindowHandler& ) = delete;
        WindowHandler& operator=( const WindowHandler& ) = delete;
        WindowHandler( WindowHandler&& ) = delete;
        WindowHandler& operator=( WindowHandler&& ) = delete;

        WindowHandler() = default;
        virtual ~WindowHandler() = default;

        virtual bool InitializeWindow( const int width, const int height, const std::string& name ) = 0;
        virtual bool IsWindowOpen() const = 0;
        virtual void ProcessEvents() const = 0;
        virtual void Shutdown() const = 0;
    };
}

#endif // AUX_WINDOWHANDLER_H
