check_include_file_cxx(stdint.h HAVE_STDINT_H)
if(HAVE_STDINT_H)
    add_definitions(-DHAVE_STDINT_H)
endif()

set(examples_as_tests_sources)
if(${ENABLE_EXAMPLES})
    set(examples_as_tests_sources
        #test/SniffUtils-examples-test-suite.cc
        )
endif()

build_lib(
    LIBNAME SniffUtils
    SOURCE_FILES model/SniffUtils.cc
                 helper/SniffUtils-helper.cc
    HEADER_FILES model/SniffUtils.h
                 helper/SniffUtils-helper.h
    LIBRARIES_TO_LINK     ${libinternet}
    ${libmobility}
    ${libaodv}
    ${libwifi}
    TEST_SOURCES test/SniffUtils-test-suite.cc
                 ${examples_as_tests_sources}
)
