#pragma once
// ���������������� ���� ������� ��������� ������, ������������ � glut-��������, � ���� �����
class ICallbacks // �����-���������
{
public:
    // ������� ��� ��������� ������, �������������� ������� �������� �� ����������
    // ��������� �������� ������� � ���������� ���� � ������ ������� �������
    virtual void SpecialKeyboardCB(int Key, int x, int y) = 0;
    // ��� ���������� ���������
    virtual void KeyboardCB(unsigned char Key, int x, int y) = 0;
    // ��� ������������ ����
    virtual void PassiveMouseCB(int x, int y) = 0;
    // ������ �����
    virtual void RenderSceneCB() = 0;
    // ������ �������, ������� ������ ����� ������� - RenderSceneCB
    virtual void IdleCB() = 0;
};