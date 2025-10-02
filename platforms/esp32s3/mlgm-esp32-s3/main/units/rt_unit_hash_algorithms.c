
#include "units.h"

#include "../mlgm_logger.h"
#include "../mlgm_hex.h"

#include "../crypto/md5.h"
#include "../crypto/sha1.h"
#include "../crypto/sha256.h"

#include <memory.h>

// 测试各个 hash 算法的计算结果是否正确
mlgm_error rt_unit_test_hash_algorithms(mlgm_unit *u)
{

    // init

    char data[] = "hello,hash";
    mlgm_size len = sizeof(data) - 1;
    char str_buf[100];

    mlgm_md5_sum wantMD5sum = mlgm_md5_sum_from_hex_string("3780399c464db8c9c4700a06f0352aae");
    mlgm_sha1_sum wantSha1sum = mlgm_sha1_sum_from_hex_string("9eddfdd3b2688e1b4cf4bbe70a0d95c406679bf6");
    mlgm_sha256_sum wantSha256sum = mlgm_sha256_sum_from_hex_string("7c33e6cd386705d95beaa40fe640ab6f4f7afebc342260b22173da1109a756a8");

    // compute

    mlgm_md5_sum haveMD5sum = mlgm_md5_compute(data, len);
    mlgm_sha1_sum haveSha1sum = mlgm_sha1_compute(data, len);
    mlgm_sha256_sum haveSha256sum = mlgm_sha256_compute(data, len);

    // log

    mlgm_hex_to_string(data, len, str_buf, sizeof(str_buf));
    mlgm_logger_info(NIL, "raw_data.str   = [%s]", data);
    mlgm_logger_info(NIL, "raw_data.hex   = [%s]", str_buf);
    mlgm_logger_info(NIL, "raw_data.size  = %d", len);

    mlgm_hex_to_string(haveMD5sum.body, sizeof(haveMD5sum.body), str_buf, sizeof(str_buf));
    mlgm_logger_info(NIL, "   md5sum: %s", str_buf);

    mlgm_hex_to_string(haveSha1sum.body, sizeof(haveSha1sum.body), str_buf, sizeof(str_buf));
    mlgm_logger_info(NIL, "  sha1sum: %s", str_buf);

    mlgm_hex_to_string(haveSha256sum.body, sizeof(haveSha256sum.body), str_buf, sizeof(str_buf));
    mlgm_logger_info(NIL, "sha256sum: %s", str_buf);

    // check

    if (!mlgm_sha1_sum_equals(&haveSha1sum, &wantSha1sum))
    {
        return mlgm_error_make_with_format(500, "bad sha1 checksum");
    }

    if (!mlgm_sha256_sum_equals(&haveSha256sum, &wantSha256sum))
    {
        return mlgm_error_make_with_format(500, "bad sha256 checksum");
    }

    if (!mlgm_md5_sum_equals(&haveMD5sum, &wantMD5sum))
    {
        return mlgm_error_make_with_format(500, "bad md5 checksum");
    }

    return NIL;
}

// c:test-not
// 测试各个 sum 结构中， head & body 是否对齐
mlgm_error rt_unit_test_sum_struct_bytes_align(mlgm_unit *u)
{

    mlgm_md5_sum theMD5sum = mlgm_md5_sum_from_hex_string("3780399c464db8c9c4700a06f0352aae");
    mlgm_sha1_sum theSha1sum = mlgm_sha1_sum_from_hex_string("9eddfdd3b2688e1b4cf4bbe70a0d95c406679bf6");
    mlgm_sha256_sum theSha256sum = mlgm_sha256_sum_from_hex_string("7c33e6cd386705d95beaa40fe640ab6f4f7afebc342260b22173da1109a756a8");

    typedef struct t_my_sum_info
    {
        mlgm_sum_head *head;
        mlgm_byte *in_head;
        mlgm_byte *in_body;

    } my_sum_info;

    int i, count;
    i = count = 0;
    const int length = 5;
    my_sum_info items[length];
    my_sum_info *item;

    // md5
    i = count;
    item = items + i;
    item->head = &theMD5sum.head;
    item->in_head = theMD5sum.head.sum;
    item->in_body = theMD5sum.body;
    count++;

    // sha1
    i = count;
    item = items + i;
    item->head = &theSha1sum.head;
    item->in_head = theSha1sum.head.sum;
    item->in_body = theSha1sum.body;
    count++;

    // sha256
    i = count;
    item = items + i;
    item->head = &theSha256sum.head;
    item->in_head = theSha256sum.head.sum;
    item->in_body = theSha256sum.body;
    count++;

    // for
    char str_buf[256];

    for (i = 0; i < count; ++i)
    {
        item = items + i;
        mlgm_size len = item->head->size;
        mlgm_byte *p1 = item->in_head;
        mlgm_byte *p2 = item->in_body;

        mlgm_hex_to_string(p2, len, str_buf, sizeof(str_buf));
        mlgm_logger_info(NIL, "sum[%d].hex = %s", i, str_buf);

        if (memcmp(p1, p2, len) != 0)
        {
            const mlgm_string fmt = "rt_unit_test_sum_struct_bytes_align: head & body of sum is NOT align. size(bytes)=%d";
            return mlgm_error_make_with_format(500, fmt, len);
        }
    }

    return NIL;
}
