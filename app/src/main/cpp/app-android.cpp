//
// Created by SultanbekovIR on 09.09.2020.
//
#include <jni.h>
#include <android/log.h>
#include <ctime>
#include <cassert>

#include "importgl.h"
#include "app.h"
#include "shapes.h"

int gAppAlive = 1;

static int sWindowWidth = 320;
static int sWindowHeight = 480;
static int sDemoStopped = 0;
static long sTimeStopped = 0;
static long sTimeOffset = 0;
static int sTimeOffsetInit;

void _pause();
void _resume();

static long _getTime() {
    struct timeval now{};

    gettimeofday(&now, nullptr);

    return (long)(now.tv_sec * 1000 + now.tv_usec / 1000);
}

extern "C"
JNIEXPORT void JNICALL
Java_ru_itis_firstnativeproject_DemoGLSurfaceView_nativeTogglePauseResume(JNIEnv *env, jobject /* this */) {
    sDemoStopped = !sDemoStopped;
    if (sDemoStopped)
        _pause();
    else
        _resume();
}

void _resume() {
    sDemoStopped = 0;
    sTimeOffset -= _getTime() - sTimeStopped;
}

void _pause() {
    sDemoStopped = 1;
    sTimeStopped = _getTime();
}

extern "C"
JNIEXPORT void JNICALL
Java_ru_itis_firstnativeproject_DemoGLSurfaceView_nativeResume(JNIEnv *env, jobject /* this */) {
    _resume();
}

extern "C"
JNIEXPORT void JNICALL
Java_ru_itis_firstnativeproject_DemoGLSurfaceView_nativePause(JNIEnv *env, jobject /* this */) {
    _pause();
}

extern "C"
JNIEXPORT void JNICALL
Java_ru_itis_firstnativeproject_DemoRenderer_nativeInit(JNIEnv *env, jobject /* this */) {
    importGLInit();
    appInit();
    gAppAlive = 1;
}

extern "C"
JNIEXPORT void JNICALL
Java_ru_itis_firstnativeproject_DemoRenderer_nativeResize(JNIEnv *env, jobject /* this */, jint width, jint height) {
    sWindowWidth = width;
    sWindowHeight = height;
    __android_log_print(ANDROID_LOG_INFO, "DEMO", "resize w=%d h=%d", width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_ru_itis_firstnativeproject_DemoRenderer_nativeRender(JNIEnv *env, jobject /* this */) {
    long currentTime;

    if (sDemoStopped) {
        currentTime = sTimeStopped + sTimeOffset;
    } else {
        currentTime = _getTime() + sTimeOffset;

        if (sTimeOffsetInit == 0) {
            sTimeOffsetInit = 1;
            sTimeOffset = -currentTime;
            currentTime = 0;
        }
    }

    appRender(currentTime, sWindowWidth, sWindowHeight);
}

extern "C"
JNIEXPORT void JNICALL
Java_ru_itis_firstnativeproject_DemoRenderer_nativeDone(JNIEnv *env, jobject /* this */) {
    appDeinit();
    importGLDeinit();
}

