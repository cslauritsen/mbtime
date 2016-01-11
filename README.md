mbtime
=======

Introduction
-----------
mbtime is a little library that parses out fields from the undocumented MBTIME01 structure created by IBM Integration Bus aka IIB aka Websphere Message Broker. 

There appear to be more fields in the structure than I was able to reverse engineer, so pull requests are welcome.

INSTALLATION
------------

This library requires cmake & the MQ include files (<cmqc.h>, etc.) to build. It installs the shared library and include files to /usr/local.

Build Procedure:
```
 cd mbtime
 mkdir target
 cmake ..
 make install
 sudo make install
```
