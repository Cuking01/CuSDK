#pragma once

template<typename... Ts>
concept Not_Empty_Pack=sizeof...(Ts)>=1;

template<template<typename...> typename Template,typename Ins>
concept Instance_Of=is_instance_of_v<Template,Ins>;

