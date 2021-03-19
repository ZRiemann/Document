#!/usr/bin/python3
# _*_ coding: UTF-8 _*_

import sys, fibo

print("dir(<modeule-name>): 用于查找模块定义的名称")
print('dir(fibo):\n', dir(fibo))
print('dir(sys):\n', dir(sys))
print('dir(): 列出当前定义的名称\n', dir())

"""
sound/                          Top-level package
      __init__.py               Initialize the sound package
      formats/                  Subpackage for file format conversions
              __init__.py
              wavread.py
              wavwrite.py
              aiffread.py
              aiffwrite.py
              auread.py
              auwrite.py
              ...
      effects/                  Subpackage for sound effects
              __init__.py
              echo.py
              surround.py
              reverse.py
              ...
      filters/                  Subpackage for filters
              __init__.py
              equalizer.py
              vocoder.py
              karaoke.py
              ...
文件 sound/effects/__init__.py 可以包含以下代码:
__all__ = ["echo", "surround", "reverse"]

from . import echo
from .. import formats
from ..filters import equalizer
"""