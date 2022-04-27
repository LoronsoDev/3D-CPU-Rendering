
// Código bajo licencia Boost Software License, version 1.0
// Ver www.boost.org/LICENSE_1_0.txt
// angel.rodriguez@esne.edu
// 2020.12

#ifndef ARGB_COLOR_FILTERS_HEADER
#define ARGB_COLOR_FILTERS_HEADER

    #include "Color_Buffer.hpp"

    namespace argb
    {

        template< class COLOR >
        void apply_rgb_gray_scale_filter (COLOR & color);

        template< >
        inline void apply_rgb_gray_scale_filter< Rgb332 > (Rgb332 & color)
        {
            unsigned r3 = color.value >> 5;
            unsigned g3 = color.value >> 2 & 0b111;
            unsigned b2 = color.value      & 0b11;

            uint8_t gray5 = uint8_t( (((r3 + g3) >> 1) + (b2 << 1)) >> 1 );

            color.value = (gray5 << 5) | (gray5 << 2) | (gray5 >> 1);
        }

        template< >
        inline void apply_rgb_gray_scale_filter< Rgb565 > (Rgb565 & color)
        {
            unsigned r5 = color.value >> 11;
            unsigned g6 = color.value >>  5 & 0b111111;
            unsigned b5 = color.value       & 0b11111;

            // Se pretende aplicar la fórmula "((r + b) / 2 + g) / 2", pero r5 y b5 ya están divididos
            // entre dos respecto al rango de g6, por lo que nos ahorramos la primera división.
            // Por otro lado, el resultado final estará en el rango de 6 bits y antes de empaquetarlo
            // en r5 y b5 hay que dividirlo entre 2, por lo que aplicamos esa división directamente
            // (combinándola con la anterior) para dejar a gray en el rango de 5 bits. Luego habrá
            // que multiplicar por 2 al empaquetar g6.

            uint16_t gray5 = uint16_t( (r5 + b5 + g6) >> 2 );

            color.value = (gray5 << 11) | (gray5 << 6) | gray5;
        }

        template< >
        inline void apply_rgb_gray_scale_filter< Rgb24 > (Rgb24 & pixel)
        {
            unsigned r8 = pixel.red   ();
            unsigned g8 = pixel.green ();
            unsigned b8 = pixel.blue  ();

            // En lugar de aplicar la fórmula "(r + g + b) / 3" se aplica una aproximación con la
            // fórmula "((r + b) / 2 + g) / 2" (que es equivalente a "(r + g * 2 + b) / 4").
            // El objetivo es prescindir de divisiones y de multiplicaciones como medida de optimización
            // a costa de la exactitud (si bien el sistema visual humano da más importancia a los tonos
            // de verde, tal como ocurre con la nueva fórmula aunque en distinta proporción y, en
            // cualquier caso, el promedio RGB tampoco es en sí mismo una aproximación precisa).

            uint8_t  gray8 = uint8_t( (((r8 + b8) >> 1) + g8) >> 1 );

            pixel.red   () = gray8;
            pixel.green () = gray8;
            pixel.blue  () = gray8;
        }

        // -------------------------------------------------------------------------------------- //

        template< class COLOR >
        inline void apply_rgb_gray_scale_filter (Color_Buffer< COLOR > & image)
        {
            for (auto & pixel : image)
            {
                apply_rgb_gray_scale_filter (pixel);
            }
        }

    }

#endif
