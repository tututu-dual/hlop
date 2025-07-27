#include <iostream>

#include "node/node.h"
#include "struct/comm_pair.h"

hlop::comm_pair::comm_pair(const hlop::const_node_ptr_t src_node, int src_rank,
                           const hlop::const_node_ptr_t dst_node, int dst_rank)
    : src_pnr{src_node, src_rank}, dst_pnr{dst_node, dst_rank}, sendrecv(nullptr) {}

hlop::comm_pair::comm_pair(const hlop::const_node_ptr_t self_node, int self_rank, const comm_pair_ptr_t sr)
    : src_pnr{self_node, self_rank}, dst_pnr{self_node, self_rank}, sendrecv{sr} {}

hlop::comm_pair::comm_pair(const comm_pair_t &other)
    : src_pnr{other.src_pnr}, dst_pnr{other.dst_pnr}, sendrecv{other.sendrecv} {}

hlop::comm_pair &hlop::comm_pair::operator=(const comm_pair_t &other) {
	src_pnr = other.src_pnr;
	dst_pnr = other.dst_pnr;
	sendrecv = other.sendrecv;
	return *this;
}

hlop::comm_pair &hlop::comm_pair::operator=(comm_pair_t &&other) noexcept {
	src_pnr = other.src_pnr;
	dst_pnr = other.dst_pnr;
	sendrecv = other.sendrecv;
	return *this;
}

bool hlop::comm_pair::operator==(const comm_pair_t &other) const {
	const auto &this_src_node = get_src_node();
	const auto &this_dst_node = get_dst_node();
	const auto &other_src_node = other.get_src_node();
	const auto &other_dst_node = other.get_dst_node();

	if (is_mid_pair() && other.is_mid_pair()) {
		return (this_src_node == other_src_node) &&
		       (this_src_node.get_unit_id(get_src_rank()) ==
		        other_src_node.get_unit_id(other.get_src_rank())) &&
		       (*sendrecv == *other.sendrecv);
	}

	if (!is_mid_pair() && !other.is_mid_pair()) {
		if (is_intra_node_pair() && other.is_intra_node_pair()) {
			const auto &this_node = get_src_node();
			const auto &other_node = other.get_src_node();

			if (this_node != other_node)
				return false;

			if (is_intra_unit_pair() && other.is_intra_unit_pair()) {
				return this_node.get_unit_id(get_src_rank()) ==
				       other_node.get_unit_id(other.get_src_rank());
			}

			if (is_inter_unit_pair() && other.is_inter_unit_pair()) {
				return ((this_node.get_unit_id(get_src_rank()) ==
				         other_node.get_unit_id(other.get_src_rank())) ||
				        (this_node.get_unit_id(get_src_rank()) ==
				         other_node.get_unit_id(other.get_dst_rank()))) &&
				       ((this_node.get_unit_id(get_dst_rank()) ==
				         other_node.get_unit_id(other.get_dst_rank())) ||
				        (this_node.get_unit_id(get_dst_rank()) ==
				         other_node.get_unit_id(other.get_src_rank())));
			}
		}

		if (is_inter_node_pair() && other.is_inter_node_pair()) {
			return ((this_src_node == other_src_node) ||
			        (this_src_node == other_dst_node)) &&
			       ((this_dst_node == other_dst_node) ||
			        (this_dst_node == other_src_node));
		}
	}

	return false;
}

bool hlop::comm_pair::operator!=(const comm_pair_t &other) const {
	return !operator==(other);
}

bool hlop::comm_pair::operator<(const comm_pair_t &other) const {
	return operator!=(other) &&
	       (get_src_node() < other.get_src_node() ||
	        (get_src_node() == other.get_src_node() &&
	         get_dst_node() < other.get_dst_node()));
}

bool hlop::comm_pair::operator>(const comm_pair_t &other) const {
	return !operator<(other) && operator!=(other);
}

bool hlop::comm_pair::is_mid_pair() const { return sendrecv != nullptr; }

bool hlop::comm_pair::is_intra_node_pair() const { return get_src_node() == get_dst_node(); }

bool hlop::comm_pair::is_inter_node_pair() const { return !is_intra_node_pair(); }

bool hlop::comm_pair::is_intra_unit_pair() const {
	return is_intra_node_pair() &&
	       (get_src_node().get_unit_id(get_src_rank()) ==
	        get_dst_node().get_unit_id(get_dst_rank()));
}

bool hlop::comm_pair::is_inter_unit_pair() const {
	return is_intra_node_pair() &&
	       (get_src_node().get_unit_id(get_src_rank()) !=
	        get_dst_node().get_unit_id(get_dst_rank()));
}

const hlop::node_t &hlop::comm_pair::get_src_node() const { return *src_pnr.first; }

const hlop::node_t &hlop::comm_pair::get_dst_node() const { return *dst_pnr.first; }

int hlop::comm_pair::get_src_rank() const { return src_pnr.second; }

int hlop::comm_pair::get_dst_rank() const { return dst_pnr.second; }

std::ostream &hlop::operator<<(std::ostream &os, const comm_pair_t &self) {
	if (self.sendrecv == nullptr)
		os << "comm_pair{ src: " << self.get_src_node()
		   << "{" << self.src_pnr.second << ", " << self.get_src_node().get_core(self.src_pnr.second)
		   << "}; dst: " << self.get_dst_node()
		   << "{" << self.dst_pnr.second << ", " << self.get_dst_node().get_core(self.dst_pnr.second)
		   << "}; }";
	else
		os << "comm_pair{ src: " << self.sendrecv->get_src_node()
		   << "{" << self.sendrecv->src_pnr.second << ", " << self.sendrecv->get_src_node().get_core(self.sendrecv->src_pnr.second)
		   << "}; dst: " << self.sendrecv->get_dst_node()
		   << "{" << self.sendrecv->dst_pnr.second << ", " << self.sendrecv->get_dst_node().get_core(self.sendrecv->dst_pnr.second)
		   << "}; self: " << self.get_src_node()
		   << "{" << self.src_pnr.second << ", " << self.get_src_node().get_core(self.src_pnr.second)
		   << "}; }";
	return os;
}