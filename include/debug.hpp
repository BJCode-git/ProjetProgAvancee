#ifndef DEBUG_HPP
#define DEBUG_HPP
	#ifdef DEBUG
	#include <iostream>
	#include <string>  
	#define debug(x) std::cout << x << std::endl << std::flush
	#endif
#endif
