# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "GreetingLib",
    srcs = glob(["**/*.cc"]),
    defines = ["BAZEL_BUILD"],
    hdrs = glob(["**/*.h"]),
    visibility = ["//visibility:public"],
    # deps = [
    #     "//protos:fcdeduction_cc_grpc",
    #     # http_archive made this label available for binding
    #     "@com_github_grpc_grpc//:grpc++",
    # ],
)
