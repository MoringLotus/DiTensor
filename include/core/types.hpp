#pragma once

namespace ditensor {
    enum class DeviceType {
        CPU = 0,
        CUDA = 1,
        NPU = 1
    };

    enum class DataType {
        FLOAT32 = 0,
        INT32 = 1,
        FLOAT16 = 2
    };
}
