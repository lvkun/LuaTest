package site.lvkun.luandroid;

import android.util.Log;
import android.util.LongSparseArray;

public class LuaState {

    static {
        System.loadLibrary("luandroid");
    }

    public long mStateHandle;

    private static LongSparseArray<LuaState> sLuaStateMap = new LongSparseArray<>();

    public static LuaState newState() {
        LuaState state = nativeNewState();
        sLuaStateMap.put(state.mStateHandle, state);
        return state;
    }

    public static native LuaState nativeNewState();

    public void close() {
        sLuaStateMap.delete(mStateHandle);
        nativeClose();
    }

    public native void nativeClose();

    public int loadString(String str) {
        return nativeLoadString(str);
    }

    public LuaValue getGlobal(String name) {
        return nativeGetGlobal(name);
    }

    public native int nativeLoadString(String str);

    public native LuaValue nativeGetGlobal(String name);

    public void callback() {
        Log.d("LUASTATE", "callback");
    }
}
