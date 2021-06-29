
add_library(xyz INTERFACE)
add_library(xyz::xyz ALIAS xyz)

target_include_directories(xyz INTERFACE ${XYZ_ROOT_DIR}/include)


set(XYZ_BASE_SRCS
    ${XYZ_ROOT_DIR}/src/version.cpp
    ${XYZ_ROOT_DIR}/include/xyz/version.h
    ${XYZ_ROOT_DIR}/include/xyz/define.h
    ${XYZ_ROOT_DIR}/include/xyz/xyz.h
    )

add_library(xyz_base STATIC ${XYZ_BASE_SRCS})
add_library(xyz::base ALIAS xyz_base)
set(XYZ_LIBS ${XYZ_LIBS} xyz::base)


add_subdirectory(log)
set(XYZ_LIBS ${XYZ_LIBS} xyz::log)

add_subdirectory(json)
set(XYZ_LIBS ${XYZ_LIBS} xyz::json)


target_link_libraries(xyz INTERFACE ${XYZ_LIBS})
