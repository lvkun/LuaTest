#include "LuaValue.h"
#include "../Constants.h"

#define LUA_INTEGER_CLASS_NAME "site/lvkun/luandroid/value/LuaInteger"
#define LUA_NUMBER_CLASS_NAME "site/lvkun/luandroid/value/LuaNumber"

jobject newLuaInteger(JNIEnv* env, int value) {
    jclass luaNumberClass = env->FindClass(LUA_INTEGER_CLASS_NAME);
    jmethodID constructor = env->GetMethodID(luaNumberClass, CONSTRUCTOR_METHOD_NAME, "(I)V");

    jobject newObj = nullptr;
    if (constructor != nullptr) {
        newObj = env->NewObject(luaNumberClass, constructor, value);
    }

    return newObj;
}

jobject newLuaNumber(JNIEnv* env, double value) {
    jclass luaNumberClass = env->FindClass(LUA_NUMBER_CLASS_NAME);
    jmethodID constructor = env->GetMethodID(luaNumberClass, CONSTRUCTOR_METHOD_NAME, "(D)V");

    jobject newObj = nullptr;
    if (constructor != nullptr) {
        newObj = env->NewObject(luaNumberClass, constructor, value);
    }

    return newObj;
}