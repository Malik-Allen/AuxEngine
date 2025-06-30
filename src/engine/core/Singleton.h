// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_SINGLETON_H
#define AUX_SINGLETON_H

#include <memory>

namespace  AuxEngine
{
    template <typename T>
    class Singleton
    {
        inline static std::unique_ptr<T> g_instance = nullptr;
        friend std::default_delete<T>;

    public:
        Singleton( const Singleton& ) = delete;
        Singleton& operator=( const Singleton& ) = delete;
        Singleton( Singleton&& ) = delete;
        Singleton& operator=( Singleton&& ) = delete;

    protected:
        Singleton() = default;
        virtual ~Singleton() = default;

    public:
        static T& Get()
        {
            if( !g_instance )
            {
                g_instance.reset( new T() );
            }

            return *g_instance.get();
        }
    };
}

#endif // AUX_SINGLETON_H