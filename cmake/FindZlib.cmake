set_extra_dirs_include(ZLIB zlib)
find_path(ZLIB_INCLUDEDIR
        NAMES zlib.h
        HINTS ${HINTS_ZLIB_INCLUDEDIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Zlib DEFAULT_MSG ZLIB_INCLUDEDIR)

mark_as_advanced(ZLIB_INCLUDEDIR)

if(ZLIB_FOUND)
    set(ZLIB_LIBRARIES)
    set(ZLIB_INCLUDE_DIRS ${ZLIB_INCLUDEDIR})
    set(ZLIB_COPY_FILES)
    is_bundled(ZLIB_BUNDLED "${ZLIB_INCLUDEDIR}")
endif()
