cc_library(
    name = "spdlog",
    hdrs = glob(["include/**"]),
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    # deps = ["@hinnant_date//:date"],
)