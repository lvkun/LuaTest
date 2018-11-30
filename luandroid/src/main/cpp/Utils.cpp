#include "Utils.h"
#include "Log.h"

#define TAG "LUASTACK"

static void stackDump (lua_State *L) {
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {

            case LUA_TSTRING:  /* strings */
                LOGD(TAG, "`%s'", lua_tostring(L, i));
                break;

            case LUA_TBOOLEAN:  /* booleans */
                LOGD(TAG, lua_toboolean(L, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:  /* numbers */
                LOGD(TAG, "%g", lua_tonumber(L, i));
                break;

            default:  /* other values */
                LOGD(TAG, "%s", lua_typename(L, t));
                break;

        }
        LOGD(TAG, "  ");  /* put a separator */
    }
    LOGD(TAG, "\n");  /* end the listing */
}