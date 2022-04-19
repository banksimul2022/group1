# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DLLSerialPort_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DLLSerialPort_autogen.dir\\ParseCache.txt"
  "DLLSerialPort_autogen"
  )
endif()
