check_include_file_cxx(stdint.h HAVE_STDINT_H)
if(HAVE_STDINT_H)
    add_definitions(-DHAVE_STDINT_H)
endif()

set(examples_as_tests_sources)
if(${ENABLE_EXAMPLES})
    set(examples_as_tests_sources
        #test/QNs3-examples-test-suite.cc
        )
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

build_lib(
    LIBNAME QNs3
    SOURCE_FILES model/QNs3.cc
                 helper/QNs3-helper.cc
    HEADER_FILES model/QNs3.h
                 helper/QNs3-helper.h
    LIBRARIES_TO_LINK ${libcore}
    TEST_SOURCES test/QNs3-test-suite.cc
                 ${examples_as_tests_sources}
)
