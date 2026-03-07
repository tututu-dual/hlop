#ifndef __TH_NODE_H__
#define __TH_NODE_H__

#include <array>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

#include "node/node.h"

namespace hlop {
class th_node : public node {
public:
	using th_node_t = hlop::th_node;
	using th_node_ptr = std::shared_ptr<hlop::th_node>;
	using th_node_ptr_t = th_node_ptr;
	using const_th_node_ptr = std::shared_ptr<const hlop::th_node>;
	using const_th_node_ptr_t = const_th_node_ptr;

public:
	static constexpr int MAX_NODE_LEVEL{4};
	static constexpr int MAX_CORE_LEVEL{3};
	static constexpr int NUMA_NUM{4};
	static constexpr int NCORE_PER_NODE{16};
	static constexpr int NCORE_PER_NUMA{8};
	static constexpr int NCORE_PER_UNIT{4};
	static constexpr int TOP_LEVEL_IDX{0};
	static constexpr int MID_LEVEL_IDX{0};
	static constexpr int BOTTOM_LEVEL_IDX{0};
	static const std::regex NODE_REGEX;
	static const std::regex NODE_LIST_REGEX;

public:
	/**
	 */
	static const std::vector<hlop::const_node_ptr> parse_node_list(const std::string &node_list_str);

private:
	/**
	 */
	static const std::vector<std::string> parse_node_list_aux(const std::string &node_list_str);

public:
	th_node() = delete;
	th_node(const std::string &node_str);
	~th_node() = default;

public:
	bool operator==(const hlop::node_t &other) const override;
	bool operator!=(const hlop::node_t &other) const override;
	bool operator<(const hlop::node_t &other) const override;
	bool operator>(const hlop::node_t &other) const override;
	const int operator-(const hlop::node_t &other) const override;

private:
	const th_node *operator_cast(const hlop::node_t &other) const;

public:
	const int get_max_node_level() const override;
	const int get_max_core_level() const override;
	const int get_numa_num() const override;
	const int get_ncore_per_node() const override;
	const int get_ncore_per_numa() const override;
	const int get_ncore_per_unit() const override;
	const std::regex &get_node_regex() const override;

private:
	const std::array<std::string_view, hlop::th_node::MAX_NODE_LEVEL> node_levels;
};
typedef th_node::th_node_t th_node_t;
typedef th_node::th_node_ptr th_node_ptr;
typedef th_node::th_node_ptr_t th_node_ptr_t;
typedef th_node::const_th_node_ptr const_th_node_ptr;
typedef th_node::const_th_node_ptr_t const_th_node_ptr_t;
} // namespace hlop

#endif // __TH_NODE_H__
