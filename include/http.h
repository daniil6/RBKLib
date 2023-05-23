#pragma once
/** Create http header */

enum StatusCode : int {
    nullptr_status_code = 0,
    ok,
    not_found,
};

enum ContentType : int {
    nullptr_content_type = 0,
    text_html,        // HTML документ
    text_plain,       // Текстовый документ
    application_json, // JSON документ
    application_xml,  // XML документ
    image_jpeg,       // Изображение в формате JPEG
    image_png,        // Изображение в формате PNG
    video_mp4,        // Видео в формате MP4
    audio_mpeg,       // Аудио в формате MPEG
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

class CHTTP
{
private:
    StatusCode mStatusCode;
    ContentType mContentType;
    ContentTransferEncoding mContentTransferEncoding;
    unsigned long mContentLength;
    Charset mCharset;

    char* mBuffer;
    char* mpBuffer;

    void set(const unsigned long& value);
    void set(const char* value);

public:
    CHTTP();
    ~CHTTP();

    void setStatusCode(const StatusCode& id);
    void setContentType(const ContentType& id);
    void setContentTransferEncoding(const ContentTransferEncoding& id);
    void setContentLength(const unsigned long& contentLength);
    void setCharset(const Charset& id);

    unsigned long makeHeader(char* buffer);
};