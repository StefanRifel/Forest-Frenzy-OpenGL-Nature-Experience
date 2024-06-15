#ifndef OPENGL_CONTEXT_HH
#define OPENGL_CONTEXT_HH

#include "RenderContext.hpp"
#include "../Window.hpp"

/**
 * @brief The OpenGLContext class manages the OpenGL rendering context.
 */
class OpenGLContext : public RenderContext {
public:
    OpenGLContext() = default;
    ~OpenGLContext();

    bool init(Window* pWindow) override;
    void preRender() override;
    void postRender() override;
};

#endif