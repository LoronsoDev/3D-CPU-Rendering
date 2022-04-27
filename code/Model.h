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
    std::vector<int>                            original_indices;
    std::vector<argb::Rgb888>                   original_colors;

	size_t                                      number_of_vertices;

	aiMesh * assimpMesh = nullptr;

    //Should be managed by another class, here for this demo...
    std::vector<glm::fvec4>                     transformed_vertices;
    std::vector<glm::ivec4>                     display_vertices;

public:
    Mesh() = default;

	Mesh(aiMesh * assimpMesh)
	{
		this->assimpMesh = assimpMesh;

		this->number_of_vertices = assimpMesh->mNumVertices;
		this->original_vertices.resize(number_of_vertices);
        this->transformed_vertices.resize(number_of_vertices);
        this->display_vertices.resize(number_of_vertices);

        //Copying vertex data...
        for (size_t index = 0; index < number_of_vertices; index++)
        {
            auto& vertex = assimpMesh->mVertices[index];

            original_vertices[index] = glm::vec4(vertex.x, -vertex.y, vertex.z, 1.f);
        }

        original_colors.resize(number_of_vertices);
        
        // Colores aleatorios de cada vertice...

        for (size_t index = 0; index < number_of_vertices; index++)
        {
            original_colors[index].set(rand_clamp(), rand_clamp(), rand_clamp());
        }

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
	Model(Camera& renderCam, const char path[])
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
                meshes[i] = Mesh(scene->mMeshes[i]);
                
                //  Lo demás menos la representación en pantalla (transformed_vertices, display_vertices)
                // está manejado en el constructor Mesh();
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