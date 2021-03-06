// Filename:-	tr_font.h
//
// font support

#ifndef TR_FONT_H
#define TR_FONT_H



#define GLYPH_MAX_KOREAN_SHADERS 3
#define GLYPH_MAX_TAIWANESE_SHADERS 4
#define GLYPH_MAX_JAPANESE_SHADERS 3
#define GLYPH_MAX_ASIAN_SHADERS 4	// this MUST equal the larger of the above defines

#define MAX_FONT_VARIANTS 8

class CFontInfo
{
private:
	// From the fontdat file
	glyphInfo_t		mGlyphs[GLYPH_COUNT];

	int				mPointSize;
	int				mHeight;
	int				mAscender;
	int				mDescender;

	int				mAsianHack;
	// end of fontdat data


	int				mShader;				// handle to the shader with the glyph

	char			m_sFontName[MAX_QPATH];	// eg "fonts/lcd"	// needed for korean font-hint if we need >1 hangul set

	int				m_hAsianShaders[GLYPH_MAX_ASIAN_SHADERS];	// shaders for Korean glyphs where applicable
	glyphInfo_t		m_AsianGlyph;			// special glyph containing asian->western scaling info for all glyphs
	int				m_iAsianGlyphsAcross;	// needed to dynamically calculate S,T coords
	int				m_iAsianPagesLoaded;
	bool			m_bAsianLastPageHalfHeight;
	int				m_iAsianLanguageLoaded;	// doesn't matter what this is, so long as it's comparable as being changed

	CFontInfo		*m_variants[MAX_FONT_VARIANTS];
	int				m_numVariants;
	int				m_handle;

public:
	bool			mbRoundCalcs;	// trying to make this !@#$%^ thing work with scaling

	CFontInfo(const char *fontName);
	CFontInfo(int fill) { memset(this, fill, sizeof(*this)); }
	~CFontInfo(void) {}

	int GetHandle();

	void AddVariant(CFontInfo *variant);
	int GetNumVariants();
	CFontInfo *GetVariant(int index);

	const int GetPointSize(void) const { return(mPointSize); }
	const int GetHeight(void) const { return(mHeight); }
	const int GetAscender(void) const { return(mAscender); }
	const int GetDescender(void) const { return(mDescender); }

	const glyphInfo_t *GetLetter(const unsigned int uiLetter, int *piShader = NULL);
	const int GetAsianCode(unsigned int uiLetter) const;

	const int GetLetterWidth(const unsigned int uiLetter) const;
	const int GetLetterHorizAdvance(const unsigned int uiLetter) const;
	const int GetShader(void) const { return(mShader); }

	void FlagNoAsianGlyphs(void) { m_hAsianShaders[0] = 0; m_iAsianLanguageLoaded = -1; }	// used during constructor
	bool AsianGlyphsAvailable(void) const { return !!(m_hAsianShaders[0]); }

	void UpdateAsianIfNeeded( bool bForceReEval = false);
};

void R_ShutdownFonts(void);
void R_InitFonts(void);
int RE_RegisterFont(const char *psName);
int RE_Font_StrLenPixels(const char *psText, const int iFontHandle, float fScale, float xadjust, float yadjust);
int RE_Font_StrLenChars(const char *psText);
int RE_Font_HeightPixels(const int iFontHandle, float fScale, float xadjust, float yadjust);
void RE_Font_DrawString(int ox, int oy, const char *psText, const vec4_t rgba,
	int iFontHandle, int iCharLimit, float fScale, float xadjust, float yadjust);
qboolean Language_IsAsian(void);
qboolean Language_UsesSpaces(void);
unsigned int AnyLanguage_ReadCharFromString( const char *psText, int *piAdvanceCount, qboolean *pbIsTrailingPunctuation/* = NULL*/ );



#endif	// #ifndef TR_FONT_H

// end

