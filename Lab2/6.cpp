//#include <stdio.h>
//#include <string.h>
//#include <assert.h>
//#include <math.h>
//#include <GL/glew.h>
//#include <GL/freeglut.h>
//#include "pipeline.h"
//
//#define WINDOW_WIDTH 1024
//#define WINDOW_HEIGHT 768
//
//// инициализируем переменную VBO для работы с буфером вершин
//GLuint VBO;
//GLuint IBO;
//// указатель для доступа к всемирной матрице
//GLuint gWVPLocation;
//
////определяем позиции вершин (вершинный шейдер)
//static const char* pVS = "                                                          \n\
//#version 330                                                                        \n\
//                                                                                    \n\
//layout (location = 0) in vec3 Position;                                             \n\
//                                                                                    \n\
//uniform mat4 gWVP;                                                                  \n\
//                                                                                    \n\
//out vec4 Color;                                                                     \n\
//                                                                                    \n\
//void main()                                                                         \n\
//{                                                                                   \n\
//    gl_Position = gWVP * vec4(Position, 1.5);                                       \n\
//    Color = vec4(clamp(Position, 0.0, 1.0), 1.0);                                   \n\
//}";
//
////определяем цвет фрагментов (фрагментный шейдер)
//static const char* pFS = "                                                          \n\
//#version 330                                                                        \n\
//                                                                                    \n\
//in vec4 Color;                                                                      \n\
//                                                                                    \n\
//out vec4 FragColor;                                                                 \n\
//                                                                                    \n\
//void main()                                                                         \n\
//{                                                                                   \n\
//    FragColor = Color;                                                              \n\
//}";
//
//// функция для отображения сцены 
//static void RenderSceneCB()
//{
//    // очищаем цветовой буфер
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    static float Scale = 0.0f;
//
//    // скорость вращения
//    Scale += 0.0001f;
//
//    Pipeline p;
//    //поворот треугольника
//    p.Rotate(0.0f, 0.0f, 0.0f);
//    //координаты треугольника
//    p.WorldPos(sin(Scale*50), 0.0f, 3.0f);
//    //мастабирование
//    //p.Scale(cos(Scale), cos(Scale), 0.0f);
//    //координаты камеры
//    Vector3f CameraPos(0.0f, 0.0f, 0.0f);
//    //
//    Vector3f CameraTarget(0.0f, 0.0f, 1.0f);
//    //поворот камеры
//    Vector3f CameraUp(0.0f, 1.0f, 0.0f);
//    p.SetCamera(CameraPos, CameraTarget, CameraUp);
//    p.SetPerspectiveProj(100.0f, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f, 100.0f);
//
//    glUniformMatrix4fv(gWVPLocation, 1, GL_TRUE, (const GLfloat*)p.GetTrans());
//
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//
//    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
//
//    glDisableVertexAttribArray(0);
//
//    // выводим на экран
//    glutSwapBuffers();
//}
//
//// функция для инициализации функций GLUT
//static void InitializeGlutCallbacks()
//{
//    glutDisplayFunc(RenderSceneCB);
//    glutIdleFunc(RenderSceneCB);
//}
//
//// функция для создания буфера вершин
//static void CreateVertexBuffer()
//{
//    // создаем массив вершин
//    Vector3f Vertices[4];
//    Vertices[0] = Vector3f(-1.0f, -1.0f, 0.5773f);
//    Vertices[1] = Vector3f(0.0f, -1.0f, -1.15475);
//    Vertices[2] = Vector3f(1.0f, -1.0f, 0.5773f);
//    Vertices[3] = Vector3f(0.0f, 1.0f, 0.0f);
//
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
//}
//
//// функция для создания массива индексов
//static void CreateIndexBuffer()
//{
//    unsigned int Indices[] = { 0, 3, 1,
//                               1, 3, 2,
//                               2, 3, 0,
//                               0, 2, 1 };
//
//    glGenBuffers(1, &IBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);
//}
//
//// функция для добавления шейдера к программ
//static void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
//{
//    GLuint ShaderObj = glCreateShader(ShaderType);
//
//    if (ShaderObj == 0) {
//        fprintf(stderr, "Error creating shader type %d\n", ShaderType);
//        exit(0);
//    }
//
//    const GLchar* p[1];
//    p[0] = pShaderText;
//    GLint Lengths[1];
//    Lengths[0] = strlen(pShaderText);
//    glShaderSource(ShaderObj, 1, p, Lengths);
//    glCompileShader(ShaderObj);
//    GLint success;
//    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
//    if (!success) {
//        GLchar InfoLog[1024];
//        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
//        fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
//        exit(1);
//    }
//
//    glAttachShader(ShaderProgram, ShaderObj);
//}
//
////функция для компиляции шейдеров
//static void CompileShaders()
//{
//    GLuint ShaderProgram = glCreateProgram();
//
//    if (ShaderProgram == 0) {
//        fprintf(stderr, "Error creating shader program\n");
//        exit(1);
//    }
//
//    AddShader(ShaderProgram, pVS, GL_VERTEX_SHADER);
//    AddShader(ShaderProgram, pFS, GL_FRAGMENT_SHADER);
//
//    GLint Success = 0;
//    GLchar ErrorLog[1024] = { 0 };
//
//    glLinkProgram(ShaderProgram);
//    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);
//    if (Success == 0) {
//        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//        fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
//        exit(1);
//    }
//
//    glValidateProgram(ShaderProgram);
//    glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
//    if (!Success) {
//        glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
//        fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
//        exit(1);
//    }
//
//    glUseProgram(ShaderProgram);
//
//    gWVPLocation = glGetUniformLocation(ShaderProgram, "gWVP");
//    assert(gWVPLocation != 0xFFFFFFFF);
//}
//
//int main(int argc, char** argv)
//{
//    // инициализируем GLUT
//    glutInit(&argc, argv);
//
//    // указываем параметры дисплея
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("Window1");
//
//    InitializeGlutCallbacks();
//
//    // инициализируем GLEW
//    // Must be done after glut is initialized!
//    GLenum res = glewInit();
//    if (res != GLEW_OK) {
//        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
//        return 1;
//    }
//
//    // устанавливаем цвет фона
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//    CreateVertexBuffer();
//    CreateIndexBuffer();
//
//    CompileShaders();
//
//    // запускаем главный цикл GLUT
//    glutMainLoop();
//
//    return 0;
//}
