project('your_project', 'cpp', version : '0.1')

gtest_dep = dependency('gtest', main : true, required : false)
if not gtest_dep.found()
  gtest_src = fetch.wrap('gtest', '1.10.0')
  gtest_dep = declare_dependency(
    include_directories : include_directories(gtest_src / 'googletest' / 'include'),
    link_with : static_library('gtest', gtest_src / 'googletest' / 'src' / 'gtest-all.cc')
  )
endif

gtest_main_dep = dependency('gtest_main', required : false)
if not gtest_main_dep.found()
  gtest_main_dep = declare_dependency(
    link_with : static_library('gtest_main', gtest_src / 'googletest' / 'src' / 'gtest_main.cc')
  )
endif

subdir('src')
subdir('tests')
