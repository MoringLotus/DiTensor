#include "kernel/kernel.hpp"


namespace ditensor {
    class AddKernelCPU : public Kernel {
    public:
        ~AddKernelCPU() override = default;

        DeviceType device_type() const override {
            return DeviceType::CPU;
        }

        void compute(const std::vector<Tensor *> & input, std::vector<Tensor *> &  output);
    };
}
