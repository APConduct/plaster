module;
#include <array>
#include <glm/glm.hpp>

export module plaster.input.manager;

export namespace plaster {
namespace input {
struct Manager {
    Manager() : mouse_pos(0, 0) {
        mouse_buttons.fill(false);
        mouse_buttons_prev.fill(false);
        keys.fill(false);
        keys_prev.fill(false);
    };
    void update() {
        mouse_buttons_prev = mouse_buttons;
        keys_prev = keys;
    };

    glm::vec2 get_mouse_pos() const { return mouse_pos; }
    bool is_mouse_pressed(int button) const { return button >= 0 && button < 8 ? mouse_buttons[button] : false; };
    bool is_mouse_released(int button) const {
        return button >= 0 && button < 8 ? !mouse_buttons[button] && mouse_buttons_prev[button] : false;
    };
    bool is_key_pressed(int key) const { return key >= 0 && key < 256 ? keys[key] : false; };
    bool is_key_released(int key) const { return key >= 0 && key < 256 ? !keys[key] && keys_prev[key] : false; };

    void set_mouse_pos(glm::vec2 pos) { mouse_pos = pos; }
    void set_mouse_pressed(int button, bool pressed) {
        if (button >= 0 && button < 8) {
            mouse_buttons[button] = pressed;
        }
    };
    void set_key_pressed(int key, bool pressed) {
        if (key >= 0 && key < 256) {
            keys[key] = pressed;
        }
    };

private:
    glm::vec2 mouse_pos{};
    std::array<bool, 8> mouse_buttons{};
    std::array<bool, 8> mouse_buttons_prev{};
    std::array<bool, 512> keys{};
    std::array<bool, 512> keys_prev{};
};
} // namespace input
} // namespace plaster
