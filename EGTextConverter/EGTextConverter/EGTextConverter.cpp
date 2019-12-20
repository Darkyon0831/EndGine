// EGTextConverter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

#include <d3d11.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

#include <DirectXTex.h>

// Command line usage: EGTextConverter <ttfFilepath>
// arguments:
// -w: Text Weight
// -s: Text Size

ID3D11Device* pDevice;
ID3D11DeviceContext* pDeviceContext;

FT_Library ftLib;
FT_Face ftFace;

const int charsPerRow = 12;
int charSize = 24;

struct Vector2D
{
	float x = 0;
	float y = 0;
};

struct Characher
{
	char characher;
	ID3D11Texture2D* pTexture;
	float width;
	float height;
	float usedImageHeight;
	float brearingY;
	float bearingX;
	float advance;
	float left;
	float right;
	float up;
	float down;
};

std::vector<Characher> charachers;

void InitDevice()
{
	IDXGIFactory* pFactory;
	IDXGIAdapter* pAdapter;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pFactory));
	pFactory->EnumAdapters(0, &pAdapter);

	D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		D3D11_CREATE_DEVICE_DEBUG,
		&featureLevel,
		1,
		D3D11_SDK_VERSION,
		&pDevice,
		nullptr,
		&pDeviceContext);

	pFactory->Release();
	pAdapter->Release();
}

void InitFreeType(const char* fontFilePath)
{
	if (FT_Init_FreeType(&ftLib))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		exit(0);
	}

	if (FT_New_Face(ftLib, fontFilePath, 0, &ftFace))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		exit(0);
	}

	FT_Set_Pixel_Sizes(ftFace, 0, charSize);
}

void ReleaseDevice()
{
	pDevice->Release();
	pDeviceContext->Release();
}

float CalculateMaxRowWidth(int totalChars)
{
	std::vector<float> rowWidths(charachers.size() / charsPerRow);
	int rowID = 0;
	int elapsedChars = 0;
	float rowWidth = 0;

	for (unsigned int i = 0; i < charachers.size(); i++)
	{
		rowWidth += charachers.at(i).advance;
		elapsedChars++;

		if (elapsedChars == charsPerRow)
		{
			rowWidths.at(rowID) = rowWidth;
			rowID++;
			rowWidth = 0;
			elapsedChars = 0;
		}
	}

	float currentMaxRowWidh = rowWidths.at(0);

	for (unsigned int i = 1; i < rowWidths.size(); i++)
	{
		if (rowWidths.at(i) > currentMaxRowWidh)
			currentMaxRowWidh = rowWidths.at(i);
	}

	return currentMaxRowWidh;
}

Vector2D CalculateFinalImageSize(const int totalChars, float maxHeight)
{
	const float maxRowWidth = CalculateMaxRowWidth(totalChars);
	const int numRows = (128 - 32) / charsPerRow;
	const float height = static_cast<float>(numRows) * maxHeight;

	const Vector2D size =
	{
		maxRowWidth,
		height
	};

	return size;
}

float GetMaxheight()
{
	float maxHeight = 0;

	for (int i = 0; i < charachers.size(); i++)
	{
		if (charachers.at(i).height > maxHeight)
			maxHeight = charachers.at(i).height;
	}

	return maxHeight;
}

void PopulateFinalImage(ID3D11Texture2D* finalTexture, Vector2D finalImageSize, float maxHeight)
{
	Vector2D position = { 0.0f, 0.0f };

	int currentRowPos = 0;
	
	for (unsigned int i = 0; i < charachers.size(); i++)
	{
		Characher& rCharacher = charachers.at(i);
		
		float newY = position.y + (maxHeight - rCharacher.brearingY);
		
		if (rCharacher.pTexture != nullptr)
		{
			pDeviceContext->CopySubresourceRegion
			(
				finalTexture,
				0,
				position.x + rCharacher.bearingX,
				position.y + (maxHeight - rCharacher.brearingY),
				0.0f,
				rCharacher.pTexture,
				0,
				nullptr
			);
		}

		rCharacher.left = position.x / finalImageSize.x;
		rCharacher.right = (position.x + rCharacher.advance) / finalImageSize.x;
		rCharacher.up = position.y / finalImageSize.y;
		rCharacher.down = (position.y + maxHeight) / finalImageSize.y;

		position.x += rCharacher.advance;
		currentRowPos++;

		if (currentRowPos == charsPerRow)
		{
			position.x = 0.0f;
			position.y += maxHeight;
			currentRowPos = 0;
		}
	}

	
}

void RoundToPowerOfTwo(Vector2D& finalImageSize)
{
	unsigned int finalImageX = static_cast<unsigned int>(finalImageSize.x);
	unsigned int finalImageY = static_cast<unsigned int>(finalImageSize.y);
	
	finalImageX--;
	finalImageX |= finalImageX >> 1;
	finalImageX |= finalImageX >> 2;
	finalImageX |= finalImageX >> 4;
	finalImageX |= finalImageX >> 8;
	finalImageX |= finalImageX >> 16;
	finalImageX++;

	finalImageY--;
	finalImageY |= finalImageY >> 1;
	finalImageY |= finalImageY >> 2;
	finalImageY |= finalImageY >> 4;
	finalImageY |= finalImageY >> 8;
	finalImageY |= finalImageY >> 16;
	finalImageY++;

	finalImageSize.x = static_cast<float>(finalImageX);
	finalImageSize.y = static_cast<float>(finalImageY);
}

bool isNumber(char* str)
{
	size_t strSize = strlen(str);

	for (int i = 0; i < strSize; i++)
	{
		if (isdigit(str[i]) == false)
			return false;
	}

	return true;
}

void ReadArguments(int argc, char* argv[])
{
	if (argc > 2)
	{
		char* argument = argv[2];

		if (strcmp(argument, "-s") == 0)
		{
			if (argc > 3 && isNumber(argv[3]))
			{
				charSize = std::stoi(argv[3]);
			}
			else
			{
				std::cout << "Invalid value for the argument -s, Usage: " << "-s <number>" << std::endl;
			}
		}
	}
}

void WriteBoxDataFile(const float maxHeight)
{
	std::ofstream fileStream;

	fileStream.open("fontBox.data");

	for (int i = 0; i < charachers.size(); i++)
	{
		Characher& rChar = charachers.at(i);

		fileStream << rChar.left << ";" << rChar.right << ";" << rChar.up << ";" << rChar.down << ";" << rChar.advance << ";" << maxHeight << std::endl;
	}

	fileStream.close();
}

int main(int argc, char* argv[])
{
	if (argc >= 2)
	{
		ReadArguments(argc, argv);
		InitDevice();
		InitFreeType(argv[1]);
		
		for (int i = 33; i < 127; i++)
		{
			FT_Load_Char(ftFace, i, FT_LOAD_RENDER);

			FT_Glyph glyph;

			FT_Get_Glyph(ftFace->glyph, &glyph);

			FT_Render_Glyph(ftFace->glyph, FT_Render_Mode::FT_RENDER_MODE_NORMAL);

			FT_BBox box;
			FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_PIXELS, &box);

			ID3D11Texture2D* pTexture = nullptr;
			D3D11_TEXTURE2D_DESC textureDesc;

			float glyphWidth = box.xMax - box.xMin;
			float glyphHeight = box.yMax - box.yMin;

			textureDesc.Width = ftFace->glyph->bitmap.width;
			textureDesc.Height = ftFace->glyph->bitmap.rows;
			textureDesc.MipLevels = textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.SampleDesc.Quality = 0;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = 0;
			textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			textureDesc.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA resourceData;

			resourceData.pSysMem = ftFace->glyph->bitmap.buffer;
			resourceData.SysMemPitch = ftFace->glyph->bitmap.pitch;
			resourceData.SysMemSlicePitch = ftFace->glyph->bitmap.width * ftFace->glyph->bitmap.rows;

			HRESULT res = pDevice->CreateTexture2D(&textureDesc, &resourceData, &pTexture);

			Characher characher =
			{
				i,
				pTexture,
				ftFace->glyph->bitmap.width,
				ftFace->glyph->bitmap.rows,
				glyphHeight,
				ftFace->glyph->bitmap_top,
				ftFace->glyph->bitmap_left,
				ftFace->glyph->advance.x >> 6
			};
		
			charachers.push_back(characher);
		}


		const float maxHeight = GetMaxheight();
		Vector2D finalImageSize = CalculateFinalImageSize(ftFace->num_glyphs, maxHeight);
		RoundToPowerOfTwo(finalImageSize);

		
		// Create final dds texture

		D3D11_TEXTURE2D_DESC texture2DDesc;
		ID3D11Texture2D* pFinalTexture;

		
		texture2DDesc.Width = finalImageSize.x;
		texture2DDesc.Height = finalImageSize.y;
		texture2DDesc.MipLevels = 1;
		texture2DDesc.ArraySize = 1;
		texture2DDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8_UNORM;
		texture2DDesc.SampleDesc.Count = 1;
		texture2DDesc.SampleDesc.Quality = 0;
		texture2DDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		texture2DDesc.BindFlags = 0;
		texture2DDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		texture2DDesc.MiscFlags = 0;

		HRESULT hrCode = pDevice->CreateTexture2D(&texture2DDesc, nullptr, &pFinalTexture);

		if (hrCode != S_OK)
		{
			std::cout << "Could not create final image: " << hrCode << std::endl;
			exit(0);
		}

		PopulateFinalImage(pFinalTexture, finalImageSize, maxHeight);

		DirectX::ScratchImage finalScratchImage;
		HRESULT dsadsa2 = DirectX::CaptureTexture(pDevice, pDeviceContext, pFinalTexture, finalScratchImage);
		HRESULT dsadsa = DirectX::SaveToDDSFile(finalScratchImage.GetImages(), finalScratchImage.GetImageCount(), finalScratchImage.GetMetadata(), 0, L"test.dds");

		WriteBoxDataFile(maxHeight);
	}
	else
		std::cout << "Usage: EGTextConverter <tffFilepath> arguments..." << std::endl;
}
