cc_test(
    name = "tests",
    srcs = [
        "Greeting_test.cc",
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
    linkopts = [
        "-ldl",
        "-lm",
    ],
    deps = [
        "//src:serverLib",
        "@googletest//:gtest_main",
    ],
)
