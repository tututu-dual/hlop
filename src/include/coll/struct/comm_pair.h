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
	using comm_pair_t = hlop::comm_pair;
	using comm_pair_ptr = std::shared_ptr<hlop::comm_pair>;
	using comm_pair_ptr_t = comm_pair_ptr;
	using const_comm_pair_ptr = std::shared_ptr<const hlop::comm_pair>;
	using const_comm_pair_ptr_t = const_comm_pair_ptr;

private:
	using pnr = std::pair<hlop::const_node_ptr, int>;
	using pnr_t = pnr;

public:
	/**
	 * @brief default constructor for a communication pair.
	 * @note This constructor is deleted to prevent creating an empty communication pair.
	 * It is intended to be used only with specific source and destination pairs.
	 */
	comm_pair() = delete;
	/**
	 * @brief constructor for a communication pair with node names and ranks.
	 * @param src_node const_node_ptr, source node.
	 * @param src_rank int, source rank.
	 * @param dst_node const_node_ptr, destination node.
	 * @param dst_rank int, destination rank.
	 */
	comm_pair(const hlop::const_node_ptr_t src_node, int src_rank, const hlop::const_node_ptr_t dst_node, int dst_rank);
	/**
	 * @brief constructor for a middle communication pair with node name and rank.
	 * @param self_node const_node_ptr, source and destination node.
	 * @param self_rank int, source and destination rank.
	 * @param sr comm_pair_ptr, shared pointer to the communication pair.
	 */
	comm_pair(const hlop::const_node_ptr_t self_node, int self_rank, const comm_pair_ptr_t sr);
	/**
	 * @brief copy constructor for a communication pair.
	 * @param other comm_pair, another communication pair to copy from.
	 */
	comm_pair(const comm_pair_t &other);

	~comm_pair() = default;

public:
	hlop::comm_pair &operator=(const comm_pair_t &other);
	hlop::comm_pair &operator=(comm_pair_t &&other) noexcept;
	bool operator==(const comm_pair_t &other) const;
	bool operator!=(const comm_pair_t &other) const;
	bool operator<(const comm_pair_t &other) const;
	bool operator>(const comm_pair_t &other) const;

	friend std::ostream &operator<<(std::ostream &os, const comm_pair_t &self);

public:
	/**
	 * @brief check whether this pair is a middle pair(using sendrecv).
	 * @return bool, true if it is a middle pair, false otherwise.
	 */
	bool is_mid_pair() const;
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
	 * @return node, the source node.
	 */
	const hlop::node_t &get_src_node() const;
	/**
	 * @brief get the destination node in the pair.
	 * @return node, the destination node.
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
	pnr_t src_pnr;
	pnr_t dst_pnr;
	comm_pair_ptr_t sendrecv;
};
typedef comm_pair comm_pair_t;
typedef comm_pair::comm_pair_ptr comm_pair_ptr;
typedef comm_pair::comm_pair_ptr_t comm_pair_ptr_t;
typedef comm_pair::const_comm_pair_ptr const_comm_pair_ptr;
typedef comm_pair::const_comm_pair_ptr_t const_comm_pair_ptr_t;

std::ostream &operator<<(std::ostream &, const comm_pair_t &);
} // namespace hlop

#endif // __COMM_PAIR_H__