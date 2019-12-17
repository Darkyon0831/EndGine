#include "Shader.h"
#include <fstream>

EG::Shader::Shader()
	: Asset(Asset::AssetType::AShader)
	, m_pRasterizerState(nullptr)
	, m_pSamplerState(nullptr)
	, m_pInputLayout(nullptr)
	, m_pConstantsVertex(nullptr)
	, m_pConstantsPixel(nullptr)
	, m_pVertexShader(nullptr)
	, m_pPixelShader(nullptr)
	, m_pVertexShaderBuffer(nullptr)
	, m_pPixelShaderBuffer(nullptr)
	, m_pError(nullptr)
	, isLoadError(false)
{
	// Create default states, input layouts and constant buffers

	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_INPUT_ELEMENT_DESC defaultLayout[3];
	D3D11_SAMPLER_DESC samplerDesc;
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();

	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.DepthBias = false;
	rasterDesc.DepthBiasClamp = 0;
	rasterDesc.SlopeScaledDepthBias = 0;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.ScissorEnable = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.AntialiasedLineEnable = false;

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	
	EGCHECKHR(pDevice->CreateRasterizerState(&rasterDesc, &m_pRasterizerState));
	
	EGCHECKHR(pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState));

	int i = 0;
}

EG::Shader::~Shader()
{
	if (m_pError == nullptr)
	{
		if (m_pRasterizerState != nullptr)
			m_pRasterizerState->Release();

		if (m_pSamplerState != nullptr)
			m_pSamplerState->Release();

		if (m_pInputLayout != nullptr)
			m_pInputLayout->Release();

		if (m_pConstantsVertex != nullptr)
			m_pConstantsVertex->Release();
		
		if (m_pConstantsPixel != nullptr)
			m_pConstantsPixel->Release();

		if (m_pVertexShader != nullptr)
			m_pVertexShader->Release();

		if (m_pPixelShader != nullptr)
			m_pPixelShader->Release();

		if (m_pVertexShaderBuffer != nullptr)
			m_pVertexShaderBuffer->Release();

		if (m_pPixelShaderBuffer != nullptr)
			m_pPixelShaderBuffer->Release();	
	}
	else
		m_pError->Release();

	int debug = 0;
}

void EG::Shader::Load(const String& vsShaderName, const String& psShaderName, bool initializeLayout)
{
	D3D11_INPUT_ELEMENT_DESC defaultLayout[3];
	
	defaultLayout[0].SemanticName = "POSITION";
	defaultLayout[0].SemanticIndex = 0;
	defaultLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	defaultLayout[0].InputSlot = 0;
	defaultLayout[0].AlignedByteOffset = 0;
	defaultLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	defaultLayout[0].InstanceDataStepRate = 0;

	defaultLayout[1].SemanticName = "COLOR";
	defaultLayout[1].SemanticIndex = 0;
	defaultLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	defaultLayout[1].InputSlot = 0;
	defaultLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	defaultLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	defaultLayout[1].InstanceDataStepRate = 0;

	defaultLayout[2].SemanticName = "TEXCOORD";
	defaultLayout[2].SemanticIndex = 0;
	defaultLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	defaultLayout[2].InputSlot = 0;
	defaultLayout[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	defaultLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	defaultLayout[2].InstanceDataStepRate = 0;
	
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();

	m_psShaderName = psShaderName;
	m_vsShaderName = vsShaderName;

	String vsFilePath = "data/shaders/";
	vsFilePath += vsShaderName.GetString();

	String psFilePath = "data/shaders/";	
	psFilePath += psShaderName.GetString();

	wchar_t* vsWS = new wchar_t[vsFilePath.GetSize()];
	mbstowcs(vsWS, vsFilePath.GetString(), vsFilePath.GetSize());
	
	wchar_t* psWS = new wchar_t[psFilePath.GetSize()];
	mbstowcs_s(nullptr, &psWS[0], psFilePath.GetSize(), psFilePath.GetString(), psFilePath.GetSize() - 1);
	
	HRESULT result = D3DCompileFromFile(
		vsWS,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"vs_5_0",
		D3DCOMPILE_DEBUG,
		0,
		&m_pVertexShaderBuffer,
		&m_pError);

	
	if (FAILED(result))
	{
		if (m_pError)
			PrintError(ShaderStage::VS);
		
		isLoadError = true;
		return;
	}

	result = D3DCompileFromFile(
		psWS,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"main",
		"ps_5_0",
		D3DCOMPILE_DEBUG,
		0,
		&m_pPixelShaderBuffer,
		&m_pError);

	if (FAILED(result))
	{
		if (m_pError)
			PrintError(ShaderStage::PS);
		
		isLoadError = true;
		return;
	}

	pDevice->CreateVertexShader(
		m_pVertexShaderBuffer->GetBufferPointer(),
		m_pVertexShaderBuffer->GetBufferSize(),
		nullptr,
		&m_pVertexShader);
	
	pDevice->CreatePixelShader(
		m_pPixelShaderBuffer->GetBufferPointer(),
		m_pPixelShaderBuffer->GetBufferSize(),
		nullptr,
		&m_pPixelShader);

	if (initializeLayout)
	{
		EGCHECKHR(pDevice->CreateInputLayout(
			defaultLayout,
			3,
			m_pVertexShaderBuffer->GetBufferPointer(),
			m_pVertexShaderBuffer->GetBufferSize(),
			&m_pInputLayout));
	}

	delete[] vsWS;
	delete[] psWS;
}

void EG::Shader::SetInputLayout(ID3D11InputLayout* pInputLayout)
{
	if (m_pInputLayout)
		m_pInputLayout->Release();

	m_pInputLayout = pInputLayout;
}

void EG::Shader::PrintError(const ShaderStage errorSource) const
{
	std::ofstream fout;

	char* compileErrors = static_cast<char*>(m_pError->GetBufferPointer());
	const unsigned long bufferSize = m_pError->GetBufferSize();

	String psErrorFile = String();
	psErrorFile += m_psShaderName.GetString();
	psErrorFile += ".txt";

	String vsErrorFile = String();
	vsErrorFile += m_vsShaderName.GetString();
	vsErrorFile += ".txt";
	
	if (errorSource == ShaderStage::PS)
		fout.open(psErrorFile.GetString());
	else if (errorSource == ShaderStage::VS)
		fout.open(vsErrorFile.GetString());

	for (unsigned int i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();
}

size_t EG::Shader::GetTotalSizeOfVariables(const ShaderStage& shaderStage)
{
	size_t size = 0;

	for (unsigned int i = 0; i < m_shaderVariables.size(); i++)
	{
		if (m_shaderVariables.at(i).shaderStage == shaderStage)
			size += m_shaderVariables.at(i).varSize;
	}

	return size;
}
