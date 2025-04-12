#pragma once
/** Create http header */

enum ResponseCode : int {
    nullptr_status_code = 0,
    ok,
    not_found,
    http_version_not_supported,
    unauthorized,
    conflict,
    internal_server_error,
    bad_request,
};

enum ContentType : int {
    nullptr_content_type = 0,
    text_html,              // HTML документ
    text_plain,             // Текстовый документ
    text_css,               // Текстовый документ CSS
    application_json,       // JSON документ
    application_xml,        // XML документ
    application_javascript, // JS скрипт
    image_jpeg,             // Изображение в формате JPEG
    image_png,              // Изображение в формате PNG
    video_mp4,              // Видео в формате MP4
    audio_mpeg,             // Аудио в формате MPEG
};

enum ContentTransferEncoding : int {
    nullptr_content_transfer_encoding = 0,
    binary,
};

enum Charset : int {
    nullptr_charset = 0,
    utf_8,
    iso_8859_4,
};

enum AccessControlAllowOrigin : int {
    nullptr_access_control_allow_origin = 0,
    all_origin,
};

enum AccessControlAllowMethods : int {
    nullptr_access_control_allow_methods = 0,
    all_methods,
};

class CHTTP
{
private:
    ResponseCode mResponseCode;
    ContentType mContentType;
    ContentTransferEncoding mContentTransferEncoding;
    unsigned long mContentLength;
    Charset mCharset;
    const char* mAccessControlAllowOrigin;
    const char* mAccessControlAllowMethods;

    char* mBuffer;
    char* mpBuffer;

    void set(const unsigned long& value);
    void set(const char* value);

public:
    CHTTP();
    ~CHTTP();

    void setStatusCode(const ResponseCode& id);
    void setContentType(const ContentType& id);
    void setContentTransferEncoding(const ContentTransferEncoding& id);
    void setContentLength(const unsigned long& contentLength);
    void setCharset(const Charset& id);
    void setAccessControlAllowOrigin(const char* value);
    void setAccessControlAllowMethods(const char* value);

    unsigned long makeHeader(char* buffer);

    void clear();
};