# C++ 设计题

## 特性要求

- 设计一个 **扣费服务管理** 的后台系统，具备  “查看扣费服务列表”、“开通扣费服务”、“关闭扣费服务” 的功能。
- 原型参考：微信 -> "我" -> “支付” -> 右上角"…" -> 扣费服务。
- 1 个账户只能在 1 个终端上登录，当切换终端登录时，其他已登录终端会被踢出。

## 技术要求

- `must` 使用 C++ 实现客户端（命令行交互即可）、服务端，代码风格良好
- `must` 扣费服务数据需要存储，且需考虑数据安全和传输安全，存储选型不限
- `must` 代码托管到 [Github](https://github.com/)
- `must` 使用 [gRPC](https://grpc.io) 框架
- `must` 使用 [bazel]( https://bazel.build/ ) 管理编译
- `better` 使用 [googletest]( https://github.com/google/googletest ) 做单元测试
- `better` 接入[Travis流水线](https://travis-ci.org/)

## 交付物

- `must` 源代码、设计文档、说明文档
- `better` 已部署好的服务端、可运行的客户端

## 时间要求

- 1-2 周

