#include "pch.h"

int main()
{
    if (Window::initWindow("OpenGL", 800, 600) != 0)
    {
        return -1;
    }

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    const char* paths[] = { "res/defaultVertexShader.vs", "res/defaultFragmentShader.fs" };
    int types[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
    Shader program1 = Shader(paths, types, 2);

    const char* paths2[] = { "res/type2.vs", "res/type2.fs" };
    int types2[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
    Shader program2 = Shader(paths2, types2, 2);

    Chunk obj = Chunk(&program1);

    Light light(glm::vec3(0.2f, -1.0f, 1.2f), { glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(1.0f) });
    Light::lights.push_back(&light);

    // Light flashLight = Light(glm::vec3(0.0f), glm::vec3(0.0f),
    // 	{ glm::vec3(0.1f), glm::vec3(1.0f), glm::vec3(0.5f) },
    // 	{ 1.0f, 0.09f, 0.032f }, 12.5f, 20.0f);

    // Light::lights.push_back(&flashLight);

    Camera camera = Camera();
    Input::setCamera(&camera, 3.0f, 0.1f);

    unsigned int textureId = Texture::loadTexture("res/chunk.png", GL_RGB);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);


    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSetInputMode(Window::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(Window::window, Input::mouseInput);


    float deltaTime = 0.0f;
    float lastTime = 0.0f;
    float counter = 0.0f;
    int fps = 0;
    while (!glfwWindowShouldClose(Window::window))
    {
        float now = (float)glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        fps++;
        counter += deltaTime;
        if (counter >= 1)
        {
            std::cout << fps << std::endl;
            counter -= 1;
            fps = 0;
        }

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Input::keyInput(deltaTime);

        camera.update();

        // flashLight.setPosition(camera.position);
        // flashLight.setDirection(camera.front);

        glm::mat4 projection = glm::perspective(glm::radians(camera.fov),
            (float)Window::width / (float)Window::height, 0.1f, 100.0f);

        glm::mat4 pv = projection * camera.viewMatrix;

        obj.render(&camera, pv);

        glfwSwapBuffers(Window::window);
        glfwPollEvents();
    }

    glfwTerminate();
}
