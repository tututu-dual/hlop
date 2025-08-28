# Tutorial

## prepare

1. 创建目录`cd ${user_dir} && mkdir -p install log`, `user_dir`是用户各自的目录.

## install

### osu benchmark

1. 加载模块
   - `module purge`
   - `module load compiler/devtoolset/7.3.1`
   - `module load compiler/rocm/dtk/24.04.1`
   - `module load mpi/mpich/3.4-gcc-7.3.1`
   - `module load mathlib/gsl/2.7/gnu`
2. 检查环境
   - `which mpicc`
   - `which mpicxx`
   - `make --version`
3. 获取源码
   - `cd ${user_dir}`
   - `cp -r /public/home/dfcs2025/zhwang/osu-micro-benchmarks-7.3 .`
4. 编译
   - `cd osu-micro-benchmarks-7.3`
   - `./configure CC=mpicc CXX=mpicxx --prefix=$(pwd)/../install`
   - `make && make install`
5. 检查软件
   - `cd ${user_dir}`
   - `ls $(pwd)/install/libexec/osu-micro-benchmarks/mpi/pt2pt`
   - `ls $(pwd)/install/libexec/osu-micro-benchmarks/mpi/collective`

### H-Lop

1. 获取源码
   - `cd ${user_dir}`
   - `cp -r /public/home/dfcs2025/zhwang/H-Lop .`
2. 编译
   - `cd H-Lop && bash build.sh`
3. 检查软件
   - `ls $(pwd)/install/bin`
   - `ls $(pwd)/install/lib`
   - `ls $(pwd)/install/share/resources`
4. 导出环境变量
   - `cd ${user_dir}`
   - `export HLOP=$(pwd)/install/bin/hlop`

## case 1

1. 拷贝模板
   - `cp param-template.sh param-coll.sh`
2. 修改模板内容
   - `vim param-coll.sh`
   - `NTASK & PPN`: 修改进程数和每节点进程数, 主要影响收集数据的进程对数量, `PPN`需要是`NTASK`的一半;
   - `JOBNAME`: 用户自己随意;
   - `$(pwd)/install/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_multi_lat`: 一般不用修改，如果想测试带宽可以替换成`osu_mbw_mr`;
3. 提交任务
   - `bash param.sh`
4. 检查结果
   - `cat log/${job_id}.log`

## case 2 (Bcast)

1. 拷贝模板
   - `cp op-template.sh bcast.sh`
2. 修改模板内容
   - `vim bcast.sh`
   - `NTASK & PPN`: 修改进程数和每节点进程数, 主要影响收集数据的进程对数量, `PPN`需要是`NTASK`的一半;
   - `JOBNAME`: 用户自己随意;
   - `$(pwd)/install/libexec/osu-micro-benchmarks/mpi/collective/osu_coll`: 修改成测试用的集合通信操作的相应可执行文件`osu_bcast`;
   - `MPIR_CVAR_COLL_INTRA_ALGORITHM=nb`, `MPIR_CVAR_ICOLL_INTRA_ALGORITHM=sched_binomial`: 把其中的`COLL`修改为相应集合通信操作的名称, 如: `MPIR_CVAR_BCAST_INTRA_ALGORITHM`和`MPIR_CVAR_IBCAST_INTRA_ALGORITHM`
3. 提交任务
   - `bash bcast.sh`
4. 检查结果
   - `cat log/${job_id}.log`
5. 获取建模结果
   - `$HLOP --op=BCAST --algo=BINOMIAL --pf=DF --nl=h04r4n[01-02] --ppn=16 --msz="4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536"`

## case 3 (Scatter)

1. 拷贝模板
   - `cp op-template.sh scatter.sh`
2. 修改模板内容
   - `vim scatter.sh`
   - `NTASK & PPN`: 修改进程数和每节点进程数, 主要影响收集数据的进程对数量, `PPN`需要是`NTASK`的一半;
   - `JOBNAME`: 用户自己随意;
   - `$(pwd)/install/libexec/osu-micro-benchmarks/mpi/collective/osu_coll`: 修改成测试用的集合通信操作的相应可执行文件`osu_scatter`;
   - `MPIR_CVAR_COLL_INTRA_ALGORITHM=nb`, `MPIR_CVAR_ICOLL_INTRA_ALGORITHM=sched_binomial`: 把其中的`COLL`修改为相应集合通信操作的名称, 如: `MPIR_CVAR_SCATTER_INTRA_ALGORITHM`和`MPIR_CVAR_ISCATTER_INTRA_ALGORITHM`
3. 提交任务
   - `bash scatter.sh`
4. 检查结果
   - `cat log/${job_id}.log`
5. 获取建模结果
   - `$HLOP --op=SCATTER --algo=BINOMIAL --pf=DF --nl=h04r4n[01-02] --ppn=16 --msz="4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536"`