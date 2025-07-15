#ifndef __NODE_LIST_H__
#define __NODE_LIST_H__

#include <functional>
#include <iostream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "comm_pair.h"
#include "platform.h"

namespace hlop {
class node_list {
public:
	node_list() = delete;
	node_list(hlop::platform_t pf, const std::string &node_list_str, int ppn);
	~node_list() = default;

public:
	/// @brief get number of cores in a node
	/// @return
	const int get_node_cores() const;
	/// @brief get number of numa cores in a node
	/// @return
	const int get_numa_cores() const;
	/// @brief get the max net level in this system
	/// @return
	const int get_max_network_level() const;
	/// @brief get number of node in this list
	/// @return
	const int get_node_num() const;
	/// @brief get node list
	/// @return
	const std::vector<std::string> &get_node_list() const;
	/// @brief get number of process per node
	/// @return
	const int get_ppn() const;
	/// @brief get process ranks in this node list
	/// @return
	const std::vector<int> get_ranks() const;
	/// @brief get platform this node list belong to
	/// @return
	const hlop::platform_t get_platform() const;

	/// @brief get net level between node1 and node2
	/// @param node1
	/// @param node2
	/// @return
	const int get_level(const std::string &node1, const std::string &node2) const;
	/// @brief get net level between node in this communicate pair
	/// @param cp
	/// @return
	const int get_level(const hlop::comm_pair_t &cp) const;

	/// @brief get node name by process rank
	/// @param rank
	/// @return
	const std::string &get_node_id_by_rank(int rank) const;

	/// @brief get the first k node in this node list
	/// @param k
	/// @return
	const std::vector<std::string_view> get_top_k_nodes(int k) const;

public:
	friend std::ostream &operator<<(std::ostream &os, const node_list &nl);

private:
	/// @brief check whether node in this node list
	/// @param node
	/// @return
	bool has_node(const std::string &node) const;

private:
	std::function<int(int, int)> rule;
	std::vector<std::string> nlist;

	hlop::platform_t platform;
	int node_cores;
	int numa_cores;
	int max_network_level;
	int nproc_per_node;
	std::regex node_regex;
};
typedef node_list node_list_t;

std::ostream &operator<<(std::ostream &os, const node_list &nl);
} // namespace hlop

#endif // __NODE_LIST_H__