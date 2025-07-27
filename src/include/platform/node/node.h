#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <unordered_map>

namespace hlop {
/**
 * @brief class node.
 * This class represents a node in a system.
 * It provides methods to retrieve information about the node,
 * such as its name, maximum node level, number of cores, and core levels.
 * It also allows for binding cores to process ranks and retrieving core levels.
 * @throws hlop_err, if the core level is not valid or if the rank is not in the range of the node's cores.
 * @note This class is intended to be used as a base class for specific node implementations.
 */
class node {
public:
	using node_t = hlop::node;
	using node_ptr = std::shared_ptr<hlop::node>;
	using node_ptr_t = node_ptr;
	using const_node_ptr = std::shared_ptr<const hlop::node>;
	using const_node_ptr_t = const_node_ptr;

public:
	node() = delete;
	node(const std::string &node_str);
	virtual ~node() = default;

public:
	virtual bool operator==(const node_t &other) const = 0;
	virtual bool operator!=(const node_t &other) const = 0;
	virtual bool operator<(const node_t &other) const = 0;
	virtual bool operator>(const node_t &other) const = 0;
	virtual const int operator-(const node_t &other) const = 0;

	friend std::ostream &operator<<(std::ostream &os, const node_t &n);

public:
	/**
	 * @brief get the maximum node level.
	 * @return int, the maximum node level.
	 */
	virtual const int get_max_node_level() const = 0;
	/**
	 * @brief get the maximum core level.
	 * @return int, the maximum core level.
	 */
	virtual const int get_max_core_level() const = 0;
	/**
	 * @brief get the number of NUMA nodes in the node.
	 * @return int, the number of NUMA nodes in the node.
	 */
	virtual const int get_numa_num() const = 0;
	/**
	 * @brief get the number of cores in the node.
	 * @return int, the number of cores in the node.
	 */
	virtual const int get_ncore_per_node() const = 0;
	/**
	 * @brief get the number of cores per NUMA node.
	 * @return int, the number of cores per NUMA node.
	 */
	virtual const int get_ncore_per_numa() const = 0;
	/**
	 * @brief get the number of units in the node.
	 * @return int, the number of units in the node.
	 */
	virtual const int get_ncore_per_unit() const = 0;
	/**
	 * @brief get the regex for matching node names.
	 * @return regex, the regex for matching node names.
	 */
	virtual const std::regex &get_node_regex() const = 0;

public:
	/**
	 * @brief get the name of the node.
	 * @return string, the name of the node.
	 */
	const std::string &name() const;
	/**
	 * @brief bind a process rank to a core.
	 * @param rank int, the process rank to bind.
	 * @param core int, the core to bind the rank to.
	 * @throws hlop_err, if the core is not in the range of [0, node_cores - 1] or the rank is already bound to a core.
	 */
	void bind_core(int rank, int core) const;
	/**
	 * @brief get the core of a process rank.
	 * @param rank int, the process rank.
	 * @return int, the core of the process rank.
	 * @throws hlop_err, if the rank is not bound to any core.
	 */
	const int get_core(int rank) const;
	/**
	 * @brief get the unit id of a process rank.
	 * @param rank int, the process rank.
	 * @return int, the unit id of the process rank.
	 * @throws hlop_err, if the rank is not in the range of [0, node_cores - 1].
	 */
	const int get_unit_id(int rank) const;
	/**
	 * @brief get the core level between two process ranks.
	 * @param rank1 int, the first process rank.
	 * @param rank2 int, the second process rank.
	 * @return int, the core level between the two process ranks.
	 * @throws hlop_err, if rank1 or rank2 is not in the range of [0, node_cores - 1].
	 */
	const int get_core_level(int rank1, int rank2) const;

protected:
	const std::string node_name;
	mutable std::unordered_map<int, int> rank_core_map;
};
typedef node::node_t node_t;
typedef node::node_ptr node_ptr;
typedef node::node_ptr_t node_ptr_t;
typedef node::const_node_ptr const_node_ptr;
typedef node::const_node_ptr_t const_node_ptr_t;

std::ostream &operator<<(std::ostream &os, const node_t &n);
} // namespace hlop

#endif // __NODE_H__