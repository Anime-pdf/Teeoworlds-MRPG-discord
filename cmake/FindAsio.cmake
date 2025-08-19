set_extra_dirs_include(ASIO asio)
find_path(ASIO_INCLUDEDIR
        NAMES asio.hpp
        HINTS ${HINTS_ASIO_INCLUDEDIR}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Asio DEFAULT_MSG ASIO_INCLUDEDIR)

mark_as_advanced(ASIO_INCLUDEDIR)

if(ASIO_FOUND)
    set(ASIO_LIBRARIES)
    set(ASIO_INCLUDE_DIRS ${ASIO_INCLUDEDIR})
    set(ASIO_COPY_FILES)
    is_bundled(ASIO_BUNDLED "${ASIO_INCLUDEDIR}")
endif()
