Import("env")

env.Append(
    CCFLAGS=[
        "-mfpu=fpv4-sp-d16",
        "-mfloat-abi=hard",
    ],
    LINKFLAGS=[
        "-mfpu=fpv4-sp-d16",
        "-mfloat-abi=hard",
    ]
)