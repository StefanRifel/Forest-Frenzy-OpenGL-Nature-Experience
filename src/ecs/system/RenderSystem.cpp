#include "../../../include/RenderSystem.hpp"

RenderSystem::RenderSystem() : windowManager {nullptr} {}

RenderSystem::~RenderSystem() {}

bool RenderSystem::init(WindowManager* windowManager, Shader& shader) {
    this->windowManager = windowManager;
    if(!shader.createShader("../shaders/shader_vert.glsl", "../shaders/shader_frag.glsl")) {
        std::cerr << "ERROR::RenderSystem::FAILED_TO_CREATE_SHADER" << std::endl;
        return false;
    }
    
    windowManager->coordinator.addEventListener(METHOD_LISTENER(event::CHANGECOLOR, RenderSystem::onChangeColor));

    // RenderSystem settings
    cullFace(false);
    polygonModeRasterized(false);
    depthTest(true);

    return true;
}

void RenderSystem::createObject(const char* path, vec3 color, vec3 position) {
    GLuint VAO, VBO, EBO;
    vector<Vertex> vertices;
    vector<GLuint> indices;

    ModelLoader loader {};
    loader.load(path, vertices, indices);
    
    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO for Position
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &(vertices.at(0)), GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,                      // location attribute number in vertex shader  
        3,                      // size of the vertex attribute
        GL_FLOAT,               // type of the data
        GL_FALSE,               // if we want the data to be normalized
        sizeof(Vertex),         // stride and tells us the space between consecutive vertex attributes
        (void*)0                // offset of where the position data begins in the buffer
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,                      
        3,                      
        GL_FLOAT,               
        GL_FALSE,               
        sizeof(Vertex),           
        (void*)sizeof(vec3)                
    );
    glEnableVertexAttribArray(1);

    if(indices.size() != 0) {
        //EBO
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &(indices.at(0)), GL_STATIC_DRAW);
    }

    ecs::Entity entity = windowManager->coordinator.createEntity();
    windowManager->coordinator.addComponent(entity, 
        ecs::Transform{
            .position = position,
            .rotation = vec3 {0.0f, 0.0f, 0.0f},
            .scale = vec3 {0.5f, 0.5f, 0.5f}
        }
    );

    windowManager->coordinator.addComponent(entity, 
        ecs::Renderable{
            .VAO = VAO,
            .VBO = VBO,
            .EBO = EBO,
            .color = color,
            .vertices = vertices,
            .indices = indices,
        }
    );
}

void RenderSystem::render(Shader& shader) {
    shader.use();
    for (auto const& entity : entities) {
        auto& renderable = windowManager->coordinator.getComponent<ecs::Renderable>(entity);
        auto& transform = windowManager->coordinator.getComponent<ecs::Transform>(entity);
        glBindVertexArray(renderable.VAO);
        mat4 model {1.0f};

        model = Transformation::translate(model, transform.position);
        //model = Transformation::scale(model, transform.scale);

        shader.setModel(model);
        shader.setColor(renderable.color, "color");

        glDrawElements(GL_TRIANGLES, renderable.indices.size(), GL_UNSIGNED_INT, 0);
    }
}

void RenderSystem::cullFace(bool b) {
    b ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
}

void RenderSystem::polygonModeRasterized(bool b) {
    b ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void RenderSystem::depthTest(bool b) {
    b ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
}

void RenderSystem::onChangeColor(Event e) {
    for (auto& entity : entities) {
        float* receivedColor = std::any_cast<float*>(e.getData());
        vec3 newColor = {receivedColor[0], receivedColor[1], receivedColor[2]};
        auto& rend = windowManager->coordinator.getComponent<ecs::Renderable>(entity);
        rend.color = newColor;
        std::cout << rend.color << std::endl;
    }
}

void RenderSystem::processInput() {
    if(glfwGetKey(windowManager->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        windowManager->onClose();
    }
    
/*
    const float cameraSpeed = 0.05f; // adjust accordingly

    // Zoom camera out = "." and in = ","
    if (glfwGetKey(windowManager, GLFW_KEY_COMMA) == GLFW_PRESS) {
        camera->cameraPos.z() -= cameraSpeed;
        camera->radiusXZ = camera->cameraPos.z();
        std::cout << "zoom in: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(windowManager, GLFW_KEY_PERIOD) == GLFW_PRESS) {
        camera->cameraPos.z() += cameraSpeed;
        camera->radiusXZ = camera->cameraPos.z();
        std::cout << "zoom out: " << camera->cameraPos << std::endl;
    }

    // change position and point of view of the camera
    if (glfwGetKey(windowManager, GLFW_KEY_UP) == GLFW_PRESS) {
        camera->cameraPos.y() += cameraSpeed;
        camera->cameraFront.y() += cameraSpeed;
        std::cout << "move camera up: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(windowManager, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera->cameraPos.y() -= cameraSpeed;
        camera->cameraFront.y() -= cameraSpeed;
        std::cout << "move camera down: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(windowManager, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera->cameraPos.x() -= cameraSpeed;
        camera->cameraFront.x() -= cameraSpeed;
        std::cout << "move camera left: " << camera->cameraPos << std::endl;
    } else if (glfwGetKey(windowManager, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera->cameraPos.x() += cameraSpeed;
        camera->cameraFront.x() += cameraSpeed;
        std::cout << "move camera right: " << camera->cameraPos << std::endl;
    }

    // rotate model around in x and y axis
    if (glfwGetKey(windowManager, GLFW_KEY_A) == GLFW_PRESS) {
        camera->anlgeXZ--;
        vec3 newPos = Transformation::calcPointOnCircle(camera->anlgeXZ, camera->radiusXZ);
        camera->cameraPos.x() = newPos.x();
        camera->cameraPos.z() = newPos.y();
        std::cout << "turn camera around left: " << camera->cameraPos << std::endl;
    }
    

    if (glfwGetKey(windowManager, GLFW_KEY_D) == GLFW_PRESS) {
        camera->anlgeXZ++;
        vec3 newPos = Transformation::calcPointOnCircle(camera->anlgeXZ, camera->radiusXZ);
        camera->cameraPos.x() = newPos.x();
        camera->cameraPos.z() = newPos.y();
        std::cout << "turn camera around right: " << camera->cameraPos << std::endl;
    }
    */
}