module;
#include <type_traits>

export module plaster.flat;

export import plaster.flat.point;
export import plaster.flat.size;

export namespace plaster::flat {

template <typename T>
    requires std::is_arithmetic_v<T>
struct Rect final {
    static_assert(std::is_arithmetic_v<T>, "T must be arithmetic");

protected:
    Point<T> origin_{};
    Size<T> size_{};

public:
    explicit Rect(Point<T> origin = {}, Size<T> size = {}) : origin_(origin), size_(size) {}

    explicit Rect(T x = 0, T y = 0, T width = 0, T height = 0) : origin_(x, y), size_(width, height) {}

    explicit Rect() : origin_(0, 0), size_(0, 0) {}

    Rect(const Rect&) = default;
    Rect& operator=(const Rect&) = default;

    Rect(Rect&&) = default;
    Rect& operator=(Rect&&) = default;

    ~Rect() = default;
};
} // namespace plaster::flat
