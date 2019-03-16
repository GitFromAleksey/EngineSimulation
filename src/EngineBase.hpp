/*
 * EngineBase.hpp
 *
 *  Created on: 17 мар. 2019 г.
 *      Author: AMD
 */

#ifndef SRC_ENGINEBASE_HPP_
#define SRC_ENGINEBASE_HPP_

class EngineBase
{
public:
	EngineBase(){}
	~EngineBase(){}

	virtual float getWorkTime()const = 0;
	virtual float getTengine()const = 0;
	virtual float getToverheat()const = 0;

	virtual void setTenv(float &Tenv) = 0;
	virtual void Init() = 0;
	virtual void run() = 0;
};


#endif /* SRC_ENGINEBASE_HPP_ */
