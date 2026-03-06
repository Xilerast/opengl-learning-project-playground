#include "config.h"

TriangleMesh::TriangleMesh() {
    // This data vector has 2 *attributes*,
    // the position of the vertices and their color.
    std::vector<float> data = {
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom left
         1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom right
        -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f  // Top left
    };
    vertex_count = 3;

    // Prepare vertex array object
    glGenVertexArrays(1, &this->VertexArrayObject);
    glBindVertexArray(this->VertexArrayObject);

    // Prepare vertex buffer object (0s and 1s)
    glGenBuffers(1, &this->VertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObject);
    size_t bufferSize = data.size() * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, data.data(), 
            GL_STATIC_DRAW);

    // Position attribute, being the first (0) 3 on each row
    // Type float, do not normalize, 6 floats * 4 bytes = 24
    // Point after 0 floats, at the start
    glVertexAttribPointer(0, 3, GL_FLOAT, 
            GL_FALSE, 24, (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute, being the second (1) 3 on each row
    // Type float, do not normalize, 6 floats * 4 bytes = 24
    // Point after 3 floats * 4 bytes per float = 12
    glVertexAttribPointer(1, 3, GL_FLOAT, 
            GL_FALSE, 24, (void*)12);
    glEnableVertexAttribArray(1);
}

void TriangleMesh::draw() {
    glBindVertexArray(VertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, this->vertex_count);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &this->VertexArrayObject);
    glDeleteBuffers(1, &this->VertexBufferObject);
}