#include "cl_application.h"

cl_application::cl_application(cl_application* p_head_object, std::string s_object_name) : cl_base(p_head_object)
{
}

void cl_application::bild_tree_objects()
{
	int id;
	std::string head, sub;

	std::cin >> head;
	change_object_name(head);
	while (true)
	{
		std::cin >> head;
		if (head == "endtree") break;

		std::cin >> sub >> id;
		if (get_object_by_coordinate(head))
		{
			if (get_object_by_coordinate(head)->get_sub_object_by_name(sub))
			{
				std::cout << head << "     Dubbing the names of subordinate objects" << std::endl;
				continue;
			}

			if (id == 2) new cl_base_2(get_object_by_coordinate(head), sub);
			else if (id == 3) new cl_base_3(get_object_by_coordinate(head), sub);
			else if (id == 4) new cl_base_4(get_object_by_coordinate(head), sub);
			else if (id == 5) new cl_base_5(get_object_by_coordinate(head), sub);
			else if (id == 6) new cl_base_6(get_object_by_coordinate(head), sub);
		}
		else
		{
			change_object_name(get_object_name() + "_" + head + "_broken");
			return;
		}
	}

	cl_base* from = this, * to = nullptr;
	std::vector<cl_object_signal> signals = { SIGNALFN(cl_base_2::get_signal), SIGNALFN(cl_base_3::get_signal), SIGNALFN(cl_base_4::get_signal), SIGNALFN(cl_base_5::get_signal), SIGNALFN(cl_base_6::get_signal) };
	std::vector<cl_object_handler> handlers = { HANDLERFN(cl_base_2::get_handler), HANDLERFN(cl_base_3::get_handler), HANDLERFN(cl_base_4::get_handler), HANDLERFN(cl_base_5::get_handler), HANDLERFN(cl_base_6::get_handler) };
	
	std::getline(std::cin, head, '\n');
	while (true)
	{
		std::getline(std::cin, head, '\n');
		if (head == "end_of_connections") break;
		else
		{
			from = get_object_by_coordinate(head.substr(0, head.find(' ')));
			to = get_object_by_coordinate(head.substr(head.find(' ') + 1));

			if (from->i_object_class < 2) continue;
			from->setup_object_connection(signals.at(from->i_object_class - 2), to, handlers.at(from->i_object_class - 2));
		}
	}
}

int cl_application::exec_app()
{
	if (get_object_name().find("_broken") != std::string::npos)
	{
		std::string origin_object_name = get_object_name().substr(0, get_object_name().find_last_of("_broken"));
		std::string error_coordinate = origin_object_name.substr(origin_object_name.find_last_of('_') + 1);
		origin_object_name = origin_object_name.substr(0, origin_object_name.find_last_of('_'));

		change_object_name(origin_object_name);
		std::cout << "Object tree";
		show_object_tree();
		std::cout << std::endl << "The head object " << error_coordinate << " is not found";
		return 1;
	}
	
	std::string command;
	std::vector<std::string> commands, args;
	
	while (true)
	{
		std::getline(std::cin, command, '\n');
		commands.push_back(command);
		
		if (command == "END") break;
	}

	std::cout << "Object tree";
	show_object_tree();

	cl_base* from = this, * to = nullptr;
	std::vector<cl_object_signal> signals = { SIGNALFN(cl_base_2::get_signal), SIGNALFN(cl_base_3::get_signal), SIGNALFN(cl_base_4::get_signal), SIGNALFN(cl_base_5::get_signal), SIGNALFN(cl_base_6::get_signal) };
	std::vector<cl_object_handler> handlers = { HANDLERFN(cl_base_2::get_handler), HANDLERFN(cl_base_3::get_handler), HANDLERFN(cl_base_4::get_handler), HANDLERFN(cl_base_5::get_handler), HANDLERFN(cl_base_6::get_handler) };
	for (std::string use : commands)
	{
		if (use == "END") break;
		args.clear();
		while (use.find(' ') != std::string::npos)
		{
			args.push_back(use.substr(0, use.find(' ')));
			use = use.substr(use.find(' ') + 1);
		}
		args.push_back(use);
		if (args.size() < 3) continue;
		
		from = get_object_by_coordinate(args.at(1));
		to = get_object_by_coordinate(args.at(2));
		
		if (!from)
		{
			std::cout << "Object " << args.at(1) << " not found";
			continue;
		}

		if (args.at(0) == "SET_CONDITION")
		{
			from->change_object_state(atoi(args.at(2).c_str()));
			continue;
		}
		if (from->i_object_class < 2) continue;
		
		if (args.at(0) == "EMIT") from->send_object_signal(signals.at(from->i_object_class - 2), args.at(4));
		else
		{
			if (to)
			{
				if (args.at(0) == "SET_CONNECT") from->setup_object_connection(signals.at(from->i_object_class - 2), to, handlers.at(from->i_object_class - 2));
				else if (args.at(0) == "DELETE_CONNECT") from->delete_object_connection(signals.at(from->i_object_class - 2), to, handlers.at(from->i_object_class - 2));
			}
			else std::cout << "Handler object " << args.at(2) << " not found";
		}
	}

	return 0;
}