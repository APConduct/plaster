//
// Created by Aidan Jost on 3/18/25.
//

export module plaster.core;
#include <cstdint>
#include <optional>

export namespace plaster
{

    /// @brief Result type for error handling
    template <typename T, typename E = std::string>
    struct Result
    {
    protected:
        /// @brief The value of the result.
        std::variant<T, E> value_;
    public:

        /// @brief Construct a new Result with a success value.
        explicit Result(const T& success) : value_(success) {}

        /// @brief Construct a new Result with a success value.
        explicit Result(T&& success) : value_(std::move(success)) {}

        ///
        explicit Result(E&& error) : value_(std::move(error)) {}

        // [[nodiscard]] bool is_ok() const { return std::holds_alternative<T>(value_); }
        // [[nodiscard]] bool is_err() const {return std::holds_alternative<E>(value_); }

        /// @brief Check if the result is an ok value.
        [[nodiscard]] bool is_ok() const { return value_.index() == 0; }

        /// @brief Check if the result is an error value.
        [[nodiscard]] bool is_err() const { return value_.index() == 1; }

        /// @brief Unwrap the value of the result.
        const T& unwrap() const &
        {
            if (is_err()) throw std::runtime_error("Unwrapped an error Result");
            return std::get<E>(value_);
        }

        T unwrap() &&
        {
            if (is_err()) throw std::runtime_error("Unwrapped an error Result");
            return std::move(std::get<E>(value_));
        }

        const E& error() const &
        {
            if (is_ok()) throw std::runtime_error("Called error() on an ok Result");
            return std::get<E>(value_);
        }

        template <typename F>
        auto map(F&& f) const -> Result<std::invoke_result<F, T>, E>
        {
            if (is_ok())
            {
                // return Result<std::invoke_result<F, T>, E>(f(std::get<T>(value_)));

                return Result<std::invoke_result<F, T>, E>(f(std::get<0>(value_)));

            }
            // return Result<std::invoke_result<F, T>, E>(std::get<E>(value_));

            return Result<std::invoke_result<F, T>, E>(std::get<1>(value_));
        }

        template <typename F>
        auto and_then(F&& f) const -> std::invoke_result<F, T>
        {
            if (is_ok())
            {
                return f(std::get<0>(value_));
            }
            return std::invoke_result<F, T>(std::get<1>(value_));
        }
    };

    // Resource management
    template<typename  T>
    using Ref = std::shared_ptr<T>;

    template<typename T, typename... Args>
    Ref<T> make_ref(Args&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }



    template<typename T>
    concept CanPaint = requires(T t, class Painter& p)
    {
        { t.paint(p) } -> std::same_as<void>;
    };

    template<typename T>
    concept EventHandler = requires(T t, class Event& e)
    {
        { t.handle(e) } -> std::same_as<bool>;
    };




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

        Point operator+(const Point &other) const
        {
            return Point(x + other.x, y + other.y);
        }

        Point operator*(const Point &other) const
        {
            return Point(x * other.x, y * other.y);
        }

        /// @brief Multiply a point by a scalar.
        /// @param scalar The scalar to multiply by.
        template <typename U>
        Point<U> operator/(T scalar) const
        {
            return Point(x / scalar, y / scalar);
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
