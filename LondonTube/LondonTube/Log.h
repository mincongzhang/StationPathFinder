#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#include <string>
#include <iostream>
#include <fstream>
#include "boost/filesystem.hpp"

namespace Log{
	template <typename T>
	inline void logInfo(T out){
		std::cout<<out<<std::endl;

		std::string filename("log.txt");
		std::ofstream myfile;
		myfile.open (filename.c_str(),std::ios_base::app);
		myfile << out << "\n";
		myfile.close();
	};

}

#endif /* LOG_H_INCLUDED */