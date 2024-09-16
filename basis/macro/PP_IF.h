#pragma once

#define PP_IF_0(b1,b2) b2
#define PP_IF_1(b1,b2) b1

#define PP_IF_IMPL(b,b1,b2) PP_CONCAT(PP_IF_,PP_BOOL(b))(b1,b2)
