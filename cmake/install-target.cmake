include(CPack)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/tewi
    TYPE INCLUDE)

if (TEWI_BUILD_DOC)
    install(FILES ${PROJECT_BINARY_DIR}/doc/Main.pdf
            DESTINATION share/doc
            RENAME tewidoc.pdf)
endif()

if (TEWI_BUILD_EXAMPLES)
    file(GLOB ALL_EXAMPLES "${PROJECT_BINARY_DIR}/examples/bin/*.exe")
    file(GLOB SRC_EXAMPLES "${PROJECT_SOURCE_DIR}/examples/*.cpp")
    install(PROGRAMS ${ALL_EXAMPLES} ${SRC_EXAMPLES}
            DESTINATION share/examples)
endif()

set(additional_exports "")

if (FOUND_LOCAL_ASL)
    set(additional_exports ${additional_exports} asl)
endif()

install(TARGETS tewi ${additional_exports} stb_impl stb ImGui
        EXPORT tewi-targets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(EXPORT tewi-targets
        NAMESPACE tewi::
        FILE tewiConfig.cmake
        DESTINATION lib/cmake/tewi)
