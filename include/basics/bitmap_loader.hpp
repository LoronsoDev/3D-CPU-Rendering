
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2020.12

#ifndef ARGB_BITMAP_LOADER_HEADER
#define ARGB_BITMAP_LOADER_HEADER

    #include <memory>
    #include <string>
    #include <SOIL2.h>
    #include "Color_Buffer.hpp"
    #include "color_conversions.hpp"

    namespace argb
    {

        template< class COLOR_FORMAT >
        std::unique_ptr< Color_Buffer< COLOR_FORMAT > > load_bitmap (const std::string & path)
        {
            std::unique_ptr< Color_Buffer< COLOR_FORMAT > > bitmap;

            int image_width    = 0;
            int image_height   = 0;
            int image_channels = 0;

            unsigned char * loaded_pixels = SOIL_load_image
            (
                 path.c_str (),
                &image_width, 
                &image_height, 
                &image_channels,
                 SOIL_LOAD_RGB              // Indica que nos devuelva los pixels en formato RGB24
            );                              // al margen del formato usado en el archivo

            // Si loaded_pixels no es nullptr la imagen se ha podido cargar correctamente:

            if (loaded_pixels)
            {
                bitmap.reset (new Color_Buffer< COLOR_FORMAT >(image_width, image_height));

                argb::copy
                (
                    reinterpret_cast< Rgb24 * >(loaded_pixels),
                    reinterpret_cast< COLOR_FORMAT * >(bitmap->pixels ()),
                    bitmap->get_size ()
                );

                // Se libera la memoria que reservó SOIL2 para cargar la imagen:

                SOIL_free_image_data (loaded_pixels);
            }

            return bitmap;
        }

    }

#endif



