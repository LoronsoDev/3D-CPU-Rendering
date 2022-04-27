
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2013.12 - 2021.04

#include <cassert>
#include <cmath>
#include "math.hpp"
#include "View.hpp"

namespace example
{

    View::View(unsigned width, unsigned height, CameraDemoMove & camMovement)
    :
        color_buffer(width, height)
    {
		light = { 0, 10.f, 0.f, 1};
        camera		= Camera (width, height);
        demoBunny_1 = Model  (camera, light, mesh_file_path);
		demoBunny_2 = Model  (camera, light, mesh_file_path);
		diorama		= Model  (camera, light, garden_mesh_file_path);

		diorama.translate({ 0.f, 2.5f, -10.f });
		diorama.scale(3.f);

		demoBunny_1.set_parent(diorama);

		demoBunny_1.scale(0.2f);
		demoBunny_1.translate({0.f, -0.7f, 5.5f});

		demoBunny_2.scale(1.f);
		demoBunny_2.translate({ 7.f, 0.f, -10.f });


		diorama.update();
		demoBunny_1.update();
		demoBunny_2.update();

		this->camMovement = &camMovement;
    }

    void View::update ()
    {

        // Se actualizan los parámetros de transformation (sólo se modifica el ángulo):
		diorama.rotate({ 0, 0.025f, 0.f });
		demoBunny_1.translate({ 0 ,0, 0 });


		switch (*camMovement)
		{
			case CameraDemoMove::forward:
				camera.translate({ 0.0f, 0.0f, -0.01f });
				break;
			case CameraDemoMove::back:
				camera.translate({ 0.f, 0.0f, 0.01f });
				break;
			case CameraDemoMove::left:
				camera.translate({ -0.01f, 0.f, 0.f });
				break;
			case CameraDemoMove::right:
				camera.translate({ 0.01f, 0.f, 0.f });
				break;
			case CameraDemoMove::lookUp:
				camera.rotate({ -0.01f, 0.f, 0.f });
				break;
			case CameraDemoMove::lookDown:
				camera.rotate({ 0.01f, 0.f, 0.f });
				break;
			case CameraDemoMove::lookLeft:
				camera.rotate({ 0.0f, 0.01f, 0.f });
				break;
			case CameraDemoMove::lookRight:
				camera.rotate({ 0.0f, -0.01f, 0.f });
				break;
			default:
			case CameraDemoMove::stopped:
				camera.translate({ 0.f, 0.f, 0.f });
				camera.rotate({ 0.f, 0.f, 0.f });
				break;
		}

		diorama.update();
		demoBunny_1.update();
		camera.update();
    }

    void View::render ()
	{
		renderer.render_model(demoBunny_1);
		renderer.render_model(demoBunny_2);
		renderer.render_model(diorama);

        // Se limpian los píxeles ya pintados en la pantalla...
		renderer.clear();
    }

    
	//No funciona el algoritmo de clipping...

	/// <summary>
	/// La idea es pasarle cada triángulo para que vea si hay que clipearlo, luego cambiar lo que has pasado por los que te devuelve este método
	/// </summary>
	/// <param name="polygon_vertices">Vertices del triángulo a clippear</param>
	/// <param name="indices">Índices de los vértices (orden)</param>
	/// <param name="clipper_points">Puntos del cuadrilátero que corta (normalmente situado en los 4 ptos de la pantalla)</param>
	void View::clip_polygon(const Vertex* const polygon_vertices, const int * const indices, Vertex* clipper_points)
	{
        Vertex new_points[3];

        //This should always be a triangle, so we can presume that the polygon is a triangle.

		const Vertex& v0 = polygon_vertices[indices[0]];
		const Vertex& v1 = polygon_vertices[indices[1]];
		const Vertex& v2 = polygon_vertices[indices[2]];

        //The clipping polygon will be the polygon made by the screen/window limits. So, a rectangle (4 vertices).
		const Vertex& clipping0 = clipper_points[0];
		const Vertex& clipping1 = clipper_points[1];
		const Vertex& clipping2 = clipper_points[2];
		const Vertex& clipping3 = clipper_points[3];

        int new_poly_size = 0;

        for (int i = 0; i < 3; i++)
        {
            //El resto siempre será == a numerador mientras sea < que el denominador y 0 si es == a denominador;
            int k = (i + 1) % 3;

            int first_vertex_x = polygon_vertices[i][0];
			int first_vertex_y = polygon_vertices[i][1];

			int second_vertex_x = polygon_vertices[k][0];
			int second_vertex_y = polygon_vertices[k][1];


			int first_point_pos  =  (clipping1[0] - clipping0[0]) * (first_vertex_y  - clipping0[1]) - 
                                    (clipping1[1] - clipping1[1] * (first_vertex_x  - clipping0[0]));

			int second_point_pos =  (clipping1[0] - clipping0[0]) * (second_vertex_y - clipping0[1]) - 
                                    (clipping1[1] - clipping1[1] * (second_vertex_x - clipping0[0]));

			//// Case 1 : When both points are inside
			//if (first_point_pos < 0 && second_point_pos < 0)
			//{
			//	//Only second point is added
			//	new_points[new_poly_size][0] = kx;
			//	new_points[new_poly_size][1] = ky;
			//	new_poly_size++;
			//}

			//// Case 2: When only first point is outside
			//else if (first_point_pos >= 0 && second_point_pos < 0)
			//{
			//	// Point of intersection with edge
			//	// and the second point is added
			//	new_points[new_poly_size][0] = x_intersect(x1,
			//		y1, x2, y2, ix, iy, kx, ky);
			//	new_points[new_poly_size][1] = y_intersect(x1,
			//		y1, x2, y2, ix, iy, kx, ky);
			//	new_poly_size++;

			//	new_points[new_poly_size][0] = kx;
			//	new_points[new_poly_size][1] = ky;
			//	new_poly_size++;
			//}

			//// Case 3: When only second point is outside
			//else if (first_point_pos < 0 && second_point_pos >= 0)
			//{
			//	//Only point of intersection with edge is added
			//	new_points[new_poly_size][0] = x_intersect(x1,
			//		y1, x2, y2, ix, iy, kx, ky);
			//	new_points[new_poly_size][1] = y_intersect(x1,
			//		y1, x2, y2, ix, iy, kx, ky);
			//	new_poly_size++;
			//}

			//// Case 4: When both points are outside
			//else
			//{
			//	//No points are added
			//}


        }
		//int i_pos = (x2 - x1) * (iy - y1) - (y2 - y1) * (ix - x1);


			// 2: Calcular pto intersección con la línea que trazan los clipping points.
			// 3: Tratar los casos según el resultado de la intersección.
	}

}
