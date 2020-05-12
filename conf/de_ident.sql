-- 用来生成sqlpp11的头文件
create table de_ident(
    `tnt_inst_id` varchar(8) not null comment '租户Id',
    `ident_id` varchar(32) not null comment '识别Id, 主键',
    `user_id` varchar(32) not null comment '用户Id',
    `ident_type` varchar(8) not null comment '识别类型, 1: 账密, 2: 人脸, 3: 安保问题',
    `ident_key` varchar(255) not null comment '识别key, 如邮箱, 手机号, 具体的安保问题',
    `ident_value` varchar(255) not null comment '识别value, 如密码, 安全问题答案',
    `gmt_create` datetime not null comment '创建时间',
    `gmt_modified` datetime not null comment '修改时间',
    primary key(tnt_inst_id, ident_id),
    constraint idx_user_id_type unique (tnt_inst_id, user_id, ident_type)
);
