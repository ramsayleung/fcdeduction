cc_test(
    name = "tests",
    timeout = "short",
    srcs = [
        "greeting_test.cc",
    ],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "redis_test",
    timeout = "short",
    srcs = [
        "redis_manager_test.cc",
    ],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "db_test",
    timeout = "short",
    srcs = ["db_test.cc"],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "user_dao_test",
    timeout = "short",
    srcs = ["user_dao_test.cc"],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "token_manager_test",
    timeout = "short",
    srcs = ["token_manager_test.cc"],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "crypto_manager_test",
    timeout = "short",
    srcs = ["crypto_manager_test.cc"],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "product_dao_test",
    timeout = "short",
    srcs = ["product_dao_test.cc"],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "arrangement_dao_test",
    timeout = "short",
    srcs = ["arrangement_dao_test.cc"],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "identification_dao_test",
    timeout = "short",
    srcs = ["identification_dao_test.cc"],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "user_facade_test",
    timeout = "short",
    srcs = ["user_facade_test.cc"],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "snowflake_id_manager_test",
    timeout = "short",
    srcs = ["snowflake_id_manager_test.cc"],
    linkopts = ["-lpthread "],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)
