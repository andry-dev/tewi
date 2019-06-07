cmake_minimum_required(VERSION 3.6)


find_program(XELATEX_EXE NAMES "xelatex" DOC "Path to xelatex executable")
if (XELATEX_EXE)
    message(STATUS "[tewi] xelatex found: ${XELATEX_EXE}")

    configure_file(Main.tex.in ${PROJECT_SOURCE_DIR}/doc/Main.tex @ONLY)

    add_custom_target(doc
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/doc
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/doc/apidoc
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/doc/apidoc/video
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/doc/tutorials
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/doc/howto
        COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/doc/design
        COMMAND ${XELATEX_EXE} -shell-escape -output-directory=${PROJECT_BINARY_DIR}/doc Main.tex
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/doc
        COMMENT "[tewi] Generating documentation with xelatex" VERBATIM)
else()
    message(STATUS "[tewi] Can't find xelatex, docs will not be built")
endif()
