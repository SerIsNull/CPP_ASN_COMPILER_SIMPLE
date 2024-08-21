# set names of src files
set(SOURCES
    token_stream.cpp
    fixture_test.cpp
    main_test.cpp
)

# set names of header files
set(HEADERS
    token_stream.h
    fixture_test.h
)

# set src files.asn for testing
set(ASN_FILES
    INTEGER_TYPE.asn
    OCTET_STRING_TYPE.asn
)

# add full path for src files.asn
list(TRANSFORM ASN_FILES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

# DBG Print 
foreach( f IN LISTS ASN_FILES)
    message("file is " ${f})
endforeach()

# create the target for testing class token_stream
add_executable(token_stream_test ${CMAKE_SOURCE_DIR}/src/${SOURCES})

# set output and include directories for token_stream_test.
target_include_directories(token_stream_test PRIVATE
    "${CMAKE_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}"
)

# add link options for linking gtest.
target_link_options(token_stream_test PRIVATE
    "-pthread"
)

# add gtest library for linker
target_link_libraries(token_stream_test gtest)


# add suit test #1. Test class token_stream
add_test(NAME token_stream_test
    COMMAND $<TARGET_FILE:token_stream_test> "${ASN_FILES}"
)

# auto run all suit tests just after building.
add_custom_command(TARGET token_stream_test
    POST_BUILD
    COMMAND ${CMAKE_CTEST_COMMAND} --V --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    VERBATIM
)
