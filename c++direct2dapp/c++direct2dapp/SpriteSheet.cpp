#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(wchar_t* filename, int _frameWidth, int _frameHeight, int _frame, Graphics* gfx)
{
	frameWidth = _frameWidth;
	frameHeight = _frameHeight;
	frame = _frame;
	this->gfx = gfx;
	
	bmp = NULL;
	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);


	IWICBitmapDecoder *wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		filename,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);


IWICBitmapFrameDecode* wicFrame = NULL;
hr = wicDecoder->GetFrame(0, &wicFrame);

IWICFormatConverter *wicConverter = NULL;
hr = wicFactory->CreateFormatConverter(&wicConverter);

hr = wicConverter->Initialize(
	wicFrame,
	GUID_WICPixelFormat32bppPBGRA,
	WICBitmapDitherTypeNone,
	NULL,
	0.0,
	WICBitmapPaletteTypeCustom
	);

hr = gfx->GetRenderTarget()->CreateBitmapFromWicBitmap(
	wicConverter,
	NULL,
	&bmp
	);
if (wicFactory) wicFactory->Release();
if (wicDecoder) wicDecoder->Release();
if (wicConverter) wicConverter->Release();
if (wicFrame) wicFrame->Release();
}

SpriteSheet::~SpriteSheet()
{
	if (bmp) bmp->Release();
}

void SpriteSheet::Draw(int _frame, float _x, float _y)
{
	gfx->GetRenderTarget()->DrawBitmap(
		bmp,
		D2D1::RectF(_x, _y,
		_x + frameWidth, _y + frameHeight),
		1.0f,
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		D2D1::RectF(frameWidth*_frame, 0,
		frameWidth*_frame+frameWidth, 100)
		);
}