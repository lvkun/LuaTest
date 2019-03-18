#ifndef LUANDROID_LUAVALUE_H
#define LUANDROID_LUAVALUE_H

#include <jni.h>

jobject newLuaInteger(JNIEnv* env, int value);
jobject newLuaNumber(JNIEnv* env, double value);

#endif //LUANDROID_LUAVALUE_H
