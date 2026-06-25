#pragma once
#include <vector>
#include "kernel/kernel.hpp"
#include "tensor.hpp"

namespace ditensor {


class AddKernelCPU : public Kernel {
public:
    AddKernelCPU() = default;
    ~AddKernelCPU() override = default;
    DeviceType device_type() const override { return DeviceType::CPU; }
    void compute(const std::vector<Tensor*>& inputs,
                 std::vector<Tensor*>& outputs) override;
};


} // namespace ditensor
