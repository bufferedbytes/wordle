cmake_minimum_required(VERSION 4.0)
project(wordle, LANGUAGES C)

add_executable(wordle)
target_sources(wordle
  PRIVATE
    "main.c"
)
configure_file(
    "wordlist.txt"
    "wordlist.txt"
    COPYONLY
)