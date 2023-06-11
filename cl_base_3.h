#ifndef CL_BASE_3_H
#define CL_BASE_3_H

#include "cl_base_2.h"

class cl_base_3 : public cl_base
{
public:
	cl_base_3(cl_base*, std::string);

	void get_signal(std::string&);
	void get_handler(std::string);
};

#endif