
// Código bajo licencia Boost Software License, version 1.0
// Ver www.boost.org/LICENSE_1_0.txt
// angel.rodriguez@esne.edu
// 2020.12

#ifndef ARGB_BLEND_FUNCTIONS_HEADER
#define ARGB_BLEND_FUNCTIONS_HEADER

    #include "Color.hpp"

    namespace argb
    {

        // ES NECESARIO PORDER ESPECIFICAR ALPHA COMO FLOAT Y COMO UINT8_T.
        // UNA ALTERNATIVA ES QUE EL ALPHA SEA UN ATRIBUTO DE COLOR Y QUE SE PUEDAN COMBINAR FORMATOS
        // DE PIXEL CON Y SIN ALPHA INDISTINTAMENTE. CUANDO FALTA EL COMPONENTE ALPHA SE USA EL
        // VALOR MÁXIMO EN SU LUGAR (1.0, 255, ETC.).
        // ESTA APROXIMACIÓN PODRÍA REDUCIR LA COMPLEJIDAD Y MEJORAR LA FLEXIBILIDAD.

        template< class COLOR >
        using blend_function = void (*) (COLOR & destination, const COLOR & source);
        
        // -------------------------------------------------------------------------------------- //
        // BLEND REPLACE

        template< class COLOR >
        inline void blend_replace (COLOR & destination, const COLOR & source)
        {
            destination = source;
        }
        
        // -------------------------------------------------------------------------------------- //
        // BLEND HALF

        // QUIZÁS LA VERSIÓN FAST DEBERÍA SER LA VERSIÓN POR DEFECTO?

        template< class COLOR >
        void blend_half (COLOR & destination, const COLOR & source);

        template< class COLOR >
        inline void blend_half_fast (COLOR & destination, const COLOR & source)
        {
            blend_half (destination, source);
        }

        template< >
        inline void blend_half< Rgb332 > (Rgb332 & destination, const Rgb332 & source)
        {
            destination.value = Rgb332::Composite_Type
            ( 
                (
                    ((unsigned(source.value)             ) + (unsigned(destination.value) & 0b11100000) & 0b111000000) | 
                    ((unsigned(source.value) & 0b00011100) + (unsigned(destination.value) & 0b00011100) & 0b000111000) | 
                    ((unsigned(source.value) & 0b00000011) + (unsigned(destination.value) & 0b00000011)              )
                )
                >> 1 
            );
        }

        template< >
        inline void blend_half_fast< Rgb332 > (Rgb332 & destination, const Rgb332 & source)
        {
            destination.value = Rgb332::Composite_Type
            (
                ( (unsigned(destination.value) & 0xda) + (unsigned(source.value) & 0xda) ) >> 1
            );
        }

        template< >
        inline void blend_half< Rgb565 > (Rgb565 & destination, const Rgb565 & source)
        {
            destination.value = Rgb565::Composite_Type
            (
                ( (unsigned(destination.value) & 0xf7de) + (unsigned(source.value) & 0xf7de) ) >> 1
            );
        }

        template< >
        inline void blend_half< Rgb24 > (Rgb24 & destination, const Rgb24 & source)
        {
            destination.red   () = (destination.red   () + source.red   ()) >> 1;
            destination.green () = (destination.green () + source.green ()) >> 1;
            destination.blue  () = (destination.blue  () + source.blue  ()) >> 1;
        }

    }

#endif
