#
# @file binding.gyp
# @brief This file provides the configuration and building options for node-gyp
#
# This file is created at "DO bots". It is open-source software and part of "dodedodo". 
# This software is published under the Apache Licence license (LGPLv3).
#
# Copyright © 2013 Marc Hulscher <marc@almende.org>
#
# @author                    Marc Hulscher
# @date                      dec 10, 2013
# @organisation              DO bots
# @project                   dodedodo
#
{
	"targets": [
		{
			"target_name": "MorsePifaceModule",
			
			"include_dirs": [
				"../../inc",
				"../../aim-core/inc"
				
			],
			
			"dependencies":[
			],
			
			"cflags": [
			],
			
			"libraries": [
			],
			
			"ldflags": [
				"-pthread",
			],
			
			"sources":[
				"../../aim-core/src/MorsePifaceModule.cpp",
				"MorsePifaceModuleNode.cc",
				"../../src/MorsePifaceModuleExt.cpp"
			],
		}
	]
}
