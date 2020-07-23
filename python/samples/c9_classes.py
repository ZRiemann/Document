#!/usr/bin/python3
#_*_ coding: UTF-8 _*_

import sys

# 9. 类¶
# - 所有成员函数都是 virtual
# - 类继承机制允许多个基类
#
# 9.1. 名称和对象¶
# 别名对涉及可变对象，如列表，字典和大多数其他类型，的Python代码的语义可能会产生惊人的影响。
# 这通常用于程序的好处，因为别名在某些方面表现得像指针。
#
# 9.2. Python 作用域和命名空间¶
# namespace （命名空间）是一个从名字到对象的映射。
# 我把任何跟在一个点号之后的名称都称为 属性
# 一个 作用域 是一个命名空间可直接访问的 Python 程序的文本区域。
# nonlocal 语句声明为非本地变量
# 9.2.1. 作用域和命名空间示例¶
def scope_test():
    def do_local():
        spam = "local spam"

    def do_nonlocal():
        nonlocal spam
        spam = "nonlocal spam"

    def do_global():
        global spam
        spam = "global spam"

    spam = "test spam"
    do_local()
    print("After local assignment:", spam)
    do_nonlocal()
    print("After nonlocal assignment:", spam)
    do_global()
    print("After global assignment:", spam)

scope_test()
print("In global scope:", spam)
# After local assignment: test spam
# After nonlocal assignment: nonlocal spam
# After global assignment: nonlocal spam
# In global scope: global spam

# 9.3.1. 类定义语法¶
#class ClassName:
#    <statement-1>
#    .
#    .
#    .
#    <statement-N>
# 9.3.2. 类对象¶
class MyClass:
    """A simple example class this is __doc__ attribute"""
    i = 12345

    def f(self):
        return 'hello world'
m = MyClass() # 实例化

class Complex:
    def __init__(self, realpart, imagepart):
        self.r = realpart
        self.i = imagepart

x = Complex(3.0, -4.5)
print(f'{x.r} + ({x.i})i')

m.counter = 1 # 动态添加属性
while m.counter < 10:
    m.counter = m.counter * 2
print(m.counter)
del m.counter # 删除属性
# x.f 与 MyClass.f 并不是一回事 --- 它是一个 方法对象，不是函数对象。
# 9.3.4. 方法对象¶
mf = m.f
print('mf = m.f, mf()', mf())

# 9.3.5. 类和实例变量¶
# 实例变量用于每个实例的唯一数据，而类变量用于类的所有实例共享的属性和方法:
class Dog:
    kind = 'canine'         # class variable shared by all instances
    def __init__(self, name):
        self.name = name    # instance variable unique to each instance
d = Dog('Fido')
e = Dog('Buddy')
print(d.kind)                 # shared by all dogs
print(e.kind)
print(d.name)
print(e.name)

# 9.4. 补充说明¶
# 每个值都是一个对象，因此具有 类 （也称为 类型），并存储为 object.__class__

# 9.5. 继承¶
# class DerivedClassName(BaseClassName):
#     pass
# class DerivedClassName(modname.BaseClassName):
#     pass
# 使用 isinstance() 来检查一个实例的类型:
# 使用 issubclass() 来检查类的继承关系:

# 9.5.1. 多重继承¶
# class DerivedClassName(Base1, Base2, Base3):
# 自动计算多重继承的公共祖父类, 避免多次应用

# 9.6. 私有变量¶
# 带有一个下划线的名称 (例如 _spam) 应该被当作是 API 的非公有部分 (无论它是函数、方法或是数据成员)。
# 任何形式为 __spam 的标识符（至少带有两个前缀下划线，至多一个后缀下划线）的文本将被替换
# 为 _classname__spam

# 9.8. 迭代器¶
# 9.9. 生成器¶
# Generator 是一个用于创建迭代器的简单而强大的工具。
