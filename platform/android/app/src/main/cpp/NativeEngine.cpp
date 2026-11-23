#include <jni.h>
#include <GLES3/gl3.h>
#include <android/log.h>

#define LOG_TAG "ZETTON_ENGINE"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static GLuint shaderProgram = 0;
static GLuint vertexBuffer = 0;
static GLuint vertexArray = 0;

static const char* vertexShaderSource = R"(
#version 300 es

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;

out vec3 vertexColor;

void main() {
    gl_Position = vec4(aPosition, 1.0);
    vertexColor = aColor;
}
)";

static const char* fragmentShaderSource = R"(
#version 300 es

precision mediump float;

in vec3 vertexColor;
out vec4 fragmentColor;

void main() {
    fragmentColor = vec4(vertexColor, 1.0);
}
)";

static GLuint compileShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char log[1024];
        glGetShaderInfoLog(shader, sizeof(log), nullptr, log);
        LOGE("Shader error: %s", log);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static void initializeRenderer() {
    GLuint vertexShader =
        compileShader(GL_VERTEX_SHADER, vertexShaderSource);

    GLuint fragmentShader =
        compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (!vertexShader || !fragmentShader) {
        LOGE("Shader initialization failed");
        return;
    }

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint linked = 0;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    if (!linked) {
        LOGE("Shader program linking failed");
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
        return;
    }

    const GLfloat vertices[] = {
         0.0f,  0.65f, 0.0f,  1.0f, 0.2f, 0.2f,
        -0.65f, -0.55f, 0.0f,  0.2f, 1.0f, 0.3f,
         0.65f, -0.55f, 0.0f,  0.2f, 0.5f, 1.0f
    };

    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(GLfloat), nullptr
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(GLfloat),
        reinterpret_cast<void*>(3 * sizeof(GLfloat))
    );

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    LOGI("ZETTON ENGINE renderer initialized");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zetton_engine_MainActivity_nativeInitialize(
    JNIEnv* env,
    jclass clazz
) {
    (void)env;
    (void)clazz;

    initializeRenderer();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zetton_engine_MainActivity_nativeResize(
    JNIEnv* env,
    jclass clazz,
    jint width,
    jint height
) {
    (void)env;
    (void)clazz;

    glViewport(0, 0, width, height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_zetton_engine_MainActivity_nativeRender(
    JNIEnv* env,
    jclass clazz
) {
    (void)env;
    (void)clazz;

    glClearColor(0.035f, 0.045f, 0.08f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (shaderProgram == 0) {
        return;
    }

    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArray);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
}
