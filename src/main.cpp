#include "config.h"

int main() {
    GLFWwindow* window;

    // Shader file initialization
    const char *fragment_shader = "fragment_shader.fx", *vertex_shader = "vertex_shader.fx";

    long fragmentShaderFileSize = findFileSize(fragment_shader);
    char *fragmentShaderFile = (char *)malloc(sizeof(char) * fragmentShaderFileSize);
    memset(fragmentShaderFile, 0, fragmentShaderFileSize);
    printFileContents(fragment_shader, &fragmentShaderFile, fragmentShaderFileSize, false);

    long vertexShaderFileSize = findFileSize(vertex_shader);
    char *vertexShaderFile = (char *)malloc(sizeof(char) * vertexShaderFileSize);
    memset(vertexShaderFile, 0, vertexShaderFileSize);
    printFileContents(vertex_shader, &vertexShaderFile, vertexShaderFileSize, false);

    // GLFW initialization
    if (!glfwInit()) {
        fprintf(stderr, "GLFW could not start\n");
        return -1;
    }

    // window initialization
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Test Window", NULL, NULL);
    // Attach window context to current thread (?)
    glfwMakeContextCurrent(window);

    // GLAD stuff
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        glfwTerminate();
        return -1;
    }

    // Get framebuffer info because otherwise scaling will ruin rendering
    int framebufferWidth, framebufferHeight;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    // Set callback for resize
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Rendering
    glClearColor(0.33f, 0.0f, 0.66f, 1.0f);

    TriangleMesh* triangle_mesh = new TriangleMesh();
    Material *material = new Material("./img/kitty.png");
    Material *mask = new Material("./img/mask.png");

    // Make the shader program
    unsigned int shader = make_shader(vertexShaderFile, fragmentShaderFile);

    // set texture units
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "material"), 0);
    glUniform1i(glGetUniformLocation(shader, "mask"), 1);

    glm::vec3 quad_position = {0.1f, -0.2f, 0.0f};

    // Find uniform locations on shader
    unsigned int model_location = glGetUniformLocation(shader, "model");
    unsigned int view_location = glGetUniformLocation(shader, "view");
    unsigned int projection_location = glGetUniformLocation(shader, "projection");

    // Change camera values
    glm::vec3 camera_position = {-5.0f, 0.0f, 3.0f};
    glm::vec3 camera_target   = {0.0f, 0.0f, 0.0f};
    glm::vec3 up              = {0.0f, 0.0f, 1.0f};
    glm::mat4 view = glm::lookAt(camera_position, camera_target, up);

    // Send view to shader
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

    // Make projection
    // Field of View Y, Aspect Ratio, Near, Far
    glm::mat4 projection = glm::perspective(
        45.0f, ASPECT_RATIO, 0.1f, 10.0f
    );

    // Send projection to shader
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, quad_position); // This should have normally been after rotation, but for some reason in GLM it's made that way
        model = glm::rotate(model, (float)glfwGetTime(), { 0.0f, 0.0f, 1.0f }); // This should have normally been before translation, but for some reason in GLM it's made that way

        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shader);

        // Upload model matrix to shader
        glUniformMatrix4fv(model_location, 1, GL_FALSE, value_ptr(model));

        material->use(0);
        mask->use(1);
        triangle_mesh->draw();

        glfwSwapBuffers(window);
    }

    // Close
    glfwTerminate();
    
    free(fragmentShaderFile);
    free(vertexShaderFile);
    delete mask;
    delete material;
    delete triangle_mesh;
    glDeleteProgram(shader);

    return 0;
}