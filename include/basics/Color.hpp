
// Código bajo licencia Boost Software License, version 1.0
// Ver www.boost.org/LICENSE_1_0.txt
// angel.rodriguez@esne.edu
// 2020.12

#ifndef ARGB_COLOR_HEADER
#define ARGB_COLOR_HEADER

    #include <cstdint>

    namespace argb
    {

        constexpr unsigned RGBH         = 116U;
        constexpr unsigned RGBF         = 132U;
        constexpr unsigned RGB332       = 1030302U;
        constexpr unsigned RGB565       = 1050605U;
        constexpr unsigned RGB888       = 1080808U;
        constexpr unsigned RGB111110    = 1111110U;
        constexpr unsigned RGB161616    = 1161616U;
        constexpr unsigned RGB212221    = 1212221U;
        constexpr unsigned RGB323232    = 1323232U;

        constexpr unsigned RGB8         = RGB332;
        constexpr unsigned RGB16        = RGB565;
        constexpr unsigned RGB24        = RGB888;
        constexpr unsigned RGB32        = RGB111110;
        constexpr unsigned RGB48        = RGB161616;
        constexpr unsigned RGB64        = RGB212221;
        constexpr unsigned RGB96        = RGB323232;

        constexpr unsigned BGRH         = 216U;
        constexpr unsigned BGRF         = 232U;
        constexpr unsigned BGR233       = 2020303U;
        constexpr unsigned BGR565       = 2050605U;
        constexpr unsigned BGR888       = 2080808U;
        constexpr unsigned BGR101111    = 2101111U;
        constexpr unsigned BGR161616    = 2161616U;
        constexpr unsigned BGR212221    = 2212221U;
        constexpr unsigned BGR323232    = 2323232U;

        constexpr unsigned BGR8         = BGR233;
        constexpr unsigned BGR16        = BGR565;
        constexpr unsigned BGR24        = BGR888;
        constexpr unsigned BGR32        = BGR101111;
        constexpr unsigned BGR48        = BGR161616;
        constexpr unsigned BGR64        = BGR212221;
        constexpr unsigned BGR96        = BGR323232;

        constexpr unsigned ARGBH        = 316U;
        constexpr unsigned ARGBF        = 332U;
        constexpr unsigned ARGB1232     = 301020302U;
        constexpr unsigned ARGB2222     = 302020202U;
        constexpr unsigned ARGB1555     = 301050505U;
        constexpr unsigned ARGB4444     = 304040404U;
        constexpr unsigned ARGB01101110 = 301101110U;
        constexpr unsigned ARGB8888     = 308080808U;
        constexpr unsigned ARGB01212121 = 301212121U;
        constexpr unsigned ARGB16161616 = 316161616U;
        constexpr unsigned ARGB32323232 = 332323232U;

        constexpr unsigned ARGB8        = ARGB2222;
        constexpr unsigned ARGB16       = ARGB4444;
        constexpr unsigned ARGB32       = ARGB8888;
        constexpr unsigned ARGB64       = ARGB16161616;
        constexpr unsigned ARGB128      = ARGB32323232;

        constexpr unsigned RGBAH        = 416U;
        constexpr unsigned RGBAF        = 432U;
        constexpr unsigned RGBA2321     = 402030201U;
        constexpr unsigned RGBA2222     = 402020202U;
        constexpr unsigned RGBA5551     = 405050501U;
        constexpr unsigned RGBA4444     = 404040404U;
        constexpr unsigned RGBA10111001 = 410111001U;
        constexpr unsigned RGBA8888     = 408080808U;
        constexpr unsigned RGBA21212101 = 421212101U;
        constexpr unsigned RGBA16161616 = 416161616U;
        constexpr unsigned RGBA32323232 = 432323232U;

        constexpr unsigned RGBA8        = RGBA2222;
        constexpr unsigned RGBA16       = RGBA4444;
        constexpr unsigned RGBA32       = RGBA8888;
        constexpr unsigned RGBA64       = RGBA16161616;
        constexpr unsigned RGBA128      = RGBA32323232;
        
        constexpr unsigned ABGRH        = 516U;
        constexpr unsigned ABGRF        = 532U;
        constexpr unsigned ABGR1232     = 501020302U;
        constexpr unsigned ABGR2222     = 502020202U;
        constexpr unsigned ABGR1555     = 501050505U;
        constexpr unsigned ABGR4444     = 504040404U;
        constexpr unsigned ABGR01101110 = 501101110U;
        constexpr unsigned ABGR8888     = 508080808U;
        constexpr unsigned ABGR01212121 = 501212121U;
        constexpr unsigned ABGR16161616 = 516161616U;
        constexpr unsigned ABGR32323232 = 532323232U;

        constexpr unsigned ABGR8        = ABGR2222;
        constexpr unsigned ABGR16       = ABGR4444;
        constexpr unsigned ABGR32       = ABGR8888;
        constexpr unsigned ABGR64       = ABGR16161616;
        constexpr unsigned ABGR128      = ABGR32323232;

        constexpr unsigned BGRAH        = 616U;
        constexpr unsigned BGRAF        = 632U;
        constexpr unsigned BGRA2321     = 602030201U;
        constexpr unsigned BGRA2222     = 602020202U;
        constexpr unsigned BGRA5551     = 605050501U;
        constexpr unsigned BGRA4444     = 604040404U;
        constexpr unsigned BGRA10111001 = 610111001U;
        constexpr unsigned BGRA8888     = 608080808U;
        constexpr unsigned BGRA21212101 = 621212101U;
        constexpr unsigned BGRA16161616 = 616161616U;
        constexpr unsigned BGRA32323232 = 632323232U;

        constexpr unsigned BGRA8        = BGRA2222;
        constexpr unsigned BGRA16       = BGRA4444;
        constexpr unsigned BGRA32       = BGRA8888;
        constexpr unsigned BGRA64       = BGRA16161616;
        constexpr unsigned BGRA128      = BGRA32323232;

        // ------------------------------------------------------------------------------------------ //

        template< typename COMPONENT_TYPE >
        struct Component_Type_Traits;

        template< >
        struct Component_Type_Traits< uint8_t >
        {
            using  Type = uint8_t;

            static constexpr bool  is_integer = true;
            static constexpr bool  is_float   = false;
            static constexpr bool  is_signed  = false;

            static constexpr Type  min  = 0;
            static constexpr Type  max  = 255;
            static constexpr float minf = 0.f;
            static constexpr float maxf = 255.f;

            static constexpr auto  bits = sizeof(Type) * 8;

            static Type scale (const float   & value) { return Type(value * maxf); }
            static Type scale (const uint8_t & value) { return value; }
        };

        template< >
        struct Component_Type_Traits< float >
        {
            using  Type = float;

            static constexpr bool  is_integer = false;
            static constexpr bool  is_float   = true;
            static constexpr bool  is_signed  = false;      // Aunque float tiene signo, solo se
                                                            // considera el intervalo [0-1]
            static constexpr Type  min  = 0.f;
            static constexpr Type  max  = 1.f;
            static constexpr float minf = 0.f;
            static constexpr float maxf = 1.f;

            static constexpr auto  bits = sizeof(Type) * 8;

            static Type scale (const float   & value) { return value; }
            static Type scale (const uint8_t & value) { return value * (1.f / 255.f); }     // USAR UNA TABLA? (256*4=1KB)
        };

        /*template< >
        struct Component_Type_Traits< half >
        {
        };*/

        // ------------------------------------------------------------------------------------------ //

        template< unsigned BIT_COUNT >
        struct Composite_Type
        {
            using Type = void;
        };

        template< > struct Composite_Type<  8 > { using Type = uint8_t;  };
        template< > struct Composite_Type< 16 > { using Type = uint16_t; };
        template< > struct Composite_Type< 32 > { using Type = uint32_t; };
        template< > struct Composite_Type< 64 > { using Type = uint64_t; };

        // ------------------------------------------------------------------------------------------ //

        template< unsigned COMPONENT_COUNT, typename COMPONENT_TYPE >
        struct Unpacked_Layout
        {
            static constexpr unsigned component_count = COMPONENT_COUNT;
            static constexpr unsigned bits            = component_count * sizeof(COMPONENT_TYPE) * 8U;

            using  Component_Type        = COMPONENT_TYPE;
            using  Component_Type_Traits = Component_Type_Traits< Component_Type >;
            using  Composite_Type        = typename Composite_Type< bits >::Type; 
        };

        template< typename COMPONENT_TYPE >
        struct Rgb_Layout : public Unpacked_Layout< 3, COMPONENT_TYPE >
        {
            enum Components : unsigned
            {
                RED = 0, GREEN = 1, BLUE = 2, R = RED, G = GREEN, B = BLUE
            };
        };

        template< typename COMPONENT_TYPE >
        struct Bgr_Layout : public Unpacked_Layout< 3, COMPONENT_TYPE >
        {
            enum Components : unsigned
            {
                RED = 2, GREEN = 1, BLUE = 0, R = RED, G = GREEN, B = BLUE
            };
        };

        template< typename COMPONENT_TYPE >
        struct Argb_Layout : public Unpacked_Layout< 4, COMPONENT_TYPE >
        {
            enum Components : unsigned
            {
                ALPHA = 0, RED = 1, GREEN = 2, BLUE = 3, A = ALPHA, R = RED, G = GREEN, B = BLUE
            };
        };

        template< typename COMPONENT_TYPE >
        struct Rgba_Layout : public Unpacked_Layout< 4, COMPONENT_TYPE >
        {
            enum Components : unsigned
            {
                ALPHA = 3, RED = 0, GREEN = 1, BLUE = 2, A = ALPHA, R = RED, G = GREEN, B = BLUE
            };
        };

        template< typename COMPONENT_TYPE >
        struct Abgr_Layout : public Unpacked_Layout< 4, COMPONENT_TYPE >
        {
            enum Components : unsigned
            {
                ALPHA = 0, RED = 3, GREEN = 2, BLUE = 1, A = ALPHA, R = RED, G = GREEN, B = BLUE
            };
        };

        template< typename COMPONENT_TYPE >
        struct Bgra_Layout : public Unpacked_Layout< 4, COMPONENT_TYPE >
        {
            enum Components : unsigned
            {
                ALPHA = 3, RED = 2, GREEN = 1, BLUE = 0, A = ALPHA, R = RED, G = GREEN, B = BLUE
            };
        };

        // ------------------------------------------------------------------------------------------ //

        template< unsigned COMPONENT_COUNT, unsigned ...COMPONENT_BITS >
        struct Packed_Layout
        {
        private:

            template< unsigned  TARGET_INDEX >
            static constexpr unsigned value_at (unsigned index) { return 0; }

            template< unsigned  TARGET_INDEX, typename ...TYPE_PACK >
            static constexpr unsigned value_at (unsigned index, unsigned value, const TYPE_PACK & ...value_pack)
            {
                return index == TARGET_INDEX ? value : value_at< TARGET_INDEX > (index + 1, value_pack...);
            }

            static constexpr unsigned sum () { return 0; }

            template< typename ...TYPE_PACK >
            static constexpr unsigned sum (unsigned value, const TYPE_PACK & ...value_pack)
            {
                return value + sum (value_pack...);
            }

            template< unsigned  START_INDEX >
            static constexpr unsigned sum_beyond (unsigned index) { return 0; }

            template< unsigned  START_INDEX, typename ...TYPE_PACK >
            static constexpr unsigned sum_beyond (unsigned index, unsigned value, const TYPE_PACK & ...value_pack)
            {
                return (index > START_INDEX ? value : 0) + sum_beyond< START_INDEX > (index + 1, value_pack...);
            }

        public:

            static constexpr unsigned component_count =      COMPONENT_COUNT;
            static constexpr unsigned bits            = sum (COMPONENT_BITS...);

            using  Component_Type = void;
            using  Composite_Type = typename Composite_Type< bits >::Type; 

            template< unsigned COMPONENT_INDEX >
            struct Component_Traits
            {
                static constexpr unsigned       index = COMPONENT_INDEX;
                static constexpr unsigned       bits  = value_at  < COMPONENT_INDEX > (0, COMPONENT_BITS...);
                static constexpr unsigned       shift = sum_beyond< COMPONENT_INDEX > (0, COMPONENT_BITS...);
                static constexpr Composite_Type mask  = (1 << bits) - 1;
                static constexpr float          maxf  = float((1 << bits) - 1);
            };

        };

        template< unsigned RED_BITS, unsigned GREEN_BITS, unsigned BLUE_BITS >
        struct Packed_Rgb_Layout : public Packed_Layout< 3, RED_BITS, GREEN_BITS, BLUE_BITS >
        {
            enum Components : unsigned
            {
                RED = 0, GREEN = 1, BLUE = 2, R = RED, G = GREEN, B = BLUE
            };
        };

        template< unsigned BLUE_BITS, unsigned GREEN_BITS, unsigned RED_BITS >
        struct Packed_Bgr_Layout : public Packed_Layout< 3, BLUE_BITS, GREEN_BITS, RED_BITS >
        {
            enum Components : unsigned
            {
                RED = 2, GREEN = 1, BLUE = 0, R = RED, G = GREEN, B = BLUE
            };
        };

        template< unsigned ALPHA_BITS, unsigned RED_BITS, unsigned GREEN_BITS, unsigned BLUE_BITS >
        struct Packed_Argb_Layout : public Packed_Layout< 4, ALPHA_BITS, RED_BITS, GREEN_BITS, BLUE_BITS >
        {
            enum Components : unsigned
            {
                ALPHA = 0, RED = 1, GREEN = 2, BLUE = 3, A = ALPHA, R = RED, G = GREEN, B = BLUE
            };
        };

        template< unsigned RED_BITS, unsigned GREEN_BITS, unsigned BLUE_BITS, unsigned ALPHA_BITS >
        struct Packed_Rgba_Layout : public Packed_Layout< 4, RED_BITS, GREEN_BITS, BLUE_BITS, ALPHA_BITS >
        {
            enum Components : unsigned
            {
                ALPHA = 3, RED = 0, GREEN = 1, BLUE = 2, A = ALPHA, R = RED, G = GREEN, B = BLUE
            };
        };

        template< unsigned ALPHA_BITS, unsigned BLUE_BITS, unsigned GREEN_BITS, unsigned RED_BITS >
        struct Packed_Abgr_Layout : public Packed_Layout< 4, ALPHA_BITS, BLUE_BITS, GREEN_BITS, RED_BITS >
        {
            enum Components : unsigned
            {
                ALPHA = 0, RED = 3, GREEN = 2, BLUE = 1, A = ALPHA, R = RED, G = GREEN, B = BLUE
            };
        };

        template< unsigned BLUE_BITS, unsigned GREEN_BITS, unsigned RED_BITS, unsigned ALPHA_BITS >
        struct Packed_Bgra_Layout : public Packed_Layout< 4, BLUE_BITS, GREEN_BITS, RED_BITS, ALPHA_BITS >
        {
            enum Components : unsigned
            {
                ALPHA = 3, RED = 2, GREEN = 1, BLUE = 0, A = ALPHA, R = RED, G = GREEN, B = BLUE
            };
        };

        // ------------------------------------------------------------------------------------------ //

        template
        <
            unsigned FORMAT_ID,
            class    COMPONENT_LAYOUT,
            typename COMPONENT_TYPE = typename COMPONENT_LAYOUT::Component_Type,
            typename COMPOSITE_TYPE = typename COMPONENT_LAYOUT::Composite_Type
        >
        struct Color : public COMPONENT_LAYOUT
        {
            using Component_Layout = COMPONENT_LAYOUT;
            using Component_Type   = COMPONENT_TYPE;
            using Composite_Type   = COMPOSITE_TYPE;

            static constexpr unsigned format_id = FORMAT_ID;

            union
            {
                Component_Type components[Component_Layout::component_count];
                Composite_Type value;
            };
        };

        template< unsigned FORMAT_ID, class COMPONENT_LAYOUT, typename COMPONENT_TYPE >
        struct Color< FORMAT_ID, COMPONENT_LAYOUT, COMPONENT_TYPE, void > : public COMPONENT_LAYOUT
        {
            using Component_Layout = COMPONENT_LAYOUT;
            using Component_Type   = COMPONENT_TYPE;

            static constexpr unsigned format_id = FORMAT_ID;

            Component_Type components[Component_Layout::component_count];
        };

        template< unsigned FORMAT_ID, class COMPONENT_LAYOUT, typename COMPOSITE_TYPE >
        struct Color< FORMAT_ID, COMPONENT_LAYOUT, void, COMPOSITE_TYPE > : public COMPONENT_LAYOUT
        {
            using Component_Layout = COMPONENT_LAYOUT;
            using Composite_Type   = COMPOSITE_TYPE;

            static constexpr unsigned format_id = FORMAT_ID;

            Composite_Type value;

            Color() = default;
            Color(const Composite_Type & initial_value) : value(initial_value) {}
        };

        // ------------------------------------------------------------------------------------------ //

        template
        <
            unsigned FORMAT_ID,
            class    COMPONENT_LAYOUT,
            typename COMPONENT_TYPE = typename COMPONENT_LAYOUT::Component_Type,
            typename COMPOSITE_TYPE = typename COMPONENT_LAYOUT::Composite_Type
        >
        struct Additive_Primaries : public Color< FORMAT_ID, COMPONENT_LAYOUT >
        {
        private:

            using Base = Color< FORMAT_ID, COMPONENT_LAYOUT >;

        public:

            using typename Base::Component_Type;
            using typename Base::Component_Type_Traits;
            using typename Base::Component_Layout::Components;
            using          Base::components;

        public:

            Additive_Primaries() = default;

            Additive_Primaries
            (
                const float & normalized_r,
                const float & normalized_g,
                const float & normalized_b
            )
            {
                set (normalized_r, normalized_g, normalized_b);
            }

            Additive_Primaries & set
            (
                const float & normalized_r,
                const float & normalized_g,
                const float & normalized_b
            )
            {
                set_red   (normalized_r);
                set_green (normalized_g);
                set_blue  (normalized_b);
                return    *this;
            }

            Component_Type & set_red   (const float & normalized_r)
            {
                return components[Components::RED  ] = Component_Type_Traits::scale (normalized_r);
            }

            Component_Type & set_green (const float & normalized_g)
            {
                return components[Components::GREEN] = Component_Type_Traits::scale (normalized_g);
            }

            Component_Type & set_blue  (const float & normalized_b)
            {
                return components[Components::BLUE ] = Component_Type_Traits::scale (normalized_b);
            }

            Component_Type & red   ()       { return components[Components::RED  ]; }
            Component_Type   red   () const { return components[Components::RED  ]; }
            Component_Type & green ()       { return components[Components::GREEN]; }
            Component_Type   green () const { return components[Components::GREEN]; }
            Component_Type & blue  ()       { return components[Components::BLUE ]; }
            Component_Type   blue  () const { return components[Components::BLUE ]; }
        };

        template
        <
            unsigned FORMAT_ID,
            class    COMPONENT_LAYOUT,
            typename COMPOSITE_TYPE
        >
        struct Additive_Primaries< FORMAT_ID, COMPONENT_LAYOUT, void, COMPOSITE_TYPE > : public Color< FORMAT_ID, COMPONENT_LAYOUT >
        {
        private:

            using Base = Color< FORMAT_ID, COMPONENT_LAYOUT >;

        public:

            using typename Base::Component_Layout::Components;
            using typename Base::Component_Layout::Composite_Type;
            using          Base::value;

            using   red_traits = typename Base::Component_Layout::template Component_Traits< Components::RED   >;
            using green_traits = typename Base::Component_Layout::template Component_Traits< Components::GREEN >;
            using  blue_traits = typename Base::Component_Layout::template Component_Traits< Components::BLUE  >;

        public:

            Additive_Primaries() = default;

            Additive_Primaries(const Composite_Type & initial_value) : Base(initial_value) {}

            Additive_Primaries
            (
                const float & normalized_r,
                const float & normalized_g,
                const float & normalized_b
            )
            {
                set (normalized_r, normalized_g, normalized_b);
            }

            Additive_Primaries & set
            (
                const float & normalized_r,
                const float & normalized_g,
                const float & normalized_b
            )
            {
                value =
                    (Composite_Type(normalized_r *   red_traits::maxf) <<   red_traits::shift) |
                    (Composite_Type(normalized_g * green_traits::maxf) << green_traits::shift) |
                    (Composite_Type(normalized_b *  blue_traits::maxf) <<  blue_traits::shift);

                return *this;
            }

            Composite_Type red   () const { return (value >>   red_traits::shift) &   red_traits::mask; }
            Composite_Type green () const { return (value >> green_traits::shift) & green_traits::mask; }
            Composite_Type blue  () const { return (value >>  blue_traits::shift) &  blue_traits::mask; }
        };

        template
        <
            unsigned FORMAT_ID,
            class    COMPONENT_LAYOUT,
            typename COMPONENT_TYPE = typename COMPONENT_LAYOUT::Component_Type,
            typename COMPOSITE_TYPE = typename COMPONENT_LAYOUT::Composite_Type
        >
        struct Additive_Primaries_And_Alpha : public Additive_Primaries< FORMAT_ID, COMPONENT_LAYOUT >
        {
        private:

            using Base = Additive_Primaries< FORMAT_ID, COMPONENT_LAYOUT >;

        public:

        };

        template
        <
            unsigned FORMAT_ID,
            class    COMPONENT_LAYOUT,
            typename COMPOSITE_TYPE
        >
        struct Additive_Primaries_And_Alpha< FORMAT_ID, COMPONENT_LAYOUT, void, COMPOSITE_TYPE > : public Additive_Primaries< FORMAT_ID, COMPONENT_LAYOUT >
        {
        private:

            using Base = Additive_Primaries< FORMAT_ID, COMPONENT_LAYOUT >;

        public:

        };

        // ------------------------------------------------------------------------------------------ //

        using Rgbf         = Additive_Primaries< RGBF,      Rgb_Layout< float    > >;
        using Rgb888       = Additive_Primaries< RGB888,    Rgb_Layout< uint8_t  > >;
        using Rgb161616    = Additive_Primaries< RGB161616, Rgb_Layout< uint16_t > >;
        using Rgb323232    = Additive_Primaries< RGB323232, Rgb_Layout< uint32_t > >;

        using Rgb332       = Additive_Primaries< RGB332,    Packed_Rgb_Layout<  3,  3,  2 > >;
        using Rgb565       = Additive_Primaries< RGB565,    Packed_Rgb_Layout<  5,  6,  5 > >;
        using Rgb111110    = Additive_Primaries< RGB111110, Packed_Rgb_Layout< 11, 11, 10 > >;
        using Rgb212221    = Additive_Primaries< RGB212221, Packed_Rgb_Layout< 21, 22, 21 > >;

        using Rgb8         = Rgb332;
        using Rgb16        = Rgb565;
        using Rgb24        = Rgb888;
        using Rgb32        = Rgb111110;
        using Rgb48        = Rgb161616;
        using Rgb64        = Rgb212221;
        using Rgb96        = Rgb323232;

        using Bgrf         = Additive_Primaries< BGRF,      Bgr_Layout< float    > >;
        using Bgr888       = Additive_Primaries< BGR888,    Bgr_Layout< uint8_t  > >;
        using Bgr161616    = Additive_Primaries< BGR161616, Bgr_Layout< uint16_t > >;
        using Bgr323232    = Additive_Primaries< BGR323232, Bgr_Layout< uint32_t > >;

        using Bgr233       = Additive_Primaries< BGR233,    Packed_Bgr_Layout<  2,  3,  3 > >;
        using Bgr565       = Additive_Primaries< BGR565,    Packed_Bgr_Layout<  5,  6,  5 > >;
        using Bgr101111    = Additive_Primaries< BGR101111, Packed_Bgr_Layout< 10, 11, 11 > >;
        using Bgr212221    = Additive_Primaries< BGR212221, Packed_Bgr_Layout< 21, 22, 21 > >;

        using Bgr8         = Bgr233;
        using Bgr16        = Bgr565;
        using Bgr24        = Bgr888;
        using Bgr32        = Bgr101111;
        using Bgr48        = Bgr161616;
        using Bgr64        = Bgr212221;
        using Bgr96        = Bgr323232;

        using Argbf        = Additive_Primaries< ARGBF,        Argb_Layout< float    > >;
        using Argb8888     = Additive_Primaries< ARGB8888,     Argb_Layout< uint8_t  > >;
        using Argb16161616 = Additive_Primaries< ARGB16161616, Argb_Layout< uint16_t > >;
        using Argb32323232 = Additive_Primaries< ARGB32323232, Argb_Layout< uint32_t > >;

        using Argb1232     = Additive_Primaries< ARGB1232,     Packed_Argb_Layout< 1,  2,  3,  2 > >;
        using Argb2222     = Additive_Primaries< ARGB2222,     Packed_Argb_Layout< 2,  2,  2,  2 > >;
        using Argb1555     = Additive_Primaries< ARGB1555,     Packed_Argb_Layout< 1,  5,  5,  5 > >;
        using Argb4444     = Additive_Primaries< ARGB4444,     Packed_Argb_Layout< 4,  4,  4,  4 > >;
        using Argb01101110 = Additive_Primaries< ARGB01101110, Packed_Argb_Layout< 1, 10, 11, 10 > >;
        using Argb01212121 = Additive_Primaries< ARGB01212121, Packed_Argb_Layout< 1, 21, 21, 21 > >;

        using Argb8        = Argb2222;
        using Argb16       = Argb4444;
        using Argb32       = Argb8888;
        using Argb64       = Argb16161616;
        using Argb128      = Argb32323232;

    }

#endif
