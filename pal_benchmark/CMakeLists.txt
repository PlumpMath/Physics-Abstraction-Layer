OPTION(PAL_BUILD_BENCHMARK "Set to ON to build PAL Benchmark." ON)
IF (PAL_BUILD_BENCHMARK)
	IF (PAL_CONFIG_HAS_BEEN_RUN_BEFORE)
		SET_ADDITIONAL_SEARCH_PATHS("Irrlicht" "irrlicht-1.6" "irrlicht-1.6.1")
		FIND_PACKAGE(IRRLICHT)
	ENDIF()
	ADD_SUBDIRECTORY(palBenchmark)
	IF (PAL_EXAMPLES_DISPLAY)
		ADD_SUBDIRECTORY(test_collision)
		ADD_SUBDIRECTORY(test_drop)
		ADD_SUBDIRECTORY(test_friction)
		ADD_SUBDIRECTORY(test_links)
		ADD_SUBDIRECTORY(test_restitution)
		ADD_SUBDIRECTORY(test_stack)
		ADD_SUBDIRECTORY(test_stress)
	ENDIF()
ENDIF()
