#pragma once

class TriangleMesh {
    public:
        TriangleMesh();
        void draw();
        ~TriangleMesh();

    private:
        unsigned int ElementBufferObject, VertexArrayObject, ElementCount;
        std::vector<unsigned int> VertexBufferObjects;
};