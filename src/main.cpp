#include "Engine.hpp"
#include "Stend.hpp"

int main()
{
    std::size_t arr_size = 6;
	float arr_M[arr_size] = {20,75,100,105,75,0};
    float arr_V[arr_size] = {0,75,150,200,250,300};

    Engine en;

    en.set_M_V_Depend(arr_M, arr_V, arr_size);

    Stend stend;

    stend.setEngine(&en);
    if(stend.TestEngine())
    {
    	std::cout << "Working time: " << stend.getWorkingTime() << std::endl;
    }
    else
    {
    	std::cout << "Working fault" << std::endl;
    }

	return 0;
}
