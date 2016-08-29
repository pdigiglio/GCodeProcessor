set(INCLUDE_DIRECTORIES
	${GCodeProcessor_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIRECTORIES})

set(GCodeProcessor_SOURCES
    GCodeProcessor.cpp
    InputFileIterator.cpp
    main.cpp
)

add_executable(${PROJECT_NAME} ${GCodeProcessor_SOURCES})
