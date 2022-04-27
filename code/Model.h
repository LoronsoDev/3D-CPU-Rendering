#pragma once

#include "math.hpp"
#include "Entity.hpp"
#include "Camera.hpp"

#include <string>
#include <vector>
#include <basics/Color_Buffer.hpp>
#include <memory>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

/// <summary>
/// A mesh contains all the vertex data.
/// </summary>
class Mesh
{
public:
	std::vector<glm::fvec4>                     original_vertices;
    std::vector<glm::vec3>                      original_normals;
    std::vector<int>                            original_indices;
    std::vector<argb::Rgb888>                   original_colors;

	size_t                                      number_of_vertices;

	aiMesh * assimpMesh = nullptr;

    //Should be managed by another class, here for this demo...
    std::vector<glm::fvec4>                     transformed_vertices;
    std::vector<glm::ivec4>                     display_vertices;

private:
    glm::vec3 original_color;
    glm::fvec4 lightingPosition;

public:
    Mesh() = default;

	Mesh(aiMesh * assimpMesh, glm::fvec4& lightingPosition)
	{
		this->assimpMesh = assimpMesh;
        this->lightingPosition = lightingPosition;
        this->original_color = { rand_clamp(), rand_clamp(), rand_clamp() };

		this->number_of_vertices = assimpMesh->mNumVertices;
		this->original_vertices     .resize (number_of_vertices);
		this->original_normals      .resize (number_of_vertices);
        this->transformed_vertices  .resize (number_of_vertices);
        this->display_vertices      .resize (number_of_vertices);
		this->original_colors       .resize (number_of_vertices);

        //Copying vertex data...
        for (size_t index = 0; index < number_of_vertices; index++)
        {
            auto& vertex = assimpMesh->mVertices[index];
            auto& normal = assimpMesh->mNormals[index];

            original_vertices[index] = glm::vec4(vertex.x, -vertex.y, vertex.z, 1.f);
            original_normals[index] = glm::normalize(glm::vec3(normal.x, normal.y, normal.z));
        }

        
        // Colores de cada vertice...

        update_lighting();

        // Se generan los índices de los triángulos:

        size_t number_of_triangles = assimpMesh->mNumFaces;

        original_indices.resize(number_of_triangles * 3);

        std::vector<int>::iterator indices_iterator = original_indices.begin();

        for (size_t index = 0; index < number_of_triangles; index++)
        {
            auto& face = assimpMesh->mFaces[index];

            assert(face.mNumIndices == 3);              // Una face puede llegar a tener de 1 a 4 índices,
                                                        // pero nos interesa que solo haya triángulos
            auto indices = face.mIndices;

            *indices_iterator++ = int(indices[0]);
            *indices_iterator++ = int(indices[1]);
            *indices_iterator++ = int(indices[2]);
        }

	}

    /// <summary>
    /// Lambertian shading (no cameras needed)
    /// </summary>
    void update_lighting()
    {
        //LambertShading();
        HalfLambertShading();
    }

    /// <summary>
    /// Shading with reflective surfaces (modified by camera pov)
    /// </summary>
    void update_lighting(Camera& camera)
    {
        PhongShading(camera);
    }

    /// <summary>
    /// Implements Lambert rendering
    /// </summary>
    void LambertShading()
    {
		for (size_t index = 0; index < number_of_vertices; index++)
		{
			glm::vec3 vertexPos = { original_vertices[index].x, original_vertices[index].y, original_vertices[index].z };
			glm::vec3 distance = glm::normalize((glm::vec3)lightingPosition - vertexPos);

			float normalizedDot = glm::max(0.0f, glm::dot(original_normals[index], distance));

            float modifier = normalizedDot;
            
            glm::vec3 modifiedColor;

            //Lambert:
            modifiedColor = original_color * modifier;

			original_colors[index].set(modifiedColor.x, modifiedColor.y, modifiedColor.z);
		}
    }

    void HalfLambertShading()
    {
		for (size_t index = 0; index < number_of_vertices; index++)
		{
			glm::vec3 vertexPos = { original_vertices[index].x, original_vertices[index].y, original_vertices[index].z };
			glm::vec3 distance = glm::normalize((glm::vec3)lightingPosition - vertexPos);

			float normalizedDot = glm::max(0.0f, glm::dot(original_normals[index], distance));

			glm::vec3 modifiedColor;

			//Half-Lambert (Valve):
			// Tries to evade how parts not in light fall to a near-black color.
			// wrap value can be anywhere from 0.5f to 1
			float diffuseWrap = 0.65f;
			modifiedColor = original_color * (float)glm::pow(normalizedDot * diffuseWrap + 1 - diffuseWrap, 2.0);

			original_colors[index].set(modifiedColor.x, modifiedColor.y, modifiedColor.z);
		}
    }

    // Works weird¿?¿?
    void PhongShading(Camera & camera)
    {
		for (size_t index = 0; index < number_of_vertices; index++)
		{
			glm::vec3 vertexPos = { original_vertices[index].x, original_vertices[index].y, original_vertices[index].z };
			glm::vec3 vertexNormal = original_normals[index];

			glm::vec3 lightDir           = glm::normalize((glm::vec3)lightingPosition - vertexPos);

			glm::vec3 viewDir           = glm::normalize(camera.get_position() - vertexPos);
			glm::vec3 lightReflectDir   = glm::reflect(-lightDir, vertexNormal);

			//Phong:

			float RDotV = glm::max(0.0f, glm::dot(viewDir, lightReflectDir));
            float LdotN = glm::max(0.0f, glm::dot(lightDir, vertexNormal));

			float specularStrength = 50.f;
			float shinyness = 128;

            glm::vec3 lightColor = glm::vec3(1, 1, 1);

			glm::vec3 specular = specularStrength * glm::pow(RDotV, shinyness) * lightColor;
            float diffuse = LdotN;

            glm::vec3 modifier = specular + diffuse;
            
            glm::vec3 modifiedColor = original_color * modifier;

			original_colors[index].set(modifiedColor.x, modifiedColor.y, modifiedColor.z);
		}
    }


private:
    //                        Preguntar : (rand() & 0xff) * 0.0039215f

    /// <summary>
    /// Returns a random clamped float (0 - 1)
    /// </summary>
    /// <returns></returns>
    float rand_clamp() { return float(rand() & 0xff) * 0.0039215f; }
};

/// <summary>
/// A model contains an undefined amount of meshes and is visible to a single camera at a time.
/// </summary>
class Model : public Entity
{
private:

	const char* PATH = "UNINITIALIZED";

public:

    std::vector<Mesh> meshes;

    /// <summary>
    /// Each model can control from where it's visible (simulating visibility layers). Also eases implementation of multiple cameras.
    /// </summary>
    Camera* renderCam = nullptr;

    Model() = default;


	/// <param name="renderCam">camera that will render this model</param>
	/// <param name="path">data path storing the model's information</param>
	Model(Camera& renderCam, glm::fvec4& lightingPosition, const char path[])
	{
        this->PATH = path;
        this->renderCam = &renderCam;

		Assimp::Importer importer;

		auto scene = importer.ReadFile
		(
			path,
			aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType
		);

        assert(scene);

		if (scene && scene->mNumMeshes > 0)
		{
            meshes.resize(scene->mNumMeshes);

			for (int i = 0; i < scene->mNumMeshes; i++)
            {
                meshes[i] = Mesh(scene->mMeshes[i], lightingPosition);
            }

		}
	}

    /// <summary>
    /// Changes rendering objective camera.
    /// </summary>
    /// <param name="otherCam"></param>
    void set_render_camera(Camera & otherCam)
    {
        this->renderCam = &otherCam;
    }
};