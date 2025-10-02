

#ifndef __mlgm_objects_h__
#define __mlgm_objects_h__

#include "mlgm_types.h"
#include "mlgm_errors.h"

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_object mlgm_object;
typedef struct t_mlgm_class mlgm_class;

typedef struct t_mlgm_interface mlgm_interface;
typedef struct t_mlgm_interface_info mlgm_interface_info;

typedef struct t_mlgm_object_maker mlgm_object_maker;
typedef struct t_mlgm_object_holder mlgm_object_holder;
typedef struct t_mlgm_object_entity mlgm_object_entity;

typedef struct t_mlgm_object_manager mlgm_object_manager;
typedef struct t_mlgm_object_manager_inner mlgm_object_manager_inner;

// mlgm_object_entity_on_life_func 是对象实例的生命周期回调函数
typedef void (*mlgm_object_entity_on_life_func)(mlgm_object_entity *entity);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_object
{
} mlgm_object;

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_interface
{

    mlgm_interface_info *info;

    mlgm_object_entity *entity;

} mlgm_interface;

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_interface_info
{
} mlgm_interface_info;

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_object_maker
{

    mlgm_object_manager *manager;
    mlgm_class *class_info;
    mlgm_object_holder *owner;

    mlgm_size body_size; // 该对象 的身部 在内存占用的空间大小

} mlgm_object_maker;

void mlgm_object_maker_init(mlgm_object_maker *self);
mlgm_error mlgm_object_maker_make(mlgm_object_maker *self);

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_object_holder
{

    mlgm_object_manager *manager;
    mlgm_class *class_info;

    mlgm_object_entity *entity;

} mlgm_object_holder;

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_object_entity
{
    mlgm_object_manager *manager;
    mlgm_class *class_info;
    mlgm_object_holder *owner;

    void *mem; // 该对象在内存中的起始位置

    mlgm_size total_size; // 该对象在内存占用的空间 总 大小
    mlgm_size head_size;  // 该对象 的头部 在内存占用的空间大小
    mlgm_size body_size;  // 该对象 的身部 在内存占用的空间大小

    mlgm_byte body[0];

} mlgm_object_entity;

// 由 mlgm_object_manager 在初始化对象时调用
void mlgm_object_entity_init(mlgm_object_entity *self) {}

// 由 mlgm_object_manager 在释放对象时调用
void mlgm_object_entity_release(mlgm_object_entity *self) {}

// 检测并确认该对象是否存在
mlgm_bool mlgm_object_entity_exists(mlgm_object_entity *self) {

    return NO ; // todo ...
}

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_class
{

    mlgm_string name;

    mlgm_object_entity_on_life_func on_object_init;    // 当对象初始化时，执行回调
    mlgm_object_entity_on_life_func on_object_release; // 当对象被释放时，执行回调

} mlgm_class;

////////////////////////////////////////////////////////////////////////////////

typedef struct t_mlgm_object_manager
{

    mlgm_object_manager_inner *inner;

} mlgm_object_manager;

mlgm_object_manager *mlgm_object_manager_get_instance();

mlgm_error mlgm_object_manager_new_object(mlgm_object_manager *self, mlgm_object_maker *maker);

void mlgm_object_manager_gc(mlgm_object_manager *self);

////////////////////////////////////////////////////////////////////////////////

#endif //   __mlgm_objects_h__
