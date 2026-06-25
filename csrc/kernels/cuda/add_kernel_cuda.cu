#include <cuda_runtime.h>

namespace ditensor {
     __global__ void add_kernel_cuda(const float * x, const float* y, float* z, int numel){
          int idx = threadIdx.x + blockIdx.x * blockDim.x;
          if(idx < numel){
                 z[idx] = x[idx] + y[idx];
          }
     }

     void launch_add_cuda(const float * x, const float * y, float * z, int numel){
          int block_size = 256;
          int grid_size = (numel + block_size - 1) / block_size;

          add_kernel_cuda<<<grid_size, block_size>>>(x, y, z, numel);

          cudaDeviceSynchronize();
     }
}

