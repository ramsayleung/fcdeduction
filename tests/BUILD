cc_test(
    name = "tests",
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
    srcs = ["db_test.cc"],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)
