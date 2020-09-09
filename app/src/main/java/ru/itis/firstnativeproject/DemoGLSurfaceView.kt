package ru.itis.firstnativeproject

import android.content.Context
import android.opengl.GLSurfaceView
import android.view.MotionEvent

class DemoGLSurfaceView(context: Context) : GLSurfaceView(context) {
    private val mRenderer = DemoRenderer()

    init {
        setRenderer(mRenderer)
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        if (event?.action == MotionEvent.ACTION_DOWN)
            nativeTogglePauseResume()
        return true
    }

    override fun onPause() {
        super.onPause()
        nativePause()
    }

    override fun onResume() {
        super.onResume()
        nativeResume()
    }

    private external fun nativeTogglePauseResume()
    private external fun nativeResume()
    private external fun nativePause()
}