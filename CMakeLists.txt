project( LargeImageDatabaseITKIO )

find_package(ITK REQUIRED)

find_package(MongoDB REQUIRED)


add_subdirectory( Source )
add_subdirectory( Testing )
add_subdirectory( Documents )
