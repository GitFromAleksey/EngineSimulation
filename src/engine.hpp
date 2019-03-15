/*
 * engine.cpp
 *
 *  Created on: 13 ���. 2019 �.
 *      Author: user1
 */

#include <iostream>
#include <vector>

class Engine
{
public:
    Engine()
    {
        std::cout << "Create engine" << std::endl;

        Tengine = cTengine_begin;
        Tenv = cTengine_begin;

        I = cI;
        t_overheat = ct_overheat;
        Hm = cHm;
        Hn = cHn;
        Hc = cHc;

        a = 0.0;
        V_heat = 0.0;
        Vc = 0.0;
        M = 0;
        C = 0;
    }
    ~Engine(){}

    // ���������� ���������
    float Calc_a()
    {
        return a = M/I;
    }

    // ���������� �������� �������
    float Calc_Vheat()
    {
        return V_heat = M*Hm + N*N*Hn;
    }

    // ���������� �������� ����������
    float Calc_Vc()
    {
        return Vc = C * (Tenv - Tengine);
    }

    void Set_Vector_M_V_Depend(std::vector<float> &m, std::vector<float> &v)
    {
        vM = m;
        vV = v;
    }

private:
    // ��������� �������
    const float cTengine_begin = 25;
    const float cI = 1.0;
    const float ct_overheat = 110;
    const float cHm = 1.0;
    const float cHn = 1.0;
    const float cHc = 1.0;

    // ���������� ���������
    float I; // ������ �������, ��*�2
    float t_overheat; // ����������� ���������, ������� �������
    float Hm; // ����.�������� ������� �� ��������� �������, [����/(H*m*���)]
    float Hn; // ����. �������� ������ �� ������� �������� [C*���/���2]
    float Hc; // ����. �������� ���������� �� ����������� ��������� [1/���]
    std::vector<float> vM; // ����������� ������� �� �������� ��������
    std::vector<float> vV; // ����������� ������� �� �������� ��������

    float C; // ����. ���. ���������� �� ����������� ��������� � �����

    // ����������� ���������
    float Tengine; // ����������� ���������, ���� �������
    float Tenv; // ����������� ����� �����, ���� �������
    float a; // �������� ��������� [�/(��*�)]
    float V_heat; // �������� ������� ��������� [����/���]
    float Vc; // �������� ���������� ��������� [����/���]
    float M; // ������� ������ ���������, �*�
    float N; // ������� ���������, 1/���
};


