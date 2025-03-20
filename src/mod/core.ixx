//
// Created by Aidan Jost on 3/18/25.
//

export module plaster.core;
#include <cstdint>
#include <optional>

export namespace plaster
{





    template <typename T>
    struct Point
    {
        T x;
        T y;

        Point(T x, T y) : x(x), y(y) {}
        // explicit operator T() const { return x; }

        bool operator==(const Point &other) const
        {
            return x == other.x && y == other.y;
        }

        float distance(const Point &other) const
        {
            return sqrt(pow(x - other.x, 2) + pow(y - other.y, 2));
        }

        Point operator-(const Point &other) const
        {
            return Point(x - other.x, y - other.y);
        }
    };

    template <typename T>
    struct Size
    {
        T width;
        T height;

        Size(T width, T height) : width(width), height(height) {}

        bool operator==(const Size &other) const
        {
            return width == other.width && height == other.height;
        }

        Size operator-(const Size &other) const
        {
            return Size(width - other.width, height - other.height);
        }
    };

    template <typename T>
    struct Rect
    {
        // std::optional<float> corner_radius_;
        Point<T> origin_;
        Size<T> size;

        Rect(Point<T> origin, Size<T> size) : origin_(origin), size(size) {}

        bool operator==(const Rect &other) const
        {
            return origin_ == other.origin_ && size == other.size;
        }

        Rect operator-(const Rect &other) const
        {
            return Rect(origin_ - other.origin_, size - other.size);
        }
    };

    struct Color
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

        bool operator==(const Color &other) const
        {
            return r == other.r && g == other.g && b == other.b && a == other.a;
        }

        static Color rgb(uint8_t r, uint8_t g, uint8_t b)
        {
            return {r, g, b, 255};
        }

        static Color rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        {
            return {r, g, b, a};
        }

        static Color rgb(int r, int g, int b)
        {
            return {
                static_cast<uint8_t>(r),
                static_cast<uint8_t>(g),
                static_cast<uint8_t>(b),
                255};
        }

        /// @brief Create a color from a hex value.
        static Color rgb(int hex)
        {
            return {
                static_cast<uint8_t>(hex >> 16 & 0xFF),
                static_cast<uint8_t>(hex >> 8 & 0xFF),
                static_cast<uint8_t>(hex & 0xFF),
                255};
        }

        static Color rgba(int hex)
        {
            return {
                static_cast<uint8_t>(hex >> 24 & 0xFF),
                static_cast<uint8_t>(hex >> 16 & 0xFF),
                static_cast<uint8_t>(hex >> 8 & 0xFF),
                static_cast<uint8_t>(hex & 0xFF)};
        }
    };







}
