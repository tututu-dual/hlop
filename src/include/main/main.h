#ifndef __MAIN_H__
#define __MAIN_H__

#include <vector>

#include "structs/node_list.h"
#include "structs/types.h"

namespace hlop {
struct exec_args {
	hlop::op_type_t op;
	hlop::algo_type_t algo;
	hlop::node_list_t nl;
	std::vector<int> msz;
};
typedef exec_args exec_args_t;
hlop::exec_args_t parse_argument(int *argc, char ***argv);

double execute_with_arg(hlop::op_type_t op, hlop::algo_type_t algo, hlop::node_list_t nl, int msg_size);
std::vector<double> execute_with_args(hlop::op_type_t op, hlop::algo_type_t algo, hlop::node_list_t nl,
                                      std::vector<int> msg_sizes);
} // namespace hlop

#endif // __MAIN_H__