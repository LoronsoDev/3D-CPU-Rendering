
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2013.12 - 2021.04

#ifndef VIEW_HEADER
#define VIEW_HEADER

    #include <basics/Color_Buffer.hpp>
    #include <cstdlib>
    #include "math.hpp"
    #include "Rasterizer.hpp"
    #include <vector>
    #include "Model.h"
    #include "Camera.hpp"
    #include "Renderer.hpp"

    namespace example
    {

        using  std::vector;
        using argb::Rgb888;
        using argb::Color_Buffer;

        class View
        {
        private:

            typedef Rgb888                Color;
            typedef Color_Buffer< Color > Color_Buffer;
            typedef Point4f               Vertex;
            typedef vector< Vertex >      Vertex_Buffer;
            typedef vector< int    >      Index_Buffer;
            typedef vector< Color  >      Vertex_Colors;

        private:

            static constexpr char mesh_file_path[] =        "../../assets/stanford-bunny.obj";
            static constexpr char garden_mesh_file_path[] = "../../assets/ball.obj";

            Color_Buffer                    color_buffer;
            Renderer                        renderer;

            glm::fvec4 light;
            Model  demoBunny_1, diorama, demoBunny_2;
            Camera camera;

        public:

            /// <summary>
            /// This is just for this demo. Allows camere to move freely inside of the scene.
            /// </summary>
            enum CameraDemoMove
            {
                stopped = 0,

                forward,
                back,
                left,
                right,

                lookUp,
                lookDown,
                lookLeft,
                lookRight
            };

            CameraDemoMove * camMovement = nullptr;

            View(unsigned width, unsigned height, CameraDemoMove & camMovement);

            void update ();
            void render ();

        private:

            void clip_polygon(const Vertex * const polygon_vertices, const int* const indices, Vertex* clipper_points);
        };

    }

#endif
