#ifndef __MAIN_H__
#define __MAIN_H__

#include <vector>

#include "structs/node_list.h"
#include "structs/types.h"

namespace hlop {
/**
 * @brief struct exec_args.
 * This struct is used to hold the arguments for the execution of a specific operation.
 * It contains the operation type, algorithm type, node list, and message sizes.
 */
struct exec_args {
	hlop::op_type_t op;
	hlop::algo_type_t algo;
	hlop::node_list_t nl;
	std::vector<int> msz;
};
typedef exec_args exec_args_t;

/**
 * @brief parse command line arguments
 * @param argc int *, pointer to the argument count
 * @param argv char ***, pointer to the argument vector
 * @return exec_args, struct containing parsed arguments
 * @throws hlop_err, if the arguments are invalid
 */
hlop::exec_args_t parse_argument(int *argc, char ***argv);

/**
 * @brief execute the operation with the given arguments
 * @param op op_type, the operation type
 * @param algo algo_type, the algorithm type
 * @param nl node_list, the node list
 * @param msg_size int, the message size
 * @return double, the result of the execution
 * @throws hlop_err, if the operation type is not supported
 */
double execute_with_arg(hlop::op_type_t op, hlop::algo_type_t algo, hlop::node_list_t nl, int msg_size);

/**
 * @brief execute the operation with multiple message sizes
 * @param op op_type, the operation type
 * @param algo algo_type, the algorithm type
 * @param nl node_list, the node list
 * @param msg_sizes vector<int>, the message sizes
 * @return vector<double>, the results of the execution for each message size
 */
std::vector<double> execute_with_args(hlop::op_type_t op, hlop::algo_type_t algo, hlop::node_list_t nl,
                                      std::vector<int> msg_sizes);
} // namespace hlop

#endif // __MAIN_H__