//
// Created by Aidan Jost on 3/20/25.
//
module;
#include <GLFW/glfw3.h>
#include <string>
#include <functional>
export module plaster.window;

import plaster.core;
import plaster.event;

export namespace plaster::window
{
    struct WindowProps
    {
        std::string title{"Plaster"};

        uint32_t width{800}, height{600};

        bool resizable{true};
        bool decorated{true};
        bool fullscreen{false};
        bool vsync{true};

        WindowProps() = default;

        WindowProps(std::string& title, uint32_t width, uint32_t height) : title(std::move(title)), width(width), height(height) {}

    };

    struct Window
    {
        using EventCallbackFn = std::function<void(Event&)>;

    protected:
        struct WindowData
        {
            std::string title;
            uint32_t width, height;
            bool resizable, decorated, fullscreen, vsync;
            EventCallbackFn event_callback;
        };

        GLFWwindow* window_handle_;
        WindowData data_;
        bool initialized_;

    public:
        explicit Window(const WindowProps& props);
        ~Window();

        Window(const Window&) = delete;

        Window(Window&& other) noexcept;
        Window& operator=(Window&& other) noexcept;

        void on_update();

        [[nodiscard]] uint32_t get_width() const
        {
            return data_.width;
        };

        [[nodiscard]] uint32_t get_height() const
        {
            return data_.height;
        }

        void set_vsync(bool enabled);
        [[nodiscard]] bool is_vsync() const;

        void set_event_callback(const EventCallbackFn& callback);

        [[nodiscard]] bool is_initialized() const
        {
            return initialized_;
        }

        [[nodiscard]] void* get_native_window() const
        {
            return window_handle_;
        }

        [[nodiscard]] bool should_close() const;
        void set_should_close(bool should_close);

        void set_title(const std::string& title);

        [[nodiscard]] Point<float> get_size() const;
        void set_size(const Point<float>& size);

        [[nodiscard]] float get_time() const;
    };

    class WindowManager
    {
    protected:
        std::unordered_map<uint32_t, std::unique_ptr<Window>> windows_;
        uint32_t next_id_{0};
        uint32_t active_window_id_{0};

    public:
        WindowManager() = default;
        ~WindowManager() = default;

        uint32_t create_window(const WindowProps& props);

        Window* get_window(uint32_t id);

        void destroy_window(uint32_t id);

        void set_active_window(uint32_t id);

        [[nodiscard]] Window* get_active_window() const;

        void update_all();

        [[nodiscard]] bool has_open_windows() const;
    };
}
