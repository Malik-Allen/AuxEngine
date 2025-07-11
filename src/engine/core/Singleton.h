// MIT License, Copyright (c) 2024 Malik Allen

#ifndef AUX_SINGLETON_H
#define AUX_SINGLETON_H

#include <memory>

namespace  AuxEngine
{
    template <typename T>
    class Singleton
    {
        inline static std::unique_ptr<T> instance_ = nullptr;
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
            if( !instance_ )
            {
                instance_.reset( new T() );
            }

            return *instance_.get();
        }
    };
}

#endif // AUX_SINGLETON_H