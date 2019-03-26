find_program(CLANG_TIDY_EXE NAMES "clang-tidy" DOC "Path to clang-tidy executable")
if(CLANG_TIDY_EXE)
	message(STATUS "[tewi] clang-tidy found: ${CLANG_TIDY_EXE}")

    file(GLOB_RECURSE
        ALL_SOURCES
        ${PROJECT_SOURCE_DIR}/include/*.h
        ${PROJECT_SOURCE_DIR}/include/*.hpp
        ${PROJECT_SOURCE_DIR}/include/*.hxx
        ${PROJECT_SOURCE_DIR}/src/*.cpp)

	add_custom_target(clang-tidy
        COMMAND ${CLANG_TIDY_EXE} ${ALL_SOURCES}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "[tewi] Checking code with clang-tidy" VERBATIM)
endif()

find_program(CLANG_FORMAT_EXE
    NAMES
    "clang-format"
    DOC
    "Path to clang-format executable")

if (CLANG_FORMAT_EXE)
    message(STATUS "[tewi] clang-format found: ${CLANG_FORMAT_EXE}")

    file(GLOB_RECURSE
        ALL_SOURCES
        ${PROJECT_SOURCE_DIR}/include/*.h
        ${PROJECT_SOURCE_DIR}/include/*.hpp
        ${PROJECT_SOURCE_DIR}/include/*.hxx
        ${PROJECT_SOURCE_DIR}/src/*.cpp)

    add_custom_target(clang-format
        COMMAND
        ${CLANG_FORMAT_EXE} -i -style=file ${ALL_SOURCES}
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
        COMMENT "[tewi] Formatting code with clang-format" VERBATIM)
endif()

find_program(COMPDB_EXE NAMES "compdb" DOC "Path to compdb executable")
if(COMPDB_EXE)
    message(STATUS "[tewi] compdb found: ${COMPDB_EXE}")
    add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/compile_commands.json
        COMMAND ${COMPDB_EXE} -p ${PROJECT_BINARY_DIR} list > compile_commands.json
        COMMAND ${CMAKE_COMMAND} -E copy
            ${PROJECT_SOURCE_DIR}/compile_commands.json
            ${PROJECT_BINARY_DIR}/compile_commands.json
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "[tewi] Generating compile_commands for header files" VERBATIM)
    add_custom_target(regendb DEPENDS ${PROJECT_SOURCE_DIR}/compile_commands.json)
endif()
