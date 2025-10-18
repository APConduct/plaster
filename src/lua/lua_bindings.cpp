#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include "plaster/lua_api.hpp"
#include "plaster/ui_engine.hpp"


namespace plaster {
static const char* PLASTER_METATABLE = "plaster_instance";

LuaAPI::LuaAPI(lua_State* L, ui::Engine* engine) : L(L), engine(engine) {
    lua_pushlightuserdata(L, this);
    lua_setfield(L, LUA_REGISTRYINDEX, PLASTER_METATABLE);
    register_functions();
}

LuaAPI* LuaAPI::get_instance(lua_State* L) {
    lua_getfield(L, LUA_REGISTRYINDEX, PLASTER_METATABLE);
    LuaAPI* instance = static_cast<LuaAPI*>(lua_touserdata(L, -1));
    lua_pop(L, 1);
    return instance;
    // return static_cast<LuaAPI*>(lua_touserdata(L, lua_gettop(L)));
}

void LuaAPI::register_functions() {
    // Create UI table
    lua_newtable(L);

    // Register functions
    lua_pushcfunction(L, button);
    lua_setfield(L, -2, "button");

    lua_pushcfunction(L, panel);
    lua_setfield(L, -2, "panel");

    lua_pushcfunction(L, text);
    lua_setfield(L, -2, "text");

    lua_pushcfunction(L, get_mouse_pos);
    lua_setfield(L, -2, "get_mouse_pos");

    // Set as global "ui"
    lua_setglobal(L, "ui");
}

int LuaAPI::button(lua_State* L) {
    LuaAPI* api = get_instance(L);

    // Arguments: id, x, y, width, height, label
    const char* id = luaL_checkstring(L, 1);
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);
    float w = (float)luaL_checknumber(L, 4);
    float h = (float)luaL_checknumber(L, 5);
    const char* label = luaL_optstring(L, 6, "Button");

    glm::vec2 pos(x, y);
    glm::vec2 size(w, h);

    bool clicked = api->engine->button(id, pos, size, label);
    lua_pushboolean(L, clicked);
    return 1;
}

int LuaAPI::panel(lua_State* L) {
    LuaAPI* api = get_instance(L);

    // Arguments: id, x, y, width, height, color
    const char* id = luaL_checkstring(L, 1);
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);
    float w = (float)luaL_checknumber(L, 4);
    float h = (float)luaL_checknumber(L, 5);

    uint32_t color = 0xFFFFFFFF;
    if (lua_isnumber(L, 6)) {
        color = (uint32_t)lua_tonumber(L, 6);
    }

    glm::vec2 pos(x, y);
    glm::vec2 size(w, h);

    api->engine->panel(id, pos, size, color);
    return 0;
}
int LuaAPI::text(lua_State* L) {
    LuaAPI* api = get_instance(L);

    // Arguments: text, x, y, color, scale
    const char* str = luaL_checkstring(L, 1);
    float x = (float)luaL_checknumber(L, 2);
    float y = (float)luaL_checknumber(L, 3);
    uint32_t color = (uint32_t)luaL_optnumber(L, 4, 0xFFFFFFFF);
    float scale = (float)luaL_optnumber(L, 5, 1.0f);

    glm::vec2 pos(x, y);
    api->engine->text(pos, str, color, scale);
    return 0;
}

int LuaAPI::get_mouse_pos(lua_State* L) {
    LuaAPI* api = get_instance(L);

    auto pos = api->engine->get_state().mouse_pos;
    lua_pushnumber(L, pos.x);
    lua_pushnumber(L, pos.y);
    return 2;
}
} // namespace plaster
