package ru.itis.firstnativeproject

import android.app.Activity
import android.os.Bundle

class DemoActivity : Activity() {
    private lateinit var mGLView: DemoGLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        mGLView = DemoGLSurfaceView(this)
        setContentView(mGLView)
    }

    override fun onPause() {
        super.onPause()
        mGLView.onPause()
    }

    override fun onResume() {
        super.onResume()
        mGLView.onResume()
    }

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }
}