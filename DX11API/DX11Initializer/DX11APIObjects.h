#pragma once

/**@file DX11APIObjects.h
@author nieznanysprawiciel
@copyright Plik jest cz�ci� silnika graficznego SWEngine.

@brief Zawiera deklaracj� klasy DX11APIObjects i DX11AuxiliaryObjects s�u��cych do
inicjowania i przechowywania obiekt�w DirectXa.
*/

#include <string>

#pragma warning( disable : 4005 )
#include "d3dx11.h"
#include "d3d11.h"
#pragma warning( default : 4005 )


typedef ID3D11DeviceContext DeviceContext;
typedef ID3D11Device Device;


/**Kody b��d�w zwracane przez funkcje klasy DX11APIObjects.*/
enum DX11_INIT_RESULT
{
	DX11_INIT_OK,								///< Funkcja wykonana poprawnie
	NO_CLASS_INHERTIS_THIS_INTERFACE,			///< �adna klasa nie odziedziczy�a po DX11APIObjects. Zmienne s� niezainicjalizowane.
	COULD_NOT_INIT_DEVICES_AND_SWAPCHAIN,		///< Nie uda�o si� utworzy� obiek�w device, device_context i swap_chain.
	COULD_NOT_CREATE_BACKBUFFER,				///< Nie uda�o si� utworzy� bufora tylnego.
	COULD_NOT_CREATE_RENDERTARGET,				///< Nie uda�o si� zainicjowa� widoku na bufor tylni.
	COULD_NOT_CREATE_DEPTHSTENCIL,				///< Nie usta�o si� stworzy� bufora g��boko�ci.
	COULD_NOT_CREATE_DEPTHSTENCIL_VIEW,			///< Nie uda�o si� stworzy� widoku na bufor g��boko�ci.
	COULD_NOT_CREATE_PIXEL_SHADER,				///< Nie uda�o si� skompilowa� pixel shadera.
	COULD_NOT_CREATE_VERTEX_SHADER,				///< Nie uda�o si� skompilowa� vertex shadera.
	COULD_NOT_CREATE_SAMPLER,					///< Nie uda�o si� utworzy� obiektu samplera.
	DX11_DEVICE_NOT_INITIALIZED,				///< DirectX nie zosta� zainicjowany (obiekt device wskazuje na nullptr).
	DX11_DEVICECONTEXT_NOT_INITIALIZED			///< DirectX nie zosta� zainicjowany (obiekt device_context wskazuje na nullptr).
};

/**Enumeruje wbudowane typy layout�w.*/
enum DX11_DEFAULT_VERTEX_LAYOUT
{
	VERTEX_NORMAL_TEXTURE = 0,			///< Pozycja, normalne wsp�rz�dne UV
	VERTEX_TEXTURE = 1,					///< Pozycja, wsp�rz�dne UV
	VERTEX_COLOR = 2,					///< Pozycja, kolor
	VERTEX_NORMAL_COLOR = 3				///< Pozycja, normalne, kolor
};

/**@brief Klasa przechowuje w zmiennych statycznych najwa�niejsze interfejsy
DirectX11.

Obiekty, kt�re ich potrzebuj�, powinny odziedziczy� po tej klasie,
dzi�ki czemu maj� bezpo�redni dost�p.

Aby naj�atwiej zainicjowa� DirectX, najlepiej jest wywo�a� funkcj� init_DX11.
Z wyj�tkiem rzeczy podawanych w parametrach, wszystko zostanie zainicjowane zgodnie z deskryptorami
domy�lnymi. Je�eli chcesz co� zmieni�, to musisz to zrobi� przed wywo�aniem tej funkcji.

Mo�na te� inicjowa� ka�d� rzecz z osobna, ale w zasadzie nie ma to wi�kszego sensu,
skoro wiszystkie deskryptory mo�na zmodyfikowa�.

Klasa daje te� mo�liwo�� kompilowania shader�w.*/

class DX11APIObjects
{
protected:
	static DX11APIObjects*			this_ptr;		///<Wa�ne, �eby nie zainicjowac obiektu wielokrotnie.

	static bool						m_useDebugLayer;

	static unsigned int				_window_width;
	static unsigned int				_window_height;
	static std::string				_pixel_shader_model;
	static std::string				_vertex_shader_model;

	static DXGI_SWAP_CHAIN_DESC		_swap_chain_desc;	///<Domy�lny deskryptor g��wnych obiekt�w DirectX11
	static D3D11_VIEWPORT			_view_port_desc;	///<Domy�lny deskryptor viewportu. Je�eli u�ytkownik poda w�asny to zostanie on nadpisany.
	static D3D_FEATURE_LEVEL*		_feature_levels;	///<Tablica z preferowanymi poziomami DirectX. Domy�lnie nullptr, uzytkownik mo�e zdefiniowa�.
	static unsigned int				_num_feature_levels;///<Liczba element�w powy�szej tablicy.
	static D3D_FEATURE_LEVEL		_current_feature_level;		///<Przechowuje poziom DirectXa.
	static D3D11_TEXTURE2D_DESC		_z_buffer_desc;				///<Deskryptor z i stencil bufora.
	static D3D11_DEPTH_STENCIL_VIEW_DESC	_z_buffer_view_desc;	///<Deskryptor widoku z i stencil bufora.
	static D3D11_INPUT_ELEMENT_DESC*		_vertex_layout_desc;	///<Aktualny deskryptor layoutu wierzcho�ka.
	static unsigned int				_layout_elements_count;			///<Liczba element�w w talicy deskryptora layoutu.
	static D3D11_SAMPLER_DESC		_sampler_desc;			///<Deskryptor samplera.
	static D3D11_RASTERIZER_DESC	_rasterizer_desc;		///<Deskryptor rasteryzatora.
protected:
	static ID3D11Debug*				debug_interface;		///<Pozwala na pobranie bardziej szczeg�owych informacji debugowych.
	static ID3D11Device*			device;					///<Zmienna s�u�y do tworzenia obiekt�w, bufor�w tekstur i zasob�w
	static ID3D11DeviceContext*		device_context;			///<Zmienna u�ywana do renderowania sceny, ustawiania bufor�w, shader�w itp.
	static IDXGISwapChain*			swap_chain;				///<S�u�y do prezentowania ramki na ekranie
	static ID3D11RenderTargetView*	render_target;			///<Widok bufora docelowego renderowania, czyli bufora tylnego
	static ID3D11DepthStencilView*	z_buffer_view;			///<Widok z-buffora
	static ID3D11Texture2D*			back_buffer;			///<Tekstura bufora tylnego.
	static ID3D11Texture2D*			z_buffer;				///<Tekstura z-bufora.

	static ID3D11SamplerState*		default_sampler;		///<Obiekt domy�lnego samplera
	static ID3D11InputLayout*		default_vertex_layout;	///<Layout formatu wierzcho�ka u�ywanego dla meshy
	static ID3D11VertexShader*		default_vertex_shader;	///<Obiekt domy�lnego vertex shadera
	static ID3D11PixelShader*		default_pixel_shader;	///<Obiekt domy�lnego piksel shadera
protected:	//public:	Inicjalizacje powinien zrobi� obiekt, kt�ry dzidziczy po tej klasie, dlatego zmieni�em.
	// Funkcje do ustawiania deskryptor�w i innych parametr�w
	void set_swapchain_desc				( const DXGI_SWAP_CHAIN_DESC& swap_chain_desc );
	void set_viewport_desc				( const D3D11_VIEWPORT& view_port_desc );
	void set_feature_levels				( D3D_FEATURE_LEVEL* feature_levels, unsigned int elements );
	void set_window_resolution			( unsigned int window_width, unsigned int window_height );
	void set_depth_stencil_format		( DXGI_FORMAT depth_stencil_format );
	void set_vertex_layout				( DX11_DEFAULT_VERTEX_LAYOUT layout );
	void set_vertex_layout				( D3D11_INPUT_ELEMENT_DESC* layout, unsigned int array_size );
	void set_sampler_desc				( D3D11_SAMPLER_DESC sampler_desc );
	void set_rasterizer_desc			( const D3D11_RASTERIZER_DESC& rasterizer_desc );

	// Pobieranie deskryptor�w
	static DXGI_SWAP_CHAIN_DESC					get_swap_chain_desc()		{ return _swap_chain_desc; }
	static D3D11_VIEWPORT						get_viewport_desc()			{ return _view_port_desc; }
	static D3D_FEATURE_LEVEL					get_current_feature_level() { return _current_feature_level; }
	static D3D11_TEXTURE2D_DESC					get_z_buffer_desc()			{ return _z_buffer_desc; }
	static D3D11_DEPTH_STENCIL_VIEW_DESC		get_z_buffer_view_desc()	{ return _z_buffer_view_desc; }
	static D3D11_SAMPLER_DESC					get_sampler_desc()			{ return _sampler_desc; }
	static D3D11_RASTERIZER_DESC				get_rasterizer_desc()		{ return _rasterizer_desc; }

	ID3D11VertexShader*		load_vertex_shader( const std::wstring& file_name, const std::string& shader_name, const char* shader_model );
	ID3D11VertexShader*		load_vertex_shader( const std::wstring& file_name, const std::string& shader_name,
											ID3D11InputLayout** layout, D3D11_INPUT_ELEMENT_DESC* layout_desc,
											unsigned int array_size, const char* shader_model );
	ID3D11PixelShader*		load_pixel_shader( const std::wstring& file_name, const std::string& shader_name, const char* shader_model );


	// Funkcje inicjuj�ce
	DX11_INIT_RESULT InitDevicesAndSwapChain	( HWND window, bool fullscreen, bool single_thread = true );
	DX11_INIT_RESULT init_viewport				();
	DX11_INIT_RESULT init_z_buffer_and_render_target();
	DX11_INIT_RESULT init_vertex_shader( const std::wstring& file_name, const std::string& shader_name );
	DX11_INIT_RESULT init_pixel_shader( const std::wstring& file_name, const std::string& shader_name );
	DX11_INIT_RESULT init_sampler();

protected:
	DX11APIObjects();
	~DX11APIObjects() = default;

	DX11_INIT_RESULT init_DX11( int width, int height, HWND window, bool fullscreen,
								const std::wstring& pix_shader_file, const std::string& pix_shader_name,
								const std::wstring& vert_shader_file, const std::string& vert_shader_name,
								bool single_thread = true );
	DX11_INIT_RESULT init_DX11( int width, int height, HWND window, bool fullscreen, bool single_thread = true );


	virtual void release_DirectX();

	void begin_scene();
	inline void end_scene_and_present() { swap_chain->Present( 0, 0 ); }	///<Wywo�uje funkcj� swap_chain->Present w celu wy�wietlenia narysowanej sceny na monitorze

protected:

	void			SetDebugName		( ID3D11DeviceChild* child, const std::string& name );
	bool			IsDebugLayerEnabled	();
};



/**@brief Klasa zawiera wska�niki na bufory sta�ych zawieraj�ce podstawowe zestawy
element�w przekazywanych do shader�w. S� to miedzy innymi macierze transformacji.

@note Je�eli w jakimkolwiek miejscu s� u�ywane obiekty z tej klasy (DX11AuxiliaryObjects), a nie tylko z klasy bazowej,
to przy zwalnianiu nale�y koniecznie wywo�a� funkcj� release_DirectX tego obiektu, a nie klasy bazowej. Czyli innymi s�owy klasa
odpowiedzialna za zwalnianie musi odziedziczy� po tym obiekcie nawet, je�eli nie u�ywa jego zmiennych.
W przeciwnym razie zostanie wywo�any funkcja wirtualna dla klasy bazowej.*/
class DX11AuxiliaryObjects : public DX11APIObjects
{
protected:
	static ID3D11Buffer*				const_per_frame;	///<Bufor sta�ych zmieniaj�cych si� nie cz�ciej ni� co ramk�
	static ID3D11Buffer*				const_per_mesh;		///<Bufor sta�ych zmieniaj�cy si� dla ka�dej cz�ci mesha
	static ID3D11DepthStencilState*		depth_enabled;		///<Do w��czania z-bufora
	static ID3D11DepthStencilState*		depth_disabled;		///<Do wy��czania z-bufora

	void init_buffers( unsigned int size_per_frame, unsigned int size_per_mesh );
	void init_depth_states();

	void release_DirectX() override;
};


