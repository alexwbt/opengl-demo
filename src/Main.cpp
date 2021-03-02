#include "pch.h"

Camera camera;
CameraControl control(camera, 0.1f, 0.1f);

void MouseInput(GLFWwindow* window, double x, double y)
{
    control.MouseMove((float)x, (float)y);
}

int main()
{
    Window window("OpenGL", 800, 600);
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

    unsigned int textureId = Texture::loadTexture("res/chunk.png", GL_RGB);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);


    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);

    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSetInputMode(window.window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window.window(), MouseInput);

    auto start_time = std::chrono::high_resolution_clock::now();
    double delta_time = 0.0;
    constexpr double time_step = 1000000000.0 / 60.0;

    auto update_timer = std::chrono::high_resolution_clock::now();
    int update_counter = 0;
    while (!glfwWindowShouldClose(window.window()))
    {
        auto now = std::chrono::high_resolution_clock::now();
        delta_time += (double)std::chrono::duration_cast<std::chrono::nanoseconds>(now - start_time).count() / time_step;
        start_time = now;


        bool should_update = delta_time >= 1;
        while (delta_time >= 1)
        {
            // update
            control.Update(
                {
                    glfwGetKey(window.window(), GLFW_KEY_W) == GLFW_PRESS,
                    glfwGetKey(window.window(), GLFW_KEY_S) == GLFW_PRESS,
                    glfwGetKey(window.window(), GLFW_KEY_D) == GLFW_PRESS,
                    glfwGetKey(window.window(), GLFW_KEY_A) == GLFW_PRESS,
                    glfwGetKey(window.window(), GLFW_KEY_SPACE) == GLFW_PRESS,
                    glfwGetKey(window.window(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS
                }
            );
            camera.update();

            update_counter++;
            delta_time--;
        }

        if (should_update)
        {
            // render
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            window.GetSize();
            glm::mat4 projection = glm::perspective(glm::radians(camera.fov),
                (float)window.width() / (float)window.height(), 0.1f, 100.0f);

            glm::mat4 pv = projection * camera.viewMatrix;

            obj.render(&camera, pv);

            glfwSwapBuffers(window.window());
        }

        if (std::chrono::duration_cast<std::chrono::nanoseconds>(now - update_timer).count() >= 1000000000)
        {
            std::cout << update_counter << std::endl;
            update_counter = 0;
            update_timer = now;
        }

        // flashLight.setPosition(camera.position);
        // flashLight.setDirection(camera.front);

        glfwPollEvents();
    }

    glfwTerminate();
}
