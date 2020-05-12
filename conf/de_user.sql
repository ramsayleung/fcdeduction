-- 用来生成sqlpp11的头文件, user.h
create table de_user(
    `tnt_inst_id` varchar(8) not null comment '租户Id',
    `user_id` varchar(32) not null comment '用户Id',
    `user_name` varchar(255) not null comment  '用户名',
    `user_type` varchar(32) not null comment '用户类型, 1: 个人, 2: 企业',
    `gmt_create` datetime not null comment '创建日期',
    `gmt_modified` datetime not null comment '修改日期',
    primary key(tnt_inst_id, user_id)
);
