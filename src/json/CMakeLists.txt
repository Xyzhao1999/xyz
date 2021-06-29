
set(JSON_GIT_TAG v3.9.1)
set(JSON_GIT_URL https://github.com/nlohmann/json.git)
add_git_external_party(nlohmann_json ${JSON_GIT_URL} ${JSON_GIT_TAG})


#set(XYZ_JSON_SRCS
#    ${XYZ_ROOT_DIR}/include/xyz/json/json.h
#    )


add_library(xyz_json INTERFACE)
target_link_libraries(xyz_json INTERFACE nlohmann_json)
add_library(xyz::json ALIAS xyz_json)
