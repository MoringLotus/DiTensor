#include <gtest/gtest.h>
#include <vector>
#include "tensor.hpp"
#include "operator/add_operator.hpp"

namespace ditensor {

TEST(AddOpTest, CUDAForwardBasic) {
    // 1. 设定矩阵形状 (以 2x3 的矩阵为例，共 6 个元素)
    std::vector<int> shape = {2, 3};
    int numel = 6;

    // 2. 在 CPU 上创建源数据张量
    // 🛠️ 已对齐你的标准顺序：(shape, device, dtype)
    Tensor x_cpu(shape, DeviceType::CPU, DataType::FLOAT32);
    Tensor y_cpu(shape, DeviceType::CPU, DataType::FLOAT32);

    // 3. 填充 CPU 测试数据
    float* x_ptr = x_cpu.data<float>();
    float* y_ptr = y_cpu.data<float>();
    for (int i = 0; i < numel; ++i) {
        x_ptr[i] = static_cast<float>(i + 1);        // [1.0, 2.0, 3.0, 4.0, 5.0, 6.0]
        y_ptr[i] = static_cast<float>((i + 1) * 10); // [10.0, 20.0, 30.0, 40.0, 50.0, 60.0]
    }

    // 4. 一键搬运到 GPU 
    Tensor x_cuda = x_cpu.to(DeviceType::CUDA);
    Tensor y_cuda = y_cpu.to(DeviceType::CUDA);

    // 5. 在 GPU 上创建用于接收结果的空 Tensor 壳子
    // 🛠️ 同样对准顺序：(shape, device, dtype)
    Tensor z_cuda(shape, DeviceType::CUDA, DataType::FLOAT32);

    // 6. 实例化算子并分发 GPU 任务
    AddOperator add_op;
    std::vector<Tensor*> inputs = {&x_cuda, &y_cuda};
    std::vector<Tensor*> outputs = {&z_cuda};
    
    add_op.forward(inputs, outputs);

    // 7. 把 GPU 上的计算结果拉回 CPU 准备断言
    Tensor z_cpu = z_cuda.to(DeviceType::CPU);
    const float* res_ptr = z_cpu.data<float>();

    // 8. 验证每一个元素的计算正确性
    float expected_data[6] = {11.0f, 22.0f, 33.0f, 44.0f, 55.0f, 66.0f};
    for (int i = 0; i < numel; ++i) {
        EXPECT_FLOAT_EQ(res_ptr[i], expected_data[i]) 
            << "Mismatch detected at index " << i;
    }
}

} // namespace ditensor
