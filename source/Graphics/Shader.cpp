#include "Shader.h"
#include <fstream>

EG::Shader::Shader()
	: m_pInputLayout(nullptr)
	, m_pVertexShader(nullptr)
	, m_pPixelShader(nullptr)
	, m_pSamplerState(0)
{

	int debug = 0;
}

EG::Shader::~Shader()
{
	if (m_pError == nullptr)
	{
		m_pInputLayout->Release();
		m_pConstantBuffer->Release();
		m_pVertexShader->Release();
		m_pPixelShader->Release();
		m_pVertexShaderBuffer->Release();
		m_pPixelShaderBuffer->Release();
	}
	else
		m_pError->Release();

	int debug = 0;
}

void EG::Shader::Load(const String& vsShaderName, const String& psShaderName)
{
	D3D11_INPUT_ELEMENT_DESC defaultLayout[3];
	D3D11_SAMPLER_DESC samplerDesc;
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();

	m_psShaderName = psShaderName;
	m_vsShaderName = vsShaderName;

	String vsFilePath;
	if (IsDebuggerPresent())
		vsFilePath += "../../game/data/shaders/";
	else
		vsFilePath += "data/shaders/";

	vsFilePath += vsShaderName.GetString();

	String psFilePath;
	if (IsDebuggerPresent())
		psFilePath += "../../game/data/shaders/";
	else
		psFilePath += "data/shaders/";
	
	psFilePath += psShaderName.GetString();
	
	std::wstring vsWS(vsFilePath.GetSize(), L'#');
	mbstowcs_s(nullptr, &vsWS[0], vsFilePath.GetSize(), vsFilePath.GetString(), vsFilePath.GetSize() - 1);

	std::wstring psWS(psFilePath.GetSize(), L'#');
	mbstowcs_s(nullptr, &psWS[0], psFilePath.GetSize(), psFilePath.GetString(), psFilePath.GetSize() - 1);

	HRESULT result = D3DCompileFromFile(
		vsWS.c_str(),
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
		psWS.c_str(),
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

	pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState);
	
	result = pDevice->CreateInputLayout(
		defaultLayout, 
		3, 
		m_pVertexShaderBuffer->GetBufferPointer(),
		m_pVertexShaderBuffer->GetBufferSize(),
		&m_pInputLayout);
}

void EG::Shader::SetInputLayout(ID3D11InputLayout* pInputLayout)
{
	if (m_pInputLayout)
		m_pInputLayout->Release();

	m_pInputLayout = pInputLayout;
}

void EG::Shader::PrintError(ShaderStage errorSource) const
{
	char* compileErrors;
	unsigned long bufferSize, i;
	std::ofstream fout;

	compileErrors = static_cast<char*>(m_pError->GetBufferPointer());
	bufferSize = m_pError->GetBufferSize();

	String psErrorFile = String("../../game/");
	psErrorFile += m_psShaderName.GetString();
	psErrorFile += ".txt";

	String vsErrorFile = String("../../game/");
	vsErrorFile += m_vsShaderName.GetString();
	vsErrorFile += ".txt";
	
	if (errorSource == ShaderStage::PS)
		fout.open(psErrorFile.GetString());
	else if (errorSource == ShaderStage::VS)
		fout.open(vsErrorFile.GetString());

	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();
}
