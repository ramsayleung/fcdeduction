load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

git_repository(
    name = "googletest",
    remote = "https://github.com/google/googletest",
    tag = "release-1.8.1",
)

new_git_repository(
    name = "hinnant_date",
    build_file = "//:third-party/date/BUILD.bzl",
    tag = "v2.4.1",
    remote = "https://github.com/HowardHinnant/date.git",
)

new_git_repository(
    name = "sqlpp11",
    build_file = "//:third-party/sqlpp11/BUILD.bzl",
    remote = "https://github.com/rbock/sqlpp11.git",
    tag = "0.58"
)


# new_git_repository(
#     name = "sqlpp11postgresql",
#     build_file = "//:third-party/sqlpp11postgresql/BUILD.bzl",
#     remote = "https://github.com/matthijs/sqlpp11-connector-postgresql.git",
#     tag = "v0.54"
# )

new_git_repository(
    name = "sqlpp11mysql",
    build_file = "//:third-party/sqlpp11mysql/BUILD.bzl",
    remote = "https://github.com/rbock/sqlpp11-connector-mysql.git",
    tag = "0.29"
)

new_git_repository(
    name = "mariadb_connector",
    build_file = "//:third-party/mariadb_connector/BUILD.bzl",
    commit = "184a16d2f1d0bb24bea6bcf23e1604093fef8f93",
    remote = "https://github.com/MariaDB/mariadb-connector-c.git",
)

##### Protobuf Rules for Bazel
##### See https://github.com/bazelbuild/rules_proto
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_proto",
    sha256 = "602e7161d9195e50246177e7c55b2f39950a9cf7366f74ed5f22fd45750cd208",
    strip_prefix = "rules_proto-97d8af4dc474595af3900dd85cb3a29ad28cc313",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
        "https://github.com/bazelbuild/rules_proto/archive/97d8af4dc474595af3900dd85cb3a29ad28cc313.tar.gz",
    ],
)
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

##### gRPC Rules for Bazel
##### See https://github.com/grpc/grpc/blob/master/src/cpp/README.md#make
http_archive(
    name = "com_github_grpc_grpc",
    urls = [
        "https://github.com/grpc/grpc/archive/de893acb6aef88484a427e64b96727e4926fdcfd.tar.gz",
    ],
    strip_prefix = "grpc-de893acb6aef88484a427e64b96727e4926fdcfd",
)
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
# Not mentioned in official docs... mentioned here https://github.com/grpc/grpc/issues/20511
load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()



# Group the sources of the library so that CMake rule have access to it
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

# Rule repository
http_archive(
    name = "rules_foreign_cc",
    strip_prefix = "rules_foreign_cc-master",
    url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies(register_default_tools = True)

# Hiredis
http_archive(
    name = "hiredis",
    build_file_content = all_content,
    strip_prefix = "hiredis-0.14.1",
    urls = ["https://github.com/redis/hiredis/archive/v0.14.1.tar.gz"],
)


# # https://github.com/HowardHinnant/date/archive/v2.4.1.tar.gz
# http_archive(
#     name = "date",
#     build_file_content = all_content,
#     strip_prefix = "date-2.4.1",
#     urls = ["https://github.com/HowardHinnant/date/archive/v2.4.1.tar.gz"],
# )

# # sqlpp11
# http_archive(
#     name = "sqlpp11",
#     build_file_content = all_content,
#     strip_prefix = "sqlpp11-0.58",
#     urls = ["https://github.com/rbock/sqlpp11/archive/0.58.tar.gz"],
# )

# https://github.com/matthijs/sqlpp11-connector-postgresql/archive/v0.54.tar.gz 

# sqlpp11-connector-postgresql
# http_archive(
#     name = "pgconnector",
#     build_file_content = all_content,
#     strip_prefix = "sqlpp11-connector-postgresql-0.54",
#     urls = ["https://github.com/matthijs/sqlpp11-connector-postgresql/archive/v0.54.tar.gz "],
# )
