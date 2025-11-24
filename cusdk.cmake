
if(TARGET CuSDK)
  return()
endif()

add_library(CuSDK INTERFACE)

#设置 include 目录
target_include_directories(CuSDK INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}/include"
)

#最低需要 C++23 标准
target_compile_features(CuSDK INTERFACE
  cxx_std_23
)

# -fno-strict-aliasing 会被添加到链接 target 的编译选项中
target_compile_options(CuSDK INTERFACE
  -fno-strict-aliasing
)

