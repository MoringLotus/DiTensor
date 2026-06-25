#pragma once
#include <vector>
#include <memory>
#include "core/types.hpp"

namespace ditensor {
class Tensor {
private:
    std::vector<int> shape_;
    DataType dtype_;
    std::shared_ptr<void> data_ptr_; // 使用 void* 承载所有类型的底层物理内存
    DeviceType device_;

public:
    Tensor(const std::vector<int>& shape,const DeviceType & device,const DataType & dtype);
    ~Tensor();

    Tensor to(DeviceType target) const;

    int ndim() const { return static_cast<int>(shape_.size()); }
    DataType dtype() const { return dtype_; }
    
    // 获取底层指针时，由调用方（Kernel）转换为具体类型
    template<typename T>
    T* data() { 
        return static_cast<T*>(data_ptr_.get()); 
    }
    
    template<typename T>
    const T* data() const { 
        return static_cast<const T*>(data_ptr_.get()); 
    }

    DeviceType device()  { return device_; }
    
    const std::vector<int>& shape() const { return shape_; }

    size_t numel() const {
        int tmp = 1;
        for(int i = 0; i < shape_.size(); i ++){
            tmp *= shape_[i];
        }
        return tmp;
    }
};

} // namespace ditensor
