#ifndef __COMM_PAIR_H__
#define __COMM_PAIR_H__

#include <iostream>
#include <memory>
#include <string>
#include <utility>

namespace hlop {
/**
 * @brief class communication pair
 * This class represents a pair of communication endpoints.
 * It contains information about the source and destination nodes and ranks,
 * and can be used to determine the nature of the communication (intra-node, inter-node, or middle pair).
 */
class comm_pair {
public:
	using comm_pair_ptr = std::shared_ptr<comm_pair>;
	using pnr = std::pair<std::string, int>;

public:
	comm_pair();
	comm_pair(const hlop::comm_pair::pnr &src, const hlop::comm_pair::pnr &dst);
	comm_pair(const std::string &src_node, int src_rank, const std::string &dst_node, int dst_rank);
	comm_pair(const hlop::comm_pair::pnr &self, hlop::comm_pair::comm_pair_ptr sr);
	comm_pair(const std::string &self_node, int self_rank, hlop::comm_pair::comm_pair_ptr sr);
	comm_pair(const hlop::comm_pair &other);
	~comm_pair() = default;

	comm_pair &operator=(const hlop::comm_pair &other);
	comm_pair &operator=(hlop::comm_pair &&other) noexcept;

public:
	bool operator==(const hlop::comm_pair &other) const;
	friend bool operator<(const hlop::comm_pair &lhs, const hlop::comm_pair &rhs);
	friend std::ostream &operator<<(std::ostream &os, const hlop::comm_pair &self);

public:
	/**
	 * @brief check whether this pair is a middle pair(using sendrecv)
	 * @return bool, true if it is a middle pair, false otherwise
	 */
	bool is_mid_pair() const;
	/**
	 * @brief check whether this pair is in the same node
	 * @return bool, true if it is an intra-node pair, false otherwise
	 */
	bool is_intra_pair() const;
	/**
	 * @brief check whether this pair is in different node
	 * @return bool, true if it is an inter-node pair, false otherwise
	 */
	bool is_inter_pair() const;
	/**
	 * @brief get the source node in the pair
	 * @return string, the source node name
	 */
	const std::string &get_src_node() const;
	/**
	 * @brief get the destination node in the pair
	 * @return string, the destination node name
	 */
	const std::string &get_dst_node() const;

private:
	hlop::comm_pair::pnr src_pnr;
	hlop::comm_pair::pnr dst_pnr;
	hlop::comm_pair::comm_pair_ptr sendrecv;
};
typedef comm_pair comm_pair_t;
typedef comm_pair::comm_pair_ptr comm_pair_ptr_t;

bool operator<(const hlop::comm_pair &lhs, const hlop::comm_pair &rhs);
std::ostream &operator<<(std::ostream &, const hlop::comm_pair &);
} // namespace hlop

#endif // __COMM_PAIR_H__