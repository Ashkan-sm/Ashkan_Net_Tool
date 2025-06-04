if(NOT EXISTS "/media/dev/H/projects/AshkanTool/cmake-build-debug/install_manifest.txt")
  message(FATAL_ERROR "Cannot find install manifest: /media/dev/H/projects/AshkanTool/cmake-build-debug/install_manifest.txt")
endif()

file(READ "/media/dev/H/projects/AshkanTool/cmake-build-debug/install_manifest.txt" files)
string(REGEX REPLACE "\n" ";" files "${files}")
foreach(file ${files})
  message(STATUS "Uninstalling $ENV{DESTDIR}${file}")
  if(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    execute_process(
      COMMAND "/media/dev/H/clion-2024.3/bin/cmake/linux/x64/bin/cmake" -E remove "$ENV{DESTDIR}${file}"
      OUTPUT_VARIABLE rm_out
      RESULT_VARIABLE rm_retval
      )
    if(NOT "${rm_retval}" STREQUAL 0)
      message(FATAL_ERROR "Problem when removing $ENV{DESTDIR}${file}")
    endif()
  else(IS_SYMLINK "$ENV{DESTDIR}${file}" OR EXISTS "$ENV{DESTDIR}${file}")
    message(STATUS "File $ENV{DESTDIR}${file} does not exist.")
  endif()
endforeach()
file(REMOVE "/media/dev/H/projects/AshkanTool/cmake-build-debug/install_manifest.txt")
