#include <mupdf/fitz.h>
#include "mupdf_tools.h"
#include "mupdf_adapter/ccpdfdocument.h"

/* Definitions of tools */

static constexpr const char* META_KEYS[] = {
    FZ_META_INFO_TITLE,
    FZ_META_INFO_AUTHOR,
    FZ_META_INFO_SUBJECT,
    FZ_META_INFO_KEYWORDS,
    FZ_META_INFO_CREATOR,
    FZ_META_INFO_PRODUCER,
    FZ_META_INFO_CREATIONDATE,
    FZ_META_INFO_MODIFICATIONDATE,
};

namespace ccpdf_tools
{

/* request metas fulls*/
/* request metas fulls */
CCPdfMetaInfo
request_meta(const CCPdfDocument* document)
{
    fz_context*     context = document->raw_context();
    fz_document*    doc = document->raw_handle();
    CCPdfMetaInfo   metas;

    if (!context || !doc) {
        return metas; // 返回空结构体
    }

    // 辅助函数：获取单个元数据字段
    auto get_metadata = [&](const char* key) -> QString {
        char* buffer = nullptr;
        int size = fz_lookup_metadata(context, doc, key, nullptr, 0);
        if (size > 0) {
            buffer = (char*)malloc(size);
            if (fz_lookup_metadata(context, doc, key, buffer, size) > 0) {
                QString result = QString::fromUtf8(buffer);
                qDebug() << key << " : " << result;
                free(buffer);
                return result;
            }
            free(buffer);
        }
        return QString(); // 返回空字符串表示未找到
    };

    // 获取所有元数据字段
    metas.author = get_metadata(FZ_META_INFO_AUTHOR);
    metas.title = get_metadata(FZ_META_INFO_TITLE);
    metas.subject = get_metadata(FZ_META_INFO_SUBJECT);
    metas.keywords = get_metadata(FZ_META_INFO_KEYWORDS);
    metas.creator = get_metadata(FZ_META_INFO_CREATOR);
    metas.producer = get_metadata(FZ_META_INFO_PRODUCER);
    metas.creation_datetime = get_metadata(FZ_META_INFO_CREATIONDATE);
    metas.modify_datetime = get_metadata(FZ_META_INFO_MODIFICATIONDATE);

    return metas;
}

/* request metas seperates */

QVariant
request_target_meta(const CCPdfDocument *document,
                    const CCPdfMetaInfo::Field field)
{
    fz_context*     context = document->raw_context();
    fz_document*    doc = document->raw_handle();
    char*           meta_buffer = nullptr;
    int             size = 0;
    QVariant        result;

    if (!context || !doc) {
        return QVariant();
    }

    /* query the meta with doc */
    const char* mupdf_key = nullptr;
    switch(field)
    {
    case CCPdfMetaInfo::Field::Author:
        mupdf_key = FZ_META_INFO_AUTHOR;
        break;
    case CCPdfMetaInfo::Field::Title:
        mupdf_key = FZ_META_INFO_TITLE;
        break;
    case CCPdfMetaInfo::Field::Subject:
        mupdf_key = FZ_META_INFO_SUBJECT;
        break;
    case CCPdfMetaInfo::Field::Keywords:
        mupdf_key = FZ_META_INFO_KEYWORDS;
        break;
    case CCPdfMetaInfo::Field::Creator:
        mupdf_key = FZ_META_INFO_CREATOR;
        break;
    case CCPdfMetaInfo::Field::Producer:
        mupdf_key = FZ_META_INFO_PRODUCER;
        break;
    case CCPdfMetaInfo::Field::CreationDateTime:
        mupdf_key = FZ_META_INFO_CREATIONDATE;
        break;
    case CCPdfMetaInfo::Field::ModifyDateTime:
        mupdf_key = FZ_META_INFO_MODIFICATIONDATE;
        break;
    default:
        return QVariant(); // 未知字段
    }

    /* we request the metas */
    size = fz_lookup_metadata(context, doc, mupdf_key, nullptr, 0);
    if (size > 0) {
        /* oh that means as other needed of metadata */
        /* we passed 0, thus we nees size cnt of buffer */
        meta_buffer = (char*)malloc(size);
        if (fz_lookup_metadata(context, doc, mupdf_key, meta_buffer, size)) {
            result = QString::fromUtf8(meta_buffer); // 转换为QString存储
        }
        free(meta_buffer);
    }

    return result;
}

QImage
request_target_page(CCPdfImageRequest* simpleRequest)
{
    fz_context*     document_context    = simpleRequest->request_document->raw_context();
    fz_document*    document_handle     = simpleRequest->request_document->raw_handle();
    fz_page*        request_page        = fz_load_page(document_context, document_handle, simpleRequest->request_page);
    fz_matrix zoom_matrix = fz_scale(simpleRequest->zoom, simpleRequest->zoom);
    fz_rect page_rect = fz_bound_page(document_context, request_page);
    fz_irect bbox = fz_round_rect(fz_transform_rect(page_rect, zoom_matrix));

    int new_width = bbox.x1 - bbox.x0;
    int new_height = bbox.y1 - bbox.y0;

    // 根据 zoom_factor 增加分辨率
    new_width *= simpleRequest->zoom;
    new_height *= simpleRequest->zoom;

    fz_pixmap *pix = fz_new_pixmap(
            document_context, fz_device_rgb(document_context),
            new_width, new_height, nullptr, 0);

    /* filled with white */
    fz_clear_pixmap_with_value(document_context, pix, 255);

    fz_device* dev = fz_new_draw_device(document_context,zoom_matrix, pix);
    fz_run_page(document_context, request_page, dev, zoom_matrix, nullptr);
    /* clean up the sessions */
    fz_close_device(document_context, dev);
    fz_drop_device(document_context, dev);
    fz_drop_page(document_context, request_page);

    QImage image(
        pix->samples, pix->w, pix->h,
        pix->stride, QImage::Format_RGB888);
    QImage result = image.copy();
    fz_drop_pixmap(document_context, pix);
    return result;
}

static QList<CCPdfChapterNode>
parse_outline(fz_context* ctx, fz_document* doc, fz_outline* fz_outline_node)
{
    QList<CCPdfChapterNode> parse_result;
    while(fz_outline_node)
    {
        CCPdfChapterNode current_node;
        current_node.chapter_title = QString::fromUtf8(fz_outline_node->title ? fz_outline_node->title : "");

        if (fz_outline_node->page.page >= 0) {
            current_node.chapter_page = fz_page_number_from_location(
                ctx, doc, fz_outline_node->page);
        } else if (fz_outline_node->uri) {
            fz_location target =
                fz_resolve_link(ctx, doc, fz_outline_node->uri, nullptr, nullptr);
            if (target.page >= 0) {
                current_node.chapter_page = fz_page_number_from_location(ctx, doc, target);
            }else{
                current_node.chapter_page = -1;
            }
        } else {
            current_node.chapter_page = -1;
        }

        if (fz_outline_node->down) {
            current_node.childs = parse_outline(ctx, doc, fz_outline_node->down);
        }

        parse_result.append(current_node);
        fz_outline_node = fz_outline_node->next;
    }

    return parse_result;
}


QList<CCPdfChapterNode>
request_chapter_tree(const CCPdfDocument* document)
{
    fz_context*     document_context    = document->raw_context();
    fz_document*    document_handle     = document->raw_handle();

    fz_outline* outline = fz_load_outline(document_context, document_handle);

    /* if there is an outline */
    QList<CCPdfChapterNode> result;
    if (outline) {
        result = parse_outline(document_context, document_handle, outline);
        fz_drop_outline(document_context, outline);
    }

    return result;
}

} // namespace ccpdf_tools
