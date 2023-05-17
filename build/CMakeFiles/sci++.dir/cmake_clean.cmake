file(REMOVE_RECURSE
  "libsci++.a"
  "libsci++.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/sci++.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
