package(default_visibility = ["//visibility:public"])

# load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")
load("@rules_foreign_cc//tools/build_defs:make.bzl", "make")
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")
load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")
load("@rules_proto//proto:defs.bzl", "proto_library")
load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

# See https://github.com/bazelbuild/rules_foreign_cc
load("@rules_foreign_cc//tools/build_defs:configure.bzl", "configure_make")
load("@rules_foreign_cc//tools/build_defs:cmake.bzl", "cmake_external")

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

config_setting(
    name = "darwin_build",
    values = {"cpu": "darwin"},
)

# See https://wiki.openssl.org/index.php/Compilation_and_Installation
# See https://github.com/bazelbuild/rules_foreign_cc/issues/338
configure_make(
    name = "openssl",
    configure_command = "config",
    configure_env_vars =
        select({
            ":darwin_build": {
                "OSX_DEPLOYMENT_TARGET": "10.14",
                "AR": "",
            },
            "//conditions:default": {},
        }),
    configure_options =
        select({
            ":darwin_build": [
                "shared",
                "ARFLAGS=r",
                "enable-ec_nistp_64_gcc_128",
                "no-ssl2",
                "no-ssl3",
                "no-comp",
            ],
            "//conditions:default": [
            ],
        }),
    #defines = ["NDEBUG"], Don't know how to use -D; NDEBUG seems to be the default anyway
    lib_source = "@openssl//:all",
    shared_libraries =
        select({
            ":darwin_build": [
                "libssl.dylib",
                "libcrypto.dylib",
            ],
            "//conditions:default": [
                "libssl.so",
                "libcrypto.so",
            ],
        }),
    visibility = ["//visibility:public"],
)

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
        "dal/arrangement_dao.cc",
        "dal/identification_dao.cc",
        "dal/product_dao.cc",
        "dal/user_dao.cc",
        "facade/deduction_facade.cc",
        "facade/greeter_facade.cc",
        "facade/user_facade.cc",
        "manager/Greeting.cc",
        "manager/crypto_manager.cc",
        "manager/database_manager.cc",
        "manager/redis_manager.cpp",
        "manager/snowflake_id_manager.cc",
        "manager/token_manager.cc",
        "util/response_enum.cc",
    ],
    hdrs = [
        "dal/arrangement.h",
        "dal/arrangement_dao.h",
        "dal/arrangement_do.h",
        "dal/base_dao.h",
        "dal/identification.h",
        "dal/identification_dao.h",
        "dal/identification_do.h",
        "dal/product.h",
        "dal/product_dao.h",
        "dal/product_do.h",
        "dal/user.h",
        "dal/user_ar_rel.h",
        "dal/user_ar_rel_do.h",
        "dal/user_dao.h",
        "dal/user_do.h",
        "facade/deduction_facade.h",
        "facade/greeter_facade.hpp",
        "facade/user_facade.h",
        "manager/Greeting.h",
        "manager/crypto_manager.h",
        "manager/database_manager.hpp",
        "manager/redis_manager.hpp",
        "manager/snowflake_id_manager.h",
        "manager/token_manager.h",
        "util/constant.h",
        "util/ident_type_enum.h",
        "util/rel_status_enum.h",
        "util/response_enum.h",
    ],
    linkopts = [
        "-ldl",
        "-lm",
    ],
    visibility = ["//visibility:public"],
    # defines = ["BAZEL_BUILD"],
    deps = [
        ":hiredis",
        ":openssl",
        ":helloworld_cc_grpc",
        # http_archive made this label available for binding
        "@com_github_grpc_grpc//:grpc++",
        "@mariadb_connector//:connector",
        "@sqlpp11",
        "@sqlpp11mysql",
        "@spdlog",
    ],
)

cc_binary(
    name = "server_starter",
    srcs = ["server_starter.cc"],
    deps = [
        ":serverLib",
    ],
)
