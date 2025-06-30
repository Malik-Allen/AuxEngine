// MIT License, Copyright (c) 2019 Malik Allen

#ifndef AUX_RENDERER_H
#define AUX_RENDERER_H

#include <string>
#include <memory>

namespace Flow
{
    class IWindowHandler;
    class ICamera;

    class IRenderer
    {
    public:
        IRenderer(const IRenderer&) = delete;
        IRenderer& operator=(const IRenderer&) = delete;
        IRenderer(IRenderer&&) = delete;
        IRenderer& operator=(IRenderer&&) = delete;

        IRenderer() = default;
        virtual ~IRenderer()
        {
            Shutdown();
        }

        bool Init(const std::string& name, IWindowHandler* window)
        {
            return IRenderer_Init(name, window);
        }

        void DrawFrame()
        {
            IRenderer_DrawFrame();
        }

        void Shutdown()
        {
            IRenderer_Shutdown();
        }

        virtual ICamera& GetCamera() = 0;

    private:
        virtual bool IRenderer_Init(const std::string& name, IWindowHandler* window) { return true; }
        virtual void IRenderer_DrawFrame() {}
        virtual void IRenderer_Shutdown() {}
    };
}

#endif // !AUX_RENDERER_H