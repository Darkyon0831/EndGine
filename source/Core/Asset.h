#pragma once

namespace EG
{
	class Asset
	{
	public:
		enum AssetType
		{
			Mesh,
			Texture
		};

		Asset(AssetType assetType);

		const AssetType& GetAssetType() const { return m_assetType; }
		
	private:
		AssetType m_assetType;
	};
}