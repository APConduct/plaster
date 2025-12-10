module;
#include <algorithm>
#include <type_traits>


export module plaster.flat.size;

export namespace plaster::flat {

template <typename T>
    requires std::is_arithmetic_v<T>
struct Size final {
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic");

protected:
    T width_{};
    T height_{};

public:
    explicit Size(T width = 0, T height = 0) : width_(width), height_(height) {}

    Size operator+(const Size& other) const { return Size(width_ + other.width_, height_ + other.height_); }

    Size operator-(const Size& other) const { return Size(width_ - other.width_, height_ - other.height_); }

    Size operator*(const Size& other) const { return Size(width_ * other.width_, height_ * other.height_); }

    Size operator/(const Size& other) const { return Size(width_ / other.width_, height_ / other.height_); }

    Size operator%(const Size& other) const { return Size(width_ % other.width_, height_ % other.height_); }

    Size& operator+=(const Size& other) {
        width_ += other.width_;
        height_ += other.height_;
        return *this;
    }

    Size& operator-=(const Size& other) {
        width_ -= other.width_;
        height_ -= other.height_;
        return *this;
    }

    Size operator*(T scalar) const { return Size(width_ * scalar, height_ * scalar); }

    Size operator/(T scalar) const { return Size(width_ / scalar, height_ / scalar); }

    bool operator==(const Size& other) const { return width_ == other.width_ && height_ == other.height_; }

    bool operator!=(const Size& other) const { return !(*this == other); }

    T width() const { return width_; }
    T height() const { return height_; }

    Size& of_width(T width) {
        width_ = width;
        return *this;
    }

    Size& of_height(T height) {
        height_ = height;
        return *this;
    }

    template <typename U>
    U max_diff(const Size& other) const {
        return std::max(width_ - other.width_, height_ - other.height_);
    }

    template <typename U>
    U height_diff(const Size& other) const {
        return height_ - other.height_;
    }

    template <typename U>
    U width_diff(const Size& other) const {
        return width_ - other.width_;
    }
};

template <typename T>
concept SizeTrait = requires(T p) {
    { p.width() } -> std::convertible_to<T>;
    { p.height() } -> std::convertible_to<T>;
};

template <typename T>
concept SizeInterface = requires(T p) {
    { p.width } -> std::convertible_to<T>;
    { p.height } -> std::convertible_to<T>;
};

template <typename T>
concept HasSizeMember = requires(T p) {
    { p.width } -> std::convertible_to<T>;
    { p.height } -> std::convertible_to<T>;
};

template <typename T>
concept HasSizeMethod = requires(T p) {
    { p.width() } -> std::convertible_to<T>;
    { p.height() } -> std::convertible_to<T>;
};

template <typename T>
concept HashSize = HasSizeMember<T> || HasSizeMethod<T>;

template <typename T>
concept SizeLike = SizeTrait<T> || SizeInterface<T>;


} // namespace plaster::flat
