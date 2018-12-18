#include "LuaValue.h"

#define LUA_NUMBER_CLASS_NAME "site/lvkun/luandroid/value/LuaState"

jobject newLuaNumber(JNIEnv* env) {
    jclass luaNumberClass = env->FindClass(LUA_NUMBER_CLASS_NAME);
    jmethodID constructor = env->GetMethodID(luaNumberClass, "")
}