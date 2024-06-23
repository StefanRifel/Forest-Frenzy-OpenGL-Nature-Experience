#ifndef FRAMEBUFFER_HH
#define FRAMEBUFFER_HH

#include "../../libs/SMath/include/vector.hpp"

#include "typs/Vertex.h"
#include "typs/Light.h"

#include "../Shader.hpp"

#include "../../include/loader/AssetLoader.hpp"
#include "../../include/loader/OBJModelLoader.hpp"
#include "../../include/loader/TextureLoader.hpp"

class Framebuffer {
public:
    unsigned int fbo{}, tcb{}, depthBuffer{};
    Shader shader;

    unsigned int quadVAO{}, quadVBO{};

    float quadVertices[24] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
            1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
            1.0f, -1.0f,  1.0f, 0.0f,
            1.0f,  1.0f,  1.0f, 1.0f
    };

    Framebuffer() {
        if (!shader.createShader(
                AssetLoader::getShaderPath("framebuffer_vert.glsl"),
                AssetLoader::getShaderPath("framebuffer_frag.glsl")
        )) {
            std::cerr << "ERROR::MODEL::FAILED_TO_CREATE_SHADER" << std::endl;
        }

        shader.use();
        shader.setInt("framebufferTexture", 0);

        init();
    }

    void init() {
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        // create a color attachment texture
        glGenTextures(1, &tcb);
        glBindTexture(GL_TEXTURE_2D, tcb);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1024, 768, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tcb, 0);
        // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)

        glGenRenderbuffers(1, &depthBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // qued
        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &quadVBO);
        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    }

    void postProcess() const {
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // Zurück zum Standard-Framebuffer
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.use();
        GLint resolutionLoc = glGetUniformLocation(shader.ID, "resolution");
        glUniform2f(resolutionLoc, 1024, 768);
        glBindVertexArray(quadVAO);
        glDisable(GL_DEPTH_TEST);

        glBindTexture(GL_TEXTURE_2D, tcb);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};

#endif //FRAMEBUFFER_HH
