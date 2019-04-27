cmake_minimum_required(VERSION 3.6)


#find_package(Doxygen)
#if(DOXYGEN_FOUND)
#    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
#    add_custom_target(doc
#        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
#        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#        COMMENT "[tewi] Generating documentation with Doxygen" VERBATIM
#    )
#endif(DOXYGEN_FOUND)

find_program(STANDARDESE_EXE NAMES "standardese" DOC "Path to standardese executable")
if (STANDARDESE_EXE)
    message(STATUS "[tewi] standardese found: ${STANDARDESE_EXE}")

    add_custom_target(standardese
        COMMAND ${STANDARDESE_EXE} --config ${PROJECT_SOURCE_DIR}/doc/standardese.ini ${PROJECT_SOURCE_DIR}/include
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc
        COMMENT "[tewi] Generating documentation with standardese" VERBATIM)

    add_custom_command(
        TARGET standardese PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/doc)
endif()
