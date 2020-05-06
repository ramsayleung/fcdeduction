package(default_visibility = ["//visibility:public"])

# load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")
load("@rules_foreign_cc//tools/build_defs:make.bzl", "make")

make(
    name = "hiredis",
    # Taken from https://github.com/envoyproxy/envoy/blob/master/bazel/foreign_cc/luajit.patch
    # However, only a pair of variables are taken to make the luajit build work.
    # Probably you want to explore other variables more exactly;
    # For instance, CFLAGS are not copied into TARGET_FLAGS
    # make_env_vars = {
    #     "TARGET_CFLAGS": "-fno-function-sections -fno-data-sections",
    #     "TARGET_LDFLAGS": "-fno-function-sections -fno-data-sections",
    #     "LSAN_OPTIONS": "exitcode=0",
    # },
    lib_source = "@hiredis//:all",
    static_libraries = ["libhiredis.a"],
)

load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

# cmake_external(
#     name = "openblas",
#     # Values to be passed as -Dkey=value on the CMake command line;
#     # here are serving to provide some CMake script configuration options
#    cache_entries = {
#        "NOFORTRAN": "on",
#        "BUILD_WITHOUT_LAPACK": "no",
#    },
#     lib_source = "@openblas//:all",

#    # We are selecting the resulting static library to be passed in C/C++ provider
#     # as the result of the build;
#     # However, the cmake_external dependants could use other artefacts provided by the build,
#     # according to their CMake script
#    static_libraries = ["libopenblas.a"],
# )

# cmake_external(
#     name = "eigen",
#     # These options help CMake to find prebuilt OpenBLAS, which will be copied into
#     # $EXT_BUILD_DEPS/openblas by the cmake_external script
#    cache_entries = {
#        "BLA_VENDOR": "OpenBLAS",
#        "BLAS_LIBRARIES": "$EXT_BUILD_DEPS/openblas/lib/libopenblas.a",
#    },
#     headers_only = True,
#     lib_source = "@eigen//:all",
#     # Dependency on other cmake_external rule; can also depend on cc_import, cc_library rules
#    deps = [":openblas"],
# )

load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

# The following three rules demonstrate the usage of the cc_grpc_library rule in
# in a mode compatible with the native proto_library and cc_proto_library rules.
proto_library(
    name = "helloworld_proto",
    srcs = glob(["proto/*.proto"]),
)

cc_proto_library(
    name = "helloworld_cc_proto",
    deps = [":helloworld_proto"],
)

cc_grpc_library(
    name = "helloworld_cc_grpc",
    srcs = [":helloworld_proto"],
    grpc_only = True,
    deps = [":helloworld_cc_proto"],
)

cc_binary(
    name = "user_client",
    srcs = ["facade/user_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":helloworld_cc_grpc",
        # http_archive made this label available for binding
        "@com_github_grpc_grpc//:grpc++",
    ],
)

cc_binary(
    name = "greeter_client",
    srcs = ["facade/greeter_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":helloworld_cc_grpc",
        # http_archive made this label available for binding
        "@com_github_grpc_grpc//:grpc++",
    ],
)

cc_library(
    name = "serverLib",
    # ,"greeter_server.cc","deduction_server.cc"
    srcs = [
        "facade/greeter_server.cc",
        "facade/user_server.cc",
        "manager/Greeting.cc",
        "manager/database_manager.cc",
        "manager/redis_manager.cpp",
    ],
    hdrs = [
        "dao/user.h",
        "facade/greeter_server.hpp",
        "facade/user_server.hpp",
        "manager/Greeting.h",
        "manager/database_manager.hpp",
        "manager/redis_manager.hpp",
    ],
    visibility = ["//visibility:public"],
    # defines = ["BAZEL_BUILD"],
    deps = [
        ":hiredis",
        ":helloworld_cc_grpc",
        # http_archive made this label available for binding
        "@com_github_grpc_grpc//:grpc++",
        "@mariadb_connector//:connector",
        "@sqlpp11",
        "@sqlpp11mysql",
    ],
)

cc_binary(
    name = "server_starter",
    srcs = ["server_starter.cc"],
    deps = [
        ":serverLib",
    ],
)
