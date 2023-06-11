#ifndef CL_BASE_6_H
#define CL_BASE_6_H

#include "cl_base_5.h"

class cl_base_6 : public cl_base
{
public:
	cl_base_6(cl_base*, std::string);

	void get_signal(std::string&);
	void get_handler(std::string);
};

#endif