#pragma once
#include "operator/operator.hpp"
#include "kernel/kernel.hpp"

namespace ditensor {
    class AddOperator : public Operator {
    public:
        AddOperator() = default;
        ~AddOperator()  = default;
        
        std::string get_name() const override { return "AddOperator";}
        void infer_shape(const std::vector<Tensor*>& inputs,
                     std::vector<std::vector<int>>& output_shapes) override;
        void forward(const std::vector<Tensor*>& inputs,
                 std::vector<Tensor*>& outputs) override;
        
    };
}
