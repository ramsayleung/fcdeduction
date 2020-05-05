-- 用来生成sqlpp11的头文件
create table de_prod(
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
