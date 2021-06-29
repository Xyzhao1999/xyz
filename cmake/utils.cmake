include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14
if (${CMAKE_VERSION} VERSION_LESS 3.14)
  include(add_FetchContent_MakeAvailable.cmake)
endif ()

if (NOT add_git_external_party)
  macro(add_git_external_party _NAME _URL _TAG)
    FetchContent_Declare(
        ${_NAME}
        GIT_REPOSITORY ${_URL}
        GIT_TAG ${_TAG}
        SOURCE_DIR ${XYZ_ROOT_DIR}/external/${_NAME}
    )
    FetchContent_MakeAvailable(${_NAME})
  endmacro()
  set(add_git_external_party TRUE)
endif ()

if (NOT get_git_hash)
  macro(get_git_hash _GIT_HASH)
    find_package(Git QUIET)
    if (GIT_FOUND)
      execute_process(
          COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%H
          OUTPUT_VARIABLE ${_GIT_HASH}
          OUTPUT_STRIP_TRAILING_WHITESPACE
          ERROR_QUIET
          WORKING_DIRECTORY
          ${CMAKE_CURRENT_SOURCE_DIR}
      )
    endif ()
    if ("${${_GIT_HASH}}" STREQUAL "")
      set(${_GIT_HASH} "unknown")
    endif ()
  endmacro()
  set(get_git_hash TRUE)
endif ()


