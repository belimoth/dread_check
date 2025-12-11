#pragma once

#define D3D11_NO_HELPERS

// todo which header to include, was d3d11_1
#include <d3d11_4.h>
#pragma comment( lib, "d3d11.lib" )

#include <d3dcompiler.h>
#pragma comment( lib, "d3dcompiler.lib" )
#pragma comment( lib, "dxguid.lib" )

#include <directxtk/ddstextureloader.h>
#pragma comment( lib, "directxtk.lib" )
