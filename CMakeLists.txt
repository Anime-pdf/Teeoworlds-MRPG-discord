cmake_minimum_required(VERSION 3.22)

### Common

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(TARGET_BITS "32")
else()
    set(TARGET_BITS "64")
endif()
if(WIN32)
    set(TARGET_OS "windows")
elseif(UNIX)
    set(TARGET_OS "linux")
endif()

set(LIB_DIR "${TARGET_OS}/lib${TARGET_BITS}")

function(set_extra_dirs_lib VARIABLE NAME)
    set(DIR "libs/${NAME}/${LIB_DIR}/")
    set("HINTS_${VARIABLE}_LIBDIR" "${DIR}" PARENT_SCOPE)
    set("EXTRA_${VARIABLE}_LIBDIR" "${DIR}" PARENT_SCOPE)
endfunction()

function(set_extra_dirs_include VARIABLE NAME)
    set("HINTS_${VARIABLE}_INCLUDEDIR" "libs/${NAME}/include" PARENT_SCOPE)
endfunction()

function(is_bundled VARIABLE PATH)
    if(PATH)
        string(FIND "${PATH}" "${PROJECT_SOURCE_DIR}" LOCAL_PATH_POS)
        if(LOCAL_PATH_POS EQUAL 0 AND TARGET_BITS AND TARGET_OS)
            set("${VARIABLE}" ON PARENT_SCOPE)
        else()
            set("${VARIABLE}" OFF PARENT_SCOPE)
        endif()
    else()
        set("${VARIABLE}" OFF PARENT_SCOPE)
    endif()
endfunction()

function(show_dependency_status OUTPUT_NAME NAME REQUIRED)
    if(${NAME}_FOUND)
        if(${NAME}_BUNDLED)
            message(STATUS " * ${OUTPUT_NAME} not found (using bundled version)")
        else()
            message(STATUS " * ${OUTPUT_NAME} found")
        endif()
    else()
        message(STATUS " * ${OUTPUT_NAME} not found")
        if(REQUIRED)
            message(SEND_ERROR "You must install ${OUTPUT_NAME} to compile Teeworlds MMO")
        endif()
    endif()
endfunction()

### Project

project(jellyfin-manage-bot VERSION 1.0)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.hpp)
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(Threads)
find_package(ZLIB)
find_package(OpenSSL)
find_package(Asio)
find_package(Crow)
find_package(DPP)

show_dependency_status("Zlib" ZLIB FALSE)
show_dependency_status("OpenSSL" OPENSSL FALSE)
show_dependency_status("Asio" ASIO TRUE)
show_dependency_status("Crow" CROW TRUE)
show_dependency_status("DPP" DPP TRUE)

target_link_libraries(${PROJECT_NAME}
        ${ZLIB_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        ${ASIO_LIBRARIES}
        ${CROW_LIBRARIES}
        ${DPP_LIBRARIES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${ZLIB_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIRS}
        ${ASIO_INCLUDE_DIRS}
        ${CROW_INCLUDE_DIRS}
        ${DPP_INCLUDE_DIRS}
)

set(COPY_FILES
        ${ZLIB_COPY_FILES}
        ${OPENSSL_COPY_FILES}
        ${ASIO_COPY_FILES}
        ${CROW_COPY_FILES}
        ${DPP_COPY_FILES}
)
file(COPY ${COPY_FILES} DESTINATION .)

set_target_properties(${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
