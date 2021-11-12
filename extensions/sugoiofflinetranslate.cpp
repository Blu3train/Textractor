﻿#include "qtcommon.h"
#include "translatewrapper.h"
#include "network.h"

extern const wchar_t* TRANSLATION_ERROR;
extern const char* SUGOI_HOST;
extern QFormLayout* display;
extern Settings settings;

const char* TRANSLATION_PROVIDER = "Sugoi Offline Translate";
const char* GET_API_KEY_FROM = nullptr;
extern const QStringList languagesTo
{
   "English"
},
languagesFrom
{
	"Japanese"
};

bool translateSelectedOnly = false, useRateLimiter = true, rateLimitSelected = false, useCache = true, useFilter = true;
int tokenCount = 30, rateLimitTimespan = 60000, maxSentenceSize = 1000;
QString sugoiHost;

BOOL WINAPI DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		sugoiHost = settings.value(SUGOI_HOST).toString();
		if (sugoiHost.isEmpty()) sugoiHost = "localhost";
		auto sugoiHostEdit = new QLineEdit(sugoiHost);
		QObject::connect(sugoiHostEdit, &QLineEdit::textChanged, [sugoiHostEdit](QString host) { settings.setValue(SUGOI_HOST, sugoiHost =  host); });
		display->addRow(SUGOI_HOST, sugoiHostEdit);
	}
	break;
	}
	return TRUE;
}

std::pair<bool, std::wstring> Translate(const std::wstring& text, TranslationParam tlp)
{
	if (HttpRequest httpRequest{
		L"Mozilla/5.0 Textractor",
		sugoiHost.toStdWString().c_str(),
		L"POST",
		NULL,
		FormatString(R"({"content":"%s","message":"translate sentences"})", JSON::Escape(WideStringToString(text))),
		L"Content-type: application/json",
		14366,
		NULL,
		0
		})
		if (auto translation = Copy(JSON::Parse(httpRequest.response).String())) return { true, translation.value() };
		else return { false, FormatString(L"%s: %s", TRANSLATION_ERROR, httpRequest.response) };
		//else return { false, FormatString(L"%s", httpRequest.response) };
	else return { false, FormatString(L"%s (code=%u)", TRANSLATION_ERROR, httpRequest.errorCode) };
}