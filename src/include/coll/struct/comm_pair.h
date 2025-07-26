#ifndef __COMM_PAIR_H__
#define __COMM_PAIR_H__

#include <iostream>
#include <memory>
#include <utility>

#include "node/node.h"

namespace hlop {
/**
 * @brief class communication pair.
 * This class represents a pair of communication endpoints.
 * It contains information about the source and destination nodes and ranks,
 * and can be used to determine the nature of the communication (intra-node, inter-node, or middle pair).
 */
class comm_pair {
public:
	using comm_pair_ptr = std::shared_ptr<comm_pair>;

private:
	using pnr = std::pair<const hlop::node *, int>;

public:
	/**
	 * @brief default constructor for a communication pair.
	 * @note This constructor is deleted to prevent creating an empty communication pair.
	 * It is intended to be used only with specific source and destination pairs.
	 */
	comm_pair() = delete;
	/**
	 * @brief constructor for a communication pair with node names and ranks.
	 * @param src_node node, source node.
	 * @param src_rank int, source rank.
	 * @param dst_node node, destination node.
	 * @param dst_rank int, destination rank.
	 */
	comm_pair(const hlop::node_t &src_node, int src_rank, const hlop::node_t &dst_node, int dst_rank);
	/**
	 * @brief constructor for a middle communication pair with node name and rank.
	 * @param self_node node, source and destination node.
	 * @param self_rank int, source and destination rank.
	 * @param sr comm_pair_ptr, shared pointer to the communication pair.
	 */
	comm_pair(const hlop::node_t &self_node, int self_rank, hlop::comm_pair::comm_pair_ptr sr);
	/**
	 * @brief copy constructor for a communication pair.
	 * @param other comm_pair, another communication pair to copy from.
	 */
	comm_pair(const hlop::comm_pair &other);

	~comm_pair() = default;

public:
	comm_pair &operator=(const hlop::comm_pair &other);
	comm_pair &operator=(hlop::comm_pair &&other) noexcept;
	bool operator==(const hlop::comm_pair &other) const;
	bool operator!=(const hlop::comm_pair &other) const;
	bool operator<(const hlop::comm_pair &other) const;
	bool operator>(const hlop::comm_pair &other) const;

	friend std::ostream &operator<<(std::ostream &os, const hlop::comm_pair &self);

public:
	/**
	 * @brief check whether this pair is a middle pair(using sendrecv).
	 * @return bool, true if it is a middle pair, false otherwise.
	 */
	bool is_mid_node_pair() const;
	/**
	 * @brief check whether this pair is in the same node.
	 * @return bool, true if it is an intra-node pair, false otherwise.
	 */
	bool is_intra_node_pair() const;
	/**
	 * @brief check whether this pair is in different node.
	 * @return bool, true if it is an inter-node pair, false otherwise.
	 */
	bool is_inter_node_pair() const;
	/**
	 * @brief check whether this pair is in the same node core unit.
	 * @return bool, true if it is an intra-node pair, false otherwise.
	 */
	bool is_intra_unit_pair() const;
	/**
	 * @brief check whether this pair is in different node core unit.
	 * @return bool, true if it is an inter-node pair, false otherwise.
	 */
	bool is_inter_unit_pair() const;
	/**
	 * @brief get the source node in the pair.
	 * @return string, the source node name.
	 */
	const hlop::node_t &get_src_node() const;
	/**
	 * @brief get the destination node in the pair.
	 * @return string, the destination node name.
	 */
	const hlop::node_t &get_dst_node() const;
	/**
	 * @brief get the source process rank in the pair.
	 * @return int, the source process rank.
	 */
	int get_src_rank() const;
	/**
	 * @brief get the destination process rank in the pair.
	 * @return int, the destination process rank.
	 */
	int get_dst_rank() const;

private:
	hlop::comm_pair::pnr src_pnr;
	hlop::comm_pair::pnr dst_pnr;
	hlop::comm_pair::comm_pair_ptr sendrecv;
};
typedef comm_pair comm_pair_t;
typedef comm_pair::comm_pair_ptr comm_pair_ptr_t;

std::ostream &operator<<(std::ostream &, const hlop::comm_pair &);
} // namespace hlop

#endif // __COMM_PAIR_H__