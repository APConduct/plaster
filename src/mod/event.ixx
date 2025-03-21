//
// Created by Aidan Jost on 3/20/25.
//
module;
#include <variant>


namespace plaster
{
    struct Window;
}

#include <utility>
export module plaster.event;

import plaster.core;

export namespace plaster
{
    namespace event
    {
        using MousePos = std::pair<double, double>;

        struct MouseMoveEvent
        {
            MousePos pos;
            Window* source;

        };

        struct MouseButtonEvent
        {
            int button;
            int action;
            int mod;
            MousePos pos;
            Window* source;
        };

        struct KeyEvent
        {
            int key;
            int scancode;
            int action;
            int mod;
            Window* source;
        };

        struct WindowResizeEvent
        {
            int width;
            int height;
            Window* source;
        };


    }

    using Event = std::variant<
        event::MouseMoveEvent,
        event::MouseButtonEvent,
        event::KeyEvent,
        event::WindowResizeEvent
        >;
}

