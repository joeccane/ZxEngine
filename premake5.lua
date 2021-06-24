--main

workspace "zxengine"
	architecture "x64"
	targetdir "build"

	configurations{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "zxengine-core"

	include "zxengine-core"


