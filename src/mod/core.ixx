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

        /// @brief Map the value of the result to a new value.
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


    /// @brief A point in 2D space.
    template <typename T>
    struct Point
    {
    protected:
        T x_;
        T y_;

    public:

        /// @brief Construct a new Point object.
        Point(T x, T y) : x_(x), y_(y) {}
        // explicit operator T() const { return x; }

        /// @brief Set the x and y values of the point.
        /// @param x The new x value.
        /// @param y The new y value.
        void set(T x, T y) { x_ = x, y_ = y; }

        /// @brief Set the x value of the point.
        /// @param x The new x value.
        void set_x(T x) { x_ = x; }

        /// @brief Set the y value of the point.
        void set_y(T y) { y_ = y; }

        /// @brief Check if two points are equal.
        /// @param other The other point to compare to.
        /// @return True if the points are equal.
        bool operator==(const Point &other) const
        {
            return x_ == other.x_ && y_ == other.y_;
        }

        /// @brief Check if two points are not equal.
        /// @param other The other point to compare to.
        /// @return True if the points are not equal.
        float distance(const Point &other) const
        {
            return sqrt(pow(x_ - other.x_, 2) + pow(y_ - other.y_, 2));
        }

        /// @brief Subtract a point from this point.
        /// @param other The point to subtract.
        /// @return The result of the subtraction.
        Point operator-(const Point &other) const
        {
            return Point(x_ - other.x_, y_ - other.y_);
        }

        /// @brief Add a point to this point.
        /// @param other The point to add.
        /// @return The result of the addition.
        Point operator+(const Point &other) const
        {
            return Point(x_ + other.x_, y_ + other.y_);
        }

        /// @brief Multiply a point by another point.
        /// @param other The point to multiply by.
        /// @return The result of the multiplication.
        Point operator*(const Point &other) const
        {
            return Point(x_ * other.x_, y_ * other.y_);
        }

        /// @brief Multiply a point by a scalar.
        /// @param scalar The scalar to multiply by.
        /// @return The result of the multiplication.
        /// @tparam U The type of the scalar.
        template <typename U>
        Point<U> operator/(T scalar) const
        {
            return Point(x_ / scalar, y_ / scalar);
        }

        /// @brief Get the x value of the point.
        /// @return The x value.
        T x() const { return x_; }

        /// @brief Get the y value of the point.
        /// @return The y value.
        T y() const { return y_; }

        /// @brief Set the x value of the point.
        /// @param x The new x value.
        /// @return A reference to the point.
        Point& at_x(T x) { x_ = x; return *this; }

        /// @brief Set the y value of the point.
        /// @param y The new y value.
        /// @return A reference to the point.
        Point& at_y(T y) { y_ = y; return *this; }
    };

    /// @brief A size in 2D space.
    /// @tparam T The type of the size.
    template <typename T>
    struct Size
    {

    protected:

        /// @brief The width of the size.
        T width_;

        /// @brief The height of the size.
        T height_;

    public:

        /// @brief Construct a new Size object.
        /// @param width The width of the size.
        /// @param height The height of the size.
        Size(T width, T height) : width_(width), height_(height) {}

        /// @brief Set the width and height of the size.
        /// @param width The new width.
        /// @param height The new height.
        void set(T width, T height) { width_ = width; height_ = height; }

        /// @brief Set the width of the size.
        /// @param width The new width.
        void set_width(T width) { width_ = width; }

        /// @brief Set the height of the size.
        /// @param height The new height.
        void set_height(T height) { height_ = height; }

        bool operator==(const Size &other) const
        {
            return width_ == other.width_ && height_ == other.height_;
        }

        /// @brief Subtract a size from this size.
        /// @param other The size to subtract.
        /// @return The result of the subtraction.
        Size operator-(const Size &other) const
        {
            return Size(width_ - other.width_, height_ - other.height_);
        }

        /// @brief Add a size to this size.
        /// @param other The size to add.
        /// @return The result of the addition.
        Size operator+(const Size &other) const
        {
            return Size(width_ + other.width_, height_ + other.height_);
        }

        /// @brief Multiply a size by another size.
        /// @param other The size to multiply by.
        /// @return The result of the multiplication.
        Size operator*(Size other) const{ return Size(width_ * other.width_, height_ * other.height_); }

        /// @brief Multiply a size by a scalar.\
        /// @param scalar The scalar to multiply by.
        /// @return The result of the multiplication.
        Size operator*(T scalar) const { return Size(width_ * scalar, height_ * scalar); }

        /// @brief Divide a size by a scalar.
        /// @param scalar The scalar to divide by.
        /// @return The result of the division.
        Size operator/(T scalar) const { return Size(width_ / scalar, height_ / scalar); }
    };

    /// @brief A line in 2D space.
    /// @tparam T The type of the line.
    template<typename T>
    struct Line
    {
    protected:

        /// @brief The start point of the line.
        Point<T> start_;

        /// @brief The end point of the line.
        Point<T> end_;

    public:

        /// @brief Construct a new Line object.
        /// @param start The start point of the line.
        /// @param end The end point of the line.
        /// @tparam T The type of the line.
        Line(Point<T> start, Point<T> end) : start_(start), end_(end) {}

        /// @brief Construct a new Line object.
        /// @param x1 The x value of the start point.
        /// @param y1 The y value of the start point.
        /// @param x2 The x value of the end point.
        /// @param y2 The y value of the end point.
        /// @tparam T The type of the line.
        Line(T x1, T y1, T x2, T y2) : start_(x1, y1), end_(x2, y2) {}

        /// @brief Set the start and end points of the line.
        /// @param x1 The x value of the start point.
        /// @param y1 The y value of the start point.
        /// @param x2 The x value of the end point.
        /// @param y2 The y value of the end point.
        void set(T x1, T y1, T x2, T y2){ start_.set(x1, y1); end_.set(x2, y2); }

        /// @brief Set the start and end points of the line.
        /// @param start The start point of the line.
        /// @param end The end point of the line.
        void set(Point<T> start, Point<T> end){ start_ = start; end_ = end; }

        /// @brief Set the start point of the line.
        /// @param start The new start point.
        void set_start(Point<T> start){ start_ = start; }

        /// @brief Set the end point of the line.
        /// @param end The new end point.
        void set_end(Point<T> end){ end_ = end; }

        /// @brief Get the start point of the line.
        /// @return The start point.
        Point<T> start() const { return start_; }

        /// @brief Get the end point of the line.
        /// @return The end point.
        Point<T> end() const { return end_; }

        /// @brief Set the start point of the line.
        /// @param start The new start point.
        /// @return A reference to the line.
        Line& start(Point<T> start) { start_ = start; return *this; }

        /// @brief Set the end point of the line.
        /// @param end The new end point.
        /// @return A reference to the line.
        Line& end(Point<T> end) { end_ = end; return *this; }

    };

    template <typename T>
    struct Rect
    {
        // std::optional<float> corner_radius_;

    protected:
        T x_, y_, width_, height_;

    public:

        Rect(T x, T y, T width, T height) : x_(x), y_(y), width_(width), height_(height) {}
        Rect(Point<T> origin, Size<T> size) : x_(origin.x()), y_(origin.y()), width_(size.width()), height_(size.height()) {}

        void set(Point<T> origin, Size<T> size){ x_ = origin.x(); y_ = origin.y(); width_ = size.width(); height_ = size.height(); }
        void set(T x, T y, T width, T height) { x_ = x; y_ = y; width_ = width; height_ = height; }

        void set_x(T x) { x_ = x; }
        void set_y(T y) { y_ = y; }
        void set_width(T width) { width_ = width; }
        void set_height(T height) { height_ = height; }

        bool operator==(const Rect &other) const
        {
            return x_ == other.x_ && y_ == other.y_ && width_ == other.width_ && height_ == other.height_;
        }

        bool operator!=(const Rect &other) const
        {
            return x_ != other.x_ || y_ != other.y_;
        }

        Point<T> origin() const { return Point(x_, y_); }
        Size<T> size() const { return Size(width_, height_); }

        T x() const { return x_; }
        T y() const { return y_; }
        T width() const { return width_; }
        T height() const { return height_; }

        Rect& x(T x) { x_ = x; return *this; }
        Rect& y(T y) { y_ = y; return *this; }
        Rect& width(T width) { width_ = width; return *this; }
        Rect& height(T height) { height_ = height; return *this; }

        Rect& origin(Point<T> origin)
        {
            x_ = origin.x();
            y_ = origin.y();
            return *this;
        }

        Rect& size(Size<T> size)
        {
            width_ = size.width();
            height_ = size.height();
            return *this;
        }

        bool contains(Point<T> point) const
        {
            return point.x() >= x_ && point.x() <= x_ + width_ && point.y() >= y_ && point.y() <= y_ + height_;
        }

        bool contains(T x, T y) const
        {
            return x >= x_ && x <= x_ + width_ && y >= y_ && y <= y_ + height_;
        }

        bool intersects(const Rect &other) const
        {
            return x_ < other.x_ + other.width_ && x_ + width_ > other.x_ && y_ < other.y_ + other.height_ && y_ + height_ > other.y_;
        }

        bool contains(const Rect &other) const
        {
            return x_ <= other.x_ && y_ <= other.y_ && x_ + width_ >= other.x_ + other.width_ && y_ + height_ >= other.y_ + other.height_;
        }

        Line<T> top() const { return Line<T>(x_, y_, x_ + width_, y_); }
        Line<T> bottom() const { return Line<T>(x_, y_ + height_, x_ + width_, y_ + height_); }
        Line<T> left() const { return Line<T>(x_, y_, x_, y_ + height_); }
        Line<T> right() const { return Line<T>(x_ + width_, y_, x_ + width_, y_ + height_); }

        Line<T> hyp_tl_br() const { return Line<T>(x_, y_, x_ + width_, y_ + height_); }
        Line<T> hyp_bl_tr() const { return Line<T>(x_, y_ + height_, x_ + width_, y_); }

        Point<T> center() const { return Point(x_ + width_ / 2, y_ + height_ / 2); }

    };

    struct Color
    {
    protected:
        uint8_t r_, g_ ,b_, a_;

    public:

        Color() : r_(0), g_(0), b_(0), a_(0) {}

        Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r_(r), g_(g), b_(b), a_(a) {}

        bool operator==(const Color &other) const
        {
            return r_ == other.r_ && g_ == other.g_ && b_ == other.b_ && a_ == other.a_;
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

        static Color blank() { return {0, 0, 0, 0}; }
    };







}
