#include "cl_base_4.h"

cl_base_4::cl_base_4(cl_base* p_head_object, std::string s_object_name) : cl_base(p_head_object, s_object_name)
{
	i_object_class = 4;
}

void cl_base_4::get_signal(std::string& s_message)
{
	std::cout << std::endl << "Signal from " << get_absolute_coordinate();
	s_message += " (class: " + std::to_string(i_object_class) + ")";
}

void cl_base_4::get_handler(std::string s_message)
{
	std::cout << std::endl << "Signal to " << get_absolute_coordinate() << " Text: " << s_message;
}