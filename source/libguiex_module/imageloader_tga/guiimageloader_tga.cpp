/** 
* @file guiimageloader_tga.cpp
* @brief interface to load image from file or memory.
* @author ken
* @date 2006-07-13
*/

//============================================================================//
// include 
//============================================================================// 
#include <libguiex_module/imageloader_tga/guiimageloader_tga.h>
#include <libguiex_core/guiexception.h>
#include <libguiex_core/guiinterfacemanager.h>
#include <libguiex_core/guiinterfacefilesys.h>

//============================================================================//
// declare
//============================================================================// 
namespace guiex
{
	typedef struct
	{
		uint8 Header[12];									// TGA File Header
	} TGAHeader;

	typedef struct
	{
		uint8		header[6];								// First 6 Useful Bytes From The Header
		uint32		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
		uint32		imageSize;								// Used To Store The Image Size When Setting Aside Ram
		uint32		temp;									// Temporary Variable
		EGuiPixelFormat	type;	
		uint32		Height;									//Height of Image
		uint32		Width;									//Width ofImage
		uint32		Bpp;									// Bits Per Pixel
	} TGA;


	static uint8 uTGAcompare1[12] = {0,0,2, 0,0,0,0,0,0,0,0,0}; // Uncompressed, RGB images
	static uint8 uTGAcompare2[12] = {0,0,3, 0,0,0,0,0,0,0,0,0}; // Uncompressed, black and white images
	static uint8 cTGAcompare1[12] = {0,0,10,0,0,0,0,0,0,0,0,0};	// Compressed, RGB images.
	static uint8 cTGAcompare2[12] = {0,0,11,0,0,0,0,0,0,0,0,0};	// Compressed, black and white images.
}


//============================================================================//
// function
//============================================================================// 
namespace guiex
{
	//------------------------------------------------------------------------------
	GUI_INTERFACE_IMPLEMENT(IGUIImageLoader_tga);
	//------------------------------------------------------------------------------
	const char* IGUIImageLoader_tga::StaticGetModuleName()
	{
		return "IGUIImageLoader_tga";
	}
	//------------------------------------------------------------------------------
	IGUIImageLoader_tga::IGUIImageLoader_tga()
		:IGUIInterfaceImageLoader( StaticGetModuleName() )
	{
	}
	//------------------------------------------------------------------------------
	IGUIImageLoader_tga::~IGUIImageLoader_tga()
	{
	}
	//------------------------------------------------------------------------------
	/** 
	* @brief initialize render
	* @return 0 for success
	*/
	int	IGUIImageLoader_tga::DoInitialize(void* )
	{

		return 0;
	}
	//------------------------------------------------------------------------------
	/** 
	* @brief destroy render
	* @return 0 for success
	*/
	void IGUIImageLoader_tga::DoDestroy()
	{

	}
	//------------------------------------------------------------------------------
	/**
	* @brief load image from file
	* @return pointer of CGUIImageData, NULL for failed
	*/
	CGUIImageData* IGUIImageLoader_tga::LoadFromFile( const CGUIString& rFileName  )
	{
		IGUIInterfaceFileSys* pFileSys =  CGUIInterfaceManager::Instance()->GetInterfaceFileSys();;
		CGUIDataChunk aDataChunk;
		if( 0 == pFileSys->ReadFile( rFileName, aDataChunk ))
		{
			return LoadFromMemory(aDataChunk.GetDataPtr(), aDataChunk.GetSize());
		}

		return NULL;
	}
	//------------------------------------------------------------------------------
	/**
	* @brief load image from memory
	* @return pointer of CGUIImageData, NULL for failed
	*/
	CGUIImageData* IGUIImageLoader_tga::LoadFromMemory( uint8* pFileData, size_t nSize )
	{
		if( !pFileData || nSize <= sizeof( TGAHeader) )
		{
			return NULL;
		}

		TGAHeader tgaheader;
		uint32 uHeadSize = sizeof( TGAHeader);
		memcpy( &tgaheader, pFileData, uHeadSize );
		pFileData += uHeadSize;
		nSize -= uHeadSize;

		if(memcmp(uTGAcompare1, &tgaheader, uHeadSize) == 0 ||
			memcmp(uTGAcompare2, &tgaheader, uHeadSize) == 0)	
		{														
			return LoadUncompressedTGA(pFileData, nSize );
		}
		else if(memcmp(cTGAcompare1, &tgaheader, uHeadSize) == 0 ||
			memcmp(cTGAcompare2, &tgaheader, uHeadSize) == 0 )
		{																
			return LoadCompressedTGA(pFileData, nSize);				
		}
		else															
		{
			GUI_THROW( "[IGUIImageLoader_tga::LoadFromMemory] - Failed to load tga image!");
			return NULL;
		}
	}
	//------------------------------------------------------------------------------
	CGUIImageData* IGUIImageLoader_tga::LoadUncompressedTGA( uint8* pFileData, size_t nSize )
	{
		if( !pFileData || nSize <= 0 )
		{
			return NULL;
		}

		TGA tga;
		uint32 uHeadSize = sizeof(tga.header);
		if( nSize < uHeadSize )
		{
			GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
			return NULL;
		}
		memcpy( tga.header, pFileData, uHeadSize );
		pFileData += uHeadSize;
		nSize -= uHeadSize;

		tga.Width = tga.header[1] * 256 + tga.header[0];
		tga.Height = tga.header[3] * 256 + tga.header[2];
		tga.Bpp		= tga.header[4];

		if(tga.Width <= 0 || tga.Height <= 0)
		{
			GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
			return NULL;
		}

		switch( tga.Bpp )
		{
		case 24:
			tga.type = GUI_PF_RGB_24;
			break;
		case 32:
			tga.type = GUI_PF_RGBA_32;
			break;		
		case 8:
			tga.type = GUI_PF_ALPHA_8;
			break;
		default:
			GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
			return NULL;
		}

		tga.bytesPerPixel = CGUIImageData::GetBytePerPixel( tga.type );					
		tga.imageSize = (tga.bytesPerPixel * tga.Width * tga.Height);	
		if( nSize < tga.imageSize )
		{
			GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
			return NULL;
		}
		//create image data
		CGUIImageData * pImageData = new CGUIImageData(this);
		uint8* tmpBuff = pImageData->SetImageData(tga.Width, tga.Height, tga.type);
		uint32 uDataLineBytes = pImageData->GetWidth()*pImageData->GetBytePerPixel();
		uint32 uFileLineBytes = tga.Width*pImageData->GetBytePerPixel();
		for( uint32 i=0; i<tga.Height; ++i )
		{
			memcpy( tmpBuff + i*uDataLineBytes, pFileData+i*uFileLineBytes, uFileLineBytes );
		}

		if( tga.type == GUI_PF_RGBA_32 || tga.type == GUI_PF_RGB_24 )
		{
			for( uint32 i=0; i<tga.Height; ++i )
			{
				uint32 uWidthStart = i*uDataLineBytes;
				for( uint32 j=0; j<tga.Width; ++j )
				{
					uint32 uStart = uWidthStart + j*pImageData->GetBytePerPixel();
					uint8 temp = tmpBuff[uStart];
					tmpBuff[uStart] = tmpBuff[uStart+2];
					tmpBuff[uStart+2] = temp;
				}
			}
		}
		return pImageData;
	}
	//------------------------------------------------------------------------------
	CGUIImageData* IGUIImageLoader_tga::LoadCompressedTGA( uint8* pFileData, size_t nSize )
	{
		TGA tga;
		uint32 uHeadSize = sizeof(tga.header);
		if( nSize < uHeadSize )
		{
			GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
			return NULL;
		}
		memcpy( tga.header, pFileData, uHeadSize );
		pFileData += uHeadSize;
		nSize -= uHeadSize;

		tga.Width  = tga.header[1] * 256 + tga.header[0];					// Determine The TGA Width	(highbyte*256+lowbyte)
		tga.Height = tga.header[3] * 256 + tga.header[2];					// Determine The TGA Height	(highbyte*256+lowbyte)
		tga.Bpp	= tga.header[4];										// Determine Bits Per Pixel

		if((tga.Width <= 0) || (tga.Height <= 0) || ((tga.Bpp != 24) && (tga.Bpp !=32)))
		{
			GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
			return NULL;
		}

		if(tga.Bpp == 24)		
			tga.type = GUI_PF_RGB_24;
		else					
			tga.type = GUI_PF_RGBA_32;

		tga.bytesPerPixel	= (tga.Bpp / 8);									// Compute BYTES per pixel
		tga.imageSize		= (tga.bytesPerPixel * tga.Width * tga.Height);		// Compute amout of memory needed to store image
		//create image data
		CGUIImageData * pImageData = new CGUIImageData(this);
		uint8* tmpBuff = pImageData->SetImageData(tga.Width, tga.Height, tga.type);

		uint32 pixelcount	= tga.Height * tga.Width;							// Nuber of pixels in the image
		uint32 currentpixel	= 0;												// Current pixel being read
		uint32 currentbyte	= 0;												// Current byte 
		uint8 * colorbuffer = (uint8 *)malloc(tga.bytesPerPixel);			// Storage for 1 pixel

		do
		{
			uint8 chunkheader = 0;											// Storage for "chunk" header

			uint32 uChunkHeadSize = sizeof(uint8);
			if( nSize < uChunkHeadSize )
			{
				delete pImageData;
				free( colorbuffer );
				GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
				return NULL;
			}
			memcpy( &chunkheader, pFileData, uChunkHeadSize );
			pFileData += uChunkHeadSize;
			nSize -= uChunkHeadSize;

			if(chunkheader < 128)												// If the ehader is < 128, it means the that is the number of RAW color packets minus 1
			{																	// that follow the header
				chunkheader++;													// add 1 to get number of following color values
				for(short counter = 0; counter < chunkheader; counter++)		// Read RAW color values
				{
					if( nSize < tga.bytesPerPixel )
					{
						delete pImageData;
						free( colorbuffer );
						GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
						return NULL;
					}
					memcpy( colorbuffer, pFileData, tga.bytesPerPixel );
					pFileData += tga.bytesPerPixel;
					nSize -= tga.bytesPerPixel;

					// write to memory
					tmpBuff[currentbyte		] = colorbuffer[2];				    // Flip R and B vcolor values around in the process 
					tmpBuff[currentbyte + 1	] = colorbuffer[1];
					tmpBuff[currentbyte + 2	] = colorbuffer[0];

					if(tga.bytesPerPixel == 4)												// if its a 32 bpp image
					{
						tmpBuff[currentbyte + 3] = colorbuffer[3];				// copy the 4th byte
					}

					currentbyte += tga.bytesPerPixel;										// Increase thecurrent byte by the number of bytes per pixel
					currentpixel++;															// Increase current pixel by 1

					if(currentpixel > pixelcount)											// Make sure we havent read too many pixels
					{
						delete pImageData;
						free( colorbuffer );
						GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
						return NULL;													// Return failed
					}
				}
			}
			else																			// chunkheader > 128 RLE data, next color reapeated chunkheader - 127 times
			{
				chunkheader -= 127;		
				if( nSize < tga.bytesPerPixel )
				{
					delete pImageData;
					free( colorbuffer );
					GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
					return NULL;
				}
				memcpy( colorbuffer, pFileData, tga.bytesPerPixel );
				pFileData += tga.bytesPerPixel;
				nSize -= tga.bytesPerPixel;

				for(short counter = 0; counter < chunkheader; counter++)					// copy the color into the image data as many times as dictated 
				{																			// by the header
					tmpBuff[currentbyte		] = colorbuffer[2];					// switch R and B bytes areound while copying
					tmpBuff[currentbyte + 1	] = colorbuffer[1];
					tmpBuff[currentbyte + 2	] = colorbuffer[0];

					if(tga.bytesPerPixel == 4)												// If TGA images is 32 bpp
					{
						tmpBuff[currentbyte + 3] = colorbuffer[3];				// Copy 4th byte
					}

					currentbyte += tga.bytesPerPixel;										// Increase current byte by the number of bytes per pixel
					currentpixel++;															// Increase pixel count by 1

					if(currentpixel > pixelcount)											// Make sure we havent read too many pixels
					{
						delete pImageData;
						free( colorbuffer );
						GUI_THROW( "[IGUIImageLoader_tga::LoadUncompressedTGA] - Invalid texture information!");
						return NULL;													// Return failed
					}
				}
			}
		}
		while(currentpixel < pixelcount);	

		free( colorbuffer );
		return pImageData;
	}
	//------------------------------------------------------------------------------
	/**
	* @brief destroy image data
	*/
	void IGUIImageLoader_tga::DestroyImageData(CGUIImageData* pImageData)
	{
		delete pImageData;
	}
	//------------------------------------------------------------------------------
	/**
	* @brief used to delete this object
	*/
	void IGUIImageLoader_tga::DeleteSelf()
	{
		delete this;
	}
	//------------------------------------------------------------------------------


}//namespace guiex

