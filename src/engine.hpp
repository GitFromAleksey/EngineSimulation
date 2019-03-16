/*
 * engine.cpp
 *
 *  Created on: 13 мар. 2019 г.
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
	    // значения по умолчанию
	    this->I = CONST_I; // момент инерции, кг*м2
	    this->Tenv = CONST_T_ENV; // темп. среды (задаётся с консоли)
	    this->Toverheat = CONST_T_OVERHEAT; // температура перегрева, градусы цельсия
	    this->Hm = CONST_H_M; // коэф.скорости нагрева от крутящего момента, [град/(H*m*сек)]
	    this->Hv = CONST_H_V; // коэф. скорости нарева от частоты вращения [C*сек/рад2]
	    this->C = CONST_C; // коэф. зав. охлаждения от температуры двигателя и среды [1/сек]
	    this->delta_t = CONST_DELTA_T; // дискретность приращения времени выполнения

	    Init();
	}

    ~Engine(){}

    virtual void Init()
    {
        time = 0;

        Tengine = Tenv; // температура двигателя, град цельсия
        Vheat = 0; // скорость нагрева двигателя [град/сек]
        Vc = 0; // скорость охлаждения двигателя [град/сек]
        M = 0; // текущий момент двигателя, Н*м
        V = 0; // обороты двигателя, рад/сек
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
    	// расчёт скорости вращения для следующего момента времени
    	Calc_V();
    	// получение текущего момента по текущей скорости
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
    // значения по умолчанию
    const float CONST_I = 10; // момент инерции, кг*м2
    const float CONST_T_ENV = 25; // температура среды
    const float CONST_T_OVERHEAT = 112; // температура перегрева, градусы цельсия
    const float CONST_H_M = 0.01; // коэф.скорости нагрева от крутящего момента, [град/(H*m*сек)]
    const float CONST_H_V = 0.0001; // коэф. скорости нарева от частоты вращения [C*сек/рад2]
    const float CONST_C = 0.1; // коэф. зав. охлаждения от температуры двигателя и среды [1/сек]
    const float CONST_DELTA_T = 0.1; // дискретность приращения времени выполнения

    // задаваемые параметры
    float I; // момент инерции, кг*м2
    float Tenv; // темп. среды (задаётся с консоли)
    float Toverheat; // температура перегрева, градусы цельсия
    float Hm; // коэф.скорости нагрева от крутящего момента, [град/(H*m*сек)]
    float Hv; // коэф. скорости нарева от частоты вращения [C*сек/рад2]
    float C; // коэф. зав. охлаждения от температуры двигателя и среды [1/сек]
    float delta_t; // дискретность приращения времени выполнения

    std::vector<float> vM; // зависимость момента от скорости вращения
    std::vector<float> vV; // зависимость момента от скорости вращения

    // вычисляемые параметры
    float Tengine; // температура двигателя, град цельсия
    float Vheat; // скорость нагрева двигателя [град/сек]
    float Vc; // скорость охлаждения двигателя [град/сек]
    float M; // текущий момент двигателя, Н*м
    float V; // обороты двигателя, рад/сек

    float time; // текущее время симуляции



    // расчёт момента от скорости по графику
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

    // расчёт скорости вращения
    void Calc_V()
    {
    	// из формулы a = M/V выведена V = M*delta_t/cI
    	// для зависимости скорости вращения от времени
    	// так как нам нужно рассчитать время нагрева
    	V = V + M*CONST_DELTA_T/CONST_I;
    }

    void Calc_Tengine()
    {
    	Tengine = Tengine + (Vheat+Vc) * CONST_DELTA_T;
    	Vheat = M * CONST_H_M + V*V*CONST_H_V;
    	Vc = CONST_C * (Tenv - Tengine);
    }
};


