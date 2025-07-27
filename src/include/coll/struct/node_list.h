#ifndef __NODE_LIST_H__
#define __NODE_LIST_H__

#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "node/node.h"
#include "platform.h"
#include "struct/comm_pair.h"
#include "struct/type.h"

namespace hlop {
/**
 * @brief class node list.
 * This class is used to represent a list of nodes in a system.
 * It provides methods to retrieve information about the nodes,
 * such as the number of cores, the number of nodes, and the network level between nodes.
 * It also allows for the retrieval of node names by process ranks
 * and provides functionality to check if a node is part of the list.
 * @throws hlop_err, if the node list is not valid or if the number of processes per node exceeds the maximum allowed.
 */
class node_list {
public:
	using node_list_t = node_list;

private:
	using rank_util_handler = std::function<int(int, hlop::rank_arrangement_t, const node_list_t &)>;

public:
	static const rank_util_handler get_node_id;
	static const rank_util_handler get_local_rank;
	static const rank_util_handler get_core_id;

public:
	/**
	 * @brief default constructor of node_list.
	 * @note This constructor is not accessible directly and should not be used.
	 * It is provided to prevent the creation of an empty node_list.
	 */
	node_list() = delete;
	/**
	 * @fixme
	 * @brief constructor of node_list with ranks and rule.
	 * @param pf platform, the platform type of this node list.
	 * @param node_list_str string, a string representation of the node list.
	 * @param ppn int, the number of processes per node.
	 * @param ranks vector<int>, a vector of process ranks in this node list.
	 * @param rule rank_arrangement, the rank arrangement rule to use.
	 * @throws hlop_err, if the ranks are not in the range [0, ppn * nlist.size() - 1].
	 */
	node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn, hlop::arrangement_t rule);
	/**
	 * @fixme
	 * @brief constructor of node_list with ranks.
	 * @param pf platform, the platform type of this node list.
	 * @param node_list_str string, a string representation of the node list.
	 * @param ppn int, the number of processes per node.
	 * @param rule rank_arrangement, the rank arrangement rule to use.
	 * @param ranks vector<int>, a vector of process ranks bind to core in this node list.
	 * @throws hlop_err, if the ranks are not in the range [0, ppn * nlist.size() - 1].
	 */
	node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn, hlop::arrangement_t rule, std::vector<int> ranks);

	~node_list() = default;

private:
	/**
	 * @brief constructor of node_list.
	 * @param pf platform, the platform type of this node list.
	 * @param node_list_str string, a string representation of the node list.
	 * @param ppn int, the number of processes per node.
	 * @throws hlop_err, if the ranks are not in the range [0, ppn * nlist.size() - 1].
	 * @note This can not access directly.
	 */
	node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn);

public:
	friend std::ostream &operator<<(std::ostream &os, const node_list_t &nl);

public:
	/**
	 * @brief get platform type this node list belong to.
	 * @return platform, the platform type of this node list.
	 */
	const hlop::platform_t get_platform() const;
	/**
	 * @brief get the number of process per node.
	 * @return int, the number of processes per node.
	 */
	const int get_ppn() const;
	/**
	 * @brief get the number of node in this list.
	 * @return int, the number of nodes in this list.
	 */
	const int get_node_num() const;
	/**
	 * @brief get node list.
	 * @return vector<string>, a vector of node names in this list.
	 */
	const std::vector<hlop::const_node_ptr> &get_node_list() const;
	/**
	 * @brief get the number of ranks in this node list.
	 * @return int, the number of ranks in this node list.
	 */
	const int get_rank_num() const;
	/**
	 * @brief get process ranks in this node list.
	 * @return unordered_map<int, node_cptr>, a map of process ranks with node in this node list.
	 */
	const std::unordered_map<int, hlop::const_node_ptr> &get_ranks() const;
	/**
	 * @brief get level between rank1 and rank2.
	 * @param rank1 int, rank bind to node1, core1.
	 * @param rank2 int, rank bind to node2, core2.
	 * @return int, the level between core1 and core2.
	 * @throws hlop_err, if rank1 or rank2 is not in this list, or the range greater than max core level.
	 */
	const int get_level(int rank1, int rank2) const;
	/**
	 * @brief get core level between node in this communication pair.
	 * @param cp comm_pair, communication pair.
	 * @return int, the core level between cores in the communication pair.
	 */
	const int get_level(const hlop::comm_pair_t &cp) const;
	/**
	 * @brief get node name by process rank.
	 * @param rank int, process rank.
	 * @return node, the node corresponding to the process rank.
	 */
	const hlop::node_t &get_node_by_rank(int rank) const;
	/**
	 * @brief get node pointer by process rank.
	 * @param rank int, process rank.
	 * @return const_node_ptr, a pointer to the node corresponding to the process rank.
	 */
	hlop::const_node_ptr_t get_node_ptr_by_rank(int rank) const;
	/**
	 * @brief get the first k node in this node list.
	 * @param k int, the number of top nodes to retrieve.
	 * @return vector<const_node_ptr>, a vector of the top k node.
	 * @throws hlop_err, if k is not in range [1, node_num].
	 */
	const std::vector<hlop::const_node_ptr> get_top_k_nodes(int k) const;

private:
	std::vector<hlop::const_node_ptr> nlist;
	std::unordered_map<int, hlop::const_node_ptr> rmap;
	int nproc_per_node;
	hlop::platform_t platform;
};
typedef node_list::node_list_t node_list_t;

std::ostream &operator<<(std::ostream &os, const node_list_t &nl);
} // namespace hlop

#endif // __NODE_LIST_H__