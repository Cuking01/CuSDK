#pragma once

template<typename... Ts>
concept Not_Empty_Pack=sizeof...(Ts)>=1;

