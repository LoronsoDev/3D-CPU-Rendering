#pragma once

#include "Camera.hpp"
#include "Rasterizer.hpp"
#include "Model.h"

#include <basics/Color_Buffer.hpp>

using namespace example;
using namespace argb;

//template <class COLOR_BUFFER_TYPE>
class Renderer
{
private:
    typedef Rgb888                Color;
    typedef Color_Buffer< Color > Color_Buffer;

    Color_Buffer                    color_buffer;
    Rasterizer  < Color_Buffer >    activeRasterizer;

    std::vector<Model> loadedModels;

public:
	Renderer(unsigned int width = 1920u, unsigned int height = 1080u)
    :
        color_buffer(width, height),
        activeRasterizer(color_buffer)
	{
        activeRasterizer.clear();
	}

	void render_camera(Camera& camera, Model & model)
	{
        model.set_transform(camera.get_inverse_transform() * model.get_transform());
        camera.render_pass();
	}

	void render_model(Model & model)
	{
        for (Mesh m : model.meshes)
        {
            m.update_lighting();
            render_camera(*model.renderCam, model);
            /// <summary>
            /// We apply the perspective of the camera.
            /// </summary>
            glm::mat4 projection = model.renderCam->get_perspective_matrix();
            glm::mat4 model_transform = model.get_transform();

            glm::mat4 total_transformation = projection * model_transform;

            for (size_t index = 0, number_of_vertices = m.original_vertices.size(); index < number_of_vertices; index++)
            {
                // Se multiplican todos los vértices originales con la matriz de transformación y
                // se guarda el resultado en otro vertex buffer:

                glm::fvec4& vertex = m.transformed_vertices[index] = total_transformation * m.original_vertices[index];

                // La matriz de proyección en perspectiva hace que el último componente del vector
                // transformado no tenga valor 1.0, por lo que hay que normalizarlo dividiendo:

                float divisor = 1.f / vertex.w;

                vertex.x *= divisor;
                vertex.y *= divisor;
                vertex.z *= divisor;
                vertex.w = 1.f;
            }

            // Se convierten las coordenadas transformadas y proyectadas a coordenadas
            // de recorte (-1 a +1) en coordenadas de pantalla con el origen centrado.
            // La coordenada Z se escala a un valor suficientemente grande dentro del
            // rango de int (que es lo que espera fill_convex_polygon_z_buffer).

            glm::mat4 identity(1);
            glm::mat4 scaling = glm::scale(
                identity,
                { float(model.renderCam->get_width() / 2), float(model.renderCam->get_height() / 2), 100000000.f });
            glm::mat4 translation = glm::translate(
                identity,
                { float(model.renderCam->get_width() / 2), float(model.renderCam->get_height() / 2), 0.f });

            glm::mat4 transformation = translation * scaling;

            for (size_t index = 0, number_of_vertices = m.transformed_vertices.size(); index < number_of_vertices; index++)
            {
                m.display_vertices[index] = glm::ivec4(transformation * m.transformed_vertices[index]);
            }

            for (int* indices = m.original_indices.data(), *end = indices + m.original_indices.size(); indices < end; indices += 3)
            {
                if (is_frontface(m.transformed_vertices.data(), indices))
                {
                    // Se establece el color del polígono a partir del color de su primer vértice:

                    //CLIPPING

                    activeRasterizer.set_color(m.original_colors[*indices]);

                    // Se rellena el polígono:

                    activeRasterizer.fill_convex_polygon_z_buffer(m.display_vertices.data(), indices, indices + 3);
                }
            }

            model.renderCam->reset();
            color_buffer.blit_to_window();
        }

	}

    void clear()
    {
        activeRasterizer.clear();
    }

    bool is_frontface(const glm::fvec4* const projected_vertices, const int* const indices)
    {
        const glm::fvec4& v0 = projected_vertices[indices[0]];
        const glm::fvec4& v1 = projected_vertices[indices[1]];
        const glm::fvec4& v2 = projected_vertices[indices[2]];

        // Se asumen coordenadas proyectadas y polígonos definidos en sentido horario.
        // Se comprueba a qué lado de la línea que pasa por v0 y v1 queda el punto v2:

        return ((v1[0] - v0[0]) * (v2[1] - v0[1]) - (v2[0] - v0[0]) * (v1[1] - v0[1]) < 0.f);
    }


};