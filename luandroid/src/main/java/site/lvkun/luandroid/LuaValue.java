package site.lvkun.luandroid;

public interface LuaValue {
    enum Type {
        BOOLEAN,
        INTEGER,
        NUMBER,
        STRING,
        TABLE,
    }

    Type getType();
}
