#include "operator/add_operator.hpp"
#include "kernel/cpu/add_kernel_cpu.hpp"   // 引入具体的 CPU 算子实现
//#include "kernel/cuda/add_kernel.h"  // 引入具体的 CUDA 算子实现
#include <stdexcept>

namespace ditensor {

void launch_add_cuda(const float * x, const float * y, float * z, int numel);

void AddOperator::infer_shape(const std::vector<Tensor*>& inputs,
                        std::vector<std::vector<int>>& output_shapes) {
    // 简单校验后直接推导
    if (inputs.size() != 2) throw std::runtime_error("AddOp requires 2 inputs.");
    output_shapes[0] = inputs[0]->shape();
}

void AddOperator::forward(const std::vector<Tensor*>& inputs,
                    std::vector<Tensor*>& outputs) {
    
    // 1. 获取输入 Tensor 的设备类型 (CPU 或 CUDA)
    DeviceType device = inputs[0]->device(); 

    // 2. 转换为 Kernel 需要的 const 视图
    std::vector<Tensor*> const_inputs(inputs.begin(), inputs.end());

    // 3. 简单粗暴的 if-else 分发
    if (device == DeviceType::CPU) {
        // 在栈上直接创建局部对象，函数结束自动释放，连内存管理的脑细胞都省了
        AddKernelCPU kernel; 
        kernel.compute(const_inputs, outputs);
    } 
    else if (device == DeviceType::CUDA) {
        int numel = inputs[0]->numel();
        const float* d_x = inputs[0]->data<float>();
        const float* d_y = inputs[0]->data<float>();
        float * d_z      = outputs[0]->data<float>();
        launch_add_cuda(d_x, d_y, d_z, numel);
    } 
    else {
        throw std::runtime_error("AddOp: Unsupported device type.");
    }
}

} // namespace ditensor
