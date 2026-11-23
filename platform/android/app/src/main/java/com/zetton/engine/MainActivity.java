package com.zetton.engine;

import android.app.Activity;
import android.os.Bundle;
import android.opengl.GLSurfaceView;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("zetton_engine");
    }

    private GLSurfaceView glView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        glView = new GLSurfaceView(this);
        glView.setEGLContextClientVersion(3);
        glView.setRenderer(new ZettonRenderer());

        setContentView(glView);
    }

    @Override
    protected void onPause() {
        super.onPause();
        glView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        glView.onResume();
    }

    private static class ZettonRenderer
            implements GLSurfaceView.Renderer {

        @Override
        public void onSurfaceCreated(
                javax.microedition.khronos.opengles.GL10 gl,
                javax.microedition.khronos.egl.EGLConfig config) {
            nativeInitialize();
        }

        @Override
        public void onSurfaceChanged(
                javax.microedition.khronos.opengles.GL10 gl,
                int width,
                int height) {
            nativeResize(width, height);
        }

        @Override
        public void onDrawFrame(
                javax.microedition.khronos.opengles.GL10 gl) {
            nativeRender();
        }
    }

    private static native void nativeInitialize();
    private static native void nativeResize(int width, int height);
    private static native void nativeRender();
}
