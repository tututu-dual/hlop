# hlop (version 1.0)

##  directory struct
```txt
src
├── CMakeLists.txt
├── coll
│   ├── allgather.cpp
│   ├── allreduce.cpp
│   ├── alltoall.cpp
│   ├── bcast.cpp
│   ├── CMakeLists.txt
│   ├── collective.cpp
│   ├── gather.cpp
│   ├── reduce.cpp
│   ├── scatter.cpp
│   └── struct
│       ├── comm_pair.cpp
│       ├── node_list.cpp
│       └── type.cpp
├── include
│   ├── coll
│   │   ├── allgather.h
│   │   ├── allreduce.h
│   │   ├── alltoall.h
│   │   ├── bcast.h
│   │   ├── collective.h
│   │   ├── gather.h
│   │   ├── reduce.h
│   │   ├── scatter.h
│   │   └── struct
│   │       ├── comm_pair.h
│   │       ├── node_list.h
│   │       └── type.h
│   ├── main
│   │   └── main.h
│   ├── platform
│   │   ├── node
│   │   │   ├── df_node.h
│   │   │   ├── node.h
│   │   │   └── th_node.h
│   │   ├── param
│   │   │   └── param.h
│   │   └── platform.h
│   └── util
│       ├── aux.h
│       ├── err.h
│       ├── fit.h
│       ├── m_debug.h
│       └── msg.h
├── main
│   ├── CMakeLists.txt
│   └── main.cpp
├── platform
│   ├── CMakeLists.txt
│   ├── node
│   │   ├── df_node.cpp
│   │   ├── node.cpp
│   │   └── th_node.cpp
│   ├── param
│   │   └── param.cpp
│   └── platform.cpp
└── util
    ├── aux.cpp
    ├── CMakeLists.txt
    └── fit.cpp
```

## dependencies

- [x] `GSL`:
- [x] `magic_enum`:
- [x] `gflags`:
