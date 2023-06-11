#ifndef CL_BASE_H
#define CL_BASE_H

#include "main.h"

class cl_base
{
public:
	cl_base(cl_base* = nullptr, std::string = "Base_object");
	
	cl_base* get_head_object();
	cl_base* get_object_by_name(std::string);
	cl_base* get_sub_object_by_name(std::string);
	cl_base* get_branch_object_by_name(std::string);
	cl_base* get_object_by_coordinate(std::string = "/");

	std::string get_object_name();
	std::string get_absolute_coordinate();
	bool change_object_name(std::string);
	void change_object_state(int);
	bool change_head_object(cl_base*);
	void delete_sub_object_by_name(std::string);

	void show_object_tree(int = 0);
	void show_traversal_tree(int = 0);

	typedef void (cl_base::*cl_object_signal)(std::string&);
	typedef void (cl_base::*cl_object_handler)(std::string);

	struct cl_object_connection
	{
		cl_object_signal p_signal;
		cl_base* p_target;
		cl_object_handler p_handler;
	};

	void setup_object_connection(cl_object_signal, cl_base*, cl_object_handler);
	void delete_object_connection(cl_object_signal, cl_base*, cl_object_handler);
	void send_object_signal(cl_object_signal, std::string&);

	int i_object_class = 1;
private:
	int i_object_state = 1;
	std::string s_object_name;
	cl_base* p_head_object = nullptr;
	std::vector<cl_base*> subordinate_objects;
	std::vector<cl_object_connection*> object_connections;
};

#define SIGNALFN(signal_fn) (cl_object_signal)(&signal_fn)
#define HANDLERFN(handler_fn) (cl_object_handler)(&handler_fn)

#endif