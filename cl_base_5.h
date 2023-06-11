#ifndef CL_BASE_5_H
#define CL_BASE_5_H

#include "cl_base_4.h"

class cl_base_5 : public cl_base
{
public:
	cl_base_5(cl_base*, std::string);

	void get_signal(std::string&);
	void get_handler(std::string);
};

#endif