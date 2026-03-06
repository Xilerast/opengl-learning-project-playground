#pragma once

class TriangleMesh {
    public:
        TriangleMesh();
        void draw();
        ~TriangleMesh();

    private:
        unsigned int VertexBufferObject, VertexArrayObject, vertex_count;
};