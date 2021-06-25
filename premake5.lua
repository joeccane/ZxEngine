--main

workspace "zxengine"
	architecture "x64"
	targetdir "build"
	startproject "sandbox"
	configurations{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "zxengine-core"

	include "zxengine-core"
	include "glfw"
	include "sandbox"

