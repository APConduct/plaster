#pragma once
#include <array>
#include <glm/glm.hpp>

namespace plaster {

namespace input {
struct Manager {
public:
    Manager();

    void update();

    glm::vec2 get_mouse_pos() const { return mouse_pos; }
    bool is_mouse_pressed(int button) const;
    bool is_mouse_released(int button) const;
    bool is_key_pressed(int key) const;
    bool is_key_released(int key) const;

    void set_mouse_pos(glm::vec2 pos) { mouse_pos = pos; }
    void set_mouse_pressed(int button, bool pressed);
    void set_key_pressed(int key, bool pressed);

private:
    glm::vec2 mouse_pos;
    std::array<bool, 8> mouse_buttons;
    std::array<bool, 8> mouse_buttons_prev;
    std::array<bool, 512> keys;
    std::array<bool, 512> keys_prev;
};
} // namespace input

} // namespace plaster
