Connected Clock
===============

Connected clock is a C++ program reproducing a church clock sound. This application uses the system audio output following public clock rules.

Clock audio output matrix:

| | **Type of melody** | **Hour count** |
|---|:---:|:---:|
|**00 min** | Hour | X |
|**05 min** | Hour | X |
|**15 min** | Quarter | - |
|**30 min** | Half | - |
|**45 min** | Three quarter | - |

Dependencies
------------

Connected clock program uses GStreamer for audio output and Boost libraries for timer, program options and log. 

For more informations about Boost: http://www.boost.org/
For more informations about GStreamer: http://gstreamer.freedesktop.org/

Build
-----

This project use Meson as build system: http://mesonbuild.com/index.html

`$ meson build && cd build`

`$ ninja`

`$ sudo ninja install`

Run
---

To launch the connected clock program in Big Ben style with a volume of 5%:

`$ connected-clock -c westminster -p /etc/connected-clock/westminster/bigben -v 5`

To launch the connected clock program in Cuckoo clock style with a volume of 10%:

`$ connected-clock -c cuckoo -p /etc/connected-clock/cuckoo/classic -v 10`


