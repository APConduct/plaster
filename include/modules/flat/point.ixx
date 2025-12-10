module;
#include <concepts>

export module plaster.flat.point;

export namespace plaster::flat {
/**
 * @brief A template class representing a 2D point with arithmetic operations.
 * @tparam T The type of the coordinates, must be an arithmetic type.
 */
template <typename T>
    requires std::is_arithmetic_v<T>
struct Point final {
    static_assert(std::is_arithmetic_v<T>, "Point must be of an arithmetic type");

protected:
    T x_{}; ///< The x-coordinate of the point.
    T y_{}; ///< The y-coordinate of the point.

public:
    /**
     * @brief Constructs a Point with given x and y coordinates.
     * @param x The x-coordinate (default is 0).
     * @param y The y-coordinate (default is 0).
     */
    explicit Point(T x = 0, T y = 0) : x_(x), y_(y) {}

    /**
     * @brief Adds two points.
     * @param other The other point to add.
     * @return A new Point that is the sum of this and the other point.
     */
    Point operator+(const Point& other) const { return Point(x_ + other.x_, y_ + other.y_); }

    /**
     * @brief Adds another point to this point.
     * @param other The other point to add.
     * @return A reference to this point after addition.
     */
    Point& operator+=(const Point& other) {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    /**
     * @brief Subtracts another point from this point.
     * @param other The other point to subtract.
     * @return A new Point that is the difference of this and the other point.
     */
    Point operator-(const Point& other) const { return Point(x_ - other.x_, y_ - other.y_); }

    /**
     * @brief Subtracts another point from this point.
     * @param other The other point to subtract.
     * @return A reference to this point after subtraction.
     */
    Point& operator-=(const Point& other) {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    /**
     * @brief Multiplies this point by a scalar.
     * @param scalar The scalar value to multiply by.
     * @return A new Point that is the result of the multiplication.
     */
    Point operator*(T scalar) const { return Point(x_ * scalar, y_ * scalar); }

    /**
     * @brief Divides this point by a scalar.
     * @param scalar The scalar value to divide by.
     * @return A new Point that is the result of the division.
     */
    Point operator/(T scalar) const { return Point(x_ / scalar, y_ / scalar); }

    /**
     * @brief Checks if two points are equal.
     * @param other The other point to compare.
     * @return True if the points are equal, false otherwise.
     */
    bool operator==(const Point& other) const { return x_ == other.x_ && y_ == other.y_; }

    /**
     * @brief Checks if two points are not equal.
     * @param other The other point to compare.
     * @return True if the points are not equal, false otherwise.
     */
    bool operator!=(const Point& other) const { return !(*this == other); }

    /**
     * @brief Gets the x-coordinate of the point.
     * @return The x-coordinate.
     */
    T x() const { return x_; }

    /**
     * @brief Gets the y-coordinate of the point.
     * @return The y-coordinate.
     */
    T y() const { return y_; }

    /**
     * @brief Sets the x-coordinate of the point.
     * @param new_x The new x-coordinate.
     * @return A reference to this point.
     */
    Point& at_x(T new_x) {
        x_ = new_x;
        return *this;
    }

    /**
     * @brief Sets the y-coordinate of the point.
     * @param new_y The new y-coordinate.
     * @return A reference to this point.
     */
    Point& at_y(T new_y) {
        y_ = new_y;
        return *this;
    }

    /**
     * @brief Calculates the distance from this point to another point.
     * @tparam U The type of the other point's coordinates.
     * @param other The other point.
     * @return The distance between the two points.
     */
    template <typename U>
    U distance_from(const Point<U>& other) const {
        U dx = static_cast<U>(other.x() - static_cast<U>(x_));
        U dy = static_cast<U>(other.y() - static_cast<U>(y_));
        return static_cast<U>(sqrt(dx * dx + dy * dy));
    }

    /**
     * @brief Calculates the y-distance from this point to another point.
     * @tparam U The type of the other point's coordinates.
     * @param other The other point.
     * @return The y-distance between the two points.
     */
    template <typename U>
    U y_from(const Point<U>& other) const {
        return static_cast<U>(other.y() - y_);
    }

    /**
     * @brief Calculates the x-distance from this point to another point.
     * @tparam U The type of the other point's coordinates.
     * @param other The other point.
     * @return The x-distance between the two points.
     */
    template <typename U>
    U x_from(const Point<U>& other) const {
        return static_cast<U>(other.x() - x_);
    }

    /**
     * @brief Casts this point to another type.
     * @tparam U The target type for the cast.
     * @return A new Point with the coordinates cast to the target type.
     */
    template <typename U>
    Point<U> cast() const {
        return Point<U>(static_cast<U>(x_), static_cast<U>(y_));
    }
};

template <typename T>
concept PointTrait = requires(T p) {
    { p.x() } -> std::convertible_to<double>;
    { p.y() } -> std::convertible_to<double>;
};

template <typename T>
concept PointInferface = requires(T p) {
    { p.x } -> std::convertible_to<double>;
    { p.y } -> std::convertible_to<double>;
};


template <typename T>
concept HasPointMethod = requires(T p) {
    { p.x() } -> std::convertible_to<double>;
    { p.y() } -> std::convertible_to<double>;
};

template <typename T>
concept HasPointMember = requires(T p) {
    { p.x } -> std::convertible_to<double>;
    { p.y } -> std::convertible_to<double>;
};

template <typename T>
concept HasPoint = HasPointMethod<T> || HasPointMember<T>;

template <typename T>
concept Pointy = PointTrait<T> || PointInferface<T>;


} // namespace plaster::flat
