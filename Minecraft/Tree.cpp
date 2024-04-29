#include "Tree.h"

Tree::Tree(glm::vec3 spawnPos)
    : position(spawnPos)
{
    GenerateMesh();
}

void Tree::GenerateMesh()
{
    // Define block dimensions
    const float blockWidth = 1.0f;
    const float blockHeight = 1.0f;
    const float blockLength = 1.0f;

    // Initialize vectors to store vertices, texture coordinates, shading values, and indices
    std::vector<GLfloat> blockVertices;
    std::vector<GLfloat> blockTexCoords;
    std::vector<GLfloat> blockShading;
    std::vector<GLuint> blockIndices;

    // Define vertices for a single block
    std::vector<GLfloat> blockVertexTemplate = {
        // Front face
        -blockWidth / 2, 0.0f, blockLength / 2,    // 0: Bottom-left
        -blockWidth / 2, blockHeight, blockLength / 2,    // 1: Top-left
        blockWidth / 2, blockHeight, blockLength / 2,     // 2: Top-right
        blockWidth / 2, 0.0f, blockLength / 2,     // 3: Bottom-right

        // Back face
        blockWidth / 2, 0.0f, -blockLength / 2,    // 4: Bottom-right
        blockWidth / 2, blockHeight, -blockLength / 2,    // 5: Top-right
        -blockWidth / 2, blockHeight, -blockLength / 2,   // 6: Top-left
        -blockWidth / 2, 0.0f, -blockLength / 2,   // 7: Bottom-left

        // Right face
        blockWidth / 2, 0.0f, blockLength / 2,    // 8: Bottom-right
        blockWidth / 2, blockHeight, blockLength / 2,    // 9: Top-right
        blockWidth / 2, blockHeight, -blockLength / 2,   // 10: Top-left
        blockWidth / 2, 0.0f, -blockLength / 2,   // 11: Bottom-left

        // Left face
        -blockWidth / 2, 0.0f, -blockLength / 2,   // 12: Bottom-left
        -blockWidth / 2, blockHeight, -blockLength / 2,   // 13: Top-left
        -blockWidth / 2, blockHeight, blockLength / 2,    // 14: Top-right
        -blockWidth / 2, 0.0f, blockLength / 2,   // 15: Bottom-right

        // Top face
        -blockWidth / 2, blockHeight, blockLength / 2,    // 16: Bottom-left
        -blockWidth / 2, blockHeight, -blockLength / 2,   // 17: Top-left
        blockWidth / 2, blockHeight, -blockLength / 2,    // 18: Top-right
        blockWidth / 2, blockHeight, blockLength / 2,     // 19: Bottom-right

        // Bottom face
        -blockWidth / 2, 0.0f, -blockLength / 2,   // 20: Bottom-left
        -blockWidth / 2, 0.0f, blockLength / 2,    // 21: Top-left
        blockWidth / 2, 0.0f, blockLength / 2,     // 22: Top-right
        blockWidth / 2, 0.0f, -blockLength / 2     // 23: Bottom-right
    };

    // Define texture coordinates for a single block
    std::vector<GLfloat> blockTexCoordsTemplate = {
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,

        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };

    // Define shading values for a single block
    std::vector<GLfloat> blockShadingTemplate = {
        0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f,

        0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f,
        0.6f, 0.6f, 0.6f, 0.6f,

        0.4f, 0.4f, 0.4f, 0.4f,
        0.4f, 0.4f, 0.4f, 0.4f,
        0.4f, 0.4f, 0.4f, 0.4f,
        0.4f, 0.4f, 0.4f, 0.4f,

        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,

        0.8f, 0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f, 0.8f,

        0.8f, 0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f, 0.8f,
        0.8f, 0.8f, 0.8f, 0.8f
    };

    // Define indices for a single block
    std::vector<GLuint> blockIndicesTemplate = {
        0, 1, 2, 0, 2, 3,   // Front face
        4, 5, 6, 4, 6, 7,   // Back face
        8, 9, 10, 8, 10, 11,   // Right face
        12, 13, 14, 12, 14, 15,   // Left face
        16, 17, 18, 16, 18, 19,   // Top face
        20, 21, 22, 20, 22, 23   // Bottom face
    };

    // Loop through each block in the tree
    for (int i = 0; i < 4; ++i) {
        // Calculate position for each block
        float blockY = i * blockHeight;

        // Translate block vertices based on position
        std::vector<GLfloat> translatedVertices;
        for (size_t j = 0; j < blockVertexTemplate.size(); j += 3) {
            translatedVertices.push_back(blockVertexTemplate[j]);
            translatedVertices.push_back(blockVertexTemplate[j + 1] + blockY);
            translatedVertices.push_back(blockVertexTemplate[j + 2]);
        }

        // Add translated block vertices, texture coordinates, shading values, and indices to main vectors
        blockVertices.insert(blockVertices.end(), translatedVertices.begin(), translatedVertices.end());
        blockTexCoords.insert(blockTexCoords.end(), blockTexCoordsTemplate.begin(), blockTexCoordsTemplate.end());
        blockShading.insert(blockShading.end(), blockShadingTemplate.begin(), blockShadingTemplate.end());
        GLuint baseIndex = (i * blockVertexTemplate.size()) / 3; // Adjust base index for each block
        for (auto index : blockIndicesTemplate) {
            blockIndices.push_back(baseIndex + index);
        }
    }

    // Assign generated data to class member variables
    treeVertices = blockVertices;
    treeTexCoords = blockTexCoords;
    treeShading = blockShading;
    treeIndices = blockIndices;

    // Create and bind VAO
    vao.Bind();

    // Create VBOs and EBO
    VBO vertVBO(blockVertices);
    VBO texVBO(blockTexCoords);
    VBO shadingVBO(blockShading);
    EBO ebo(blockIndices);

    // Link VBOs to VAO
    vao.LinkAttrib(vertVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.LinkAttrib(texVBO, 1, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
    vao.LinkAttrib(shadingVBO, 2, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);

    // Unbind VAO, VBOs, and EBO
    vao.Unbind();
    vertVBO.Unbind();
    texVBO.Unbind();
    shadingVBO.Unbind();
    ebo.Unbind();

    // Delete VBOs and EBO
    vertVBO.Delete();
    texVBO.Delete();
    shadingVBO.Delete();
    ebo.Delete();
}


void Tree::Render()
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, treeIndices.size(), GL_UNSIGNED_INT, 0);
}