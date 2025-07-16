#include <iostream>
#include <string>
#include <string_view>
#include <utility>

#include "struct/comm_pair.h"

hlop::comm_pair::comm_pair(const hlop::comm_pair::pnr &src, const hlop::comm_pair::pnr &dst)
    : src_pnr{src}, dst_pnr{dst}, sendrecv{nullptr} {
	if (src_pnr.first > dst_pnr.first)
		std::swap(src_pnr, dst_pnr);
}

hlop::comm_pair::comm_pair(const std::string &src_node, int src_rank, const std::string &dst_node, int dst_rank)
    : src_pnr{src_node, src_rank}, dst_pnr{dst_node, dst_rank} {
	if (src_pnr.first > dst_pnr.first)
		std::swap(src_pnr, dst_pnr);
}

hlop::comm_pair::comm_pair(const hlop::comm_pair::pnr &self, hlop::comm_pair::comm_pair_ptr sr) : src_pnr{self}, dst_pnr{self}, sendrecv{sr} {}

hlop::comm_pair::comm_pair(const std::string &self_node, int self_rank, hlop::comm_pair::comm_pair_ptr sr)
    : src_pnr{self_node, self_rank}, dst_pnr{self_node, self_rank}, sendrecv{sr} {
}

hlop::comm_pair::comm_pair(const hlop::comm_pair &other)
    : src_pnr{other.src_pnr}, dst_pnr{other.dst_pnr}, sendrecv{other.sendrecv} {}

hlop::comm_pair &hlop::comm_pair::operator=(const hlop::comm_pair &other) {
	src_pnr = other.src_pnr;
	dst_pnr = other.dst_pnr;
	sendrecv = other.sendrecv;
	return *this;
}

hlop::comm_pair &hlop::comm_pair::operator=(hlop::comm_pair &&other) noexcept {
	src_pnr = other.src_pnr;
	dst_pnr = other.dst_pnr;
	sendrecv = other.sendrecv;
	return *this;
}

bool hlop::comm_pair::operator==(const hlop::comm_pair &other) const {
	if (!is_mid_pair() && !other.is_mid_pair())
		return (get_src_node() == other.get_src_node() &&
		        get_dst_node() == other.get_dst_node());
	else if (is_mid_pair() && other.is_mid_pair())
		return (get_src_node() == other.get_src_node() &&
		        get_dst_node() == other.get_dst_node() &&
		        *sendrecv == *other.sendrecv);
	else
		return false;
}

bool hlop::comm_pair::is_mid_pair() const { return sendrecv != nullptr; }

bool hlop::comm_pair::is_intra_pair() const { return src_pnr.first == dst_pnr.first; }

bool hlop::comm_pair::is_inter_pair() const { return !is_intra_pair(); }

const std::string &hlop::comm_pair::get_src_node() const { return src_pnr.first; }

const std::string &hlop::comm_pair::get_dst_node() const { return dst_pnr.first; }

bool hlop::operator<(const hlop::comm_pair &lhs, const hlop::comm_pair &rhs) {
	return (lhs.get_src_node() < rhs.get_src_node() ||
	        (lhs.get_src_node() == rhs.get_src_node() &&
	         lhs.get_dst_node() < rhs.get_dst_node()));
}

std::ostream &hlop::operator<<(std::ostream &os, const hlop::comm_pair &self) {
	if (self.sendrecv == nullptr)
		os << "comm_pair{ src: " << self.get_src_node() << "(" << self.src_pnr.second
		   << "); dst: " << self.get_dst_node() << "(" << self.dst_pnr.second << "); }";
	else
		os << "comm_pair{ src: " << self.sendrecv->get_src_node() << "(" << self.sendrecv->src_pnr.second
		   << "); dst: " << self.sendrecv->get_dst_node() << "(" << self.sendrecv->dst_pnr.second
		   << "); self: " << self.get_src_node() << "(" << self.src_pnr.second << "); }";
	return os;
}