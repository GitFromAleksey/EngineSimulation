/*
 * Stend.hpp
 *
 *  Created on: 17 мар. 2019 г.
 *      Author: AMD
 */

#ifndef SRC_STEND_HPP_
#define SRC_STEND_HPP_

#include <iostream>
#include "EngineBase.hpp"

class Stend
{
public:
	Stend()
	{
		this->pEngine = nullptr;
		workTime = 0;
	}
	~Stend(){}

	void setEngine(EngineBase *engine)
	{
		this->pEngine = engine;
	}

	float getWorkingTime()const
	{
		return workTime;
	}

	bool TestEngine()
	{
		std::size_t timeOut = 10000;

		if(pEngine == nullptr) return false;

		pEngine->Init();

		while(pEngine->getTengine() < pEngine->getToverheat())
		{
			pEngine->run();

			if(timeOut-- == 0) return false;
		}

		workTime = pEngine->getWorkTime();

		return true;
	}

private:

	EngineBase *pEngine;
	float workTime;
};


#endif /* SRC_STEND_HPP_ */
