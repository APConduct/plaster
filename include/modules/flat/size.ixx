module;
#include <type_traits>


export module plaster.flat.size;

export namespace plaster {

    template <typename T> requires std::is_arithmetic_v<T>
    struct Size final{
        protected:
        public:
    };

}
