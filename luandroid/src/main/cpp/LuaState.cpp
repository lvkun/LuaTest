#include <jni.h>
#include <lua.hpp>
#include <lauxlib.h>

#include "Log.h"
#include "value/LuaValue.h"
#include "Constants.h"

#define TAG "LUASTATE"
#define LUAJAVAJNIENVTAG "__JNIEnv"
#define LUAJAVASTATETAG "__JAVASTATE"

#define STATE_CLASS_NAME "site/lvkun/luandroid/LuaState"

void savePointer(lua_State *state, const char *tag, void *pointer) {
    void **pPointer;

    LOGD(TAG, "savePointer %s %p", tag, pointer);

    lua_pushstring(state , tag);
    lua_rawget(state, LUA_REGISTRYINDEX);

    if (!lua_isnil(state , -1)) {
        pPointer = (void**) lua_touserdata(state, -1);
        *pPointer = pointer;

        lua_pop(state, 1);
    } else {
        lua_pop(state, 1);
        pPointer = (void **) lua_newuserdata(state, sizeof(void *));
        *pPointer = pointer;

        lua_pushstring(state, tag);
        lua_insert(state, -2);
        lua_rawset(state, LUA_REGISTRYINDEX);
    }
}

void* loadPointer(lua_State *state, const char* tag) {
    void **pPointer;

    lua_pushstring(state, tag);
    lua_rawget(state, LUA_REGISTRYINDEX);

    if (!lua_isuserdata(state, -1)) {
        lua_pop(state, 1);
        return NULL;
    }

    pPointer = (void **)lua_touserdata(state, -1);
    lua_pop(state, 1);

    return *pPointer;
}

lua_State* getState(JNIEnv *env, jobject stateObject) {
    jclass luaStateClass = env->FindClass(STATE_CLASS_NAME);
    jfieldID stateHandle = env->GetFieldID(luaStateClass, "mStateHandle", "J");

    return (lua_State*) env->GetLongField(stateObject, stateHandle);
}

static int call(lua_State *state) {
    JNIEnv *env = (JNIEnv*) loadPointer(state, LUAJAVAJNIENVTAG);

    if (env == NULL) {
        return -1;
    }

    jclass luaStateClass = env->FindClass(STATE_CLASS_NAME);
    jmethodID callback = env->GetMethodID(luaStateClass, "callback", "()V");

    jobject stateObject = (jobject) loadPointer(state, LUAJAVASTATETAG);

    env->CallVoidMethod(stateObject, callback);

    return 0;
}

extern "C"
JNIEXPORT jobject
JNICALL
Java_site_lvkun_luandroid_LuaState_nativeNewState(
        JNIEnv *env,
        jobject /* this */) {
    jclass luaStateClass = env->FindClass(STATE_CLASS_NAME);
    jmethodID constructor = env->GetMethodID(luaStateClass, CONSTRUCTOR_METHOD_NAME, "()V");

    jobject stateObject = env->NewObject(luaStateClass, constructor);
    jobject globalState = env->NewGlobalRef(stateObject);

    lua_State* state = luaL_newstate();

    savePointer(state, LUAJAVAJNIENVTAG, env);
    savePointer(state, LUAJAVASTATETAG, globalState);

    lua_register(state, "android_call", call);

    jfieldID stateHandle = env->GetFieldID(luaStateClass, "mStateHandle", "J");
    env->SetLongField(stateObject, stateHandle, (jlong) state);

    env->DeleteLocalRef(luaStateClass);

    return stateObject;
}

extern "C"
JNIEXPORT void JNICALL
Java_site_lvkun_luandroid_LuaState_nativeClose(JNIEnv *env, jobject instance) {
    lua_State* state = getState(env, instance);

    jobject globalState = (jobject) loadPointer(state, LUAJAVASTATETAG);
    env->DeleteGlobalRef(globalState);

    lua_close(state);
}

extern "C"
JNIEXPORT jint JNICALL
Java_site_lvkun_luandroid_LuaState_nativeLoadString(JNIEnv *env, jobject instance, jstring str_) {
    const char *str = env->GetStringUTFChars(str_, 0);

    lua_State* state = getState(env, instance);

    int ret = luaL_dostring(state, str);

    env->ReleaseStringUTFChars(str_, str);

    return (jint) ret;
}

extern "C"
JNIEXPORT jobject JNICALL
Java_site_lvkun_luandroid_LuaState_nativeGetGlobal(JNIEnv *env, jobject instance, jstring name_) {
    const char *name = env->GetStringUTFChars(name_, 0);

    lua_State* state = getState(env, instance);

    lua_getglobal(state, name);

    LOGD(TAG, "getGlobal %s", name);

    jobject variable;
    int type = lua_type(state, -1);
    switch (type) {
        case LUA_TNUMBER:
            if (lua_isinteger(state, -1)) {
                int value = lua_tointeger(state, -1);
                variable = newLuaInteger(env, value);
            } else {
                double value = lua_tonumber(state, -1);
                variable = newLuaNumber(env, value);
            }
            break;
    }
    env->ReleaseStringUTFChars(name_, name);

    return variable;
}