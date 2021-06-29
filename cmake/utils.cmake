include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14
if (${CMAKE_VERSION} VERSION_LESS 3.14)
  include(add_FetchContent_MakeAvailable.cmake)
endif ()

if (NOT PROJECT_ROOT)
  message(STATUS "Not determined PROJECT_ROOT, set to ${CMAKE_CURRENT_LIST_DIR}")
  set(PROJECT_ROOT ${CMAKE_CURRENT_LIST_DIR})
endif ()

if (NOT add_git_external_party)
  macro(add_git_external_party _NAME _URL _TAG)
    message(STATUS "Get ${_NAME} tag ${_TAG} from ${_URL}")
    FetchContent_Declare(
        ${_NAME}
        GIT_REPOSITORY ${_URL}
        GIT_TAG ${_TAG}
        SOURCE_DIR ${PROJECT_ROOT}/external/${_NAME}
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE
        USES_TERMINAL_DOWNLOAD TRUE
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


