
// Código bajo licencia Boost Software License, version 1.0
// Ver www.boost.org/LICENSE_1_0.txt
// angel.rodriguez@esne.edu
// 2020.12

#ifndef ARGB_COLOR_CONVERSIONS_HEADER
#define ARGB_COLOR_CONVERSIONS_HEADER

    #include <algorithm>
    #include "Color_Buffer.hpp"

    namespace argb
    {

        template
        <
            class SOURCE_COLOR_FORMAT,
            class TARGET_COLOR_FORMAT 
        >
        TARGET_COLOR_FORMAT convert (const SOURCE_COLOR_FORMAT & source);
        
        template< class COLOR >
        inline COLOR convert (const COLOR & source)
        {
            return source;
        }

        template< >
        inline Rgb332 convert (const Rgb24 & source)
        {
            return
                (uint8_t(source.red   ()) >> 5 << 5) |
                (uint8_t(source.green ()) >> 5 << 2) |
                (uint8_t(source.blue  ()) >> 6     );
        }

        template< >
        inline Rgb565 convert (const Rgb24 & source)
        {
            return 
                (uint16_t(source.red   ()) >> 3 << 11) |
                (uint16_t(source.green ()) >> 2 <<  5) |
                (uint16_t(source.blue  ()) >> 3      );
        }

        template
        <
            class SOURCE_COLOR_FORMAT,
            class TARGET_COLOR_FORMAT 
        >
        void copy (const SOURCE_COLOR_FORMAT * source, TARGET_COLOR_FORMAT * target, size_t count)
        {
            while (count--)
            {
                *target++ = convert< SOURCE_COLOR_FORMAT, TARGET_COLOR_FORMAT > (*source++);
            }
        }

        template< class COLOR >
        inline void copy (const COLOR * source, COLOR * target, size_t count)
        {
            std::copy_n (source, count, target);
        }

    }

#endif
