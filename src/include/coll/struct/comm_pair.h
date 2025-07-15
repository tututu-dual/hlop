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
	/**
	 * @brief default constructor for a communication pair
	 * @note This constructor is deleted to prevent creating an empty communication pair.
	 * It is intended to be used only with specific source and destination pairs.
	 */
	comm_pair() = delete;
	/**
	 * @brief constructor for a communication pair
	 * @param src pnr, source node and rank pair
	 * @param dst pnr, destination node and rank pair
	 */
	comm_pair(const hlop::comm_pair::pnr &src, const hlop::comm_pair::pnr &dst);
	/**
	 * @brief constructor for a communication pair with node names and ranks
	 * @param src_node string, source node name
	 * @param src_rank int, source rank
	 * @param dst_node string, destination node name
	 * @param dst_rank int, destination rank
	 */
	comm_pair(const std::string &src_node, int src_rank, const std::string &dst_node, int dst_rank);
	/**
	 * @brief constructor for a middle communication pair
	 * @param self pnr, source and destination node and rank pair
	 * @param sr comm_pair_ptr, shared pointer to the communication pair
	 */
	comm_pair(const hlop::comm_pair::pnr &self, hlop::comm_pair::comm_pair_ptr sr);
	/**
	 * @brief constructor for a middle communication pair with node name and rank
	 * @param self_node string, source and destination node name
	 * @param self_rank int, source and destination rank
	 * @param sr comm_pair_ptr, shared pointer to the communication pair
	 */
	comm_pair(const std::string &self_node, int self_rank, hlop::comm_pair::comm_pair_ptr sr);
	/**
	 * @brief copy constructor for a communication pair
	 * @param other comm_pair, another communication pair to copy from
	 */
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