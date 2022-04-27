
// Código bajo licencia Boost Software License, version 1.0
// Ver www.boost.org/LICENSE_1_0.txt
// angel.rodriguez@esne.edu
// 2020.12

#ifndef ARGB_BLITTER_HEADER
#define ARGB_BLITTER_HEADER

    #include <cassert>
    #include "Color_Buffer.hpp"
    #include "blend_functions.hpp"
    #include "blitter_transforms.hpp"

    namespace argb
    {

        template< class COLOR >
        class Blitter
        {
        public:

            using Color = COLOR;
            using Color_Buffer = Color_Buffer< Color >;

            enum class Transform
            {
                NONE,
                FLIP_HORIZONTAL,
                FLIP_VERTICAL,
                ROTATE_90,
                ROTATE_180,
                ROTATE_270,
            };

        private:

            Color_Buffer & color_buffer;

        public:

            Blitter(Color_Buffer & given_color_buffer) : color_buffer(given_color_buffer)
            {
            }

            template
            <
                blend_function< COLOR > BLEND_FUNCTION = blend_replace, 
                blitter_transform::function< COLOR, BLEND_FUNCTION > = blit_normal< COLOR, BLEND_FUNCTION >
            >
            void blit
            (
                unsigned target_left_x,
                unsigned target_top_y,
                const Color_Buffer & bitmap
            );

            /*template< blend_function< COLOR > = blend_replace >
            void blit_slice
            (
                unsigned target_left_x,
                unsigned target_top_y,
                unsigned slice_left_x,
                unsigned slice_top_y,
                unsigned slice_width,
                unsigned slice_height,
                const Color_Buffer & bitmap
            );*/

        };

        template< class COLOR >
        template< blend_function< COLOR > BLEND_FUNCTION, blitter_transform::function< COLOR, BLEND_FUNCTION > TRANSFORM_FUNCTION >
        void Blitter< COLOR >::blit
        (
            unsigned target_left_x, 
            unsigned target_top_y, 
            const Color_Buffer & bitmap
        )
        {
            blitter_transform::Details< COLOR > details
            {
                {
                    bitmap.pixels     (),
                    bitmap.get_width  (),
                    bitmap.get_height (),
                    0
                },
                {
                    color_buffer.pixels     () + color_buffer.get_width () * target_top_y + target_left_x,
                    color_buffer.get_width  (),
                    color_buffer.get_height ()
                }
            };

            TRANSFORM_FUNCTION (details);
        }

    }

#endif
