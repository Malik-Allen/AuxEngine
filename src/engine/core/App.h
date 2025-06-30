// MIT License, Copyright (c) 2019 Malik Allen

#ifndef AUX_APP_H
#define AUX_APP_H

namespace  AuxEngine
{
    // TODO: Add logic to properly handle appliaction Exit and correct handling in Engine for when the application has been exited.

    class IApp
    {
    public:
        IApp( const IApp& ) = delete;
        IApp& operator=( const IApp& ) = delete;
        IApp( IApp&& ) = delete;
        IApp& operator=( IApp&& ) = delete;

        IApp() = default;
        virtual ~IApp()
        {
            Exit();
        }

        bool Enter()
        {
            return IApp_Enter();
        }

        void Update( const float deltaTime )
        {
            IApp_Update( deltaTime );
        }

        void Exit()
        {
            IApp_Exit();
        }

    private:
        virtual bool IApp_Enter() { return true; }
        virtual void IApp_Update( const float deltaTime ) {}
        virtual void IApp_Exit() {}
    };
}

#endif // !AUX_APP_H