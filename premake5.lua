project "libgwyfile"
    kind "StaticLib"
    language "C"


    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")


    files
    {
        "lib/gwyfile.h",
        "lib/gwyfile.c",
    }

    filter "system:windows"
        systemversion "latest"

	filter "configurations:Debug"
        systemversion "latest"
		runtime "Debug"
        symbols "on"
        staticruntime "off"

	filter "configurations:Release"
        systemversion "latest"
		runtime "Release"
        optimize "on"
        staticruntime "On"
