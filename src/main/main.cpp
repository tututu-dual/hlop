#include <utility>
#include <vector>

#include "aux.h"
#include "bcast.h"
#include "err.h"
#include "gflags/gflags.h"
#include "main.h"
#include "platform.h"
#include "scatter.h"
#include "struct/type.h"

DEFINE_string(op, "", "collective operation type");
DEFINE_string(algo, "", "collective operation algorithm type");
DEFINE_string(pf, "", "platform");
DEFINE_string(nl, "", "node list");
DEFINE_int32(ppn, 0, "process per node");
DEFINE_string(msz, "", "message size");

hlop::exec_args_t hlop::parse_argument(int *argc, char ***argv) {
	gflags::ParseCommandLineFlags(argc, argv, true);
	if (FLAGS_op == "")
		HLOP_ERR("operation type must be specified with --op");
	if (FLAGS_algo == "")
		HLOP_ERR("algorithm type must be specified with --algo");
	if (FLAGS_pf == "")
		HLOP_ERR("platform must be specified with --pf");
	if (FLAGS_nl == "")
		HLOP_ERR("node list must be specified with --nl");
	if (FLAGS_ppn < 1)
		HLOP_ERR("processes per node must be greater than 0");
	if (FLAGS_msz == "")
		HLOP_ERR("message size must be specified with --msz");

	hlop::op_type_t op = hlop::enum_cast<hlop::op_type>(FLAGS_op);
	hlop::algo_type_t algo = hlop::enum_cast<hlop::algo_type>(FLAGS_algo);
	hlop::node_list_t nl{hlop::enum_cast<hlop::platform>(FLAGS_pf),
	                     FLAGS_nl,
	                     FLAGS_ppn,
	                     hlop::rank_arrangement::CYCLIC};
	auto msz = hlop::stov<int>(FLAGS_msz);

	return hlop::exec_args_t{.op = op, .algo = algo, .nl = std::move(nl), .msz = std::move(msz)};
}

double hlop::execute_with_arg(hlop::op_type_t op, hlop::algo_type_t algo, hlop::node_list_t nl, int msg_size) {
	switch (op) {
	case hlop::op_type::ALLGATHER: {
		break;
	}
	case hlop::op_type::ALLREDUCE: {
		break;
	}
	case hlop::op_type::ALLTOALL: {
		break;
	}
	case hlop::op_type::BCAST: {
		hlop::bcast predictor;
		return predictor.predict(algo, nl, msg_size, 0);
		break;
	}
	case hlop::op_type::GATHER: {
		break;
	}
	case hlop::op_type::REDUCE: {
		break;
	}
	case hlop::op_type::SCATTER: {
		hlop::scatter predictor;
		return predictor.predict(algo, nl, msg_size, 0);
		break;
	}
	default: {
		HLOP_ERR(hlop::format("unknown operation type: {}", hlop::enum_name(op)));
		break;
	}
	}
	return 0.0;
}

std::vector<double> hlop::execute_with_args(hlop::op_type_t op,
                                            hlop::algo_type_t algo,
                                            hlop::node_list_t nl,
                                            std::vector<int> msg_sizes) {
	std::vector<double> res;
	for (const auto &m : msg_sizes)
		res.emplace_back(execute_with_arg(op, algo, nl, m));
	return std::move(res);
}

// ./main --op=BCAST --algo=BINOMIAL --pf=DF
// --nl="i10r4n[03-04,08-09,13-14,16,18-19]" --ppn=16 --msz="1,2,4"
int main(int argc, char *argv[]) {
	gflags::SetUsageMessage("");
	hlop::exec_args_t args = hlop::parse_argument(&argc, &argv);
	std::cout << "Operation: " << args.op << std::endl
	          << "Algorithm: " << args.algo << std::endl
	          << "Platform: " << args.nl.get_platform() << std::endl
	          << "Processes per node: " << args.nl.get_ppn() << std::endl
	          << "Node list: " << args.nl << std::endl
	          << "Message sizes: " << hlop::vtos(args.msz) << std::endl;
	const auto res = hlop::execute_with_args(args.op, args.algo, args.nl, args.msz);
	std::cout << "Predict result: " << hlop::vtos(res) << std::endl;
	return 0;
}