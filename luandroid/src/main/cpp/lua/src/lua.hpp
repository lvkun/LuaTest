// lua.hpp
// Lua header files for C++
// <<extern "C">> not supplied automatically because Lua also compiles as C++

extern "C" {
#include "LuaInterface.h"
#include "lualib.h"
#include "lauxlib.h"
}
