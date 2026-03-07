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
    window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);
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

    TriangleMesh* triangle = new TriangleMesh();
    Material *material = new Material("./img/kitty.png");
    Material *mask = new Material("./img/mask.png");

    // Make the shader program
    unsigned int shader = make_shader(vertexShaderFile, fragmentShaderFile);

    // set texture units
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader, "material"), 0);
    glUniform1i(glGetUniformLocation(shader, "mask"), 1);

    // Enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shader);
        material->use(0);
        mask->use(1);
        triangle->draw();
        glfwSwapBuffers(window);
    }

    // Close
    glfwTerminate();
    
    free(fragmentShaderFile);
    free(vertexShaderFile);
    delete mask;
    delete material;
    delete triangle;
    glDeleteProgram(shader);

    return 0;
}