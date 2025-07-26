#ifndef __DF_NODE_H__
#define __DF_NODE_H__

#include <array>
#include <string>
#include <string_view>

#include "node/df_node_parser.h"
#include "node/node.h"

namespace hlop {
class df_node : public node {
public:
	/**
	 * @brief default constructor of df_node.
	 * @note This constructor is not accessible directly and should not be used.
	 * It is provided to prevent the creation of an empty df_node.
	 */
	df_node() = delete;
	/**
	 * @brief constructor of df_node with levels.
	 * @param node_str string, the name of the node.
	 */
	df_node(const std::string &node_str);
	~df_node() = default;

public:
	bool operator==(const node &other) const override;
	bool operator!=(const node &other) const override;
	bool operator<(const node &other) const override;
	bool operator>(const node &other) const override;

public:
	const std::string &name() const override;
	const int max_node_level() const override;
	const int node_cores() const override;
	const int max_core_level() const override;
	const int numa_cores() const override;
	const int ncore_per_numa() const override;
	const int ncore_per_unit() const override;

private:
	const std::string node_name;
	const std::array<std::string_view, df_node_parser::MAX_NODE_LEVEL> levels;
};
typedef df_node df_node_t;
} // namespace hlop

#endif // __DF_NODE_H__