#pragma once

#include "Globals/WString.h"
#include <d3d11.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include "Device.h"

#include "Globals/String.h"
#include "Globals/Matrix.h"

namespace EG
{
	class Shader
	{
	public:

		enum ErrorSource
		{
			PS,
			VS
		};
		
		Shader();
		~Shader();
		
		void Load(const String& vsShaderName, const String& psShaderName);
		
		void SetInputLayout(ID3D11InputLayout* pInputLayout);

		const void* GetVertexShaderBuffer() const { return m_pVertexShaderBuffer->GetBufferPointer(); }
		const void* GetPixelShaderBuffer() const { return m_pPixelShaderBuffer->GetBufferPointer(); }
		size_t GetVertexShaderBufferSize() const { return m_pVertexShaderBuffer->GetBufferSize(); }
		size_t GetPixelShaderBufferSize() const { return m_pPixelShaderBuffer->GetBufferSize(); }
		ID3D11VertexShader* GetVertexShader() const { return m_pVertexShader; }
		ID3D11PixelShader* GetPixelShader() const { return m_pPixelShader; }
		ID3D11InputLayout* GetInputLayout() const { return m_pInputLayout; }
		ID3D11SamplerState* GetSamplerState() const { return m_pSamplerState; }
		ID3D11Buffer* GetVertexConstantBuffer() const { return m_pConstantBuffer; }
		ID3D11Buffer** GetVertexConstantBufferPtr() { return &m_pConstantBuffer; }
		
		void PrintError(ErrorSource errorSource) const;
		
	private:
		
		ID3D11InputLayout* m_pInputLayout;
		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;
		ID3D11SamplerState* m_pSamplerState;
		ID3D10Blob* m_pVertexShaderBuffer;
		ID3D10Blob* m_pPixelShaderBuffer;
		ID3D10Blob* m_pError;

		// TODO: Use and own defined constant buffer class that handles the content of the constant buffer
		ID3D11Buffer* m_pConstantBuffer;

		String m_vsShaderName;
		String m_psShaderName;

		bool isLoadError;
	};
}
