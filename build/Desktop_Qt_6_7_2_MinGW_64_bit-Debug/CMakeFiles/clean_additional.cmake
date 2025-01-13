# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\IkosDodek_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\IkosDodek_autogen.dir\\ParseCache.txt"
  "IkosDodek_autogen"
  )
endif()
