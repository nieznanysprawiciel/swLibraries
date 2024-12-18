#pragma once
/**
@file Text.h
@author nieznanysprawiciel
@copyright File is part of Sleeping Wombat Libraries.
*/

#include "swGraphicAPI/Assets/TextAsset/FontAsset.h"

#include "swCommonLib/Common/Buffers/IndexedGeometryBuffer.h"
#include "swGeometrics/GeometricsCore/Math/Types.h"
#include "swGeometrics/GeometricsCore/Types/VertexLayouts/VertexShape2D.h"
#include "swGeometrics/GeometricsCore/Types/IndexTypes.h"
#include "swGeometrics/GeometricsCore/Types/Accessors/TextAccessors.h"
#include "swGeometrics/GeometricsCore/Types/Traits/GeneratorTraits.h"



namespace sw
{

/**@brief Decides how text should be aligned.
@ingroup Text*/
enum class TextAlignment : u8
{
    Left,
    Center,
    Right,
    Justify,
};


/**@brief Arranges text.
@ingroup Text*/
class TextArranger
{
public:
    float                   Interspace;
    float                   Interline;      //< Multiplier to compute distance between lines.
    float                   SpaceSize;
    TextAlignment           TextAlign;
    bool                    UseKerning;
    /**Wrap text according to Bounds. If set to false, single text line won't have any limit and only
    NewLine characters will break line.
    Depending on TextAlignment, Bounds will be used to determine left, right or center of the text.*/
    bool                    WrapText;
    /**Text crossing lower Bound won't be generated.*/
    bool                    CutOutOfBounds;
    bool                    SnapToPixel;    //< Avoids letters blurring if they are not aligned to pixel grid.
    Rect2d                  Bounds;

public:
    explicit TextArranger()
        : Interspace( 0.0f )
        , Interline( 1.5f )
        , SpaceSize( 0.0f )
        , TextAlign( TextAlignment::Left )
        , UseKerning( true )
        , WrapText( false )
        , CutOutOfBounds( false )
        , SnapToPixel( true )
        , Bounds( { 0.0f, 0.0f, 0.0f, 0.0f } )
    {}

    /**@brief Creates Arranger setting some default values from FontAsset.*/
    static TextArranger         CreateFrom( const FontAssetPtr font );

public:
    std::vector< Position2d >   ArrangeText( const std::wstring& text, const FontLayout& layout ) const;
    std::vector< Position2d >   ArrangeLine( std::wstring_view text, const FontLayout& layout, Position2d startPosition ) const;
    void                        ApplyAlignement( const FontLayout& layout, std::vector< Position2d >& letters, std::wstring_view text ) const;
    
    float                       TextWidth( const std::vector< Position2d >& letters, const std::wstring& text, const FontLayout& layout ) const; 
    float                       MoveToPixelGrid( float value ) const;

    static bool                 IsWhitespace( wchar_t character );
    static bool                 IsNewline( wchar_t character );
    static bool                 IsSpace( wchar_t character );
    static Size                 EstimateLineLength( std::wstring_view text );
    static Rect2d               ComputeTextBounds( const std::vector< Position2d >& letters, const FontLayout& layout );
    static Size                 CountTrailingWhitespaces( const std::wstring_view& text );

    static Position2d           TopLeftVertex( const Glyph& glyph, Position2d pos );
    static Position2d           TopRightVertex( const Glyph& glyph, Position2d pos );
    static Position2d           BottomLeftVertex( const Glyph& glyph, Position2d pos );
    static Position2d           BottomRightVertex( const Glyph& glyph, Position2d pos );

public:
    Nullable< geom::IndexedGeometryBuffer< geom::VertexShape2D, Index32 > >   GenerateGeometry( const std::wstring& text, const FontAssetPtr font, bool genBackground ) const;
    Nullable< geom::IndexedGeometryBuffer< geom::VertexText2D, Index32 > >    GenerateGeometryTextured( const std::wstring& text, const FontAssetPtr font, bool genBackground ) const;

    Size                        NumBorderIndicies() const { return 6; }
};


/**@brief Class for displaying Text on screen.

Layouts and formats text according to rules and parameters provided.
Generates vertex buffer for displaying text on screen.

This class can be used to display simple texts that use only one font without special formatting.
For more complicated cases where some parts of the text have different formatting, new class should be created.

@ingroup Text*/
class Text
{
private:
protected:
    FontAssetPtr        m_font;
    VertexShaderPtr		m_vertexShader;
    PixelShaderPtr		m_pixelShader;

    TextArranger        m_arrange;

    std::wstring        m_text;     // Text to display.

public:
	explicit Text() = default;
	virtual ~Text() = default;

};


/**@brief Generates geometry for text using arranged letters.
@ingroup Text*/
template< typename VertexType, typename IndexType, typename TextAcc = geom::TextAcc< VertexType > >
class TextGeometryGenerator : public geom::GeneratorTraits< VertexType, IndexType >
{
private:
    const FontAssetPtr          m_font;
    const FontLayout&           m_layout;
    const std::wstring&         m_text;

    private:
    /**@brief Helper buffer with pregenerated text letters coordinates.*/
    std::vector< Position2d >   m_letters;

private:

    float       m_atlasWidth;
    float       m_atlasHeight;

public:
    /**@brief Generate rectangle for background of size equal to @ref TextArranger::Bounds.*/
    bool                        GenerateBackground;
    Rect2d                      Bounds;

public:
    explicit TextGeometryGenerator( std::vector< Position2d >&& letters, const FontAssetPtr font, const std::wstring& text )
        : m_layout( font->GetLayout() )
        , m_font( font )
        , m_letters( letters )
        , m_text( text )
        , GenerateBackground( false )
        , m_atlasWidth( (float)font->GetFontAtlas()->GetDescriptor().Width )
        , m_atlasHeight( (float)font->GetFontAtlas()->GetDescriptor().Height )
    {}

public:
    inline void			GenerateVertex			( VertexType& vertex, Size vertexIdx );

    template< class IndexBuffer >
    inline void			GenerateIndexBuffer		( IndexBuffer& idxBuffer, Size startIdx );

    inline Size			GetNumberVerticies		() const;
    inline Size			GetNumberIndicies		() const;

	inline Size         GetNumberTextIndicies   () const;
    inline Size         GetNumberBorderIndicies () const;

    inline ReturnResult	ValidateParams			() const;

protected:
    inline void			GenerateBackgroundVertex    ( VertexType& vertex, Size vertexIdx );
    inline void			GenerateTextVertex          ( VertexType& vertex, Size vertexIdx );

    inline Size         FindLetterIndex				( Size vertexIdx ) const;
    inline void         PutWhitespaceVertex         ( VertexType& vertex, Size vertexIdx, Position2d position ) const;
    inline void         PutLetterVertex             ( VertexType& vertex, const Glyph& glyph, Position2d position, Size vertexIdx ) const;
    inline void         PutLetterUV                 ( VertexType& vertex, const Glyph& glyph, Position2d position, Size vertexIdx ) const;
};


}	// sw

#include "Text.inl"
