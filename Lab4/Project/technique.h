#pragma once
// �����, ������������ �� �������� � ���������� ��������
#include <GL/glew.h>
#include <list>

#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF

class Technique
{
public:
    // ������ ������ ��� �������� ��������
    Technique();
    ~Technique(); // ����������
    virtual bool Init(); // �������� �������, false, ���� ��� ���� ��� �������
    void Enable(); // ��������� ��������� �������� ��� ���������

protected:
    // ���������� ���� ����� ��� ���������� �������� � ���������.
    // ����� ����������� - �������� finalize()
    bool AddShader(GLenum ShaderType, const char* pShaderText);
    // ����� ���������� ���� �������� � ��������� �������� ��� �������
    // ��� �������� � �������� ��������� �� ������
    bool Finalize();
    // ����������� ������� uniform-����������
    GLint GetUniformLocation(const char* pUniformName);

private:
    GLuint m_shaderProg; // ��������� �������
    typedef std::list<GLuint> ShaderObjList; // ������� typedef
    ShaderObjList m_shaderObjList; // ������ �������� �������
};
