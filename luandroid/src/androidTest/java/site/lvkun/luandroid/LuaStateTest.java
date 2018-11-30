package site.lvkun.luandroid;

import android.support.test.runner.AndroidJUnit4;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;

@RunWith(AndroidJUnit4.class)
public class LuaStateTest {
    LuaState mState;

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
        mState.getGlobal("i");
    }
}