project('connected-clock', 'cpp')

src = ['src/main.cpp', 'src/sound.cpp', 'src/clock.cpp', 'src/cuckoo.cpp', 'src/westminster.cpp']
incdir = include_directories('src')

boost_dep = dependency('boost', modules : ['log', 'program_options', 'system'])
gst_dep = dependency('gstreamer-1.0')
thread_dep = dependency('threads')

executable('connected-clock', src,
           include_directories : incdir,
           dependencies : [boost_dep, gst_dep, thread_dep],
           cpp_args : '-DBOOST_LOG_DYN_LINK',
           link_args : '-Wall',
           install: true)

install_subdir('data',
               install_dir : '/etc/connected-clock',
               strip_directory : true)

