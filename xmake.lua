set_project( "CursedMod" )

set_version( "0.0.1", { build = "%Y%m%d", soname = true } )

add_rules( "mode.debug", "mode.release", "mode.releasedbg", "mode.minsizerel" )

set_languages( "c++20" )

if is_plat( "windows" ) then
    add_cxflags( "/Zc:__cplusplus" )
    add_cxflags( "/Zc:preprocessor" )

    add_cxflags( "/permissive-" )
else
end

set_warnings( "allextra" )

-- maybe this helps for the ci?
set_policy( "build.across_targets_in_parallel", false )

if is_plat( "linux" ) then
    add_requires( "glib" )
elseif is_plat( "macosx" ) then
    --add_requires( "lodepng" )
elseif is_plat( "windows" ) then
    --add_requires( "lodepng" )
else
end

--add_requireconfs( "**", "*.**", { system = false } )
--add_requireconfs( "*", { configs = { shared = false } } )

target( "CursedModNative" )
    set_kind( "shared" )

    set_default( true )
    set_group( "LIBS" )

    if is_plat( "linux" ) then
        add_packages( "glib" )
    elseif is_plat( "macosx" ) then
        --add_packages( "lodepng" )
    elseif is_plat( "windows" ) then
        add_links("UxTheme", "Dwmapi", "User32")
    else
    end

    add_includedirs( "src", { public = true } )

    add_headerfiles( "src/*.h" )
    add_files( "src/*.cpp" )

    if is_plat( "linux" ) then
        add_files( "src/lin/*.cpp" )
    elseif is_plat( "macosx" ) then
        add_files( "src/mac/*.cpp" )
    elseif is_plat( "windows" ) then
        add_files( "src/win/*.cpp" )
    else
    end

