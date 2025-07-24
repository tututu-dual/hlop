#ifndef __NODE_LIST_H__
#define __NODE_LIST_H__

#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "comm_pair.h"
#include "platform.h"
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
	/**
	 * @brief default constructor of node_list.
	 * @note This constructor is not accessible directly and should not be used.
	 * It is provided to prevent the creation of an empty node_list.
	 */
	node_list() = delete;
	/**
	 * @brief constructor of node_list with ranks.
	 * @param pf platform, the platform type of this node list.
	 * @param node_list_str string, a string representation of the node list.
	 * @param ppn int, the number of processes per node.
	 * @param ranks vector<int>, a vector of process ranks in this node list.
	 * @throws hlop_err, if the ranks are not in the range [0, ppn * nlist.size() - 1].
	 */
	node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn, std::vector<int> ranks);
	/**
	 * @brief constructor of node_list with ranks and rule.
	 * @param pf platform, the platform type of this node list.
	 * @param node_list_str string, a string representation of the node list.
	 * @param ppn int, the number of processes per node.
	 * @param ranks vector<int>, a vector of process ranks in this node list.
	 * @param rule rank_arrangement, the rank arrangement rule to use.
	 * @throws hlop_err, if the ranks are not in the range [0, ppn * nlist.size() - 1].
	 */
	node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn, hlop::rank_arrangement_t rule);
	~node_list() = default;

public:
	/**
	 * @brief get the number of cores in a node.
	 * @return int, the number of cores in a node.
	 */
	const int get_node_cores() const;
	/**
	 * @brief get the number of numa cores in a node.
	 * @return int, the number of numa cores in a node.
	 */
	const int get_ncore_per_numa() const;
	/**
	 * @brief get the max network level in this system.
	 * @return int, the max network level in this system.
	 */
	const int get_max_network_level() const;
	/**
	 * @brief get the max core level in this system.
	 * @return int, the max core level in this system.
	 */
	const int get_max_core_level() const;
	/**
	 * @brief get the number of node in this list.
	 * @return int, the number of nodes in this list.
	 */
	const int get_node_num() const;
	/**
	 * @brief get node list.
	 * @return vector<string>, a vector of node names in this list.
	 */
	std::vector<std::string_view> get_node_list() const;
	/**
	 * @brief get the number of process per node.
	 * @return int, the number of processes per node.
	 */
	const int get_ppn() const;
	/**
	 * @brief get process ranks in this node list.
	 * @return vector<int>, a vector of process ranks in this node list.
	 */
	const std::unordered_map<int, const std::string &> &get_ranks() const;

	/**
	 * @brief get the number of ranks in this node list.
	 * @return int, the number of ranks in this node list.
	 */
	const int get_rank_num() const;
	/**
	 * @brief get platform type this node list belong to.
	 * @return platform, the platform type of this node list.
	 */
	const hlop::platform_t get_platform() const;
	/**
	 * @brief get core level between core1 and core2.
	 * @param rank1 int, rank bind to core1.
	 * @param rank2 int, rank bind to core2.
	 * @return int, the core level between core1 and core2.
	 * @throws hlop_err, if rank1 or rank2 is not in this list, or the range greater than max core level.
	 */
	const int get_intra_level(int rank1, int rank2) const;
	/**
	 * @brief get core level between node in this communication pair.
	 * @param cp comm_pair, communication pair.
	 * @return int, the core level between cores in the communication pair.
	 */
	const int get_intra_level(const hlop::comm_pair_t &cp) const;
	/**
	 * @brief get net level between node1 and node2.
	 * @param node1 string, name of the first node.
	 * @param node2 string, name of the second node.
	 * @return int, the network level between node1 and node2.
	 * @throws hlop_err, if node1 or node2 is not in this list, or the range greater than max network level.
	 */
	const int get_inter_level(const std::string &node1, const std::string &node2) const;
	/**
	 * @brief get net level between node in this communication pair.
	 * @param cp comm_pair, communication pair.
	 * @return int, the network level between nodes in the communication pair.
	 */
	const int get_inter_level(const hlop::comm_pair_t &cp) const;
	/**
	 * @brief get node name by process rank.
	 * @param rank int, process rank.
	 * @return string, the name of the node corresponding to the process rank.
	 */
	const std::string &get_node_id_by_rank(int rank) const;
	/**
	 * @brief get the first k node in this node list.
	 * @param k int, the number of top nodes to retrieve.
	 * @return vector<string_view>, a vector of the top k node names.
	 * @throws hlop_err, if k is not in range [1, node_num].
	 */
	std::vector<std::string_view> get_top_k_nodes(int k) const;

public:
	friend std::ostream &operator<<(std::ostream &os, const node_list &nl);

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
	/**
	 * @brief check if a node is in this node list.
	 * @param node string, name of the node to check.
	 * @return bool, true if the node is in the list, false otherwise.
	 */
	bool has_node(const std::string &node) const;

private:
	const std::vector<std::string> nlist;
	std::unordered_map<int, const std::string &> rmap;
	const int nproc_per_node;

	const hlop::platform_t platform;
	const int node_cores;
	const int numa_cores;
	const int ncore_per_numa;
	const int max_network_level;
	const int max_core_level;
	const std::regex node_regex;
	const std::unordered_map<hlop::rank_arrangement, std::function<int(int)>> rank_arrangement_map;
};
typedef node_list node_list_t;

std::ostream &operator<<(std::ostream &os, const node_list &nl);
} // namespace hlop

#endif // __NODE_LIST_H__