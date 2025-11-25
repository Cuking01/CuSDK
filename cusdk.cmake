
if(TARGET CuSDK_Basis)
  return()
endif()

#Basis
add_library(CuSDK_Basis INTERFACE)
target_compile_features(CuSDK_Basis INTERFACE cxx_std_23)
target_include_directories(CuSDK_Basis INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}/include/basis"
)


add_library(CuSDK_Audio INTERFACE)
target_include_directories(CuSDK_Audio INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}/include/audio"
)
target_link_libraries(CuSDK_Audio INTERFACE CuSDK_Basis)


add_library(CuSDK_Algorithm INTERFACE)
target_include_directories(CuSDK_Algorithm INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}/include/algorithm"
)
target_link_libraries(CuSDK_Algorithm INTERFACE CuSDK_Basis)


add_library(CuSDK_SIMD INTERFACE)
target_include_directories(CuSDK_SIMD INTERFACE 
  "${CMAKE_CURRENT_LIST_DIR}/include/simd"
)
target_link_libraries(CuSDK_Algorithm INTERFACE CuSDK_Basis)
target_compile_options(CuSDK_SIMD INTERFACE
  -fno-strict-aliasing
)





