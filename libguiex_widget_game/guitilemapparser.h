/** 
* @file guitilemapparser.h
* @brief 
* @author Lou Guoliang (louguoliang@gmail.com)
* @date 2011-01-27
*/
#ifndef	__KEN_TILEMAPPARSER_20110127_H__
#define __KEN_TILEMAPPARSER_20110127_H__


//============================================================================//
// include
//============================================================================//
#include <libguiex_core/guibase.h>
#include <libguiex_core/guiintsize.h>
#include <libguiex_core/guiintvector2.h>
#include <libguiex_core/guirect.h>
#include <vector>
#include <map>

//============================================================================//
// declare
//============================================================================//
namespace guiex
{
	enum 
	{
		TMXLayerAttribNone = 1 << 0,
		TMXLayerAttribBase64 = 1 << 1,
		TMXLayerAttribGzip = 1 << 2,
	};

	enum 
	{
		TMXPropertyNone,
		TMXPropertyMap,
		TMXPropertyLayer,
		TMXPropertyObjectGroup,
		TMXPropertyObject,
		TMXPropertyTile
	};
}
class TiXmlElement;

//============================================================================//
// class
//============================================================================// 
namespace guiex
{
	/* CCTMXLayerInfo contains the information about the layers like:
	- Layer name
	- Layer size
	- Layer opacity at creation time (it can be modified at runtime)
	- Whether the layer is visible
	This information is obtained from the TMX file.
	*/
	class CCTMXLayerInfo
	{
	public:
		CCTMXLayerInfo();
		~CCTMXLayerInfo();

	public:
		CGUIString name;
		CGUIIntSize layerSize;
		uint32 *tiles;
		bool visible;
		real opacity;
		bool ownTiles;
		uint32 minGID;
		uint32 maxGID;
		std::map<CGUIString, CGUIString> properties;
		CGUIIntVector2 offset;
	};

	class CCTMXObjectInfo
	{
	public:
		CGUIString objectName;
		CGUIString objectType;
		CGUIIntVector2 position;
		CGUIIntSize size;
		std::map<CGUIString,CGUIString>	properties;
	};

	class CCTMXObjectGroup
	{
	public:
		CCTMXObjectGroup();
		~CCTMXObjectGroup();

	public:
		CGUIString groupName;
		CGUIIntVector2 positionOffset;
		std::vector<CCTMXObjectInfo*> objects;
		std::map<CGUIString,CGUIString>	properties;
	};

	/* CCTMXTilesetInfo contains the information about the tilesets like:
	- Tileset name
	- Tilset spacing
	- Tileset margin
	- size of the tiles
	- Image used for the tiles
	- Image size

	This information is obtained from the TMX file. 
	*/
	class CCTMXTilesetInfo
	{
	public:
		CCTMXTilesetInfo();
		~CCTMXTilesetInfo();

		CGUIRect RectForGID( uint32 gid );

	public:
		CGUIString name;
		uint32 firstGid;
		CGUIIntSize tileSize;
		uint32 spacing;
		uint32 margin;
		CGUIString sourceImage; // image containing the tiles
		CGUIIntSize imageSize; // size in pixels of the image
	};


	/* CCTMXMapInfo contains the information about the map like:
	- Map orientation (hexagonal, isometric or orthogonal)
	- Tile size
	- Map size

	And it also contains:
	- Layers (an array of TMXLayerInfo objects)
	- Tilesets (an array of TMXTilesetInfo objects)
	- ObjectGroups (an array of TMXObjectGroupInfo objects)

	This information is obtained from the TMX file.
	*/
	class CCTMXMapInfo
	{	
	public:	
		CCTMXMapInfo();
		~CCTMXMapInfo();

		int32 InitWithTMXFile( const CGUIString& tmxFile );

	protected:
		int32 ParseXMLFile( const CGUIString& tmxFile );
		int32 ParseNode_map( TiXmlElement* pMapNode );
		int32 ParseNode_tileset( TiXmlElement* pTilesetNode );
		int32 ParseNode_layer( TiXmlElement* pLayerNode );
		int32 ParseNode_image( TiXmlElement* pImageNode );
		int32 ParseNode_tile( TiXmlElement* pTileNode );
		int32 ParseNode_properties( TiXmlElement* pPropertiesNode, std::map<CGUIString, CGUIString>& mapTileProperties );
		int32 ParseNode_data( TiXmlElement* pTileNode );
		int32 ParseNode_objectgroup( TiXmlElement* pObjectGroupNode );
		int32 ParseNode_object( TiXmlElement* pObjectNode );

		int32 ParseSourceFile( const CGUIString& tmxFile );


	public:
		uint32 parentGID;
		CGUIString filename; // tmx filename
		int32 orientation;	// map orientation
		CGUIIntSize mapSize; // map width & height
		CGUIIntSize tileSize; // tiles width & height
		std::vector<CCTMXLayerInfo*> layers; // Layers
		std::vector<CCTMXTilesetInfo*> tilesets; // tilesets
		std::vector<CCTMXObjectGroup*> objectGroups; // ObjectGroups
		std::map<CGUIString, CGUIString> properties; // properties
		std::map<uint32, std::map<CGUIString, CGUIString> > tileProperties; // tile properties <gid, tile property>
	};

} //namespace guiex

#endif //__KEN_TILEMAPPARSER_20110127_H__

