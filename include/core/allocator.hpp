#pragma once
#include <map>
#include <mutex>
#include <cstdlib>
#include <iostream>

namespace ditensor {
    class Allocator {
    public:
        static Allocator& instance() {
            static Allocator allocator;
            return allocator;
        }
        void* allocate(size_t bytes){
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = free_blocks_.lower_bound(bytes);
            if(it != free_blocks_.end()){
                void* ptr = it->second;
                free_blocks_.erase(it);
                return ptr;
            }
            return std::malloc(bytes);
        }

        void deallocate(void* ptr, size_t bytes){
           if(!ptr) return;
           std::lock_guard<std::mutex> lock(mutex_);

           free_blocks_.insert({bytes, ptr});
        }
    ~Allocator() {
        for(auto & pair : free_blocks_){
            std::free(pair.second);
        }
        free_blocks_.clear();
    }

   private:
    Allocator() = default;
    std::multimap<size_t, void*> free_blocks_;
    std::mutex mutex_;
};
}
