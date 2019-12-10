#pragma once

namespace EG
{
	class Asset
	{
	public:
		enum AssetType
		{
			AMesh,
			ATexture,
			AMaterial,
			AShader
		};

		Asset(AssetType assetType);

		const AssetType& GetAssetType() const { return m_assetType; }
		
	private:
		AssetType m_assetType;
	};
}