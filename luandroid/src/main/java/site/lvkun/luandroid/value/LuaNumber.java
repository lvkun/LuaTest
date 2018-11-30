package site.lvkun.luandroid.value;

import site.lvkun.luandroid.LuaValue;

public class LuaNumber implements LuaValue {

    private final Double mValue;

    public LuaNumber(Double value) {
        mValue = value;
    }

    @Override
    public int getType() {
        return TYPE_NUMBER;
    }

    public Double toDouble() {
        return mValue;
    }
}
