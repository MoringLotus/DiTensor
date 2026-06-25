#pragma once
#include <string>
#include "tensor.hpp"
#include <vector>
#include "core/types.hpp"

namespace ditensor {
    class Kernel {
        public:
        virtual ~Kernel()  = default;
        virtual DeviceType device_type() const = 0;
        virtual void compute(const std::vector<Tensor *> & inputs,
                             std::vector<Tensor *> & outputs) = 0;
        
    };
}
