#ifndef CL_BASE_4_H
#define CL_BASE_4_H

#include "cl_base_3.h"

class cl_base_4 : public cl_base
{
public:
	cl_base_4(cl_base*, std::string);

	void get_signal(std::string&);
	void get_handler(std::string);
};

#endif