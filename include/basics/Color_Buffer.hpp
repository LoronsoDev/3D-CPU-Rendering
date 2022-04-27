
// Código bajo licencia Boost Software License, version 1.0
// Ver www.boost.org/LICENSE_1_0.txt
// angel.rodriguez@esne.edu
// 2020.12

#ifndef ARGB_COLOR_BUFFER_HEADER
#define ARGB_COLOR_BUFFER_HEADER

    #include <algorithm>
    #include <cassert>
    #include "Color.hpp"
    #include <SFML/OpenGL.hpp>              // Solo se usa para mover el buffer de pixels a una ventana
    #include <vector>

    namespace argb
    {

        template< class COLOR >
        class Color_Buffer
        {
        public:

            using Color_Format = COLOR;
            using Color        = Color_Format;
            using Iterator     = Color *;

        private:

            using Buffer = std::vector< Color_Format >;

        public:

            static constexpr unsigned bits_per_color ()
            {
                return Color_Format::bits;
            }

        private:

            unsigned width;
            unsigned height;
            unsigned size;

            Buffer   buffer;

            Iterator start;
            Iterator ending;

        public:

            Color_Buffer(unsigned width, unsigned height)
            :
                width ( width          ),
                height( height         ),
                size  ( width * height ),
                buffer( size           ),
                start ( buffer.data () ),
                ending( start + size   )
            {
            }

        public:

                  Color_Format * pixels ()       { return buffer.data (); }
            const Color_Format * pixels () const { return buffer.data (); }

                  Iterator       begin  ()       { return start; }
            const Iterator       begin  () const { return start; }

                  Iterator       end    ()       { return ending; }
            const Iterator       end    () const { return ending; }

            unsigned get_width () const
            {
                return width;
            }

            unsigned get_height () const
            {
                return height;
            }

            unsigned get_size () const
            {
                return size;
            }

        public:

            void clear (const Color & color)
            {
                std::fill_n (buffer.data (), size, color);
            }

            void set_pixel (unsigned x, unsigned y, Color & color)
            {
                assert(x < width && y < height);

                buffer[y * width + x] = color;
            }

            void set_pixel (unsigned offset, Color & color)
            {
                assert(offset < buffer.size ());

                buffer[offset] = color;
            }

            explicit operator Color_Format * ()
            {
                return pixels ();
            }

            explicit operator const Color_Format * () const
            {
                return pixels ();
            }

            void blit_to_window () const;

        };

        template< >
        inline void Color_Buffer< Rgb332 >::blit_to_window () const
        {
            glRasterPos2f (-1.f, +1.f);
            glPixelZoom   (+1.f, -1.f);
            glDrawPixels  (int(width), int(height), GL_RGB, /*GL_UNSIGNED_BYTE_3_3_2*/0x8032, buffer.data ());
        }

        template< >
        inline void Color_Buffer< Rgb565 >::blit_to_window () const
        {
            glRasterPos2f (-1.f, +1.f);
            glPixelZoom   (+1.f, -1.f);
            glDrawPixels  (int(width), int(height), GL_RGB, /*GL_UNSIGNED_SHORT_5_6_5*/0x8363, buffer.data ());
        }

        template< >
        inline void Color_Buffer< Rgb24 >::blit_to_window () const
        {
            glRasterPos2f (-1.f, +1.f);
            glPixelZoom   (+1.f, -1.f);
            glDrawPixels  (int(width), int(height), GL_RGB, GL_UNSIGNED_BYTE, buffer.data ());
        }

    }

#endif
