﻿// codec_list.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

#include <wrl.h>
//#include <windows.h>
//#include <mfidl.h>
#include <mfapi.h>
//#include <mfreadwrite.h>
//#include <mferror.h>
//#include <mfobjects.h>
//#include <strmif.h>

int main()
{
	HRESULT hr;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	CLSID *codec_clsid_list = NULL;   // Pointer to an array of CLISDs. 
	UINT32 codec_cls_id_cnt = NULL;   // Size of the array.
	hr = MFTEnum(
		MFT_CATEGORY_VIDEO_ENCODER,
		0,                 // Reserved
		NULL,              // Input type to match. (Encoded type.)
		NULL,              // Output type to match. (Don't care.)
		NULL,              // Attributes to match. (None.)
		&codec_clsid_list, // Receives a pointer to an array of CLSIDs.
		&codec_cls_id_cnt  // Receives the size of the array.
	);

	std::wcout << "Encoder: " << codec_cls_id_cnt << std::endl;

	for (int i = 0; i < codec_cls_id_cnt; i++) {
		LPWSTR name;

		hr = MFTGetInfo(
			codec_clsid_list[i],
			&name,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
		);

		std::wcout << name << std::endl;

		CoTaskMemFree(name);
	}

	hr = MFTEnum(
		MFT_CATEGORY_VIDEO_DECODER,
		0,                 // Reserved
		NULL,              // Input type to match. (Encoded type.)
		NULL,              // Output type to match. (Don't care.)
		NULL,              // Attributes to match. (None.)
		&codec_clsid_list, // Receives a pointer to an array of CLSIDs.
		&codec_cls_id_cnt  // Receives the size of the array.
	);

	std::wcout << "Decoder: " << codec_cls_id_cnt << std::endl;

	for (int i = 0; i < codec_cls_id_cnt; i++) {
		LPWSTR name;

		hr = MFTGetInfo(
			codec_clsid_list[i],
			&name,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
		);

		std::wcout << name << std::endl;

		CoTaskMemFree(name);
	}
}
