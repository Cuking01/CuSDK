
if(TARGET CuSDK::Basis)
  return()
endif()

#Basis
add_library(CuSDK::Basis INTERFACE)
target_compile_features(CuSDK::Basis INTERFACE cxx_std_23)
target_include_directories(CuSDK::Basis INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}include/basis"
)


add_library(CuSDK::Audio INTERFACE)
target_include_directories(CuSDK::Audio INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}/include/audio"
)
target_link_libraries(CuSDK::Audio INTERFACE CuSDK::Basis)


add_library(CuSDK::Algorithm INTERFACE)
target_include_directories(CuSDK::Algorithm INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}/include/algorithm"
)
target_link_libraries(CuSDK::Algorithm INTERFACE CuSDK::Basis)


add_library(CuSDK::SIMD INTERFACE)
target_include_directories(CuSDK::SIMD INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}/include/simd"
)
target_link_libraries(CuSDK::Algorithm INTERFACE CuSDK::Basis)
target_compile_options(CuSDK::SIMD INTERFACE
  -fno-strict-aliasing
)





