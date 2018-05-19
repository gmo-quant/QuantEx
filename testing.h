#pragma once

#include <stdexcept>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <cassert>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


/*  Is debugging currently enabled */
bool isDebugEnabled();
/*  Enabled/disable debug */
void setDebugEnabled( bool enabled );

/*  Log an information statement */
#define INFO( A ) { \
    std::cerr << "INFO:\n" << __FILE__ <<":"<<__LINE__ << ":\n" << A <<"\n";\
}

#define TESTCase(s) do{\
    std::cout << BOLDCYAN "Testing Class : " RESET << YELLOW #s RESET << std::endl; \
}while(false)

#define TEST( f ) do {\
    std::cerr<<"Calling "<<#f<<"()\n"; \
    try { \
        f(); \
    } catch (...) { \
        std::cerr<<"\n"; \
        std::cerr<<"******* "<<#f<<"()" << RED " FAILED." RESET << " ********\n";\
        std::cerr<<"\n"; \
        exit(1); \
    }\
    std::cerr<<""<<#f<<"()" << GREEN " passed.\n" RESET; \
    std::cerr<<"\n"; \
} while (false)



// on windows we define debug mode to be when _DEBUG is set
#ifdef _DEBUG
#define DEBUG_MODE 1
#endif

// on unix we define debug mode to be when _GLIBCXX is set
#ifdef _GLIBCXX_DEBUG
#define DEBUG_MODE 1
#endif

#ifdef DEBUG
#define DEBUG_MODE 1
#endif



// our assertion macros behave differently in test mode
#ifndef DEBUG_MODE

#define DEBUG_PRINT( A )
#define ASSERT( c ) do {} while (false)
#define ASSERT_APPROX_EQUAL( x, y, tolerance ) do {} while (false)


#else
/*  Write A to std:cerr so long as debug is enabled */
#define DEBUG_PRINT( A ) { \
    if (isDebugEnabled()) { \
        std::cerr << "DEBUG:\n" << __FILE__ <<":"<<__LINE__ <<":\n"<< A <<"\n";\
    } \
}

#define ASSERT( c ) do { \
    if (!(c)) { \
        std::stringstream testing_ss_; \
		testing_ss_ << "ASSERTION FAILED \n"; \
		testing_ss_ << __FILE__ << ":" << __LINE__ << ":\n" << #c; \
		std::cerr << testing_ss_.str(); \
		throw std::runtime_error(testing_ss_.str()); \
    } \
} while (false)

#define ASSERT_APPROX_EQUAL( x, y, tolerance ) do {\
    if (!(fabs((x)-(y))<=(tolerance))) { \
		std::stringstream testing_ss_; \
		testing_ss_ << RED "ASSERTION FAILED \n"; \
		testing_ss_ << "Expected " << (y) << "\n"; \
		testing_ss_ << "Actual " << (x) << "\n" RESET; \
		testing_ss_ << __FILE__ << ":" << __LINE__ << ":\n"; \
		std::cerr << testing_ss_.str(); \
		throw std::runtime_error(testing_ss_.str()); \
    } \
} while (false)


#endif



