#include "CallbackClient.hpp"

// See <http://www.cplusplus.com/forum/unices/45878/#msg249287>

namespace curl
{

CallbackClient::CallbackClient() : curl(curl_easy_init())
{
	if (!curl)
	{
		throw CURLE_FAILED_INIT;
	}
}

CallbackClient::~CallbackClient()
{
	curl_easy_cleanup(curl); // Clean up resources for cURL library
}

CURLcode CallbackClient::read(const char* url, WriteFunction* pCallback, void* pUserdata,
		long timeout)
{
	CURLcode result(CURLE_FAILED_INIT);

	if (CURLE_OK
			== (result = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
			&& CURLE_OK
					== (result = curl_easy_setopt(curl,
							CURLOPT_FOLLOWLOCATION, 1L))
			&& CURLE_OK
					== (result = curl_easy_setopt(curl,
							CURLOPT_WRITEFUNCTION, pCallback))
			&& CURLE_OK
					== (result = curl_easy_setopt(curl, CURLOPT_WRITEDATA,
							pUserdata)) && CURLE_OK == (result =
					curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
			&& CURLE_OK
					== (result = curl_easy_setopt(curl, CURLOPT_URL, url)))
	{
		result = curl_easy_perform(curl);
	}

	return result;
}

//CURLcode CallbackClient::read(const char* url, FILE* pOutput, long timeout)
//{
//	CURLcode result(CURLE_FAILED_INIT);
//
//	if (CURLE_OK
//			== (result = curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L))
//			&& CURLE_OK
//					== (result = curl_easy_setopt(curl,
//							CURLOPT_FOLLOWLOCATION, 1L))
//			&& CURLE_OK
//					== (result = curl_easy_setopt(curl, CURLOPT_WRITEDATA,
//							pOutput)) && CURLE_OK == (result =
//					curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout))
//			&& CURLE_OK
//					== (result = curl_easy_setopt(curl, CURLOPT_URL, url)))
//	{
//		result = curl_easy_perform(curl);
//	}
//
//	return result;
//}

}