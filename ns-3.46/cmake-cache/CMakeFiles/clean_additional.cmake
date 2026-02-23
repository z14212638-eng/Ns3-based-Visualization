# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "default")
  file(REMOVE_RECURSE
  "contrib/Ns3Visualizer/ui/CMakeFiles/Ns3VisualizerApp_autogen.dir/AutogenUsed.txt"
  "contrib/Ns3Visualizer/ui/CMakeFiles/Ns3VisualizerApp_autogen.dir/ParseCache.txt"
  "contrib/Ns3Visualizer/ui/Ns3VisualizerApp_autogen"
  "contrib/Ns3Visualizer/ui/utils/CMakeFiles/ns3-script-generator_autogen.dir/AutogenUsed.txt"
  "contrib/Ns3Visualizer/ui/utils/CMakeFiles/ns3-script-generator_autogen.dir/ParseCache.txt"
  "contrib/Ns3Visualizer/ui/utils/ns3-script-generator_autogen"
  )
endif()
