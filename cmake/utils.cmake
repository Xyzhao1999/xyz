
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
