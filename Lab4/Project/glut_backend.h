#pragma once
// ������������� � ��������� glut
#include "callbacks.h"

// ������������� glut
void GLUTBackendInit(int argc, char** argv);

// �������� ����
bool GLUTBackendCreateWindow(unsigned int Width, unsigned int Height, unsigned int bpp, bool isFullScreen, const char* pTitle);

// ������ �������� ������� glut
void GLUTBackendRun(ICallbacks* pCallbacks);