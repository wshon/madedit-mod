Minipython is based on http://www.adintr.com/article/blog/281(Python 2.7.2). I updated it to 2.7.8.

Based on the description from the author:
1. ȥ�� python �������� Python Դ����ı�׼�������. 
2. ȥ����һ�µ�һЩģ��: cPickle, _io, datetime,  _random, cStringIO, _lsprof, _collections, _struct, _sre, time, _locale, _headq, _functools, _weakref, itertools
3. ȥ�����������ڽ��Ķ���: bytearray,  memoryobject

English:
1. Removed the dependency between Python interpreter and Python source code standard library.
2. Removed internal modules: cPickle, _io, datetime,  _random, cStringIO, _lsprof, _collections, _struct, _sre, time, _locale, _headq, _functools, _weakref and itertools
3. Removed internal objects: bytearray,  memoryobject