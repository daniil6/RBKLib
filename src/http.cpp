#include "http.h"
#include <cstdio>

const char* gStatusCode[] = {
    nullptr,
    "200 Ok",
    "404 Not Found",
};

const char* gContentType[] = {
    nullptr,
    "text/html",
    "text/plain",
    "application/json",
    "application/xml",
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
    mBuffer = nullptr;
    mpBuffer = nullptr;

    mStatusCode = StatusCode::nullptr_status_code;
    mContentType = ContentType::nullptr_content_type;
    mContentTransferEncoding = ContentTransferEncoding::nullptr_content_transfer_encoding;
    mContentLength = 0;
    mCharset = Charset::nullptr_charset;
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

void CHTTP::setStatusCode(const StatusCode& id)
{
    mStatusCode = id;
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

unsigned long CHTTP::makeHeader(char* buffer)
{
    mpBuffer = mBuffer = buffer;

    if(mStatusCode != StatusCode::nullptr_status_code) {
        set("HTTP/1.1 ");
        set(gStatusCode[mStatusCode]);
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

    if(mContentLength != 0) {
        set("Content-Length: ");
        set(mContentLength);
        set("\r\n");
    }

    if(mCharset != Charset::nullptr_charset) {
        set("Charset=");
        set(gCharset[mCharset]);
        set("\r\n");
    }

    // set("Connection: close\r\n");

    set("\r\n");

    return mpBuffer - mBuffer;
}
