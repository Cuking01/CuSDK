#pragma once

#define PP_POW2_0 1
#define PP_POW2_1 2
#define PP_POW2_2 4
#define PP_POW2_3 8
#define PP_POW2_4 16
#define PP_POW2_5 32
#define PP_POW2_6 64
#define PP_POW2_7 128
#define PP_POW2_8 256
#define PP_POW2_9 512
#define PP_POW2_10 1024

#define PP_POW2_IMPL(x) PP_CONCAT(PP_POW2_,x)
