package site.lvkun.luandroid.value;

import site.lvkun.luandroid.LuaValue;

public class LuaNumber implements LuaValue {
    private final double mValue;

    public LuaNumber(double value) {
        mValue = value;
    }

    @Override
    public Type getType() {
        return Type.NUMBER;
    }

    public double getValue() {
        return mValue;
    }

}
