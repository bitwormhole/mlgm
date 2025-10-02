
#include "mlgm_strings.h"

#include "mlgm_logger.h"

#include <memory.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
// mlgm_string_builder_pool_entity

typedef struct t_mlgm_string_builder_pool_entity
{

    int leak_count;
    int leak_count_max;

} mlgm_string_builder_pool_entity;

mlgm_string_builder_pool_entity *mlgm_string_builder_pool_entity_init(mlgm_string_builder_pool_entity *self);
mlgm_string_builder_pool_entity *mlgm_string_builder_pool_entity_destroy(mlgm_string_builder_pool_entity *self);

//////////////////////

mlgm_string_builder_pool_entity *mlgm_string_builder_pool_entity_init(mlgm_string_builder_pool_entity *self)
{

    if (self)
    {
        memset(self, 0, sizeof(self[0]));

        self->leak_count = 0;
        self->leak_count_max = 64;
    }

    return self;
}

mlgm_string_builder_pool_entity *mlgm_string_builder_pool_entity_destroy(mlgm_string_builder_pool_entity *self)
{

    if (self)
    {
        memset(self, 0, sizeof(self[0]));
    }

    return self;
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_string_builder_pool

void mlgm_string_builder_pool_init(mlgm_string_builder_pool *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
    }
    else
    {
        return;
    }

    const size_t entity_size = sizeof(mlgm_string_builder_pool_entity);
    mlgm_string_builder_pool_entity *entity = malloc(entity_size);
    entity = mlgm_string_builder_pool_entity_init(entity);

    if (entity)
    {
    }

    self->entity = entity;
}

void mlgm_string_builder_pool_destroy(mlgm_string_builder_pool *self)
{
    if (self == NIL)
    {
        return;
    }

    mlgm_string_builder_pool_entity *entity = self->entity;
    entity = mlgm_string_builder_pool_entity_destroy(entity);

    if (entity)
    {
        free(entity);
    }

    self->entity = NIL;
}

mlgm_string_builder *mlgm_string_builder_pool_open_builder(mlgm_string_builder_pool *self, mlgm_size want_size)
{

    // 注意： 目前暂时简单的创建|删除 string_builder, 不实现 pool 的特性

    mlgm_logger_debug(NIL, "mlgm_string_builder_pool_open_builder: string_builder.size = %d", want_size);

    mlgm_string_builder_pool_entity *entity = self->entity;
    if (entity)
    {
        // 在这里检测内存泄漏
        if (entity->leak_count < entity->leak_count_max)
        {
            entity->leak_count++;
        }
        else
        {
            mlgm_logger_warn(NIL, "mlgm_string_builder_pool_open_builder: memory leak");
        }
    }

    const size_t size = sizeof(mlgm_string_builder);
    mlgm_string_builder *builder = malloc(size);
    return mlgm_string_builder_init_with_size(builder, want_size);

    // return builder;
}

void mlgm_string_builder_pool_close_builder(mlgm_string_builder_pool *self, mlgm_string_builder *builder)
{
    if (self && builder)
    {

        mlgm_size size = builder->buffer.capacity;
        mlgm_logger_debug(NIL, "mlgm_string_builder_pool_close_builder: string_builder.size = %d", size);

        mlgm_string_builder_release(builder);
        free(builder);

        self->entity->leak_count--;
    }
}

////////////////////////////////////////////////////////////////////////////////

static mlgm_string_builder_pool *the_singleton_mlgm_string_builder_pool = NIL;

mlgm_string_builder_pool *mlgm_string_builder_pool_get_default_pool()
{
    mlgm_string_builder_pool *pool = the_singleton_mlgm_string_builder_pool;
    if (pool)
    {
        return pool;
    }

    const size_t size = sizeof(mlgm_string_builder_pool);
    pool = malloc(size);

    if (pool)
    {
        mlgm_logger_warn(NIL, "mlgm_string_builder_pool_get_default_pool: create a new pool (singleton)");
        mlgm_string_builder_pool_init(pool);
        the_singleton_mlgm_string_builder_pool = pool;
    }
    return pool;
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_string_builder_holder

void mlgm_string_builder_holder_init(mlgm_string_builder_holder *self, mlgm_size size)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
        mlgm_string_builder_pool *pool = mlgm_string_builder_pool_get_default_pool();
        if (size < 0)
        {
            size = pool->min_buffer_size;
        }
        self->builder = mlgm_string_builder_pool_open_builder(pool, size);
        self->pool = pool;
    }
}

void mlgm_string_builder_holder_release(mlgm_string_builder_holder *self)
{
    if (self)
    {
        mlgm_string_builder_pool *pool = self->pool;
        mlgm_string_builder *builder = self->builder;
        mlgm_string_builder_pool_close_builder(pool, builder);
    }
}

void mlgm_string_builder_holder_auto_release_callback(mlgm_deferable *def)
{
    if (def)
    {
        mlgm_deferable_func fn = def->fn;
        mlgm_string_builder_holder *tar = def->target;
        if (fn && tar)
        {
            mlgm_string_builder_holder_release(tar);
        }
    }
}

void mlgm_string_builder_holder_auto_release(mlgm_string_builder_holder *self, mlgm_defer_manager *dm)
{
    if (self && dm)
    {
        mlgm_deferable *def = &self->auto_release;
        def->fn = mlgm_string_builder_holder_auto_release_callback;
        def->target = self;
        mlgm_defer_manager_add(dm, def);
    }
}

////////////////////////////////////////////////////////////////////////////////
// struct:mlgm_string_builder

mlgm_string_builder *mlgm_string_builder_init(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *bb = &self->buffer;
        mlgm_bytes_buffer_init(bb);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_init_with_size(mlgm_string_builder *self, mlgm_size size)
{
    if (self)
    {
        mlgm_bytes_buffer *bb = &self->buffer;
        mlgm_bytes_buffer_init_with_size(bb, size);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_init_with_buffer(mlgm_string_builder *self, void *buf, mlgm_size buf_cap)
{
    if (self)
    {
        mlgm_bytes_buffer *bb = &self->buffer;
        mlgm_bytes_buffer_init_with_buffer(bb, buf, buf_cap);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_reset(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buffer = &self->buffer;
        mlgm_bytes_buffer_reset(buffer);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_append_string(mlgm_string_builder *self, mlgm_string str)
{
    if (self)
    {
        mlgm_bytes_buffer *pbuf = &self->buffer;
        mlgm_bytes_buffer_write_string(pbuf, str);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_append_string_slice(mlgm_string_builder *self, mlgm_string_slice *slice)
{
    if (self && slice)
    {
        mlgm_string raw = slice->raw;
        mlgm_size off = slice->offset;
        mlgm_size len = slice->length;

        mlgm_string src_data = raw + off;

        mlgm_bytes_buffer *pbuf = &self->buffer;
        mlgm_bytes_buffer_write(pbuf, (void *)src_data, len);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_append_uint(mlgm_string_builder *self, mlgm_uint n)
{
    if (self)
    {
        // const mlgm_uint max = mlgm_uint_max; // 4294967295UL
        const int tmp_cap = 15;
        char tmp[tmp_cap];
        int cb = snprintf(tmp, tmp_cap, "%u", n);
        if ((0 < cb) && (cb < tmp_cap))
        {
            mlgm_bytes_buffer *pbuf = &self->buffer;
            mlgm_bytes_buffer_write(pbuf, (mlgm_byte *)tmp, cb);
        }
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_append_int(mlgm_string_builder *self, mlgm_int n)
{
    if (self)
    {
        // const mlgm_int max = mlgm_int_max; // 2147483647L
        const int tmp_cap = 15;
        char tmp[tmp_cap];
        int cb = snprintf(tmp, tmp_cap, "%d", n);
        if ((0 < cb) && (cb < tmp_cap))
        {
            mlgm_bytes_buffer *pbuf = &self->buffer;
            mlgm_bytes_buffer_write(pbuf, (mlgm_byte *)tmp, cb);
        }
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_append_bool(mlgm_string_builder *self, mlgm_bool b)
{
    if (self)
    {
        mlgm_string str = (b == 0) ? "no" : "yes";
        mlgm_bytes_buffer *pbuf = &self->buffer;
        mlgm_bytes_buffer_write_string(pbuf, str);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_append_char(mlgm_string_builder *self, mlgm_char n)
{
    if (self)
    {
        mlgm_bytes_buffer *pbuf = &self->buffer;
        mlgm_bytes_buffer_write_byte(pbuf, n);
    }
    return self;
}

mlgm_string_builder *mlgm_string_builder_append_byte(mlgm_string_builder *self, mlgm_byte n)
{
    if (self)
    {
        mlgm_bytes_buffer *pbuf = &self->buffer;
        mlgm_bytes_buffer_write_byte(pbuf, n);
    }
    return self;
}

mlgm_string mlgm_string_builder_build(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buf = &self->buffer;
        mlgm_byte *data = buf->data;
        mlgm_size len = buf->length;
        mlgm_size cap = buf->capacity;
        if ((data) && (0 <= len) && (len < cap))
        {
            data[len] = 0;
        }
        else
        {
            mlgm_size iend = cap - 1;
            if ((data) && (iend >= 0))
            {
                data[iend] = 0;
            }
            buf->overflow = YES;
        }
        return (mlgm_string)data;
    }
    return NIL;
}

mlgm_string mlgm_string_builder_string(mlgm_string_builder *self)
{
    return mlgm_string_builder_build(self);
}

mlgm_size mlgm_string_builder_length(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buffer = &self->buffer;
        return buffer->length;
    }
    return 0;
}

mlgm_error mlgm_string_builder_error(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buffer = &self->buffer;
        return mlgm_bytes_buffer_error(buffer);
    }
    return NIL;
}

void mlgm_string_builder_release(mlgm_string_builder *self)
{
    if (self)
    {
        mlgm_bytes_buffer *buffer = &self->buffer;
        mlgm_bytes_buffer_release(buffer);
    }
}

////////////////////////////////////////////////////////////////////////////////
// mlgm_string_slice

mlgm_string_slice *mlgm_string_slice_init(mlgm_string_slice *self)
{
    if (self)
    {
        memset(self, 0, sizeof(self[0]));
    }
    return self;
}

mlgm_string_slice *mlgm_string_slice_init_with_string(mlgm_string_slice *self, mlgm_string str)
{
    self = mlgm_string_slice_init(self);
    if (self && str)
    {
        self->length = strlen(str);
        self->offset = 0;
        self->raw = str;
    }
    return self;
}

mlgm_string_slice *mlgm_string_slice_init_with_buffer(mlgm_string_slice *self, mlgm_string_builder *buf)
{
    self = mlgm_string_slice_init(self);
    if (self && buf)
    {
        mlgm_string str = mlgm_string_builder_build(buf);
        self->offset = 0;
        self->length = buf->buffer.length;
        self->raw = str;
        self->writer = buf;
    }
    return self;
}

mlgm_error mlgm_string_slice_write_to(mlgm_string_slice *self, mlgm_string_slice *dst)
{
    if (self == NIL || dst == NIL)
    {
        return mlgm_error_make(500, "mlgm_string_slice_write_to: param(s) is nil");
    }

    if (!mlgm_string_slice_is_rewritable(dst))
    {
        return mlgm_error_make(500, "mlgm_string_slice_write_to: slice(dst) is read-only");
    }

    mlgm_string_builder *w = dst->writer;
    mlgm_string_builder_append_string_slice(w, self);
    return NIL;
}

mlgm_bool mlgm_string_slice_trim_space____char_is_space(mlgm_char ch)
{
    return ((ch == ' ') || (ch == '\t') || (ch == '\r') || (ch == '\n'));
}

mlgm_string_slice mlgm_string_slice_trim_space(mlgm_string_slice *self)
{
    mlgm_string_slice res;
    memset(&res, 0, sizeof(res));

    if (self == NIL)
    {
        return res;
    }

    mlgm_string raw = self->raw;
    mlgm_size off = self->offset;
    mlgm_size len = self->length;

    if ((raw == NIL) || (off < 0) || (len < 0))
    {
        return res;
    }

    mlgm_string p1 = raw + off;
    mlgm_string p2 = raw + off + len;
    mlgm_char ch;

    for (; p1 < p2; p1++)
    {
        ch = p1[0];
        if (!mlgm_string_slice_trim_space____char_is_space(ch))
        {
            break;
        }
    }

    for (; p1 < p2; p2--)
    {
        ch = p2[-1];
        if (!mlgm_string_slice_trim_space____char_is_space(ch))
        {
            break;
        }
    }

    res.raw = raw;
    res.offset = (p1 - raw);
    res.length = (p2 - p1);

    return res;
}

mlgm_bool mlgm_string_slice_has_prefix(mlgm_string_slice *self, mlgm_string prefix)
{
    if (self == NIL || prefix == NIL)
    {
        return NO;
    }

    mlgm_size prefix_len = strlen(prefix);
    mlgm_string raw = self->raw;
    mlgm_size off = self->offset;
    mlgm_size len = self->length;
    mlgm_size i, count_ok;

    if (raw == NIL || off < 0 || len < 0)
    {
        return NO;
    }

    count_ok = 0;

    if (prefix_len <= len)
    {
        mlgm_string str = raw + off;
        for (i = 0; i < prefix_len; i++)
        {
            if (str[i] == prefix[i])
            {
                count_ok++;
            }
            else
            {
                break;
            }
        }
    }

    if (count_ok == prefix_len)
    {
        return YES;
    }

    return NO;
}

mlgm_bool mlgm_string_slice_has_suffix(mlgm_string_slice *self, mlgm_string suffix)
{
    if (self == NIL || suffix == NIL)
    {
        return NO;
    }

    mlgm_size suffix_len = strlen(suffix);
    mlgm_string raw = self->raw;
    mlgm_size off = self->offset;
    mlgm_size len = self->length;
    mlgm_size i, count_ok;

    if (raw == NIL || off < 0 || len < 0)
    {
        return NO;
    }

    count_ok = 0;

    if (suffix_len <= len)
    {
        mlgm_string str = raw + off + (len - suffix_len);
        for (i = 0; i < suffix_len; i++)
        {
            if (str[i] == suffix[i])
            {
                count_ok++;
            }
            else
            {
                break;
            }
        }
    }

    if (count_ok == suffix_len)
    {
        return YES;
    }

    return NO;
}

mlgm_bool mlgm_string_slice_is_rewritable(mlgm_string_slice *self)
{
    if (self)
    {
        if (self->writer)
        {
            return YES;
        }
    }
    return NO;
}

mlgm_string_slice mlgm_string_slice_sub_string(mlgm_string_slice *self, int start_at, int end_at)
{
    mlgm_string_slice res;
    mlgm_string_slice_init(&res);

    if (self == NIL)
    {
        return res;
    }

    const mlgm_string raw = self->raw;
    const int off = self->offset;
    const int len = self->length;

    if (raw == NIL)
    {
        return res;
    }

    int i0 = off;
    int i1 = off + start_at;
    int i2 = off + end_at;
    int i3 = off + len;

    if ((0 <= i0) && (i0 <= i1) && (i1 <= i2) && (i2 <= i3))
    {
        res.raw = self->raw;
        res.offset = i1;
        res.length = i2 - i1;
    }

    return res;
}

int mlgm_string_slice_index_of_char(mlgm_string_slice *self, mlgm_char ch)
{
    if (self)
    {
        mlgm_size len = self->length;
        mlgm_size off = self->offset;
        const char *raw = self->raw;
        if ((raw) && (off >= 0) && (len >= 0))
        {
            const void *p1 = raw + off;
            const void *p2 = memchr(p1, ch, len);
            if (p2)
            {
                return (p2 - p1);
            }
        }
    }
    return -1;
}

int mlgm_string_slice_index_of_string(mlgm_string_slice *self, mlgm_string str)
{

    return -1;
}

int mlgm_string_slice_last_index_of_char(mlgm_string_slice *self, mlgm_char ch)
{
    if (self)
    {
        mlgm_size len = self->length;
        mlgm_size off = self->offset;
        const char *raw = self->raw;
        if ((raw) && (off >= 0) && (len >= 0))
        {
            const void *p1 = (raw + off);
            const void *p2 = memrchr(p1, ch, len);
            if (p2)
            {
                return (p2 - p1);
            }
        }
    }
    return -1;
}

int mlgm_string_slice_last_index_of_string(mlgm_string_slice *self, mlgm_string str)
{

    // memmem( ,,,, ) ;

    return -1;
}

////////////////////////////////////////////////////////////////////////////////
// EOF
