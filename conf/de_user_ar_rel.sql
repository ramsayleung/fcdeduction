-- 用来生成sqlpp11的头文件
create table de_user_ar_rel(
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
    primary key(tnt_inst_id, rel_id)
)
