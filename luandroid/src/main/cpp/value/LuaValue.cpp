#include "LuaValue.h"
#include "../Constants.h"

#define LUA_NUMBER_CLASS_NAME "site/lvkun/luandroid/value/LuaInteger"

jobject newLuaInteger(JNIEnv* env, int value) {
    jclass luaNumberClass = env->FindClass(LUA_NUMBER_CLASS_NAME);
    jmethodID constructor = env->GetMethodID(luaNumberClass, CONSTRUCTOR_METHOD_NAME, "(I)V");

    jobject newIntObj;
    if (constructor != NULL) {
        newIntObj = env->NewObject(luaNumberClass, constructor, value);
    }

    return newIntObj;
}