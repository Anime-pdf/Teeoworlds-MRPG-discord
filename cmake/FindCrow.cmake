set_extra_dirs_include(CROW crow)
find_path(CROW_INCLUDEDIR
        NAMES crow.h
        HINTS ${HINTS_CROW_INCLUDEDIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Crow DEFAULT_MSG CROW_INCLUDEDIR)

mark_as_advanced(CROW_INCLUDEDIR)

if(CROW_FOUND)
    set(CROW_LIBRARIES)
    set(CROW_INCLUDE_DIRS ${CROW_INCLUDEDIR})
    set(CROW_COPY_FILES)
    is_bundled(CROW_BUNDLED "${CROW_INCLUDEDIR}")
endif()
