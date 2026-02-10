#include "Mesh.hpp"
namespace gps {

	/* Mesh Constructor */
	Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures, Material material) {

		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		this->material = material;
		this->setupMesh();
	}

	Buffers Mesh::getBuffers() {
	    return this->buffers;
	}

	/* Mesh drawing function - also applies associated textures */
	void Mesh::Draw(gps::Shader shader)
{
    shader.useShaderProgram();

    // 1? Send material colors

    glUniform3fv(
        glGetUniformLocation(shader.shaderProgram, "materialDiffuse"),
        1,
        glm::value_ptr(material.diffuse)
    );

    glUniform3fv(
        glGetUniformLocation(shader.shaderProgram, "materialSpecular"),
        1,
        glm::value_ptr(material.specular)
    );

    // 2? Tell shader if texture exists
    glUniform1i(
        glGetUniformLocation(shader.shaderProgram, "hasDiffuseTexture"),
        material.hasDiffuseTexture
    );

    // 3? Bind diffuse texture ONLY if it exists
    if (material.hasDiffuseTexture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0].id);
        glUniform1i(
            glGetUniformLocation(shader.shaderProgram, "diffuseTexture"),
            0
        );
    }

    // 4? Draw geometry
    glBindVertexArray(buffers.VAO);
    glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // 5? Cleanup
    if (material.hasDiffuseTexture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}


	// Initializes all the buffer objects/arrays
	void Mesh::setupMesh() {

		// Create buffers/arrays
		glGenVertexArrays(1, &this->buffers.VAO);
		glGenBuffers(1, &this->buffers.VBO);
		glGenBuffers(1, &this->buffers.EBO);

		glBindVertexArray(this->buffers.VAO);
		// Load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, this->buffers.VBO);
		glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffers.EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

		// Set the vertex attribute pointers
		// Vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		// Vertex Normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
		// Vertex Texture Coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

		glBindVertexArray(0);
	}
}
