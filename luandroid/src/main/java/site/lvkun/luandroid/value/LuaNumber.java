package site.lvkun.luandroid.value;

import site.lvkun.luandroid.LuaValue;

public class LuaNumber implements LuaValue {

    private final Double mValue;

    public LuaNumber(Double value) {
        mValue = value;
    }

    @Override
    public Type getType() {
        return Type.NUMBER;
    }

    public Double toDouble() {
        return mValue;
    }
}
