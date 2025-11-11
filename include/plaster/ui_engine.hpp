#pragma once
#include <cstdint>
#include <expected>
#include <functional>
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <map>
#include <stdexcept>
#include <string>
#include "plaster/input_manager.hpp"


namespace plaster {
struct Renderer;


namespace ui {
struct Element {
    std::string type;
    std::string id;
    glm::vec4 rect;
    uint32_t color;
    bool hovered;
    bool clicked;
    // bool focused;
    // bool selected;
    // bool disabled;

    std::map<std::string, std::string> props;

    template <typename T>
    std::expected<T, std::string> get_prop(const std::string& key) const {
        auto it = props.find(key);
        if (it == props.end()) {
            return std::unexpected<std::string>("Property not found");
        }
        try {
            return std::stoi(it->second);
        }
        catch (const std::invalid_argument&) {
            return std::unexpected<std::string>("Invalid value of type: " + std::string(typeid(T).name()) + ": " +
                                                it->second + " is not a property of Element: " + std::string(id));
        }
    }

    // template <typename F, typename T = void>
    // void onclick(std::function<F(T)> func) {
    //     func();
    // }
    //

    glm::vec2 get_mouse_pos() const;

    template <typename T, typename FT>
    T on_(FT&& func) {
        return func();
    }
};

struct State {
    glm::vec2 mouse_pos;
    bool mouse_pressed;
    bool mouse_released;
    std::string focused_element;
};

struct Engine {
public:
    Engine(Renderer* renderer, input::Manager* input);

    void update(float dt);
    void render();

    bool button(const std::string& id, glm::vec2 pos, glm::vec2 size, const std::string& label);

    bool checkbox(const std::string& id, glm::vec2 pos, bool* value, const std::string& label);
    void panel(const std::string& id, glm::vec2 pos, glm::vec2 size, uint32_t color);
    void text(glm::vec2 pos, const std::string& text, uint32_t color, float scale = 1.0f);

    State get_state() const { return state; }

private:
    Renderer* renderer;
    input::Manager* input;
    State state;
    std::map<std::string, Element> elements;

    bool is_point_in_rect(glm::vec2 point, glm::vec4 rect);
    void update_input();
};
}; // namespace ui
} // namespace plaster
  // namespace plaster
