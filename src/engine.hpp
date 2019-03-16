/*
 * engine.cpp
 *
 *  Created on: 13 ���. 2019 �.
 *      Author: user1
 */

#include <iostream>
#include <vector>
#include "EngineBase.hpp"


class Engine:public EngineBase
{
public:

	Engine()
	{
	    // �������� �� ���������
	    this->I = CONST_I; // ������ �������, ��*�2
	    this->Tenv = CONST_T_ENV; // ����. ����� (������� � �������)
	    this->Toverheat = CONST_T_OVERHEAT; // ����������� ���������, ������� �������
	    this->Hm = CONST_H_M; // ����.�������� ������� �� ��������� �������, [����/(H*m*���)]
	    this->Hv = CONST_H_V; // ����. �������� ������ �� ������� �������� [C*���/���2]
	    this->C = CONST_C; // ����. ���. ���������� �� ����������� ��������� � ����� [1/���]
	    this->delta_t = CONST_DELTA_T; // ������������ ���������� ������� ����������

	    Init();
	}

    ~Engine(){}

    virtual void Init()
    {
        time = 0;

        Tengine = Tenv; // ����������� ���������, ���� �������
        Vheat = 0; // �������� ������� ��������� [����/���]
        Vc = 0; // �������� ���������� ��������� [����/���]
        M = 0; // ������� ������ ���������, �*�
        V = 0; // ������� ���������, ���/���
    }

    void set_M_V_Depend(float *arr_M, float *arr_V, std::size_t arr_size)
    {
    	std::size_t i = 0;

    	for(i = 0; i < arr_size; i++)
    	{
    		vM.push_back(arr_M[i]);
    		vV.push_back(arr_V[i]);
    	}
    }

    virtual void setTenv(float &Tenv)
    {
    	this->Tenv = Tenv;
    }

    virtual float getWorkTime()const
    {
    	return time;
    }

    virtual float getTengine()const
    {
    	return Tengine;
    }

    virtual float getToverheat()const
    {
    	return Toverheat;
    }

    virtual void run()
    {
    	// ������ �������� �������� ��� ���������� ������� �������
    	Calc_V();
    	// ��������� �������� ������� �� ������� ��������
    	Calc_M();

    	Calc_Tengine();

    	time = time + delta_t;

    	std::cout << "time = " << time << std::endl;
    	std::cout << "M = " << M << std::endl;
    	std::cout << "V = " << V << std::endl;
    	std::cout << "Tengine = " << Tengine << std::endl;
    	std::cout << "Vheat = " << Vheat << std::endl;
    	std::cout << "Vc = " << Vc << std::endl;
    }

    void PrintMV()
    {
    	for(size_t i = 0; i < vM.size(); i++)
    	{
    		std::cout << "vM = " << vM[i] << "; vV = " << vV[i] << std::endl;
    	}
    }


private:
    // �������� �� ���������
    const float CONST_I = 10; // ������ �������, ��*�2
    const float CONST_T_ENV = 25; // ����������� �����
    const float CONST_T_OVERHEAT = 112; // ����������� ���������, ������� �������
    const float CONST_H_M = 0.01; // ����.�������� ������� �� ��������� �������, [����/(H*m*���)]
    const float CONST_H_V = 0.0001; // ����. �������� ������ �� ������� �������� [C*���/���2]
    const float CONST_C = 0.1; // ����. ���. ���������� �� ����������� ��������� � ����� [1/���]
    const float CONST_DELTA_T = 0.1; // ������������ ���������� ������� ����������

    // ���������� ���������
    float I; // ������ �������, ��*�2
    float Tenv; // ����. ����� (������� � �������)
    float Toverheat; // ����������� ���������, ������� �������
    float Hm; // ����.�������� ������� �� ��������� �������, [����/(H*m*���)]
    float Hv; // ����. �������� ������ �� ������� �������� [C*���/���2]
    float C; // ����. ���. ���������� �� ����������� ��������� � ����� [1/���]
    float delta_t; // ������������ ���������� ������� ����������

    std::vector<float> vM; // ����������� ������� �� �������� ��������
    std::vector<float> vV; // ����������� ������� �� �������� ��������

    // ����������� ���������
    float Tengine; // ����������� ���������, ���� �������
    float Vheat; // �������� ������� ��������� [����/���]
    float Vc; // �������� ���������� ��������� [����/���]
    float M; // ������� ������ ���������, �*�
    float V; // ������� ���������, ���/���

    float time; // ������� ����� ���������



    // ������ ������� �� �������� �� �������
    bool Calc_M()
    {
    	for(size_t i = 0; i < vV.size(); i++)
    	{
    		if(V == vV[i])
    		{
    			M = vM[i];
    			return true;
    		}
    		else if(V < vV[i])
    		{
    			float k = (vM[i] - vM[i-1])/(vV[i] - vV[i-1]);
    			float b = vM[i] - k * vV[i];
    			M = k * V + b;
    			return true;
    		}
    	}
    	return false;
    }

    // ������ �������� ��������
    void Calc_V()
    {
    	// �� ������� a = M/V �������� V = M*delta_t/cI
    	// ��� ����������� �������� �������� �� �������
    	// ��� ��� ��� ����� ���������� ����� �������
    	V = V + M*CONST_DELTA_T/CONST_I;
    }

    void Calc_Tengine()
    {
    	Tengine = Tengine + (Vheat+Vc) * CONST_DELTA_T;
    	Vheat = M * CONST_H_M + V*V*CONST_H_V;
    	Vc = CONST_C * (Tenv - Tengine);
    }
};


