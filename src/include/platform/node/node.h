#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <map>
#include <string>

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
	friend std::ostream &operator<<(std::ostream &os, const node &n);
	/**
	 * @brief get the core level between core1 and core2.
	 * @param n node, the node to which the cores belong.
	 * @param rank1 int, rank bind to core1.
	 * @param rank2 int, rank bind to core2.
	 * @return int, the core level between core1 and core2.
	 * @throws hlop_err, if rank1 or rank2 is not in the range [0, node_cores - 1], or the range greater than max core level.
	 */
	friend const int get_core_level(const node &n, int rank1, int rank2);

public:
	virtual ~node() = default;

public:
	virtual bool operator==(const node &other) const = 0;
	virtual bool operator!=(const node &other) const = 0;
	virtual bool operator<(const node &other) const = 0;
	virtual bool operator>(const node &other) const = 0;

public:
	/**
	 * @brief get the name of the node.
	 * @return string, the name of the node.
	 */
	virtual const std::string &name() const = 0;
	/**
	 * @brief get the maximum node level.
	 * @return int, the maximum node level.
	 */
	virtual const int max_node_level() const = 0;
	/**
	 * @brief get the number of cores in the node.
	 * @return int, the number of cores in the node.
	 */
	virtual const int node_cores() const = 0;
	/**
	 * @brief get the maximum core level.
	 * @return int, the maximum core level.
	 */
	virtual const int max_core_level() const = 0;
	/**
	 * @brief get the number of NUMA nodes in the node.
	 * @return int, the number of NUMA nodes in the node.
	 */
	virtual const int numa_cores() const = 0;
	/**
	 * @brief get the number of cores per NUMA node.
	 * @return int, the number of cores per NUMA node.
	 */
	virtual const int ncore_per_numa() const = 0;
	/**
	 * @brief get the number of units in the node.
	 * @return int, the number of units in the node.
	 */
	virtual const int ncore_per_unit() const = 0;

public:
	/**
	 * @brief bind a process rank to a core.
	 * @param rank int, the process rank to bind.
	 * @param core int, the core to bind the rank to.
	 * @throws hlop_err, if the core is not in the range of [0, node_cores - 1] or the rank is already bound to a core.
	 */
	void bind_core(int rank, int core);
	/**
	 * @brief get the unit id of a process rank.
	 * @param rank int, the process rank.
	 * @return int, the unit id of the process rank.
	 * @throws hlop_err, if the rank is not in the range of [0, node_cores - 1].
	 */
	const int get_unit_id(int rank) const;

protected:
	/**
	 * @brief get the core of a process rank.
	 * @param rank int, the process rank.
	 * @return int, the core of the process rank.
	 * @throws hlop_err, if the rank is not bound to any core.
	 */
	const int get_core(int rank) const;

protected:
	std::map<int, int> rank_core_map;
};
typedef node node_t;

std::ostream &operator<<(std::ostream &os, const node &n);
const int get_core_level(const node &n, int rank1, int rank2);
} // namespace hlop

#endif // __NODE_H__