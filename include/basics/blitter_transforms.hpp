
// Código bajo licencia Boost Software License, version 1.0
// Ver www.boost.org/LICENSE_1_0.txt
// angel.rodriguez@esne.edu
// 2020.12

#ifndef ARGB_BLITTER_TRANSFORMS_HEADER
#define ARGB_BLITTER_TRANSFORMS_HEADER

    #include "Color_Buffer.hpp"
    #include "blend_functions.hpp"

    namespace argb
    {

        namespace blitter_transform
        {

            template< class COLOR >
            struct Details
            {
                struct
                {
                    const COLOR * pointer;
                    unsigned width;
                    unsigned height;
                    unsigned delta;
                }
                source;

                struct
                {
                    COLOR * pointer;
                    struct
                    {
                        unsigned x, y;
                    }
                    pitch;
                }
                target;
            };

            template< class COLOR, blend_function< COLOR > BLEND_FUNCTION >
            using function = void (*) (Details< COLOR > & );
        }

        // -------------------------------------------------------------------------------------- //

        template< class COLOR, blend_function< COLOR > BLEND_FUNCTION >
        inline void blit_normal (blitter_transform::Details< COLOR > & _)
        {
            unsigned delta = _.target.pitch.x - _.source.width;

            while (_.source.height--)
            {
                for (auto end = _.target.pointer + _.source.width; _.target.pointer < end; )
                {
                    BLEND_FUNCTION (*_.target.pointer++, *_.source.pointer++);
                }

                _.source.pointer += _.source.delta;
                _.target.pointer += delta;
            }
        }

    }

#endif
