# third_party/glm/BUILD

load("@rules_cc//cc:defs.bzl", "cc_library")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "glm",
    hdrs = glob([
        "glm/**/*.h",
        "glm/**/*.hpp",
        "glm/**/*.inl",
    ]),
    includes = ["glm"],
    visibility = ["//visibility:public"],
)
