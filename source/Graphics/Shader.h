#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include "Globals/WString.h"
#include "Device.h"
#include "Globals/String.h"
#include "Globals/Matrix.h"
#include "ConstantBuffer.h"

#include <d3d11.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <vector>
#include "Core/Asset.h"

namespace EG
{
	class Shader : public Asset
	{
	public:

		friend class RenderComponent;
		friend class QuadComponent;

		enum ShaderStage
		{
			PS,
			VS
		};

		struct ShaderVariable
		{
			ShaderStage shaderStage;
			String varName;
			void* varPtr;
			size_t varSize;
		};
		
		Shader();
		~Shader();
		
		void Load(const String& vsShaderName, const String& psShaderName, bool initializeLayout = true);
		
		void SetInputLayout(ID3D11InputLayout* pInputLayout);

		const void* GetVertexShaderBuffer() const { return m_pVertexShaderBuffer->GetBufferPointer(); }
		const void* GetPixelShaderBuffer() const { return m_pPixelShaderBuffer->GetBufferPointer(); }
		size_t GetVertexShaderBufferSize() const { return m_pVertexShaderBuffer->GetBufferSize(); }
		size_t GetPixelShaderBufferSize() const { return m_pPixelShaderBuffer->GetBufferSize(); }

		ID3D11RasterizerState* GetRasterizerState() const { return m_pRasterizerState; }
		ID3D11VertexShader* GetVertexShader() const { return m_pVertexShader; }
		ID3D11PixelShader* GetPixelShader() const { return m_pPixelShader; }
		ID3D11InputLayout* GetInputLayout() const { return m_pInputLayout; }
		ID3D11SamplerState* GetSamplerState() const { return m_pSamplerState; }
		ID3D11Buffer* GetVertexConstantBuffer() const { return m_pConstantsVertex; }
		ID3D11Buffer* GetPixelConstantBuffer() const { return m_pConstantsPixel; }
		ID3D11BlendState* GetBlendState() const { return m_pBlendState; }
		
		void PrintError(ShaderStage errorSource) const;

		void AddShaderVariable(const ShaderVariable& shaderVariableToAdd) { m_shaderVariables.push_back(shaderVariableToAdd); }

		size_t GetTotalSizeOfVariables(const ShaderStage& shaderStage);
		
	private:

		ID3D11BlendState* m_pBlendState;
		ID3D11RasterizerState* m_pRasterizerState;
		ID3D11SamplerState* m_pSamplerState;
		ID3D11InputLayout* m_pInputLayout;
		ID3D11Buffer* m_pConstantsVertex;
		ID3D11Buffer* m_pConstantsPixel;
		
		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;
		
		ID3D10Blob* m_pVertexShaderBuffer;
		ID3D10Blob* m_pPixelShaderBuffer;
		ID3D10Blob* m_pError;

		std::vector<ShaderVariable> m_shaderVariables;
	
		String m_vsShaderName;
		String m_psShaderName;

		bool isLoadError;
	};
}
