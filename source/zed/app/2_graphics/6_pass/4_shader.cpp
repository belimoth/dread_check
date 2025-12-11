#include <zed/app.h>
#include <zed/app/system.h>
#include <zed/app/graphics.h>
#include <zed/platform/d3d11.h>

D3D_SHADER_MACRO shader_macros[] = {
	"zero", "0",
	0, 0
};

ID3DInclude *shader_include = D3D_COMPILE_STANDARD_FILE_INCLUDE;
uint shader_flags = D3DCOMPILE_DEBUG | D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_OPTIMIZATION_LEVEL3 | D3DCOMPILE_WARNINGS_ARE_ERRORS | D3DCOMPILE_ALL_RESOURCES_BOUND;

string _get_description_for_format( DXGI_FORMAT format ) {
	if ( format == DXGI_FORMAT_R32_UINT           ) return "DXGI_FORMAT_R32_UINT";
	if ( format == DXGI_FORMAT_R32_SINT           ) return "DXGI_FORMAT_R32_SINT";
	if ( format == DXGI_FORMAT_R32_FLOAT          ) return "DXGI_FORMAT_R32_FLOAT";
	if ( format == DXGI_FORMAT_R32G32_UINT        ) return "DXGI_FORMAT_R32G32_UINT";
	if ( format == DXGI_FORMAT_R32G32_SINT        ) return "DXGI_FORMAT_R32G32_SINT";
	if ( format == DXGI_FORMAT_R32G32_FLOAT       ) return "DXGI_FORMAT_R32G32_FLOAT";
	if ( format == DXGI_FORMAT_R32G32B32_UINT     ) return "DXGI_FORMAT_R32G32B32_UINT";
	if ( format == DXGI_FORMAT_R32G32B32_SINT     ) return "DXGI_FORMAT_R32G32B32_SINT";
	if ( format == DXGI_FORMAT_R32G32B32_FLOAT    ) return "DXGI_FORMAT_R32G32B32_FLOAT";
	if ( format == DXGI_FORMAT_R32G32B32A32_UINT  ) return "DXGI_FORMAT_R32G32B32A32_UINT";
	if ( format == DXGI_FORMAT_R32G32B32A32_SINT  ) return "DXGI_FORMAT_R32G32B32A32_SINT";
	if ( format == DXGI_FORMAT_R32G32B32A32_FLOAT ) return "DXGI_FORMAT_R32G32B32A32_FLOAT";

	return "uknown";
}

DXGI_FORMAT _get_format_for_parameter( D3D11_SIGNATURE_PARAMETER_DESC spd ) {
	if ( spd.Mask ==  1 and spd.ComponentType == D3D_REGISTER_COMPONENT_UINT32  ) return DXGI_FORMAT_R32_UINT;
	if ( spd.Mask ==  1 and spd.ComponentType == D3D_REGISTER_COMPONENT_SINT32  ) return DXGI_FORMAT_R32_SINT;
	if ( spd.Mask ==  1 and spd.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) return DXGI_FORMAT_R32_FLOAT;
	if ( spd.Mask <=  3 and spd.ComponentType == D3D_REGISTER_COMPONENT_UINT32  ) return DXGI_FORMAT_R32G32_UINT;
	if ( spd.Mask <=  3 and spd.ComponentType == D3D_REGISTER_COMPONENT_SINT32  ) return DXGI_FORMAT_R32G32_SINT;
	if ( spd.Mask <=  3 and spd.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) return DXGI_FORMAT_R32G32_FLOAT;
	if ( spd.Mask <=  7 and spd.ComponentType == D3D_REGISTER_COMPONENT_UINT32  ) return DXGI_FORMAT_R32G32B32_UINT;
	if ( spd.Mask <=  7 and spd.ComponentType == D3D_REGISTER_COMPONENT_SINT32  ) return DXGI_FORMAT_R32G32B32_SINT;
	if ( spd.Mask <=  7 and spd.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) return DXGI_FORMAT_R32G32B32_FLOAT;
	if ( spd.Mask <= 15 and spd.ComponentType == D3D_REGISTER_COMPONENT_UINT32  ) return DXGI_FORMAT_R32G32B32A32_UINT;
	if ( spd.Mask <= 15 and spd.ComponentType == D3D_REGISTER_COMPONENT_SINT32  ) return DXGI_FORMAT_R32G32B32A32_SINT;
	if ( spd.Mask <= 15 and spd.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 ) return DXGI_FORMAT_R32G32B32A32_FLOAT;

	return DXGI_FORMAT_UNKNOWN;
}

int compile_shader_from_file( string path, string function, string model, ID3DBlob **blob ) {
	wchar_t file_wide[256] = {};
	mbstowcs( file_wide, path, 256 );

	return (int)D3DCompileFromFile(
		file_wide,
		shader_macros,
		shader_include,
		function,
		model,
		shader_flags,
		0,
		blob,
		0
	);
}

int compile_shader_from_resource( int id, string function, string model, ID3DBlob **blob ) {
	handle cso_data = app_system_resource_data( id );
	int    cso_size = app_system_resource_size( id );

	return (int)D3DCompile(
		cso_data,
		cso_size,
		0,
		shader_macros,
		shader_include,
		function,
		model,
		shader_flags,
		0,
		blob,
		0
	);
}

void create_input_layout_from_shader( zed_pass_native *pass, ID3DBlob *vsb ) {
	ID3D11ShaderReflection *vsr;

	D3DReflect(
		vsb->GetBufferPointer(),
		vsb->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		(handle *)&vsr
	);

	D3D11_SHADER_DESC sd;
	vsr->GetDesc( &sd );

	// note max of 32
	D3D11_INPUT_ELEMENT_DESC ieds[32];

	for ( int i = 0; i < sd.InputParameters; i += 1 ) {
		D3D11_SIGNATURE_PARAMETER_DESC spd;

		vsr->GetInputParameterDesc( i, &spd );

		D3D11_INPUT_ELEMENT_DESC ied = {};

		ied.SemanticName         = spd.SemanticName;
		ied.SemanticIndex        = spd.SemanticIndex;
		ied.Format               = _get_format_for_parameter( spd );
		ied.InputSlot            = 0;
		ied.AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
		ied.InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
		ied.InstanceDataStepRate = 0;

		ieds[i] = ied;
	}

	app.graphics.device->CreateInputLayout(
		ieds,
		sd.InputParameters,
		vsb->GetBufferPointer(),
		vsb->GetBufferSize(),
		&pass->il
	);
}
