# hlop

## version 0.1

### util
some utilities functions.
- `fix.h`: function fit.
- `aux.h`: some check function, like pof2.

### platform
some platform features.
- `node/`: platform node infomation.
- `param/`: parameter infomation.
- `platform.h`: platform infomation.

### coll
collective operations & structs.
- `struccts/`: structs describe platform, collective operation & algorithm, etc.
- `${operation}.h`: collective operation implementment.

### main
command line interface.
- `main.h`: command line parser & execute.

### dependencies
- GSL: install by pacman, yum, apt, etc.
- gflags: install manually.

## version 0.1

### util
一些工具函数
- `fix.h`: 参数拟合相关部分，指数函数的非线性拟合。
- `aux.h`: 一些辅助函数。

### platform
平台特征表示部分
- `node/`: 解析平台节点列表内容。
- `param/`: 获取参数。
- `platform.h`: 平台信息表示。

### coll
集合通信操作相关内容
- `struccts/`: 一些辅助结构。
- `${operation}.h`: 集合通信操作的算法实现。

### main
命令行解析与执行部分
- `main.h`: 命令行参数的解析与模型的运行。

### dependencies
- GSL: 非线性拟合数学库，通过包管理器安装或加载模块。
- gflags: 参数解析库，通过手动编译安装。