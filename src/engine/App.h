// MIT License, Copyright (c) 2019 Malik Allen

#ifndef AUX_APP_H
#define AUX_APP_H

namespace  AuxEngine
{
    // TODO: Add logic to properly handle appliaction Exit and correct handling in Engine for when the application has been exited.

    class App
    {
    public:
        App( const App& ) = delete;
        App& operator=( const App& ) = delete;
        App( App&& ) = delete;
        App& operator=( App&& ) = delete;

        App() = default;
        virtual ~App()
        {
            Exit();
        }

        bool Enter()
        {
            return OnEnter();
        }

        void Update( const float deltaTime )
        {
            OnUpdate( deltaTime );
        }

        void Exit()
        {
            OnExit();
        }

    private:
        virtual bool OnEnter() { return true; }
        virtual void OnUpdate( const float deltaTime ) {}
        virtual void OnExit() {}
    };
}

#endif // !AUX_APP_H