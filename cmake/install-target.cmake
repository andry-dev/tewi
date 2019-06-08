include(CPack)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/tewi
    TYPE INCLUDE)

if (TEWI_BUILD_DOC)
    install(FILES ${PROJECT_BINARY_DIR}/doc/Main.pdf
            DESTINATION share/doc
            RENAME tewidoc.pdf)
endif()

if (TEWI_BUILD_EXAMPLES)
    file(GLOB ALL_EXAMPLES "${PROJECT_BINARY_DIR}/examples/bin/*")
    install(PROGRAMS ${ALL_EXAMPLES}
            DESTINATION share/examples)
endif()

install(TARGETS tewi
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)
