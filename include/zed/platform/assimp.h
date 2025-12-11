#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#pragma comment( lib, "assimp-vc142-mt.lib" )

#pragma comment( lib, "draco.lib"        )
#pragma comment( lib, "inireader.lib"    )
#pragma comment( lib, "kubazip.lib"      )
#pragma comment( lib, "minizip.lib"      )
#pragma comment( lib, "poly2tri.lib"     )
#pragma comment( lib, "polyclipping.lib" )
#pragma comment( lib, "pugixml.lib"      )
#pragma comment( lib, "zlib.lib"         )

void assimp_load( char *file ) {
	const aiScene* scene = aiImportFile(
		file,
		aiProcess_CalcTangentSpace       |
		aiProcess_Triangulate            |
		aiProcess_JoinIdenticalVertices  |
		aiProcess_SortByPType
	);

	if ( scene == 0 ) {

	}

	aiReleaseImport( scene );
}
