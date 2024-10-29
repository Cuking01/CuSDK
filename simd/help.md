# cu-SIMD库



### 简介

个人开发的一个 **SIMD** 封装库，主要目的是：

+ 引入更多类型，以简化各种常用操作，提升安全性，包括：
  + 省略指令的各种前后缀，如`_mm256`，`_epi32` 等。
  + 读取和写入以成员函数的形式封装，可以直接 `vec.load(addr)` 等
  + 类型不对的时候编译无法通过。
  + 详见后
+ 严格控制寄存器数量，以防止爆寄存器
  + 所有操作在语义上确保不会引入新的向量寄存器（以及掩码寄存器），除了专门定义寄存器的类型。
  + 实现了一套组件，基于此约定了一套算法接口规范，遵守此规范也可以保证从语义上就不可能引入新的寄存器，无论编译器优化好坏。
  + 详依然见后
+ 方便的循环展开支持
  + 定义了寄存器组这一类型，可以一次性定义多个寄存器，对此类型的操作也可以对每个寄存器分别执行
  + 详还是见后
+ 以及一些其他小功能
+ 并不简化 SIMD 编程的细节，相反，本库几乎暴露了所有细节。

### 引入

引入此库非常简单，只需要 `#include` 两个文件即可，一个是 `basis.h` ，一个是 `simd.h`，然后编译选项自行加上需要链接的指令集，以及`-fno-strict-aliasing` ，并开启至少 `C++23`。

### 寄存器

#### 寄存器类型：

+ 对于向量寄存器，其命名规则为 `V` + `I/U/F` + `width` + `x` +`num`，其中 `V` 表示向量，`I` 表示有符号整型，`U` 表示无符号整型，`F` 表示浮点型，`width` 是单个数据的位宽，可以是 $2^k$ ，$k\in[3,7]$ ，接下来 `x` 表示乘号，`num` 表示数据个数。
  + 例如 `VU32x8` ，表示一个保存 $8$ 个 $32$ 位无符号整型的向量寄存器，总位宽 $256$ ，对应一个 `ymm` 寄存器
  + 再比如 `VF16x32` ，表示一个保存了 $32$ 个半精度浮点数的向量寄存器，总位宽 $512$ ，对应一个 `zmm` 寄存器
+ 对于掩码寄存器，命名规则为 `Mask` + `width` 。`width` 表示掩码寄存器的宽度，可以是 $2^k,k\in[3,6]$ 。
  + 例如 `Mask16` 表示 $16$ 位的掩码寄存器。

#### 加载和写入

以 `VU32x8` 为例：

```c++
VU32x8 vec(addr);  //用地址构造，addr需要uint32*类型，此类型取决于元素类型，默认调用非对齐加载，即_mm256_loadu_si256。
vec.load(addr);   //对齐加载
vec.loadu(addr);  //非对齐加载
vec.stream_load(addr); //不过缓存的直接加载，必须对齐
vec.store(addr);  //对齐写入
vec.storeu(addr); //非对齐写入
vec.stream(addr); //直写内存，必须对齐
vec=v2;           //v2如果是__m256i，可以直接赋值，亦可构造
v2=vec;           //反过来也行
```

对于掩码寄存器暂时只支持从`__maskx` 赋值，或者直接写入指令运算结果。



#### 转型

有时候需要以其他类型进行操作，可以使用`as` ，例如：

```cpp
VU32x8 vec;
vec.as<VU64x4>().load(addr);   //此时addr应该是uint64*
vec.as<VU64x8>();              //错误！转型前后总位宽应该相同
```



#### 指令

目标是封装绝大多数 **SIMD** 指令，但暂时只试验性支持了若干个，举几个有代表性的例子：

```cpp
VI32x8 a(addr1),b(addr2);
a=a+b;   //调用_mm256_add_epi32
b=a-b;   //调用_mm256_sub_epi32
a=shuffle(a,cint<0b1101'1000>);  //调用_mm256_shuffle_epi32
a=set(1,2,3,4,5,6,7,8);          //调用_mm256_setr_spi32
b.as<VI64x4>()=a*b;              //调用_mm256_mul_epi32，注意返回类型要求是VI64x4，所以需要as一下。
a=a&b;                           //调用_mm256_and_si256，换成其他类型进行与运算也都是调用这个函数，注意浮点型不支持此操作，如果需要可以as。
a.storeu(addr3);
b.storeu(addr4);
```



#### 调试输出

有 `to_string` 方法和 `print` 方法，除了调试不建议使用。

`to_string` 返回一个描述内容的字符串。

`print` 可以传入一个提示字符串，先打印此提示字符串，然后打印 `to_string` 的内容。

```cpp
VI32x8 vec(addr);
vec.print("value of vec");
```



### Pack

`Pack` 可以用来一次定义 $n$ 个寄存器，如 `Pack<VF32x16,4>` 就一口气定义了 $4$ 个 `zmm` 寄存器。

#### 加载和写入

`Pack` 支持所有向量寄存器的加载和写入成员函数，并且支持两种调用方法，如下：

```cpp
Pack<VU32x8,4> pv(addr);   //第一种，只写一个地址参数，addr是uint32*，从此地址开始连续加载四个寄存器，也就是分别从addr,addr+8,addr+16,addr+24处加载
pv.load(addr,addr+16,add+32,addr+48);   //第二种，写4个地址，分别从4个指定位置加载，如果地址个数和寄存器个数不匹配，报错
```

#### 转型

`Pack` 也可以用 `as` 转型，但返回的不是 `Pack&` ，而是一个自定义类型 `Pack_Ref` ，后续会介绍。

#### 下标

可以使用下标获取其中的寄存器，如 `p[i]` ，其中 `p` 是一个 `Pack`

#### 指令

`Pack` 也可以直接用向量寄存器的写法进行指令调用：

```cpp
Pack<VI32x8,4> pa(addr1),pb(addr2);
VI32x8 v(addr3);
pa=pa+pb;    //执行pa[i]=pa[i]+pb[i]，其中i从0到3
pa=pa+v;     //也可以加单个向量，相当于pa[i]=pa[i]+v，其中i从0到3
pa.store(addr4);
```

#### 提取

可以获取 `Pack` 中一部分元素的引用,返回类型也是 `Pack_Ref`：

```cpp
Pack<VI32x8,4> pa(addr1);
VI32x8 v(addr2);
pa(2,3)=pa(0,1)+v;     //相当于pa[2]=pa[0]+v,pa[3]=pa[1]+v
pa.store(addr3);
```

也可以重复获取：

```cpp
Pack<VF32x8,4> pa(addr1);
Pack<VF32x8,2> pb(addr2);
Pack<VF32x8,8> pc(addr3);

pc=fmadd(pa(0,1,2,3,0,1,2,3),pb(0,1,0,1,0,1,0,1),pc);  //相当于pc[i*2+j]+=pa[i]*pb[j]，其中i从0到3，j从0到1

pc.store(addr3);
```



### Pack_Ref

`Pack_Ref`  保存若干寄存器的引用，例如：

```cpp
Pack<VI32x8,8> pv;
Pack_Ref<VI32x8,8> pvr(pv);   //pvr[i]引用pv[i]
```

当然 `Pack_Ref` 也可以参与各种指令运算，与 `Pack` 没有区别。

相比于 `Pack&` ，`Pack_Ref` 的特点在于可以保存任意若干个相同或不同的，无关的或有关的寄存器的引用，因此更通用，例如：

```cpp
VI32x8 v1,v2,v3;
Pack_Ref<VI32x8,4> pr(v1,v2,v3,v1);
```

`Pack_Ref` 本身的 `const` 限定**不影响**其引用的寄存器，如果想使用常引用，可以使用 `Pack_CRef` ，但此基本内部使用居多，使用本库时一般用不到。

后续打算更新一个用多个 `Pack` 或者 `Pack_Ref` 拼成一个 `Pack_Ref` 的写法，暂时还没实现。 

### cint与cints

有一些指令要求一些参数是立即数，这里使用 `cint` 和 `cints` 来实现，`cint` 是一个 `CInt` 类型的变量模板，使用方法如下：

```
Pack<VI32x8,8> pa(addr);
pa=shuffle(pa,cint<0b1101'1000>);  //pa[i]=_mm256_shuffle_epi32(pa[i],0b11011000);
pa=shuffle(pa,cints<c0,c1,c2...(省略若干常量)>);   //pa[0]=_mm256_shuffle_epi32(pa[0],c0) ...以此类推

```



### Scale_Pack

有一些指令需要标量参数或者返回值，用法也非常类似 `Pack` ，只不过存储类型为标量。例如：

```
Scale_Pack sp(1,2);  //自动推导为Scale_Pack<int,2>
Pack<VI32x8,2> pv=set(sp,sp,sp,sp,sp,sp,sp,sp);  //把pv[0]设置成8个1，把pv[1]设置成8个2
pv=set(1,1,1,1,1,1,1,1);    //当然，传单个标量也行，这样pv[0]和pv[1]都是纯1
pv=set(1,1,1,1,sp,sp,sp,sp);  //也可以混合，这样pv[0]是纯1，pv[1]前四个是1，后四个是2
sp=reduce_add(pv);    //sp[i]=_mm256_reduce_add_epi32(pv[i]);
```

也有类似的 `Scale_Pack_Ref` ，用法类似 `Pack_Ref` ，不过多介绍了



### 编码规范

总的原则是，严格控制寄存器使用，因此有寄存器的 "定义" "加载" "变换" "写入" 分离。其中定义和加载可以合为一步，其他不能。"变换"仅负责对已定义的寄存器进行操作，而不能定义新的寄存器。因此各种"变换"算法均是传入引用，在已传入的引用上做变换，需要的临时寄存器也从外部传入，外部需要清楚地知道此 "变换" 需要多少寄存器。同时必须声明 `ALWAYS_INLINE` ，较大的函数编译器很可能不内联，又因为是引用从而严重影响性能，内联之后可以消除所有引用。同时，表达式只能是简单形式，不能复合，也是为了控制中间不出现新的寄存器，例如此8x8矩阵转置：

```cpp

ALWAYS_INLINE void Transpose(Pack_Ref<VI32x8,8> mat,Pack_Ref<VI32x8,8> tmp)
{
	tmp(0,1,2,3)=permute2x(mat(0,1,2,3),mat(4,5,6,7),cint<0b0010'0000>);
	tmp(4,5,6,7)=permute2x(mat(0,1,2,3),mat(4,5,6,7),cint<0b0011'0001>);
	mat(0,1,4,5).as<VI64x4>()=unpacklo(tmp(0,1,4,5).as<VI64x4>(),tmp(2,3,6,7).as<VI64x4>());
	mat(2,3,6,7).as<VI64x4>()=unpackhi(tmp(0,1,4,5).as<VI64x4>(),tmp(2,3,6,7).as<VI64x4>());
	tmp=shuffle(mat,cint<0b1101'1000>);
	mat(0,2,4,6)=unpacklo(tmp(0,2,4,6),tmp(1,3,5,7));
	mat(1,3,5,7)=unpackhi(tmp(0,2,4,6),tmp(1,3,5,7));
}

int main()
{
	for(int i=0;i<64;i++)
		a<s2>[i]=rand();
	Pack<VI32x8,8> mat(a<int>),tmp;
	for(int i=0;i<8;i++)
		mat[i].print(std::format("mat[{}]",i));
	Transpose(mat,tmp);
	for(int i=0;i<8;i++)
		mat[i].print(std::format("mat[{}]",i));
}
```



### 指令适配

以 `_mm256_add_epi32` 为例

```cpp
template<typename A,typename B> requires (IFMT<VI32x8,VI32x8>::check<A,B>()&&avx2)
SIMD_OPT auto operator+(const A&a,const B&b)
{
 	return Lazy_Eval_Record<_mm256_add_epi32,VI32x8,A,B>(a,b);
}
```

其中， `IFMT` 是一个指令格式检查工具，`VI32x8` 表示必须是一个此类型的寄存器，或者此类型的 `Pack` , `Pack_Ref` ,`Pack_CRef` 之一。然后 `avx2` 是一个标志，必须开启 `avx2` 才能用。

返回的 `Lazy_Eval_Record` 的第一个参数是实际使用的指令，第二个参数是返回类型，接下来是操作数类型。



再如 `_mm256_and_si256` ：

```
template<typename A,typename B> requires (IFMT<YMM_I,YMM_I>::check<A,B>()&&avx2&&std::same_as<A,B>)
SIMD_OPT auto operator&(const A&a,const B&b)
{
	return Lazy_Eval_Record<_mm256_and_si256,get_reg<A>,A,B>(a,b);
}
```

这次使用的格式说明是 `YMM_I` ，这是所有的存储整数的 `ymm` 寄存器，如 `VU32x8`，`VI64x4` ，都可以。另外限制了两个参数类型必须相同，`Lazy_Eval_Record` 的第二个参数，也就是返回类型，使用了 `get_reg` ，其功能是用来获取其参数的寄存器类型，例如 `get_reg<VI32x8>`  就是 `VI32x8` ，而 `get_reg<Pack<VI32x8,4>>` 也是 `VI32x8` 。这里实际上就是要求参数和返回类型相同。



再如 `_mm256_shuffle_epi32` ：

```cpp
template<typename A,typename M> requires (IFMT<V32x8,FMT_Imm>::check<A,M>()&&avx)
SIMD_OPT auto shuffle(const A&a,const M&m)
{
	return Lazy_Eval_Record<_mm256_shuffle_epi32,get_reg<A>,A,M>(a,m);
}
```

这里引入了 `FMT_Imm` ，表示必须是立即数类型，也就是 `cint` 和 `cints` 。

以及引入了 `V32x8` ，这也是一个格式说明，要求必须是 $8$ 个 $32$ 位的数据，但具体是有符号，无符号，还是浮点型并不关心。



再有就是 `_mm256_setr_epi32` :

```
template<typename... Args> requires (IFMT<s2,s2,s2,s2,s2,s2,s2,s2>::check<Args...>()&&avx)
SIMD_OPT auto set(const Args&... args)
{
	return Lazy_Eval_Record<_mm256_setr_epi32,VI32x8,Args...>(args...);
}
```

其中 `s2` 就是 `int32_t` ，这里主要是引入了标量类型的参数限定。

