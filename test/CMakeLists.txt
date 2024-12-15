# set names of src files
set(SOURCES
    lexical_rules.cpp
    token_stream.cpp
    buffer.cpp
    buffer_test.cpp
    fixture_test.cpp
    main_test.cpp
    token_stream_test.cpp
)

# set names of header files
set(HEADERS
    token.h
    lexical_rules.h
    token_stream.h
    buffer.h
    fixture_test.h
)

list(TRANSFORM SOURCES PREPEND ${CMAKE_SOURCE_DIR}/src/ AT 0 1 2)

# set src files.asn for testing
set(INTEGER_TYPE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/INTEGER_TYPE.asn)
set(OCTET_STRING_TYPE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/OCTET_STRING_TYPE.asn)

# create the target for testing class token_stream
add_executable(asn_compiler_test ${SOURCES})

# set output and include directories for token_stream_test.
target_include_directories(asn_compiler_test PRIVATE
    "${CMAKE_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}"
)

# add link options for linking gtest.
target_link_options(asn_compiler_test PRIVATE
    "-pthread"
)

# add gtest library for linker
target_link_libraries(asn_compiler_test gtest)

# add suit test #1. Test class token_stream
add_test(NAME all_tests_for_asn_compiler
    COMMAND $<TARGET_FILE:asn_compiler_test> "${INTEGER_TYPE_FILE}"
)

# auto run all suit tests just after building
add_custom_command(TARGET asn_compiler_test
    POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --V --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    VERBATIM
)
