-- 用来生成sqlpp11的头文件, user_ar.h

create table de_ar(
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
