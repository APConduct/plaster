#include "plaster/input_manager.hpp"
namespace plaster::input {
input::Manager::Manager() : mouse_pos(0, 0) {
    mouse_buttons.fill(false);
    mouse_buttons_prev.fill(false);
    keys.fill(false);
    keys_prev.fill(false);
};

void input::Manager::update() {
    mouse_buttons_prev = mouse_buttons;
    keys_prev = keys;
}

bool input::Manager::is_mouse_pressed(int button) const {
    return button >= 0 && button < 8 ? mouse_buttons[button] : false;
}

bool input::Manager::is_mouse_released(int button) const {
    return button >= 0 && button < 8 ? !mouse_buttons[button] && mouse_buttons_prev[button] : false;
}

bool input::Manager::is_key_pressed(int key) const { return key >= 0 && key < 256 ? keys[key] : false; }

bool input::Manager::is_key_released(int key) const {
    return key >= 0 && key < 256 ? !keys[key] && keys_prev[key] : false;
}

void input::Manager::set_mouse_pressed(int button, bool pressed) {
    if (button >= 0 && button < 8) {
        mouse_buttons[button] = pressed;
    }
}

void input::Manager::set_key_pressed(int key, bool pressed) {
    if (key >= 0 && key < 256) {
        keys[key] = pressed;
    }
}


} // namespace plaster::input
