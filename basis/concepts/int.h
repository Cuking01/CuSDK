#pragma once

template<typename T,uint32_t bits>
concept uint_at_least=std::unsigned_integral<T>&&sizeof(T)*8>=bits;

template<typename T,uint32_t bits>
concept sint_at_least=std::signed_integral<T>&&sizeof(T)*8>=bits;


