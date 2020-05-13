create database if not exists fcdeduction CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci ;
create table if not exists fcdeduction.de_user(
    `tnt_inst_id` varchar(8) not null comment '租户Id',
    `user_id` varchar(32) not null comment '用户Id',
    `user_name` varchar(255) not null comment  '用户名',
    `user_type` varchar(32) not null comment '用户类型, 1: 个人, 2: 企业',
    `gmt_create` datetime not null comment '创建日期',
    `gmt_modified` datetime not null comment '修改日期',
    primary key(tnt_inst_id, user_id)
);
create table if not exists fcdeduction.de_ar(
  `tnt_inst_id` varchar(8) not null comment '租户Id',
  `ar_number` varchar(32) not null comment '合约号',
  `ar_name` varchar(255) not null comment '合约名',
  `ar_version` varchar(32) not null comment '合约版本',
  `properties` varchar(2048) not null comment '合约属性',
  `memo` varchar(255) comment '备注',
  `gmt_create` datetime not null comment '创建时间',
  `gmt_modified` datetime not null comment '修改时间',
  primary key(tnt_inst_id, ar_number)
);

create table if not exists fcdeduction.de_prod(
    `tnt_inst_id` varchar(8) not null comment '租户Id',
    `pd_code` varchar(32) not null comment '产品码',
    `pd_name` varchar(255) not null comment '产品名',
    `pd_desc` varchar(2048) not null comment '产品描述',
    `pd_org_name` varchar(2048) not null comment '产品所属主体',
    `memo` varchar(255) comment '备注',
    `gmt_create` datetime not null comment '创建时间',
    `gmt_modified` datetime not null comment '修改时间',
    primary key(tnt_inst_id, pd_code)
);

create table if not exists fcdeduction.de_user_ar_rel(
    `tnt_inst_id` varchar(8) not null comment '租户Id',
    `rel_id` varchar(32) not null comment '关系主键',
    `user_id` varchar(32) not null comment '用户Id',
    `rel_status`  varchar(8) not null comment '关系状态, 如生效:1, 暂停:2, 冻结:3等等',
    `pd_code` varchar(32) not null comment '产品码',
    `pd_name` varchar(255) not null comment '产品名',
    `pd_org_name` varchar(255) not null comment '产品所属主体',
    `ar_name` varchar(255) not null comment '合约名',
    `ar_no` varchar(32) not null comment '合约号',
    `property_values` varchar(2048) comment '对应合约属性及其值',
    `memo` varchar(255) comment '备注',
    `gmt_create` datetime not null comment '创建时间',
    `gmt_modified` datetime not null comment '修改时间',
    primary key(tnt_inst_id, rel_id),
    constraint idx_user_ar_pd unique(tnt_inst_id, user_id, ar_no, pd_code)
);

# ALTER TABLE de_user_ar_rel ADD pd_org_name VARCHAR( 255 ) not null comment '产品所属主体' after pd_name;

create table if not exists fcdeduction.de_ident(
    `tnt_inst_id` varchar(8) not null comment '租户Id',
    `ident_id` varchar(32) not null comment '识别Id, 主键',
    `user_id` varchar(32) not null comment '用户Id',
    `ident_type` varchar(8) not null comment '识别类型, 1: 账密, 2: 人脸, 3: 安保问题',
    `ident_key` varchar(255) not null comment '识别key, 如邮箱, 手机号, 具体的安保问题',
    `ident_value` varchar(255) not null comment '识别value, 如密码, 安全问题答案',
    `gmt_create` datetime not null comment '创建时间',
    `gmt_modified` datetime not null comment '修改时间',
    primary key(tnt_inst_id, ident_id),
    constraint idx_user_id_type unique (tnt_inst_id, user_id, ident_type),
    constraint idx_key_type unique (tnt_inst_id, ident_key, ident_type)
);
