package site.lvkun.luandroid.value;

import site.lvkun.luandroid.LuaValue;

public class LuaInteger implements LuaValue {

    private final int mValue;

    public LuaInteger(int value) {
        mValue = value;
    }

    @Override
    public Type getType() {
        return Type.INTEGER;
    }

    public int getValue() {
        return mValue;
    }
}
