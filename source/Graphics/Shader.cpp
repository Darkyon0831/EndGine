#include "Shader.h"
#include <fstream>

EG::Shader::Shader()
	: m_pInputLayout(nullptr)
	, m_pVertexShader(nullptr)
	, m_pPixelShader(nullptr)
{
}

EG::Shader::~Shader()
{
	if (m_pError == nullptr)
	{
		m_pInputLayout->Release();
		m_pVertexShader->Release();
		m_pPixelShader->Release();
		m_pVertexShaderBuffer->Release();
		m_pPixelShaderBuffer->Release();
	}
	else
		m_pError->Release();
}

void EG::Shader::Load(const String& vsShaderName, const String& psShaderName)
{
	D3D11_INPUT_ELEMENT_DESC defaultLayout[2];
	ID3D11Device* pDevice = Device::GetInstance().GetDevice();

	m_psShaderName = psShaderName;
	m_vsShaderName = vsShaderName;

	String vsFilePath = String("../../game/data/shaders/");
	vsFilePath += vsShaderName.GetString();

	String psFilePath = String("../../game/data/shaders/");
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
			PrintError(ErrorSource::VS);
		
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
			PrintError(ErrorSource::PS);
		
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

	result = pDevice->CreateInputLayout(
		defaultLayout, 
		2, 
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

void EG::Shader::PrintError(ErrorSource errorSource) const
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
	
	if (errorSource == ErrorSource::PS)
		fout.open(psErrorFile.GetString());
	else if (errorSource == ErrorSource::VS)
		fout.open(vsErrorFile.GetString());

	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	fout.close();
}
