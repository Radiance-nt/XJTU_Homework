# 面向对象程序设计题目3.2

#### 

### 题目要求

	1、定义一个类，其中有静态数据成员、各种类型非静态数据成员（含字符指针），甚至包括引用（可选，不要求），静态和非静态成员函数（含分配空间的构造函数、析构函数）。
	 2、定义全局对象、main函数中局部对象、另一个被main调用的外部函数func中定义局部对象（可以是形参），main函数中动态创建对象，每种对象至少2个。观察、分析各种对象地址。
	 3、输出对象中各个静态与非静态数据成员的值、地址、对象的存储空间大小等信息。由此理解对象的本质、静态数据成员是本类对象共享一份拷贝等问题。
	 4、对于上述各种对象，输出静态非静态成员函数地址，以及main、func的地址，并分析。

### 题解

定义`MyClass`类

1、定义一个类，其中有静态数据成员、各种类型非静态数据成员（含字符指针），引用，静态和非静态成员函数，静态和非静态成员函数

```c++
#include <iostream>
using namespace std;

class MyClass {
public:
    static int static_var;

    int non_static_var;
    char* char_ptr;
    int& ref_var;

    MyClass(int n_var, char* ptr, int& ref): non_static_var(n_var), char_ptr(ptr), ref_var(ref) {
        cout << "Constructing MyClass object..." << endl;
    }

    ~MyClass() {
        cout << "Destructing MyClass object..." << endl;
    }

    static void static_func() {
        cout << "Calling static function." << endl;
    }

    void non_static_func() {
        cout << "Calling non-static function." << endl;
    }
};

int MyClass::static_var = 0;
```

2、定义两个函数，分别为值传递和引用传递

在函数`func`中，定义了两个**局部对象**

```c++

void func(MyClass obj)
{
    cout << "In func, object address: " << &obj << endl;

    
    MyClass func_obj1(3, "Func Object", func_obj1.non_static_var);
    cout << "Func object address: " << &func_obj1 << endl
         << endl;

    MyClass func_obj2(4, "Func Object", func_obj2.non_static_var);
    cout << "Func object address: " << &func_obj2 << endl
         << endl;

}


void ref_func(MyClass &obj)
{
    cout << "Ref object address: " << &obj << endl;
}

```

我们再定义两个**全局对象**


```c++
MyClass global_obj1(1, "Global Object", MyClass::static_var);
MyClass global_obj2(2, "Global Object", MyClass::static_var);
```

在`main`函数中，我们先后定义两个**局部对象**，两个**动态对象**，并将对象传入值传递的函数`func`和引用传递的函数`ref_func`

```c++
int main()
{
    MyClass local_obj1(3, "Local Object", local_obj1.non_static_var);
    MyClass local_obj2(4, "Local Object", local_obj2.non_static_var);

    MyClass *dynamic_obj1 = new MyClass(5, "Dynamic Object 1", global_obj1.non_static_var);

    MyClass *dynamic_obj2 = new MyClass(6, "Dynamic Object 2", global_obj2.non_static_var);
    
    func(local_obj1);
    ref_func(local_obj2);

}
```

### 输出各个数据成员信息

输出对象中各个静态与非静态数据成员的值、地址、对象的存储空间大小等信息

使用类似下列语句输出了全局对象变量的地址、存储空间大小、非静态成员变量的地址和字符指针非静态成员变量的地址。*注：完整代码放在报告结尾*

```c++
cout << "Global object address: " << &global_obj1 << endl
    << "Global object size: " << sizeof(global_obj1) << endl
    << "Global object non-static var address: " << &global_obj1.non_static_var << endl
    << "Global object char pointer address: " << (void *)global_obj1.char_ptr << endl
    << endl;
```

**全局变量**地址及大小

```
Global object address: 0x407038
Global object size: 12
Global object non-static var address: 0x407038
Global object char pointer address: 0x405380  

Global object address: 0x407044
Global object size: 12
Global object non-static var address: 0x407044
Global object char pointer address: 0x405380
```

本次实验在`Windows`上进行，编译器为 `MingW32'，`Char * ` 为4字节，因此对象大小为12字节。

`main`中**局部变量**地址及大小

```
Local object address: 0x61fe90
Local object size: 12
Local object non-static var address: 0x61fe90
Local object char pointer address: 0x4051b1

Local object address: 0x61fe84
Local object size: 12
Local object non-static var address: 0x61fe84
Local object char pointer address: 0x4051b1
```

`func`中**局部变量**地址及大小

```
Call func
In func, object address: 0x61fe9c
Constructing MyClass object...
Func object address: 0x61fe54
Func object size: 12
Func object non-static var address: 0x61fe54
Func object char pointer address: 0x40509f

Constructing MyClass object...
Func object address: 0x61fe48
Func object size: 12
Func object non-static var address: 0x61fe48
Func object char pointer address: 0x40509f
```

值得注意的是，通过值传递时会调用默认的拷贝构造函数，所以地址和`local_obj1`中的地址不一样。使用引用可以避免拷贝，即

`ref_func`中使用引用传递

```
Call ref func
Ref object address: 0x61fe84
```

可以看到此时地址和`local_obj1`中的地址一样了。

**动态变量**地址及大小

```
Dynamic object 1 address: 0xfb1a78
Dynamic object 1 size: 12
Dynamic object 1 non-static var address: 0xfb1a78
Dynamic object 1 char pointer address: 0x405250

Constructing MyClass object...
Dynamic object 2 address: 0xfb1aa0
Dynamic object 2 size: 12
Dynamic object 2 non-static var address: 0xfb1aa0
Dynamic object 2 char pointer address: 0x4052e8
```

- 对象的存储空间大小为12个字节，其中包含了一个整型静态成员变量、一个整型非静态成员变量、一个字符指针非静态成员变量和一个整型引用非静态成员变量。
- 对象的地址在内存中是连续的
- 静态成员变量被所有对象共享，其地址与对象的地址不连续。静态变量的地址都相同，且与类定义时声明的静态变量地址相同。
- 不同对象的非静态成员变量地址不同，且对象的地址和非静态成员变量的地址之间相差8个字节（64位系统下）。
- 动态分配的对象的地址在内存中是不连续的，其地址和非静态成员变量的地址之间相差8个字节。

### 输出函数地址

分别对输出了局部对象和全局对象的静态函数和非静态函数地址

```c++
     cout << "Local Obj Static function address: " << reinterpret_cast<void *>(&local_obj1.static_func) << std::endl;
     cout << "Local Obj Non-Static function address: " << reinterpret_cast<void *>(&local_obj1.non_static_func) << std::endl;

     cout << "Global Obj Static function address: " << reinterpret_cast<void *>(&global_obj1.static_func) << std::endl;
     cout << "Global Obj Non-Static function address: " << reinterpret_cast<void *>(&global_obj1.non_static_func) << std::endl;

     cout << "Static function address: " << reinterpret_cast<void *>(&MyClass::static_func) << std::endl;
     cout << "Non-static function address: " << reinterpret_cast<void *>(&MyClass::non_static_func) << std::endl;
     cout << "main function address: " << reinterpret_cast<void *>(&main) << std::endl;
     cout << "func function address: " << reinterpret_cast<void *>(&func) << std::endl;
```

输出：

```
Local Obj Static function address: 0x403430
Local Obj Non-Static function address: 0x403460
Global Obj Static function address: 0x403430
Global Obj Non-Static function address: 0x403460
Static function address: 0x403430
Non-static function address: 0x403460
main function address: 0x401753
func function address: 0x4015c0
```

可以看到，静态函数、非静态函数都有一个固定的地址，与各个对象无关。

`main`函数、`func`函数也有一个固定的地址，与各个对象无关。

### 完整代码

```c++
#include <iostream>
using namespace std;

class MyClass
{
public:
     static int static_var;

     int non_static_var;
     char *char_ptr;
     int &ref_var;

     MyClass(int n_var, char *ptr, int &ref) : non_static_var(n_var), char_ptr(ptr), ref_var(ref)
     {
          cout << "Constructing MyClass object..." << endl;
     }

     ~MyClass()
     {
          cout << "Destructing MyClass object..." << endl;
     }

     static void static_func()
     {
          cout << "Calling static function." << endl;
     }

     void non_static_func()
     {
          cout << "Calling non-static function." << endl;
     }
};

int MyClass::static_var = 0;

void func(MyClass obj)
{
     cout << "In func, object address: " << &obj << endl;

     MyClass func_obj1(3, "Func Object", func_obj1.non_static_var);
     cout << "Func object address: " << &func_obj1 << endl
          << "Func object size: " << sizeof(func_obj1) << endl
          << "Func object non-static var address: " << &func_obj1.non_static_var << endl
          << "Func object char pointer address: " << (void *)func_obj1.char_ptr << endl
          << endl;

     MyClass func_obj2(4, "Func Object", func_obj2.non_static_var);
     cout << "Func object address: " << &func_obj2 << endl
          << "Func object size: " << sizeof(func_obj2) << endl
          << "Func object non-static var address: " << &func_obj2.non_static_var << endl
          << "Func object char pointer address: " << (void *)func_obj2.char_ptr << endl
          << endl;
}
void ref_func(MyClass &obj)
{
     cout << "Ref object address: " << &obj << endl;
}

MyClass global_obj1(1, "Global Object", MyClass::static_var);
MyClass global_obj2(2, "Global Object", MyClass::static_var);

int main()
{

     cout << "Global object address: " << &global_obj1 << endl
          << "Global object size: " << sizeof(global_obj1) << endl
          << "Global object non-static var address: " << &global_obj1.non_static_var << endl
          << "Global object char pointer address: " << (void *)global_obj1.char_ptr << endl
          << endl;

     cout << "Global object address: " << &global_obj2 << endl
          << "Global object size: " << sizeof(global_obj2) << endl
          << "Global object non-static var address: " << &global_obj2.non_static_var << endl
          << "Global object char pointer address: " << (void *)global_obj2.char_ptr << endl
          << endl;

     MyClass local_obj1(3, "Local Object", global_obj1.non_static_var);
     cout << "Local object address: " << &local_obj1 << endl
          << "Local object size: " << sizeof(local_obj1) << endl
          << "Local object non-static var address: " << &local_obj1.non_static_var << endl
          << "Local object char pointer address: " << (void *)local_obj1.char_ptr << endl
          << endl;

     MyClass local_obj2(4, "Local Object", global_obj1.non_static_var);
     cout << "Local object address: " << &local_obj2 << endl
          << "Local object size: " << sizeof(local_obj2) << endl
          << "Local object non-static var address: " << &local_obj2.non_static_var << endl
          << "Local object char pointer address: " << (void *)local_obj2.char_ptr << endl
          << endl;

     cout << "Call func" << endl;
     func(local_obj1);

     cout << endl
          << "Call ref func" << endl;
     ref_func(local_obj2);

     MyClass *dynamic_obj1 = new MyClass(5, "Dynamic Object 1", global_obj1.non_static_var);
     cout << "Dynamic object 1 address: " << dynamic_obj1 << endl
          << "Dynamic object 1 size: " << sizeof(*dynamic_obj1) << endl
          << "Dynamic object 1 non-static var address: " << &dynamic_obj1->non_static_var << endl
          << "Dynamic object 1 char pointer address: " << (void *)dynamic_obj1->char_ptr << endl
          << endl;

     MyClass *dynamic_obj2 = new MyClass(6, "Dynamic Object 2", global_obj2.non_static_var);
     cout << "Dynamic object 2 address: " << dynamic_obj2 << endl
          << "Dynamic object 2 size: " << sizeof(*dynamic_obj2) << endl
          << "Dynamic object 2 non-static var address: " << &dynamic_obj2->non_static_var << endl
          << "Dynamic object 2 char pointer address: " << (void *)dynamic_obj2->char_ptr << endl
          << endl;

     delete dynamic_obj1;
     delete dynamic_obj2;

     cout << "Local Obj Static function address: " << reinterpret_cast<void *>(&local_obj1.static_func) << std::endl;
     cout << "Local Obj Non-Static function address: " << reinterpret_cast<void *>(&local_obj1.non_static_func) << std::endl;

     cout << "Global Obj Static function address: " << reinterpret_cast<void *>(&global_obj1.static_func) << std::endl;
     cout << "Global Obj Non-Static function address: " << reinterpret_cast<void *>(&global_obj1.non_static_func) << std::endl;

     cout << "Static function address: " << reinterpret_cast<void *>(&MyClass::static_func) << std::endl;
     cout << "Non-static function address: " << reinterpret_cast<void *>(&MyClass::non_static_func) << std::endl;
     cout << "main function address: " << reinterpret_cast<void *>(&main) << std::endl;
     cout << "func function address: " << reinterpret_cast<void *>(&func) << std::endl;
     return 0;
}
```

### 针对引用成员的补充说明

我们设计以下代码，代码定义了一个名为 `MyClass` 的类，其中有一个成员变量 `ref_var`，类型为 `MyType` 的引用。在构造函数中，将传入的引用 `ref` 赋值给 `ref_var`。

```c++
#include <iostream>
using namespace std;

typedef char MyType;
class MyClass
{
public:
     MyType &ref_var;
     MyClass(MyType &ref) : ref_var(ref)
     {
          cout << "Constructing MyClass object..." << endl;
     }
};
MyType a = 1;
MyClass global_obj1(a);

int main()
{
     cout << "Global object size: " << sizeof(global_obj1) << endl
          << "MyType size: " << sizeof(global_obj1.ref_var) << endl
          << endl;

     return 0;
}
```

该代码输出为

```bash
Constructing MyClass object...
Global object size: 4
MyType size: 1
```

在C++中，引用变量在编译时被转换为指针，并且在运行时分配内存空间来存储指向实际对象的地址。这是为了确保引用始终引用有效的对象。`MyClass`类中的成员变量 `int& ref_var` 是一个引用类型。尽管引用本身不占用额外的存储空间，但引用变量在实际使用时需要指向一个有效的对象。

`sizeof(global_obj1)` 的结果为 4，是因为 `ref_var` 成员变量实际上是一个指针大小（当前为 4 字节，取决于系统架构）。它存储了引用的地址，而不是引用的对象本身。

在`3.2`代码中，我们将引用成员传入构造函数，假设使用引用传递，则不会发生复制。若我们用相同值传入不同对象的构造函数里，引用成员的地址相同。

```cpp
 MyClass(int n_var, char *ptr, int &ref) : non_static_var(n_var), char_ptr(ptr), ref_var(ref)
```

输出如下，已省略不必要的信息。

```bash
Global object address: 0x407038
Global object ref var pointer address: 0x407034

Global object address: 0x407044  
Global object ref var pointer address: 0x407034

Constructing MyClass object...
Local object ref var pointer address: 0x407034

Constructing MyClass object...
Local object ref var pointer address: 0x407034
```



