#include "config.h"

TriangleMesh::TriangleMesh() {
    // Elements/positions vector
    // We are reusing elements that we don't waste memory
    std::vector<float> positions = {
        -1.0f, -1.0f, 0.0f, // Bottom left
         1.0f, -1.0f, 0.0f, // Bottom right
        -1.0f,  1.0f, 0.0f, // Top left
         1.0f,  1.0f, 0.0f  // Top right
    };
    std::vector<int> colorIndices = {
        0, 1, 2, 3
    };
    std::vector<int> elements = {
        0, 1, 2, 2, 1, 3    // START TOP AND LEFT AND GO COUNTERCLOCKWISE ALWAYS
    };
    this->ElementCount = 6;

    // Prepare vertex array object
    glGenVertexArrays(1, &this->VertexArrayObject);
    glBindVertexArray(this->VertexArrayObject);

    // We need 2 Vertex Buffer Objects, 1 for each triangle to form a square
    this->VertexBufferObjects.resize(2);

    // Prepare vertex buffer object (0s and 1s)
    glGenBuffers(1, &this->VertexBufferObjects[0]);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObjects[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), 
            GL_STATIC_DRAW);

    // Position attribute, being the first (0) 3 on each row
    // Type float, do not normalize, 6 floats * 4 bytes = 24 (stride)
    // Point after 0 floats, at the start
    glVertexAttribPointer(0, 3, GL_FLOAT, 
            GL_FALSE, 12, (void*)0);
    glEnableVertexAttribArray(0);

    // Prepare the Vertex Buffer Object for color
    glGenBuffers(1, &this->VertexBufferObjects[1]);
    glBindBuffer(GL_ARRAY_BUFFER, this->VertexBufferObjects[1]);
    glBufferData(
        GL_ARRAY_BUFFER,
        colorIndices.size() * sizeof(int),
        colorIndices.data(), GL_STATIC_DRAW
    );
    // Color attribute, being the second (1) 3 on each row
    // Type float, do not normalize, 6 floats * 4 bytes = 24 (stride)
    // Point after 3 floats * 4 bytes per float = 12
    glVertexAttribIPointer(1, 1, GL_INT, 4, (void *) 0);
    glEnableVertexAttribArray(1);

    // Prepare the element buffer object
    glGenBuffers(1, &this->ElementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ElementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(int), elements.data(), GL_STATIC_DRAW);
}

void TriangleMesh::draw() {
    glBindVertexArray(VertexArrayObject);
    glDrawElements(GL_TRIANGLES, this->ElementCount, GL_UNSIGNED_INT, 0);
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &this->VertexArrayObject);
    glDeleteBuffers(this->VertexBufferObjects.size(), this->VertexBufferObjects.data());
    glDeleteBuffers(1, &this->ElementBufferObject);
}