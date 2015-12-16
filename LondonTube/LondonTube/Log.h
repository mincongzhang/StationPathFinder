#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <string>
#include <iostream>

namespace Log{
	template <typename T>
	inline void logInfo(T out){
		std::cout<<out<<std::endl;
	};

}

#endif /* LOG_H_INCLUDED */