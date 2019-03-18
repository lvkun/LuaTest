package site.lvkun.luandroid;

import android.support.test.runner.AndroidJUnit4;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

import site.lvkun.luandroid.value.LuaInteger;

@RunWith(AndroidJUnit4.class)
public class LuaStateTest {
    private LuaState mState;

    @Before
    public void before() {
        mState = LuaState.newState();
    }

    @After
    public void after() {
        mState.close();
    }

    @Test
    public void newStateTest() throws Exception {
        Assert.assertNotNull(mState);
    }

    @Test
    public void getGlobalTest() throws Exception {
        mState.loadString("i = 0");

        LuaValue value = mState.getGlobal("i");
        Assert.assertEquals(LuaValue.Type.INTEGER, value.getType());
        Assert.assertEquals(0, ((LuaInteger) value).getValue());

        mState.loadString("i = 42");
        value = mState.getGlobal("i");
        Assert.assertEquals(LuaValue.Type.INTEGER, value.getType());
        Assert.assertEquals(42, ((LuaInteger) value).getValue());
    }
}