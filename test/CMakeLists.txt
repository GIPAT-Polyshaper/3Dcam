# Compile the tests and adds a test target

# NOTE: To get the output of the failing test you should either call "make test"
# with the environmental variable CTEST_OUTPUT_ON_FAILURE set to 1 or call
# "ctest --output-on-failure" in the build directory (instead of "make test").

# A function to declare a test. testName is the name of the test. The
# source file of the test must have the same name of the test with a "_test.cpp"
# suffix. "test_" is prepended also the the name of the test. If a file named
# "${testName}_resources.qrc" exists, it is added (as QT resources) to the test
function(addTest testName)
    set(testTargetName "test_${testName}")
    set(testFileName "${testName}_test.cpp")

    set(resourceSource )
    set(resourceFile "${CMAKE_CURRENT_SOURCE_DIR}/${testName}_resources.qrc")
    if (EXISTS "${resourceFile}" AND NOT IS_DIRECTORY "${resourceFile}")
        qt5_add_resources(resourceSource "${resourceFile}")
    endif()

    add_executable("${testTargetName}" "${testFileName}" "${resourceSource}")
    target_link_libraries("${testTargetName}" 3dcamlib Qt5::Test)
    add_test(NAME "${testTargetName}" COMMAND "${testTargetName}")
endfunction()

# Adding all tests
addTest(dummy)
addTest(cgal)
addTest(stlloader)
addTest(triangularmeshgenerator)
addTest(verticesandfacesgenerator)
addTest(toolpathgenerator)
