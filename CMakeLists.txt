cmake_minimum_required(VERSION 2.8)
project(nes)

file(GLOB source
	"src/*.c"
	"src/*.h")

add_executable(nes ${source})
