#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>


namespace Util{
	template<typename IN,typename OUT>
	inline bool lexCast(const IN & in, OUT & out){
		try {
			out = boost::lexical_cast<OUT>( in );
		}
		catch( boost::bad_lexical_cast& ) {
			logInfo( "lexCast error for input : " + toString(in) );
			//logInfo( "Exception thrown: [" << e.what() << "] for INPUT[" << in << "]" );
			return false;
		}
		return true;
	}

	template<typename T>
	inline std::string toString(T value){
		std::ostringstream os;
		os << value;
		return os.str();
	}

	inline int strToInt(const std::string & value){
		int i(0);
		lexCast(value, i);
		return i;
	}

}

#endif /* UTIL_H_INCLUDED */