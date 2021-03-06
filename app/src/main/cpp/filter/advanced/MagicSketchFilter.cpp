#include "MagicSketchFilter.h"
#include "src/main/cpp/utils/OpenglUtils.h"

#define LOG_TAG "MagicSketchFilter"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif

#define GET_ARRAY_LEN(array,len){len = (sizeof(array) / sizeof(array[0]));}

/**
 * cangwang 2018.12.1
 */
MagicSketchFilter::MagicSketchFilter(){

}

MagicSketchFilter::MagicSketchFilter(AAssetManager *assetManager)
    : GPUImageFilter(assetManager,readShaderFromAsset(assetManager,"default_vertex.glsl"), readShaderFromAsset(assetManager,"sketch.glsl")){
    GET_ARRAY_LEN(inputTextureHandles,len);
}

MagicSketchFilter::~MagicSketchFilter() {

}

void MagicSketchFilter::onDestroy() {
    glDeleteTextures(len,inputTextureHandles);
    *inputTextureHandles={0};
}

void MagicSketchFilter::onDrawArraysPre() {

}

void MagicSketchFilter::onDrawArraysAfter() {

}


void MagicSketchFilter::onInit() {
    GPUImageFilter::onInit();
    mGLStrengthLocation = glGetUniformLocation(mGLProgId,"strength");
    mSingleStepOffsetLocation = glGetUniformLocation(mGLProgId,"singleStepOffset");
}

void MagicSketchFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    glUniform1f(mGLStrengthLocation, 0.5f);
}

void MagicSketchFilter::onInputSizeChanged(const int width, const int height) {
    float size[]={1.0f/width,1.0f/height};
    glUniform1f(mSingleStepOffsetLocation, *size);
}