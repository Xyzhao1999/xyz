
add_library(xyz INTERFACE)
add_library(xyz::xyz ALIAS xyz)

set(XYZ_VERSION_SRCS
    ${XYZ_ROOT_DIR}/src/version.cpp
    ${XYZ_ROOT_DIR}/include/xyz/version.h
    )

add_library(xyz_version STATIC ${XYZ_VERSION_SRCS})
add_library(xyz::version ALIAS xyz_version)


add_subdirectory(log)
set(XYZ_LIBS ${XYZ_LIBS} xyz::log)


target_link_libraries(xyz INTERFACE ${XYZ_LIBS})
