#pragma once
#include <lua.h>

namespace plaster {

namespace ui {
class Engine;
}

class LuaAPI {
public:
    LuaAPI(lua_State* L, ui::Engine* engine);

    static int button(lua_State* L);
    static int panel(lua_State* L);
    static int text(lua_State* L);
    static int get_mouse_pos(lua_State* L);

    void register_functions();

private:
    lua_State* L;
    ui::Engine* engine;

public:
    static LuaAPI* get_instance(lua_State* L);
};

} // namespace plaster
