#include "http.h"
#include <cstdio>

const char* gStatusCode[] = {
    nullptr,
    "200 Ok",
    "404 Not Found",
    "505 HTTP Version not Supported",
    "401 Unauthorized",
    "409 Conflict",
    "500 Internal Server Error",
    "400 Bad Request",
};

const char* gContentType[] = {
    nullptr,
    "text/html",
    "text/plain",
    "text/css",
    "application/json",
    "application/xml",
    "application/javascript",
    "image/jpeg",
    "image/png",
    "video/mp4",
    "audio/mpeg",
};

const char* gContentTransferEncoding[] = {
    nullptr,
    "binary",
};

const char* gCharset[] = {
    nullptr,
    "UTF-8",
    "ISO-8859-4",
};

CHTTP::CHTTP()
{
    clear();
}

CHTTP::~CHTTP() = default;

void CHTTP::set(const char* value)
{
    char ch;
    while((ch = *value++) != '\0')
        *mpBuffer++ = ch;
}

void CHTTP::set(const unsigned long& value)
{
    mpBuffer += sprintf(mpBuffer, "%lu", value);
}

void CHTTP::setStatusCode(const ResponseCode& id)
{
    mResponseCode = id;
}

void CHTTP::setContentType(const ContentType& id)
{
    mContentType = id;
}

void CHTTP::setContentTransferEncoding(const ContentTransferEncoding& id)
{
    mContentTransferEncoding = id;
}

void CHTTP::setContentLength(const unsigned long& contentLength)
{
    mContentLength = contentLength;
}

void CHTTP::setCharset(const Charset& id)
{
    mCharset = id;
}

void CHTTP::setAccessControlAllowOrigin(const char* value)
{
    mAccessControlAllowOrigin = value;
}

void CHTTP::setAccessControlAllowMethods(const char* value)
{
    mAccessControlAllowMethods = value;
}

unsigned long CHTTP::makeHeader(char* buffer)
{
    if(buffer == nullptr)
        return 0;

    mpBuffer = mBuffer = buffer;

    if(mResponseCode != ResponseCode::nullptr_status_code) {
        set("HTTP/1.1 ");
        set(gStatusCode[mResponseCode]);
        set("\r\n");
    }

    if(mContentType != ContentType::nullptr_content_type) {
        set("Content-Type: ");
        set(gContentType[mContentType]);
        set("\r\n");
    }

    if(mContentTransferEncoding != ContentTransferEncoding::nullptr_content_transfer_encoding) {
        set("Content-Transfer-Encoding: ");
        set(gContentTransferEncoding[mContentTransferEncoding]);
        set("\r\n");
    }

    set("Content-Length: ");
    set(mContentLength);
    set("\r\n");

    if(mCharset != Charset::nullptr_charset) {
        set("Charset=");
        set(gCharset[mCharset]);
        set("\r\n");
    }

    if(mAccessControlAllowOrigin != nullptr) {
        set("Access-Control-Allow-Origin: ");
        set(mAccessControlAllowOrigin);
        set("\r\n");
    }

    if(mAccessControlAllowMethods != nullptr) {
        set("Access-Control-Allow-Methods: ");
        set(mAccessControlAllowMethods);
        set("\r\n");
    }

    // set("Connection: close\r\n");

    set("\r\n");

    return mpBuffer - mBuffer;
}

void CHTTP::clear()
{
    mResponseCode = ResponseCode::nullptr_status_code;
    mContentType = ContentType::nullptr_content_type;
    mContentTransferEncoding = ContentTransferEncoding::nullptr_content_transfer_encoding;
    mContentLength = 0;
    mCharset = Charset::nullptr_charset;
    mAccessControlAllowOrigin = nullptr;
    mAccessControlAllowMethods = nullptr;

    mBuffer = nullptr;
    mpBuffer = nullptr;
}