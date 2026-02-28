# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_strategy_robosoccer_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED strategy_robosoccer_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(strategy_robosoccer_FOUND FALSE)
  elseif(NOT strategy_robosoccer_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(strategy_robosoccer_FOUND FALSE)
  endif()
  return()
endif()
set(_strategy_robosoccer_CONFIG_INCLUDED TRUE)

# output package information
if(NOT strategy_robosoccer_FIND_QUIETLY)
  message(STATUS "Found strategy_robosoccer: 0.0.0 (${strategy_robosoccer_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'strategy_robosoccer' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${strategy_robosoccer_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(strategy_robosoccer_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${strategy_robosoccer_DIR}/${_extra}")
endforeach()
